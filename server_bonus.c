/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 13:17:23 by welow             #+#    #+#             */
/*   Updated: 2024/01/31 15:35:48 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/*
	info->si_pid : client pid
*/
void	signal_handler(int signum, siginfo_t *info, void *context)
{
	static int	i;
	static int	bit;

	(void)context;
	if (signum == SIGUSR1)
		i |= (0x01 << bit);
	bit++;
	if (bit == 8)
	{
		ft_printf("%c", i);
		bit = 0;
		i = 0;
		kill(info->si_pid, SIGUSR1);
	}
}

/*
	use sa_sigaction because we need to config the handler
*/
int	main(int ac, char **av)
{
	struct sigaction	sig;

	(void)av;
	if (ac != 1)
		ft_printf("Wrong argument\n");
	ft_printf("Server id: %d\n", getpid());
	sig.sa_sigaction = signal_handler;
	while (ac == 1)
	{
		sigaction(SIGUSR1, &sig, NULL);
		sigaction(SIGUSR2, &sig, NULL);
		pause();
	}
	return (0);
}
