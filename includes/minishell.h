/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moidoubi <moidoubi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 00:00:00 by moidoubi          #+#    #+#             */
/*   Updated: 2026/06/25 06:44:49 by moidoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h" // fonctions libft
# include <dirent.h>         // opendir readdir closedir
# include <fcntl.h>
/* open O_RDONLY O_WRONLY O_CREAT O_TRUNC O_APPEND */
# include <ncurses.h>
/* tgetent tgetflag tgetnum tgetstr tgoto tputs */
# include <readline/history.h> /* add_history */
# include <readline/readline.h>
/* readline rl_clear_history rl_on_new_line rl_replace_line rl_redisplay */
# include <signal.h>
/* signal sigaction sigemptyset sigaddset kill */
# include <stdio.h>     /* printf perror */
# include <stdlib.h>    /* malloc free exit getenv */
# include <string.h>    /* strerror */
# include <sys/ioctl.h> /* ioctl */
# include <sys/stat.h>  /* stat lstat fstat */
# include <sys/wait.h>  /* wait waitpid wait3 wait4 */
# include <termios.h>   /* tcsetattr tcgetattr */
# include <unistd.h>
/* write read access fork execve dup dup2 piwatchpe
close getcwd chdir unlink isatty ttyname ttyslot */

extern volatile int	g_signal_receivd;
/* stocke le numéro du signal reçu */

typedef enum e_node_type
{
	NODE_CMD,
	NODE_PIPE, // noeud  : |
}					t_node_type;

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	HEREDOC,
}					t_token_type;

typedef struct s_redir
{
	t_token_type	type;
	char			*file;
	char			*heredoc_body;
	int				heredoc_quoted;
	struct s_redir	*next;
}					t_redir;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}					t_token;

typedef struct s_cmd
{
	char			**args;
	t_redir			*redirs;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_node
{
	t_node_type		type;
	char			**argv;
	t_redir			*redirs;
	struct s_node	*left;
	struct s_node	*right;
}					t_node;

typedef struct s_shell
{
	char			**envp;
	int				exit_code;
	int				running;
}					t_shell;

/* --- lexer  --- */
t_token				*lexer(char *line);
void				free_token_list(t_token *list);
char				*get_word(char *line, int *i);
void				add_token(t_token **list, t_token *new);
t_token				*new_token(t_token_type type, char *value);

/* --- parser  --- */
t_cmd				*parse_tokens(t_token *token);
void				free_cmd_list(t_cmd *cmd);
void				free_ast(t_node *node);
void				add_redir(t_cmd *cmd, t_token_type type, char *file);
void				add_arguments(t_cmd *cmd, char *word);
t_cmd				*new_command(void);
int					count_args(t_cmd *command);
void				free_redirs_list(t_redir *redir);
void				print_error(t_token *token);
int					check_order(t_token *token);
int					return_token(t_token *token);
void				add_heredoc_redir(t_cmd *cmd, char *delim);

/* --- expander  --- */
char				**expand_argv(char **argv, t_shell *shell);
/* substitue $VAR, retire les quotes, filtre les vides */
char				*handle_dollar_in_str(char *argv, int *i, char *result,
						t_shell *shell);
char				*expand_heredoc(char *body, t_shell *shell);
/* substitue $VAR dans un heredoc (pas de quote stripping) */
char				*expand_word(char *argv, t_shell *shell);
/* traite un mot : quotes, $VAR, littéral */
char				*append_char(char *result, char *letter);
/* concatène letter à result et libère les deux */
char				*handle_single_quote(char *argv, int *i);
/* copie le contenu entre '' sans expansion */
int					count(char **argv);
/* compte les éléments d'un tableau de strings */
char				*search_var(char *str);
/* extrait le nom de variable après un $ */
char				*handle_dollar(char *result, char *var, t_shell *shell);
/* substitue $VAR ou $? dans result */

/* --- executor  --- */
int					execute_ast(t_node *node, t_shell *shell);
/* point d'entrée : exécute l'AST entier */
int					is_builtin(char *cmd);
/* vérifie si cmd est un builtin */
int					run_builtin(char *cmd, char **argv, t_shell *shell);
/* appelle le bon builtin */
int					free_tab(char **tab);
/* libère un tableau de strings */
char				*find_path(char *cmd, char **envp);
/* cherche le chemin complet dans PATH */
int					exec_extern(char **cmd, t_shell *shell, t_node *node);

int					apply_redirs(t_redir *redir, t_shell *shell);
/* applique toutes les redirections d'une commande */
void				fork_left(t_node *node, t_shell *shell, int *pipefd);
/* child gauche du pipe */
void				fork_right(t_node *node, t_shell *shell, int *pipefd);
/* child droit du pipe */
t_node				*bridge(char *input);
/* point d'entrée : lexer + parser + conversion AST */
int					fill_heredocs(t_node *node);
/* parcourt l'AST et lit tous les heredocs */

/* --- signal ---*/
void				handle_signal(int signal);
void				setup_signal(void);

/* --- builtins  --- */
int					builtin_echo(char **argv); /* echo [-n] */
int					builtin_cd(char **argv, t_shell *shell);
/* cd [path] — met à jour PWD/OLDPWD */
int					builtin_pwd(void);
/* affiche le répertoire courant */
int					builtin_export(char **argv, t_shell *shell);
/* ajoute/modifie une variable d'env */
int					builtin_unset(char **argv, t_shell *shell);
/* supprime une variable d'env */
int					builtin_env(t_shell *shell);
/* affiche l'environnement complet */
int					builtin_exit(char **argv, t_shell *shell);
/* quitte le shell avec un code */
int					env_find(char **envp, char *key);
/* retourne l'index de key dans envp */
void				echo_print(char **argv, int i);
/* affiche argv[i..] séparés par espaces */
char				**env_add(t_shell *shell, char *entry);
/* ajoute une entrée à shell->envp */
void				export_print(t_shell *shell);
/* affiche toutes les variables avec declare -x */
void				cd_update_pwd(t_shell *shell, char *PWD, int boolen);
/* met à jour OLDPWD ou PWD */
int					is_flag_n(char *s);
char				*make_entry(char *name, char *value);
void				export_store(t_shell *shell, int idx, char *entry);
int					exit_error(char *argv);
int					is_all_num(char *argv);
void				free_envp(char **envp);
/* vérifie si s est un flag -n valide */

#endif
