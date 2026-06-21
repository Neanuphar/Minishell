/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moidoubi <moidoubi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 00:00:00 by moidoubi          #+#    #+#             */
/*   Updated: 2026/06/21 10:46:29 by moidoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>              /* write read access fork execve dup dup2 pipe close getcwd chdir unlink isatty ttyname ttyslot */
# include <stdlib.h>              /* malloc free exit getenv */
# include <stdio.h>               /* printf perror */
# include <string.h>              /* strerror */
# include <fcntl.h>               /* open O_RDONLY O_WRONLY O_CREAT O_TRUNC O_APPEND */
# include <sys/wait.h>            /* wait waitpid wait3 wait4 */
# include <sys/stat.h>            /* stat lstat fstat */
# include <sys/ioctl.h>           /* ioctl */
# include <signal.h>              /* signal sigaction sigemptyset sigaddset kill */
# include <dirent.h>              /* opendir readdir closedir */
# include <termios.h>             /* tcsetattr tcgetattr */
# include <ncurses.h>             /* tgetent tgetflag tgetnum tgetstr tgoto tputs */
# include <readline/readline.h>   /* readline rl_clear_history rl_on_new_line rl_replace_line rl_redisplay */
# include <readline/history.h>    /* add_history */
# include "../libft/libft.h"      /* fonctions libft */

extern int	g_signal; /* stocke le numéro du signal reçu */

typedef enum e_node_type
{
	NODE_CMD,  /* feuille : commande simple */
	NODE_PIPE, /* noeud  : | */
}	t_node_type;

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,     /* < */
	REDIR_OUT,    /* > */
	REDIR_APPEND, /* >> */
	HEREDOC,      /* << */
}	t_token_type;

typedef struct s_redir
{
	t_token_type	type;           /* type de redirection */
	char			*file;          /* nom du fichier ou délimiteur heredoc */
	char			*heredoc_body;  /* contenu du heredoc (NULL si pas heredoc) */
	int				heredoc_quoted; /* délimiteur quoté ? 1 = pas d'expansion */
	struct s_redir	*next;          /* redirection suivante */
}	t_redir;

typedef struct s_token
{
	t_token_type	type;           /* type du token */
	char			*value;         /* valeur (NULL pour les opérateurs) */
	struct s_token	*next;          /* token suivant */
}	t_token;

typedef struct s_cmd
{
	char			**args;         /* arguments de la commande */
	t_redir			*redirs;        /* liste de redirections */
	struct s_cmd	*next;          /* commande suivante (après un pipe) */
}	t_cmd;

typedef struct s_node
{
	t_node_type		type;   /* type du noeud */
	char			**argv; /* args bruts quotes conservées (NULL si pas NODE_CMD) */
	t_redir			*redirs;/* liste de redirections (NULL si pas NODE_CMD) */
	struct s_node	*left;  /* fils gauche (NULL si NODE_CMD) */
	struct s_node	*right; /* fils droit  (NULL si NODE_CMD) */
}	t_node;

typedef struct s_shell
{
	char	**envp;     /* copie modifiable de l'environnement */
	int		exit_code;  /* valeur de $? — code de sortie de la dernière commande */
	int		running;    /* 1 = shell actif, 0 = on quitte */
}	t_shell;

/* --- lexer  --- */
t_token		*lexer(char *line);                  /* tokenise la ligne brute */
void		free_token_list(t_token *list);       /* libère la liste de tokens */
char		*get_word(char *line, int *i);        /* extrait un mot (avec gestion quotes) */
void		add_token(t_token **list, t_token *new);      /* ajoute un token en fin de liste */
t_token		*new_token(t_token_type type, char *value);   /* alloue et initialise un token */

/* --- parser  --- */
t_cmd		*parse_tokens(t_token *token);        /* produit la liste de t_cmd depuis les tokens */
void		free_cmd_list(t_cmd *cmd);            /* libère la liste de t_cmd */
void		free_ast(t_node *node);               /* libère l'arbre récursivement */
void		add_redir(t_cmd *cmd, t_token_type type, char *file); /* ajoute une redirection à la commande */
void		add_arguments(t_cmd *cmd, char *word);                /* ajoute un argument à la commande */
t_cmd		*new_command(void);                                   /* alloue une commande vide */
int			count_args(t_cmd *command);                           /* compte les arguments */
void		free_redirs_list(t_redir *redir);                     /* libère la liste de redirections */
void		print_error(t_token *token);                          /* affiche une erreur de syntaxe sur stderr */
int			check_order(t_token *token);                          /* vérifie la syntaxe des tokens */

/* --- expander  --- */
char		**expand_argv(char **argv, t_shell *shell);              /* substitue $VAR, retire les quotes, filtre les vides */
char		*expand_heredoc(char *body, t_shell *shell);             /* substitue $VAR dans un heredoc (pas de quote stripping) */
char		*expand_word(char *argv, t_shell *shell);                /* traite un mot : quotes, $VAR, littéral */
char		*append_char(char *result, char *letter);                /* concatène letter à result et libère les deux */
char		*handle_single_quote(char *argv, int *i);                /* copie le contenu entre '' sans expansion */
int			count(char **argv);                                      /* compte les éléments d'un tableau de strings */
char		*search_var(char *str);                                  /* extrait le nom de variable après un $ */
char		*handle_dollar(char *result, char *var, t_shell *shell); /* substitue $VAR ou $? dans result */


/* --- executor  --- */
int			execute_ast(t_node *node, t_shell *shell);             /* point d'entrée : exécute l'AST entier */
int			is_builtin(char *cmd);                                 /* vérifie si cmd est un builtin */
int			run_builtin(char *cmd, char **argv, t_shell *shell);   /* appelle le bon builtin */
int			free_tab(char **tab);                                  /* libère un tableau de strings */
char		*find_path(char *cmd, char **envp);                    /* cherche le chemin complet dans PATH */
int			exec_extern(char **cmd, t_shell *shell, t_node *node); /* fork + execve + waitpid */
int			apply_redirs(t_redir *redir, t_shell *shell);          /* applique toutes les redirections d'une commande */
void		fork_left(t_node *node, t_shell *shell, int *pipefd);  /* child gauche du pipe */
void		fork_right(t_node *node, t_shell *shell, int *pipefd); /* child droit du pipe */
t_node		*bridge(char *input);                                  /* point d'entrée : lexer + parser + conversion AST */
void		fill_heredocs(t_node *node);                           /* parcourt l'AST et lit tous les heredocs */


/* --- builtins  --- */
int			builtin_echo(char **argv);                    /* echo [-n] */
int			builtin_cd(char **argv, t_shell *shell);      /* cd [path] — met à jour PWD/OLDPWD */
int			builtin_pwd(void);                            /* affiche le répertoire courant */
int			builtin_export(char **argv, t_shell *shell);  /* ajoute/modifie une variable d'env */
int			builtin_unset(char **argv, t_shell *shell);   /* supprime une variable d'env */
int			builtin_env(t_shell *shell);                  /* affiche l'environnement complet */
int			builtin_exit(char **argv, t_shell *shell);    /* quitte le shell avec un code */
int			env_find(char **envp, char *key);             /* retourne l'index de key dans envp */
void		echo_print(char **argv, int i);               /* affiche argv[i..] séparés par espaces */
char		**env_add(t_shell *shell, char *entry);       /* ajoute une entrée à shell->envp */
void		export_print(t_shell *shell);                 /* affiche toutes les variables avec declare -x */
void		cd_update_pwd(t_shell *shell, char *PWD, int boolen); /* met à jour OLDPWD ou PWD */
int			is_flag_n(char *s);                           /* vérifie si s est un flag -n valide */

#endif
