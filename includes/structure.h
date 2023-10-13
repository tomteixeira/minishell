/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebernar <hebernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:56:18 by toteixei          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/10/10 16:49:18 by toteixei         ###   ########.fr       */
=======
/*   Updated: 2023/10/11 11:41:31 by hebernar         ###   ########.fr       */
>>>>>>> 39a9775 (execution changes)
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H

# define MS_SIGHUP         "Hangup"
# define MS_SIGINT         "Interrupt"
# define MS_SIGQUIT     "Quit"
# define MS_SIGILL         "Illegal instruction"
# define MS_SIGTRAP     "BPT trace/trap"
# define MS_SIGABRT     "ABORT instruction"
# define MS_SIGEMT         "EMT instruction"
# define MS_SIGFPE         "Floating point exception"
# define MS_SIGKILL        "Killed"
# define MS_SIGBUS         "Bus error"
# define MS_SIGSEGV     "Segmentation fault"
# define MS_SIGSYS         "Bad system call"
# define MS_SIGPIPE     "Broken pipe"
# define MS_SIGALRM     "Alarm clock"
# define MS_SIGTERM     "Terminated"
# define MS_SIGURG         "Urgent IO condition"
# define MS_SIGSTOP     "Stopped (signal)"
# define MS_SIGTSTP        "Stopped"
# define MS_SIGCONT     "Continue"
# define MS_SIGCHLD     "Child death or stop"
# define MS_SIGTTIN     "Stopped (tty input)"
# define MS_SIGTTOU     "Stopped (tty output)"
# define MS_SIGIO         "I/O ready"
# define MS_SIGXCPU     "CPU limit"
# define MS_SIGXFSZ     "File limit"
# define MS_SIGVTALRM     "Alarm (virtual)"
# define MS_SIGPROF     "Alarm (profile)"
# define MS_SIGWINCH     "Window changed"
# define MS_SIGINFO        "Information request"
# define MS_SIGUSR1     "User signal 1"
# define MS_SIGUSR2     "User signal 2"

typedef enum
{
    T_PIP,
    T_STR,
	T_VAR,
	T_WORD,
	T_RED,
    T_HRD,
} t_tokentype;

typedef enum
{
    R_IN,
    R_OUT,
    A_R_OUT,
    HEREDOC,
}   t_redirection_type;

typedef struct s_env
{
    char    *var;
    struct   s_env *next;
}   t_env;

typedef struct s_token
{
    t_tokentype type;
    char *value;
} t_token;

typedef struct s_tokenlist
{
    struct s_token      *token;
    struct s_tokenlist  *next;
}   t_tokenlist;

typedef struct s_lexer
{
    const char *input_string;
    size_t position;
} t_lexer;

typedef struct s_redirection
{
    t_redirection_type      type;
    char                    *file;
    struct s_redirection    *next;

}   t_redirection;

typedef struct s_command
{
    //char                    *command;
    char                    **command_args;
    int                     pipe_after;
    int                     nb_args;
    struct s_redirection    *in_redirection;
    struct s_redirection    *out_redirection;
}   t_command;

typedef struct s_command_parser
{
    t_command                   *command;
    struct s_command_parser     *next;
    struct s_command_parser     *previous;
}   t_command_parser;

#endif