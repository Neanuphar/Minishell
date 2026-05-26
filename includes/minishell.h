/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moidoubi <moidoubi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 00:00:00 by moidoubi          #+#    #+#             */
/*   Updated: 2026/05/26 23:34:21 by moidoubi         ###   ########.fr       */
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

extern int	g_signal; /* seule variable globale autorisée — stocke le numéro du signal reçu */

typedef enum e_node_type
{
	NODE_CMD,  /* feuille : commande simple */
	NODE_PIPE, /* noeud  : | */
	NODE_AND,  /* noeud  : && */
	NODE_OR    /* noeud  : || */
}	t_node_type;

typedef enum e_redir_type
{
	REDIR_IN,     /* < */
	REDIR_OUT,    /* > */
	REDIR_APPEND, /* >> */
	REDIR_HEREDOC /* << */
}	t_redir_type;

typedef struct s_redir
{
	t_redir_type	type;           /* type de redirection */
	char			*file;          /* nom du fichier ou délimiteur heredoc */
	char			*heredoc_body;  /* contenu du heredoc (NULL si pas heredoc) */
	int				heredoc_quoted; /* délimiteur quoté ? 1 = pas d'expansion */
	struct s_redir	*next;          /* redirection suivante */
}	t_redir;

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

/* --- parser  --- */
t_node		*parse(char *input);    /* produit l'AST depuis la ligne brute */
void		free_ast(t_node *node); /* libère l'arbre récursivement */

/* --- expander  --- */
char		**expand_argv(char **argv, t_shell *shell);  /* substitue $VAR et retire les quotes */
char		*expand_heredoc(char *body, t_shell *shell); /* substitue $VAR dans un heredoc */

/* --- executor  --- */
int			execute_ast(t_node *node, t_shell *shell); /* point d'entrée : exécute l'AST entier */
int  is_builtin(char *cmd);
int  run_builtin(char *cmd, char **argv, t_shell *shell);
int free_tab(char **tab);
char	*find_path(char *cmd, char **envp);
char	*get_path_env(char **envp);
int exec_extern(char **cmd, t_shell *shell);

/* --- builtins  --- */
int			builtin_echo(char **argv);                   /* echo [-n] */
int			builtin_cd(char **argv, t_shell *shell);     /* cd [path] — met à jour PWD/OLDPWD */
int			builtin_pwd(void);                           /* affiche le répertoire courant */
int			builtin_export(char **argv, t_shell *shell); /* ajoute/modifie une variable d'env */
int			builtin_unset(char **argv, t_shell *shell);  /* supprime une variable d'env */
int			builtin_env(t_shell *shell);                 /* affiche l'environnement complet */
int			builtin_exit(char **argv, t_shell *shell);   /* quitte le shell avec un code */
int	  env_find(char **envp, char *key);
void	echo_print(char **argv, int i);
char  **env_add(t_shell *shell, char *entry);
void export_print(t_shell *shell);


#endif