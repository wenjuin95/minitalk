/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 13:17:23 by welow             #+#    #+#             */
/*   Updated: 2024/02/25 00:27:43 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/*
*	info->si_pid contains the sender's pid
*	bit is used to keep track of the current bit in the byte (8 bits in a byte)
*	0x01 is 0000 0001
*	[|] is a bitwise OR operator
*	[<<] is a bitwise left shift operator
*/
static void	signal_handler(int signum, siginfo_t *info, void *context)
{
	static int	i;
	static int	bit;

	(void)context;
	if (signum == SIGUSR1)
		i = i | (0x01 << bit);
	bit++;
	if (bit == 8)
	{
		ft_printf("%c", i);
		kill(info->si_pid, SIGUSR1);
		bit = 0;
		i = 0;
	}
}

/*
*	use sa_sigaction because of siginfo_t (siginfo_t contains the sender's pid)
*	use sa_flags = SA_SIGINFO to use sa_sigaction because sa_handler is default
*	we can't use sa_handler because it doesn't take siginfo_t as an argument
*/
int	main(int ac, char **av)
{
	struct sigaction	sig;

	(void)av;
	if (ac != 1)
		ft_printf("Wrong argument\n");
	ft_printf("Server id: %d\n", getpid());
	sig.sa_sigaction = signal_handler;
	sig.sa_flags = SA_SIGINFO;
	while (ac == 1)
	{
		sigaction(SIGUSR1, &sig, NULL);
		sigaction(SIGUSR2, &sig, NULL);
		pause();
	}
	return (0);
}
