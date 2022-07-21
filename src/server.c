/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiez-ga <sdiez-ga@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 16:54:43 by sdiez-ga          #+#    #+#             */
/*   Updated: 2022/07/21 20:32:05 by sdiez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

int main(void)
{
	struct sigaction	signal_listener;

	ft_putstr("server pid: ");
	ft_putint((int) getpid());
	ft_putstr("\nlistening...\n");
	signal_listener.sa_flags = SA_SIGINFO;
	signal_listener.sa_sigaction = sigrec;
	sigaction(SIGUSR1, &signal_listener, 0);
	sigaction(SIGUSR2, &signal_listener, 0);
	while (1)
		pause();
}

void	sigrec(int signo, siginfo_t *info, __attribute((unused)) void *context)
{
	static t_marked_buffer	mb;

	if (!mb.first_bit && signo == SIGUSR1)
	{
		kill(info->si_pid, SIGUSR1);
		mb.first_bit = 1;
		return ;
	}
	receive_bit(signo, info->si_pid, &mb);
}

void	receive_bit(int signo, pid_t pid, t_marked_buffer *mb)
{
	if (signo == SIGUSR1)
		mb->current_char |= 1 << mb->bit_count;
	mb->bit_count++;
	if (mb->bit_count == 8)
	{
		mb->buffer[mb->cursor] = mb->current_char;
		mb->cursor++;
		if (mb->current_char == 0)
		{
			ft_putstr(mb->buffer);
			ft_putchar('\n');
			clear_buffer(mb);
			mb->cursor = 0;
			mb->first_bit = 0;
			kill(pid, SIGUSR2);
		}
		mb->current_char = 0;
		mb->bit_count = 0;
	}
	kill(pid, SIGUSR1);
}

void	clear_buffer(t_marked_buffer *mb)
{
	size_t	i;

	i = 0;
	while (i < mb->cursor)
	{
		mb->buffer[i] = 0;
		i++;
	}
}
