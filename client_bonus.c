/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 13:17:37 by welow             #+#    #+#             */
/*   Updated: 2024/01/31 15:37:44 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/*
	signum refer to SIGUSR1 or SIGUSR2
*/
void	message(int signum)
{
	if (signum == SIGUSR1)
		ft_printf("message received\n");
	else
		ft_printf("message received\n");
}

void	send_char_to_bit(pid_t pid, char c)
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
	int	pid;
	int	i;

	if (ac != 3)
		ft_printf("wrong argument\n");
	i = 0;
	pid = ft_atoi(av[1]);
	while (av[2][i] != '\0')
	{
		signal(SIGUSR1, message);
		signal(SIGUSR2, message);
		send_char_to_bit(pid, av[2][i]);
		i++;
	}
	send_char_to_bit(pid, '\n');
	return (0);
}
