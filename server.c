/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttangcha <ttangcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:13:37 by ttangcha          #+#    #+#             */
/*   Updated: 2025/02/23 17:47:46 by ttangcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "libft.h"

void	get_byte(int sig, siginfo_t *info, void *ucontext)
{
	static int				i = 0;
	static unsigned char	ch = 0;
	int						bit;

	bit = 0;
	(void)ucontext;
	if (sig == SIGUSR1)
		bit = 0;
	else if (sig == SIGUSR2)
		bit = 1;
	ch = (ch << 1) | bit;
	i++;
	if (i == 8)
	{
		if (ch == 0)
			write(1, "\n", 1);
		else
			write(1, &ch, 1);
		i = 0;
		ch = 0;
	}
	if (kill(info->si_pid, SIGUSR1) == -1)
		ft_putstr_fd("Error: cant send SIGUSR1 to client.\n", 1);
}

int	main(void)
{
	int					pid;
	struct sigaction	sa;

	sa.sa_sigaction = get_byte;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	pid = getpid();
	ft_putstr_fd("Server PID : ", 1);
	ft_putnbr_fd(pid, 1);
	ft_putstr_fd("\n", 1);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
	{
		pause();
	}
	return (0);
}
