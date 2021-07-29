#include "../includes/client.h"

int	send(pid_t pid, char c)
{
	int	i;

	i = 128;
	while (i > 0)
	{
		if (c & i)
		{
			if (kill(pid, SIGUSR1) == -1)
				error_exit("Signal error\n");
		}
		else
		{
			if (kill(pid, SIGUSR2) == -1)
				error_exit("Signal error\n");
		}
		usleep(100);
		i /= 2;
	}
	return (0);
}

static void	ft_isdigit(char *c)
{
	if (c)
	{
		if (*c == '-')
			c++;
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
	pid_t	pid;
	char	*mssg;
	int		i;

	if (argc != 3)
		error_exit("bad arguments");
	ft_isdigit(argv[1]);
	pid = ft_atoi(argv[1]);
	mssg = argv[2];
	i = 0;
	while (mssg[i] != '\0')
		send(pid, mssg[i++]);
	send(pid, mssg[i]);
	return (0);
}
