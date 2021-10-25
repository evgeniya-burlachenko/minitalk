/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skelly <skelly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 13:17:38 by skelly            #+#    #+#             */
/*   Updated: 2021/10/26 00:47:38 by skelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk_bonus.h"

void	ft_signal_handler(int sig_nb, siginfo_t *sig_info, void *context)
{
	static int					count;
	static unsigned char		symbol;
	static pid_t				cli_pid;

	 (void)context;
	if (cli_pid == 0)
		cli_pid = sig_info->si_pid;
	if (!count)
		count= 128;	
	if (sig_nb == SIGUSR1)
		symbol += count;
	count /= 2;
	if (count == 0)
	{
		if (symbol == '\0')
		{
				ft_putchar_fd('\n', 1);
				kill(cli_pid, SIGUSR1);
				cli_pid = 0;
				return ;
		}
		ft_putchar_fd(symbol, 1);
		count = 128;
		symbol = 0;
	}
	if (kill(cli_pid, SIGUSR2) != 0)
		ft_putstr_fd("Signal error!\n", 1);
}

void	ft_putpid(void)
{
	int	pid;

	pid = getpid();
	ft_putstr_fd("Server PID: <<", 1);
	ft_putnbr_fd(pid, 1);
	ft_putstr_fd(">>\n", 1);
}

int	main(int argc, char **argv)
{
	struct sigaction	action;
	
	(void)argv;
	ft_putpid();
	if (argc != 1)
		error_exit("Please enter ./client ");
	action.sa_flags = SA_SIGINFO;
	action.sa_sigaction = ft_signal_handler;
	if (sigaction(SIGUSR1, &action, 0) == -1)
		error_exit("Signal error!\n");
	if (sigaction(SIGUSR2, &action, 0) == -1)
		error_exit("Signal error!\n");
	ft_putstr_fd("The server has started successfully\n", 1);
	while (1)
		pause();
	return (0);
}
