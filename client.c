/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 13:17:37 by welow             #+#    #+#             */
/*   Updated: 2024/02/26 13:56:33 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	send_char_to_bit(pid_t pid, char c)
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
	int		pid;
	int		i;
	char	*arg;

	if (ac <= 2)
	{
		return (ft_printf("wrong argument\n"));
	}
	i = 2;
	pid = ft_atoi(av[1]);
	while (av[i] != NULL)
	{
		arg = av[i];
		while (*arg)
		{
			send_char_to_bit(pid, *arg++);
		}
		if (av[i + 1] != NULL)
			send_char_to_bit(pid, ' ');
		i++;
	}
	send_char_to_bit(pid, '\n');
	return (0);
}
