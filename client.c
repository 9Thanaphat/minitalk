/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttangcha <ttangcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:13:32 by ttangcha          #+#    #+#             */
/*   Updated: 2025/02/03 14:16:20 by ttangcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include "libft.h"

void	send_bit(int pid, unsigned char ch)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		if ((ch >> i) & 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		usleep(100);
		i--;
	}
}

void	str_to_bin(int pid, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		send_bit(pid, str[i]);
		i++;
	}
	send_bit(pid, '\0');
}

int	main(int ac, char **av)
{
	if (ac == 3)
	{
		str_to_bin(ft_atoi(av[1]), av[2]);
		ft_putstr_fd("Message sent to PID: ", 1);
		ft_putnbr_fd(ft_atoi(av[1]), 1);
		ft_putstr_fd("\n", 1);
	}
	else
		ft_putstr_fd("Usage: ./client <PID> <message>\n", 1);
	return (0);
}
