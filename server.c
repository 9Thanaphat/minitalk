/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttangcha <ttangcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:13:37 by ttangcha          #+#    #+#             */
/*   Updated: 2025/02/03 14:15:37 by ttangcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include "libft.h"

static void	get_bit(int sig)
{
	static int				i = 0;
	static unsigned char	ch = 0;
	int						bit;

	if (sig == SIGUSR1)
		bit = 0;
	else if (sig == SIGUSR2)
		bit = 1;
	ch = (ch << 1) | (bit & 1);
	if (++i == 8)
	{
		if (ch == 0)
		{
			i = 0;
			return ;
		}
		write(1, &ch, 1);
		i = 0;
	}
}

int	main(void)
{
	signal(SIGUSR1, get_bit);
	signal(SIGUSR2, get_bit);
	ft_putstr_fd("Server PID : ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putstr_fd("\n", 1);
	while (1)
		pause();
	return (0);
}
