/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttangcha <ttangcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:13:32 by ttangcha          #+#    #+#             */
/*   Updated: 2025/02/26 01:52:13 by ttangcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "libft.h"

volatile sig_atomic_t	g_get_flag = 0;

void	handle_signal(int signum)
{
	(void)signum;
	g_get_flag = 1;
}

void	ft_error(char *str)
{
	ft_putstr_fd(str, 1);
	exit(0);
}

void	send_byte(int pid, unsigned char ch)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		g_get_flag = 0;
		if ((ch >> i) & 1)
		{
			if (kill(pid, SIGUSR2) == -1)
				ft_error("Error: cant send SIGUSR2 to server.\n");
		}
		else
		{
			if (kill(pid, SIGUSR1) == -1)
				ft_error("Error: cant send SIGUSR1 to server.\n");
		}
		while (!g_get_flag)
		{
		}
		i--;
	}
}

void	send_message(int pid, char *message)
{
	int	i;

	i = 0;
	while (message[i])
	{
		send_byte(pid, message[i]);
		i++;
	}
	send_byte(pid, '\0');
}

int	main(int ac, char **av)
{
	int	server_pid;

	signal(SIGUSR1, handle_signal);
	if (ac == 3)
	{
		server_pid = ft_atoi(av[1]);
		if (server_pid <= 0)
			ft_error("Error: invalid PID\n");
		if (av[2][0] == 0)
			ft_error("Error: message is empty\n");
		send_message(server_pid, av[2]);
		ft_putstr_fd("Message sent to PID: ", 1);
		ft_putnbr_fd(server_pid, 1);
		ft_putstr_fd("\n", 1);
	}
	else
		ft_error("Usage: ./client <PID> <message>\n");
	return (0);
}
