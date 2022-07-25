#ifndef MINITALK_H
# define MINITALK_H

/*
 * Includes
 * */

# include <signal.h>
# include <stdio.h>
# include <stdlib.h>  
# include <unistd.h>  

/*
 * Macros
 * */

# define MSG_DELAY_US 1
# define BUF_SIZE 1000000000

/*
 * Structs
 * */

typedef struct s_marked_buffer
{
	char	buffer[BUF_SIZE];
	char	current_char;
	size_t	cursor;
	size_t	bit_count;
	size_t	first_bit;
}				t_marked_buffer;

typedef struct s_client_info
{
	char	*msg;
	size_t	cursor;
	size_t	bit_pos;
	pid_t	server_pid;
}				t_client_info;

/*
 * Functions
 * */

/* common functions */
void    sigrec(int signo, siginfo_t *info, __attribute((unused)) void *context);

/* server.c functions */
void	receive_bit(int signo, pid_t pid, t_marked_buffer *mb);
void	clear_buffer(t_marked_buffer *mb);

/* client.c functions */
void	start_comm();
void	bit_sender(char bit);
void	error_exit_msg(char *msg);

/* utils.c functions */
void	ft_putchar(char c);
void	ft_putstr(char *str);
void	ft_putint(int num);
int		ft_isspace(char c);
size_t	ft_atoui(char *str);

#endif
