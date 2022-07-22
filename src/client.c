/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiez-ga <sdiez-ga@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 16:54:51 by sdiez-ga          #+#    #+#             */
/*   Updated: 2022/07/21 20:41:49 by sdiez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

t_client_info	g_client_info;

int main(int argc, char **argv)
{
	struct sigaction	signal_listener;
	pid_t				server_pid;
	size_t				i;

	if (argc < 3)
		error_exit_msg("To few parameters");
	else if (argc > 3)
		error_exit_msg("To many parameters");
	server_pid = (pid_t) ft_atoui(argv[1]);
	i = 0;
	if (server_pid > 1)
	{
		g_client_info.server_pid = server_pid;
		g_client_info.msg = argv[2];
		g_client_info.cursor = 0;
		g_client_info.bit_pos = 0;
		signal_listener.sa_flags = SA_SIGINFO;
		signal_listener.sa_sigaction = sigrec;
		sigaction(SIGUSR1, &signal_listener, 0);
		sigaction(SIGUSR2, &signal_listener, 0);
		start_comm();
		while (1)
			pause();
	}
	else
		error_exit_msg("Invalid pid");
}

void	sigrec(int signo, siginfo_t *info, __attribute((unused)) void *context)
{
	(void) info;
	if (signo == SIGUSR1)
	{
		usleep(1);
		bit_sender((g_client_info.msg[g_client_info.cursor] >> g_client_info.bit_pos) % 2);
		g_client_info.bit_pos++;
		if (g_client_info.bit_pos == 8)
		{
			g_client_info.bit_pos = 0;
			g_client_info.cursor++;
		}
	}
	if (signo == SIGUSR2 || !g_client_info.msg[g_client_info.cursor])
		exit(0);
}

void	start_comm()
{
	kill(g_client_info.server_pid, SIGUSR1);
}

void	bit_sender(char bit)
{
	if (bit)
		kill(g_client_info.server_pid, SIGUSR1);
	else
		kill(g_client_info.server_pid, SIGUSR2);
}

void	error_exit_msg(char *msg)
{
	ft_putstr(msg);
	ft_putstr(". The correct use of the client is:\n");
	ft_putstr("./client server_pid \"message\"");
	exit(1);
}
