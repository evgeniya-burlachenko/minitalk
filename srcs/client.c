/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skelly <skelly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 16:57:46 by gjacqual          #+#    #+#             */
/*   Updated: 2021/10/25 13:10:49 by skelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

// int	check_real_pid(int serv_pid)
// {
// 	if (99 < serv_pid && serv_pid < 99999)
// 		return (1);
// 	ft_putstr_fd("Server PID is incorrect or not exist.\n", 1);
// 	return (0);
// }
static int	error_exit(char *error)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(error, 2);
	ft_putchar_fd('\n', 2);
	exit(1);
}
int	ft_bit_decoder(int symbol, int serv_pid)
{	
	int	count;
	//int	sig_answer;

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
		// if (sig_answer != 0)
		// 	error_exit("Signal error\n");
		//usleep(115);
		count /= 2;
		while (!g_sigrecived)
			continue ;
	}
	return (0);
}

// int	bit_sender(char *message, int serv_pid)
// {
// 	int	i;

// 	i = 0;
// 	while (message[i] != '\0')
// 	{
// 		if (ft_bit_decoder(message[i], serv_pid) != 0)
// 		{
// 			ft_putstr_fd("Error: Serv PID is incorrect!\n", 1);
// 			return (0);
// 		}
// 		i++;
// 	}
// 	if (ft_bit_decoder(0, serv_pid) != 1)
// 		return (0);
// 	return (1);
// }

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
		// if (*c == '-')
		// 	c++;
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
	siginfo_t			sig_info;
	int					serv_pid;

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
			sig_info.si_pid = serv_pid;
			int i = 0;
			char *mssg = argv[2];
			while (mssg[i] != '\0')
				ft_bit_decoder(mssg[i++], serv_pid);
			ft_bit_decoder('\0', serv_pid);
	}
	// if (bit_sender(argv[2], serv_pid))
	// 	ft_putstr_fd("Message has been sent\n", 1);
	// else
	// 	ft_putstr_fd("Error: Message has not been sent\n", 1);
	return (0);
	
}
