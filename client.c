/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 13:17:37 by welow             #+#    #+#             */
/*   Updated: 2024/01/31 14:15:25 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_char_to_bit(pid_t pid, char c)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		if (c & (0x01 << bit))
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(100);
		bit++;
	}
}

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
		send_char_to_bit(pid, av[2][i++]);
	}
	send_char_to_bit(pid, '\n');
	return (0);
}
