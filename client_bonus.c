/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 13:17:37 by welow             #+#    #+#             */
/*   Updated: 2024/02/25 00:39:02 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/*
	signum refer to SIGUSR1 or SIGUSR2
*/
static void	message(int signum)
{
	if (signum == SIGUSR1)
		ft_printf("char received\n");
}

static void	send_char_to_bit(pid_t pid, char c)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		if ((c & (0x01 << bit)) != 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(1000);
		bit++;
	}
}

/*
	get the signal from the server after they print out and excute message
*/
int	main(int ac, char **av)
{
	int		pid;
	int		i;
	char	*arg;

	if (ac <= 2)
		ft_printf("wrong argument\n");
	i = 2;
	pid = ft_atoi(av[1]);
	while (av[i] != NULL)
	{
		arg = av[i];
		while (*arg)
		{
			signal(SIGUSR1, message);
			signal(SIGUSR2, message);
			send_char_to_bit(pid, *arg++);
		}
		if (av[i + 1] != NULL)
			send_char_to_bit(pid, ' ');
		i++;
	}
	send_char_to_bit(pid, '\n');
	return (0);
}
