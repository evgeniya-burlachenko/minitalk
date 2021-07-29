#include "../includes/server_bonus.h"

void	ft_signal(int sig, siginfo_t *info, void *ucontext)
{
	static int	ch;
	static int	counter;

	(void)ucontext;
	if (!counter)
		counter = 128;
	if (sig == SIGUSR1)
		ch += counter;
	counter /= 2;
	if (counter == 0)
	{
		if (ch == '\0')
		{
			if (info->si_pid != 0)
			{
				if (kill(info->si_pid, SIGUSR1) == -1)
					error_exit("Error");
			}
			ft_putchar_fd('\n', 1);
		}
		ft_putchar_fd((char)ch, 1);
		counter = 128;
		ch = 0;
	}	
}

int	main(int argc, char **argv)
{
	pid_t				pid;
	struct sigaction	sa;

	(void)argv;
	pid = getpid();
	if (argc != 1)
		error_exit("bad arguments");
	ft_putstr_fd("PID: ", 1);
	ft_putnbr_fd(pid, 1);
	ft_putchar_fd('\n', 1);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = ft_signal;
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		error_exit("Invalid value");
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
		error_exit("Invalid value");
	while (1)
		pause();
	return (0);
}
