/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiez-ga <sdiez-ga@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 16:54:33 by sdiez-ga          #+#    #+#             */
/*   Updated: 2022/07/21 19:09:28 by sdiez-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		ft_putchar(str[i]);
}

void	ft_putint(int num)
{
	size_t	u_num;

	u_num = num;
	if (num < 0)
	{
		ft_putchar('-');
		u_num = num * -1;
	}
	if (num > 9)
	{
		ft_putint((int)(num / 10));
		ft_putint((int)(num % 10));
	}
	else
		ft_putchar(num + '0');
}
/*
void	ft_putint(int num)
{
	char			buf[20];
	int				i;
	unsigned int	u_num;

	u_num = num;
	if (num == 0)
		ft_putchar('0');
	else 
	{
		if (num < 0)
		{
			ft_putchar('-');
			u_num = num * -1;
		}
		i = 0;
		while (u_num > 0)
		{
			buf[i] = u_num % 10 + '0';
			u_num /= 10;
			i++;
		}
		while (i >= 0)
			ft_putchar(buf[i--]);
	}
}
*/
int	ft_isspace(char c)
{
	return (c == '\t' || c == '\n' || c == '\v' \
			|| c == '\f' || c == '\r' || c == ' ');
}

size_t	ft_atoui(char *str)
{
	size_t  u_val;
	size_t  i;

	u_val = 0;
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-')
		return (0);
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		u_val = (u_val * 10) + (str[i] - '0');
		i++;
	}
	return (u_val);
}
