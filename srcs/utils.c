/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skelly <skelly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 13:18:09 by skelly            #+#    #+#             */
/*   Updated: 2021/10/25 13:21:24 by skelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
}

int	ft_atoi(const char *str)
{
	int				sign;
	unsigned long	r;

	r = 0;
	sign = 1;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
	{
		sign = -1;
	}
	if (*str == '+' || *str == '-')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		if (r > LONG_MAX && (sign == 1))
			return (-1);
		if (r > LONG_MAX && (sign == -1))
			return (0);
		r = r * 10 + *str - '0';
		str++;
	}
	return (sign * (int)r);
}

void	ft_putnbr_fd(int n, int fd)
{
	char	c;

	if (n < 0)
	{	
		if (n == -2147483648)
			ft_putstr_fd("-2147483648", fd);
		else
		{
			n = -n;
			ft_putchar_fd('-', fd);
			ft_putnbr_fd(n, fd);
		}
	}
	else if (n >= 10)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
	else
	{
		c = n + 48;
		ft_putchar_fd(c, fd);
	}
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}
