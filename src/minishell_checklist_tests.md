# Minishell — Tableau complet de cas de test (anti-leak / anti-crash)

> Référence de comportement = **bash**. Sauf mention contraire, tout doit matcher bash en sortie stdout, stderr et code de sortie (`$?`).
> Convention colonnes : **Attendu** = ce que bash fait / ce que tu dois faire ; **Piège** = la cause typique de leak ou de crash sur ce cas précis.
> Outils de validation : `valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes`, comparaison directe avec `bash --posix`.

---

## 0. Règles transverses (à vérifier sur CHAQUE cas)

| Point | Attendu | Piège |
|---|---|---|
| Chaque `readline()` | la string retournée doit être `free` à chaque tour de boucle | leak d'1 ligne par commande tapée — invisible sauf valgrind |
| Fuites readline internes | tolérées (sujet) **mais pas les tiennes** | ne pas confondre : valgrind avec `--suppressions` readline pour isoler ton code |
| FD ouverts | tout `open`/`pipe`/`dup` fermé sur succès **et** sur erreur | `--track-fds=yes` ; un fd qui fuit finit par faire échouer `open` après N commandes |
| Échec malloc | pas de crash, free de ce qui est déjà alloué, message d'erreur | double free / use-after-free si le cleanup est partiel |
| Structure parsée | free intégral même en cas d'erreur de syntaxe | leak garanti sur toute commande invalide si tu `continue` sans nettoyer |
| `exit` dans un enfant (pipe/fork) | free TOUTE ta mémoire avant `exit()` dans le child | valgrind voit les leaks dans les process enfants (LeaYeh/zstenger les checkent) |
| Variable globale signal | **uniquement** `int`/`sig_atomic_t` = numéro du signal | norme : interdit de mettre une struct en global ; 0 à l'éval si tu y accèdes pour autre chose |

---

## 1. Entrées vides / dégénérées (crash les plus fréquents au démarrage)

| Entrée | Attendu | Piège |
|---|---|---|
| `` (Entrée seul) | reprompt, `$?` inchangé | ne pas tokenizer une ligne vide → NULL deref dans l'executor |
| `   ` (espaces seuls) | reprompt, `$?` inchangé | trim qui renvoie `""` → cmd vide à exécuter |
| `\t\t` (tabs seuls) | reprompt | idem, tabs comme séparateurs |
| `Ctrl-D` sur ligne vide | sort proprement (`exit`), free tout | ne pas free l'env dupliqué / l'historique |
| `Ctrl-D` sur ligne non vide | bash : ignore le caractère / sort selon contexte | mauvais retour readline (NULL) mal géré → crash |
| Ligne de 10 000 caractères | exécution ou erreur propre | buffer fixe → overflow ; toujours allouer dynamiquement |
| `""` | commande vide, exit 0, rien affiché | `command not found ` (chaîne vide) au lieu de ne rien faire |
| `''` | idem `""` | idem |

---

## 2. Quotes (parsing — partie binôme, mais à tester ensemble)

| Entrée | Attendu | Piège |
|---|---|---|
| `echo "bonjour"` | `bonjour` | quotes non retirées en sortie |
| `echo 'bonjour'` | `bonjour` | |
| `echo a"b"c` | `abc` (concaténation) | espace inséré entre tokens collés |
| `echo a'b'c` | `abc` | |
| `echo "a'b'c"` | `a'b'c` (simples gardées dans doubles) | |
| `echo 'a"b"c'` | `a"b"c` (doubles gardées dans simples) | |
| `echo ""` | ligne vide | |
| `echo ''''''''''$USER''''''''''` | valeur de `$USER` | parsing de quotes alternées qui plante |
| `echo """"""""$USER""""""""` | valeur de `$USER` | |
| `echo '$USER'` | littéral `$USER` (pas d'expansion en simple quote) | expansion à tort |
| `echo "$USER"` | valeur de `$USER` (expansion en double quote) | non-expansion à tort |
| `"ec"ho hi` | exécute `echo` (quote removal sur le **nom** de commande) | **command not found** si tu cherches `"ec"ho` au lieu de `echo` dans PATH |
| `ec"ho" hi` / `e""cho hi` / `''echo hi` | exécute `echo` | idem : quote removal AVANT la résolution du binaire |
| `echo "$"USER` | `$USER` littéral (`$` collé à une quote fermante = pas d'expansion) | expansion à tort |
| `echo "$"` | `$` | |
| `'` (simple quote non fermée) | sujet : ne pas interpréter → **erreur de syntaxe** propre, pas de crash | bash attendrait la fermeture ; toi → message d'erreur + `$?`=2, surtout pas segfault |
| `"` (double quote non fermée) | erreur de syntaxe propre | |
| `echo "   "$USER` | espaces gardés + valeur | trim qui mange les espaces quotés |

---

## 2bis. Caractères `\` et `;` (explicitement nommés par le sujet)

> Le sujet dit : **ne PAS interpréter** `\` (backslash) ni `;` (point-virgule). Ils sont donc des caractères ordinaires, pas des opérateurs. Le piège = vouloir les gérer comme bash.

| Entrée | Attendu | Piège |
|---|---|---|
| `echo a\b` | `a\b` (backslash littéral, pas d'échappement) | tenter d'interpréter `\` → mange le caractère suivant |
| `echo a\ b` | `a\ b` | |
| `echo "a\b"` | `a\b` | |
| `echo a;b` | `a;b` (`;` non interprété = caractère normal) | splitter sur `;` comme bash → comportement non requis / crash |
| `ls ; ls` | bash enchaînerait ; toi → `;` littéral, **pas de crash** | |
| `echo \\` | dépend de bash, mais surtout : **pas de crash** | |

---

## 3. Expander — `$` / `$?` (TON module : section critique)

| Entrée | Attendu | Piège |
|---|---|---|
| `echo $USER` | valeur de USER | |
| `echo $PWD` | cwd | |
| `$` (seul) | littéral `$` | expansion d'un `$` orphelin → lecture hors borne |
| `echo $` | `$` | |
| `echo $ $` | `$ $` | |
| `echo $NONEXISTENT` | ligne vide (var absente = "") | renvoyer `(null)` au lieu de `""` |
| `echo "$NONEXISTENT"` | ligne vide | |
| `echo abc$NONEXISTENTdef` | `abc` (nom de var = `NONEXISTENTdef`) | mauvaise détection de fin de nom de variable |
| `echo $USER$USER` | valeur×2 collée | |
| `echo $USER/file` | valeur + `/file` | `/` mal pris dans le nom |
| `echo $1` | vide (pas d'args positionnels) | |
| `echo $?` | code du dernier foreground | `$?` non mis à jour après builtin/pipe |
| `echo $?` au **tout premier** prompt (avant toute commande) | `0` | valeur initiale non mise à 0 |
| `echo $$` / `echo $@` / `echo ${USER}` | non requis par le sujet → ne pas crash | `${ }`, `$$`, `$@` → lecture hors borne / segfault |
| `echo $?$?` | code collé deux fois | |
| `echo "$?"` | code (expansion en double quote) | |
| `echo '$?'` | littéral `$?` | |
| `echo $USER=4` | valeur + `=4` | `=` pris dans le nom |
| `echo text"$USER"test` | concat correcte | |
| `echo $9USER` | `$9` → vide, puis `USER` littéral | bash : `$9` est positionnel (vide) ; gérer chiffre après `$` |
| `echo "$"` | `$` | |
| `echo $?abc` | code + `abc` | `?` consomme un seul caractère, pas plus |
| Expansion → token vide non quoté (`$EMPTY`) | disparaît (word splitting) ; `$EMPTY` seul comme commande → rien / not found `` | crash si tu exécutes une commande NULL/`""` |
| `export A="b c"; echo $A` | `b c` sur **deux mots** (splitting hors quotes) | bash split ; `echo "$A"` garde un seul mot |

> **Leaks expander** : chaque string intermédiaire (avant/après substitution) doit être free. Le piège classique = `join` successifs sans free de l'intermédiaire. Teste `echo $USER$USER$USER$USER` sous valgrind.

---

## 4. Redirections `<` `>` `>>` (TON module executor)

| Entrée | Attendu | Piège |
|---|---|---|
| `echo hi > file` | crée/écrase, `file` = `hi` | fd de sortie non fermé → leak fd |
| `echo hi >> file` | append | mauvais flag (`O_TRUNC` au lieu de `O_APPEND`) |
| `cat < file` | lit file | fd input non fermé |
| `cat < nonexistent` | erreur `No such file or directory`, `$?`=1, pas de crash | déréférencement après open échoué |
| `> file` (sans commande) | crée `file` vide, exit 0 | exécuter une commande NULL |
| `< file` (sans commande) | ouvre (vérifie existence), rien exécuté | |
| `echo hi > a > b` | crée `a` ET `b`, écrit dans `b` (dernier) | ne créer que le dernier ; oublier d'ouvrir/fermer `a` |
| `cat < a < b` | lit `b` (dernier input gagne) | |
| `echo hi > /nonexistent_dir/x` | erreur, `$?`=1 | crash sur open échoué |
| `> /` | `Is a directory`, `$?`=1 | |
| `echo hi >` (rien après) | **erreur de syntaxe** `near unexpected token 'newline'`, `$?`=2 | crash / déréf de redir sans cible |
| `> > file` | syntax error | |
| `echo a > "f i le"` | nom de fichier `f i le` | split du nom quoté |
| `echo a > $EMPTY` | bash : `ambiguous redirect`, `$?`=1 | crash sur cible vide |
| `export V="a b"; echo x > $V` | `ambiguous redirect` (cible = 2 mots), `$?`=1 | ouvrir un fichier `a b` au lieu d'erreur |
| `echo hi>file` / `cat<file` / `ls>>f` (sans espace) | identique avec espaces | tokenizer qui exige l'espace autour du redir |
| `> out echo hi` / `< in cat` (redir AVANT la commande) | fonctionne comme après | ne gérer le redir qu'après le mot de commande |
| `ls > file; cat file` | (pas de `;` requis) → erreur syntaxe sur `;` | ne pas crash sur `;` |
| redirection sans droit d'écriture | `Permission denied`, `$?`=1 | |

> **FD leak test** : `< Makefile cat | cat | cat > out` répété en boucle. Avec `--track-fds=yes` aucun fd ne doit rester ouvert après chaque commande.

---

## 5. Heredoc `<<` (TON module — gros pourvoyeur de leaks/crash)

| Entrée | Attendu | Piège |
|---|---|---|
| `cat << EOF` puis lignes puis `EOF` | affiche les lignes | buffer heredoc non free |
| `cat << EOF` avec `$USER` dans le corps | **expansion** des variables | oublier d'expand (heredoc non quoté = expand) |
| `cat << "EOF"` (délimiteur quoté) | **PAS d'expansion** du corps | expand à tort quand le délim est quoté |
| `cat << 'EOF'` | pas d'expansion | |
| `cat << EOF` interrompu par `Ctrl-C` | annule, `$?`=130, retour au prompt | ne pas free le buffer partiel → leak ; ne pas restaurer le prompt |
| `cat << EOF` + `Ctrl-D` (EOF avant délim) | warning bash `here-document delimited by end-of-file`, continue | boucle infinie / NULL readline non géré |
| `cat << EOF << EOF2` | seul le **dernier** heredoc alimente stdin, mais les deux sont lus | ne lire qu'un seul → blocage |
| `cat << EOF | cat` | heredoc + pipe | fd heredoc non fermé dans le pipe |
| Délimiteur avec espaces / quotes `<< "E O F"` | délim = `E O F` | mauvais parse du délim |
| heredoc ne doit PAS écrire dans l'historique (sujet) | | |
| `<< EOF` sans commande | lit puis rien exécuté | |

> Le heredoc est souvent implémenté via fichier temp **ou** pipe. Dans les deux cas : fermer le fd / unlink le temp, y compris si `Ctrl-C` pendant la saisie. Les testeurs modernes (LeaYeh) checkent spécifiquement les leaks fd du heredoc.

---

## 6. Pipes `|` (TON module executor)

| Entrée | Attendu | Piège |
|---|---|---|
| `ls \| cat -e` | sortie chaînée | fork/pipe basique |
| `echo hi \| cat \| cat \| cat` | `hi` | fermeture incomplète des fd pipe → blocage (deadlock) |
| `ls \| grep introuvable` | rien, `$?`=1 (code du dernier) | `$?` = code du **dernier** process du pipe |
| `cat \| cat \| ls` | `ls` s'exécute, les `cat` reçoivent EOF | tous les fd doivent être fermés sinon `cat` attend indéfiniment |
| `\| cmd` | syntax error `near unexpected token '|'`, `$?`=2 | crash sur pipe en tête |
| `cmd \|` | bash continue la lecture ; toi → erreur de syntaxe acceptable | crash sur pipe en fin |
| `cmd \| \| cmd` | syntax error | |
| `echo a \| exit \| echo b` | `exit` builtin dans pipe → s'exécute dans un child, ne tue pas le shell | `exit` qui quitte le shell parent depuis un pipe |
| `export A=1 \| env` | `export` dans pipe = child, n'affecte PAS l'env parent | modification de l'env parent depuis un child |
| Pipe long (20× `cat -e`) | fonctionne | limite de fd / fork non récupérés (zombies) |
| `ls -la \| grep "." \| wc -l` | chaîne complète | |
| `cat /dev/random \| head -1` | head termine, cat reçoit SIGPIPE | gérer SIGPIPE / pas de crash quand le lecteur ferme tôt |

> **Deadlock** : la cause n°1 de blocage = ne pas fermer les extrémités de pipe inutilisées dans le parent ET dans chaque child. Règle : après `dup2`, ferme **tous** les fd de pipe d'origine.
> **Zombies** : `waitpid` sur **tous** les enfants, pas seulement le dernier.

---

## 7. Builtin `echo`

| Entrée | Attendu | Piège |
|---|---|---|
| `echo` | `\n` | |
| `echo -n` | rien (pas de newline) | |
| `echo -n hi` | `hi` sans `\n` | |
| `echo -nnnn hi` | `hi` sans `\n` (`-n` répété valide) | |
| `echo -n -n -n hi` | `hi` sans `\n` | s'arrêter au premier non-`-n` |
| `echo -nx hi` | `-nx hi\n` (pas une option valide → imprimé) | traiter `-nx` comme `-n` |
| `echo --n hi` | `--n hi\n` (bash n'accepte pas `--n`) | |
| `echo hi -n` | `hi -n\n` (le `-n` n'est plus en tête) | |
| `echo "-n" hi` | `-n hi\n` (quoté = littéral) | |
| `echo a   b` | `a b` (mots re-séparés par 1 espace) | conserver les espaces multiples |

---

## 8. Builtin `cd`

| Entrée | Attendu | Piège |
|---|---|---|
| `cd /tmp` | change, met à jour `PWD`/`OLDPWD` | oubli de mise à jour PWD/OLDPWD |
| `cd ..` | parent | |
| `cd .` | reste | |
| `cd` (sans arg) | va dans `HOME` | si `HOME` unset → `cd: HOME not set`, `$?`=1 |
| `cd ~` | sujet : `~` non requis → bash le fait, toi non | ne pas crash |
| `cd nonexistent` | `No such file or directory`, `$?`=1 | |
| `cd ""` | bash : ne bouge pas, `$?`=0 | crash sur chdir("") |
| `cd a b` | `cd: too many arguments`, `$?`=1, ne bouge pas | exécuter le premier arg quand même |
| `cd ../../../../..` | remonte jusqu'à `/` | |
| `cd /` puis `cd -` | `-` non requis (sujet) ; ne pas crash | |
| `cd $OLDPWD` | utilise la var | |
| `cd` après `rmdir` du cwd | `getcwd` échoue → gérer sans crash | segfault si getcwd renvoie NULL non testé |
| `unset HOME; cd` | `cd: HOME not set` | |

---

## 9. Builtin `pwd`

| Entrée | Attendu | Piège |
|---|---|---|
| `pwd` | cwd via `getcwd` | |
| `unset PWD; pwd` | `getcwd` (pas la var) → cwd correct | utiliser la var PWD au lieu de getcwd |
| `pwd` après suppression du dossier courant | bash affiche l'ancien chemin / erreur | getcwd NULL non géré → crash |
| `pwd -L` / `pwd extra` | sujet : sans options → bash ignore/erreur ; ne pas crash | |

---

## 10. Builtin `export`

| Entrée | Attendu | Piège |
|---|---|---|
| `export` (seul) | liste triée, format `declare -x NAME="value"` | tri alphabétique manquant |
| `export A=1` | ajoute A | |
| `export A` | déclare A sans valeur : visible dans `export`, **pas** dans `env` | apparaît à tort dans `env` |
| `export A=` | A vaut chaîne vide, visible dans `env` | |
| `export A=1 B=2 C=3` | les trois | n'en prendre qu'un |
| `export 1A=1` | `not a valid identifier`, `$?`=1 | accepter un nom commençant par chiffre |
| `export =1` | `not a valid identifier` | crash sur nom vide |
| `export ""` | `not a valid identifier` | |
| `export A+=x` (append) | bonus ; sans `+=` requis, mais ne pas crash | |
| `export A-=1` | `not a valid identifier` | |
| `export A=1 2B=2` | A ajouté, `2B` → erreur, `$?`=1 (continue les valides) | s'arrêter au premier invalide |
| `export A="a b c"` | A = `a b c` (un seul mot, garde espaces) | splitting de la valeur |
| `export A=b=c` / `export A=too=many=equals` | A = `b=c` (seul le **1er** `=` sépare nom/valeur) | couper au dernier `=` ou refuser |
| `export A="val $USER"` | expansion de `$USER` dans la valeur (double quote) | non-expansion |
| `export A='$USER'` | A = littéral `$USER` (simple quote) | expansion à tort |
| `export PATH=` puis `ls` | `ls` introuvable, pas de crash | |

> Valeurs autorisées dans un identifiant : `[a-zA-Z_][a-zA-Z0-9_]*`. Tester `export _A=1` (valide), `export A_=1` (valide), `export A.B=1` (invalide).

---

## 11. Builtin `unset`

| Entrée | Attendu | Piège |
|---|---|---|
| `unset A` | retire A | |
| `unset nonexistent` | rien, `$?`=0 | erreur à tort |
| `unset PATH` puis `ls` | introuvable, pas de crash | |
| `unset PWD` puis `pwd` | pwd via getcwd OK | |
| `unset 1A` | `not a valid identifier`, `$?`=1 | crash |
| `unset A B C` | retire les trois | |
| `unset` (sans arg) | rien, `$?`=0 | |
| `unset =` | invalid identifier | |

---

## 12. Builtin `env`

| Entrée | Attendu | Piège |
|---|---|---|
| `env` | toutes les vars **avec** valeur (pas les `export A` sans `=`) | afficher les vars déclarées sans valeur |
| `env extra` / `env -i` | sujet : sans options/args → bash erreur ; ne pas crash | |
| après `unset PATH` | `env` affiche le reste | |

---

## 13. Builtin `exit` (piège fréquent : la logique des args)

| Entrée | Attendu | Piège |
|---|---|---|
| `exit` | quitte avec `$?` courant, affiche `exit` (en interactif) | message `exit` envoyé sur stdout au lieu de stderr (casse les testeurs) |
| `exit 0` | code 0 | |
| `exit 42` | code 42 | |
| `exit -1` | code 255 (modulo 256) | |
| `exit 256` | code 0 | |
| `exit 257` | code 1 | |
| `exit "42"` | 42 (quotes retirées avant parse) | |
| `exit +42` | 42 | |
| `exit abc` | `numeric argument required`, **quitte** avec code 2 | ne pas quitter / mauvais code |
| `exit 42abc` | `numeric argument required`, quitte avec 2 | accepter `42` |
| `exit 42 53` | `too many arguments`, **NE quitte PAS**, `$?`=1 | quitter quand même |
| `exit abc def` | `numeric argument required`, quitte avec 2 (l'erreur numérique prime) | renvoyer `too many arguments` |
| `exit 9223372036854775807` | code 255 (`...807` % 256) | overflow non géré |
| `exit 9223372036854775808` | overflow → `numeric argument required`, quitte 2 | accepter / wrap silencieux |
| `exit ++0` / `exit --0` | bash : `numeric argument required` (double signe invalide) | |

> Subtilité d'ordre : bash teste d'abord si le **1er** arg est numérique. S'il ne l'est pas → erreur numérique + exit 2, **même s'il y a plusieurs args**. S'il est numérique mais qu'il y a >1 arg → `too many arguments` + on ne quitte pas.

---

## 14. Recherche d'exécutable / PATH (TON module executor)

| Entrée | Attendu | Piège |
|---|---|---|
| `ls` | trouvé via PATH | |
| `/bin/ls` | chemin absolu | |
| `./minishell` | chemin relatif | |
| `nonexistentcmd` | `command not found`, `$?`=**127** | mauvais code |
| `./nonexistent` | `No such file or directory`, `$?`=127 | |
| `/bin` (un dossier) | `Is a directory`, `$?`=**126** | tenter execve sur un dossier → crash/echec mal codé |
| fichier sans droit `x` | `Permission denied`, `$?`=126 | |
| `unset PATH; ls` | `No such file or directory` / not found, `$?`=127, **pas de crash** | déréf de PATH NULL |
| `PATH=:/bin ls` | entrée vide = cwd | |
| `""` (commande vide) | rien / not found `` | execve sur "" → crash |
| `$EMPTY_VAR arg` | commande vide → not found, pas de crash | |
| commande très longue / 1000 args | fonctionne ou erreur propre | |

> **Leak exec** : le tableau de PATH splitté, le chemin construit (`join(dir, "/", cmd)`), et l'`envp` reconstruit doivent être free **avant** `execve` (qui ne revient pas) côté child **si tu free avant** — ou accepter que execve remplace l'image. En cas d'échec d'execve, free **tout** puis `exit(126/127)`.

---

## 15. Signaux (comportement = bash en mode interactif)

| Action | Attendu | Piège |
|---|---|---|
| `Ctrl-C` au prompt vide | nouvelle ligne + nouveau prompt, `$?`=130 | redessiner le prompt, ne pas quitter |
| `Ctrl-D` au prompt vide | quitte (`exit`) | |
| `Ctrl-\` au prompt | ne fait rien | |
| `Ctrl-C` pendant `cat` (sans args, qui attend) | tue le child, `$?`=130, retour prompt | tuer le shell parent |
| `Ctrl-\` pendant une commande | `Quit (core dumped)`, `$?`=131 | |
| `Ctrl-C` pendant un heredoc | annule le heredoc, `$?`=130 | leak buffer + prompt cassé |
| `sleep 5` puis `Ctrl-C` | interrompt, `$?`=130 | |
| commande tuée par signal | code = `128 + n` (130 SIGINT, 131 SIGQUIT) | renvoyer un code faux |

> Norme/sujet : **une seule** variable globale, qui ne contient **que** le numéro de signal. Le handler ne touche à rien d'autre. Restauration des `sigaction` parent ↔ child.

---

## 16. Environnement vide / cassé (section "no env" des testeurs)

| Contexte | Entrée | Attendu | Piège |
|---|---|---|---|
| `env -i ./minishell` | `echo $PATH` | vide | |
| env vide | `ls` | not found / no such file, **pas de crash** | déréf PATH NULL |
| env vide | `pwd` | getcwd OK | dépendre de PWD inexistant |
| env vide | `export A=1; env` | `A=1` | |
| `unset PATH OLDPWD PWD` | `cd ..; pwd; export` | tout sans crash | OLDPWD absent géré |
| env vide | `$?` après commandes | cohérent | |

---

## 16bis. Mode non-interactif / stdin redirigé (compatibilité testeurs)

> Les testeurs lancent souvent `echo 'CMD' \| ./minishell` ou `./minishell < script`. Si tu te plantes ici, **tous** les tests stdout échouent d'un coup.

| Entrée | Attendu | Piège |
|---|---|---|
| `echo 'ls -la' \| ./minishell` | exécute, pas de prompt parasite dans la sortie | prompt écrit sur stdout en mode non-tty |
| `printf 'echo a\necho b\n' \| ./minishell` | exécute les deux lignes | s'arrêter à la 1re ligne |
| `exit` en non-interactif | le message `exit` doit aller sur **stderr** (ou rien), pas stdout | message sur stdout → casse la comparaison testeur |
| `isatty()` pour décider du prompt | prompt uniquement si entrée = terminal | toujours afficher le prompt |

---

## 17. Combinaisons lourdes (extraites des testeurs en ligne)

| Entrée | Attendu | Piège |
|---|---|---|
| `< Makefile cat > out \| < README.md cat -e` | redir + pipe mélangés | ordre d'ouverture des fd |
| `< in1 < in2 < in3 wc -l \| cat -e \| rev > out1 > out2` | dernier input + derniers outputs | |
| `wc < Makefile -l \| cat -e > out \| echo hello \| rev > out2` | chaîne complexe | un fd qui fuit dans la chaîne |
| `echo $PWD \| cat -e` | expansion + pipe | |
| `echo '$PWD hallo \| cat -e'` | littéral (simple quote) | |
| `echo "$PWD hallo \| cat -e"` | `$PWD` expand, `\|` littéral dans les quotes | |
| `cmd "str1 str2" >out \| cmd2 -arg \| cmd3 >out2 >out3` | multi-redir + pipe | |
| 20 commandes en pipe avec redirs finales | OK, 0 fd restant | |

---

## 18. Plan de passage valgrind (ordre conseillé)

1. **Démarrage / sortie** : lancer, `Ctrl-D` immédiat → 0 leak (sauf readline).
2. **Builtins purs** : `export`/`unset`/`cd`/`echo`/`env`/`pwd` en boucle → 0 leak.
3. **exit** dans tous ses cas (table §13) → 0 leak, codes corrects.
4. **Expander** : `echo $USER$USER$PWD$?` répété → 0 leak des intermédiaires.
5. **Redirections seules** (table §4) → `--track-fds=yes`, 0 fd résiduel.
6. **Heredoc** (table §5) y compris `Ctrl-C` pendant saisie → 0 leak buffer/temp.
7. **Pipes** (table §6) y compris chaînes longues → 0 zombie, 0 fd, pas de deadlock.
8. **Erreurs de syntaxe** (`|` seul, `>` seul, quote non fermée) → 0 leak de la structure parsée.
9. **Env vide** (`env -i`, `unset PATH`) → pas de crash.
10. **Combinaisons §17** sous valgrind.

> Comparaison systématique stdout / stderr / `$?` avec bash. Astuce testeurs : `bash -c 'CMD'` vs `./minishell` non interactif (implique de gérer l'entrée non-tty proprement).

---

## 19. Points "0 à l'éval" à ne jamais oublier

- Norme respectée sur **tous** les fichiers, bonus inclus.
- Aucun segfault / bus error / double free (hors comportement indéfini).
- Aucun leak **de ton code** (readline excepté).
- Makefile : `$(NAME)`, `all`, `clean`, `fclean`, `re`, pas de relink inutile, flags `-Wall -Wextra -Werror`, libft compilé via son propre Makefile.
- Une seule variable globale = numéro de signal uniquement.
- README.md conforme (1re ligne en italique + sections Description / Instructions / Resources avec usage de l'IA).
