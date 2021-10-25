/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skelly <skelly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 13:17:30 by skelly            #+#    #+#             */
/*   Updated: 2021/10/26 00:52:11 by skelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk_bonus.h"

int	ft_bit_decoder(int symbol, int serv_pid)
{	
	int	count;

	count = 128;
	while (count > 0)
	{
		g_sigrecived = 0;
		if (symbol & count)
		{
			if(kill(serv_pid, SIGUSR1) == -1)
			error_exit("Signal error1\n");
		}
		else
		{
			if(kill(serv_pid, SIGUSR2) == -1)
			error_exit("Signal error2\n");
		}
		count/= 2;
		while (!g_sigrecived);
	}
	return (0);
}

void	ft_server_signal_handler(int sig_nb, siginfo_t *sig_info, void *context)
{
	(void)sig_info;
	(void)context;
	if (sig_nb == SIGUSR1)
	{
		ft_putstr_fd("Message was received!\n", 1);
		exit(0);
	}
	if (sig_nb == SIGUSR2)
	{	
		g_sigrecived = 1;
	}
}

static void	ft_isdigit_2(char *c)
{
	if (c)
	{
		while (*c)
		{
			if (*c > '9' || *c < '0')
				error_exit("\x1b[1;30;41mERROR: INVALID PID\x1b[0m");
			c++;
		}	
	}
}
int	main(int argc, char **argv)
{
	struct sigaction	serv_act;
	pid_t				serv_pid;
	int				 	i;

	if (argc != 3)
		ft_putstr_fd("Please enter a correct PID and message after.\n", 1);
	else
	{
		ft_isdigit_2(argv[1]);
		serv_pid = ft_atoi(argv[1]);
		serv_act.sa_flags = SA_SIGINFO;
		serv_act.sa_sigaction = &ft_server_signal_handler;
		sigaction(SIGUSR1, &serv_act, 0);
		sigaction(SIGUSR2, &serv_act, 0);
		i = 0;
		char *mssg = argv[2];
		while (mssg[i] != '\0')
			ft_bit_decoder(mssg[i++], serv_pid);
		ft_bit_decoder('\0', serv_pid);
	}
	return (0);
}
