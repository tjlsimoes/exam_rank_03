/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l <tjorge-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:03:31 by tjorge-l          #+#    #+#             */
/*   Updated: 2024/10/15 13:34:07 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	putchar_fd_count(char c, int fd, int count)
{
	write(fd, &c, 1);
	return (++count);
}

int	putbase_fd_count(unsigned int nbr, int fd, char *base, int count)
{
	if (nbr >= 16)
	{
		count = putbase_fd_count(nbr / 16, fd, base, count);
		count = putbase_fd_count(nbr % 16, fd, base, count);
	}
	else
	{
		count = putchar_fd_count(base[nbr], fd, count);
	}
	return (count);
}

int	putnbr_fd_count(long nbr, int fd, int count)
{
	if (nbr < 0)
	{
		write(fd, "-", 1);
		count++;
		nbr *= -1;	
	}
	if (nbr >= 10)
	{
		count = putnbr_fd_count(nbr / 10, fd, count);
		count = putnbr_fd_count(nbr % 10, fd, count);
	}
	else
	{
		count = putchar_fd_count(nbr + 48, fd, count);
	}
	return (count);
}

int	putstr_fd_count(char *str, int fd, int count)
{
	int	i;

	i = 0;
	if (!str)
	{
		write(fd, "(null)", 6);
		count += 6;
		return (count);
	}
	while (str[i])
	{
		count = putchar_fd_count(str[i], fd, count);
		i++;
	}
	return (count);
}

int	specifier_switch(va_list args, char c, int count)
{
	if (c == 's')
		count = putstr_fd_count(va_arg(args, char *), 1, count);
	else if (c == 'd')
		count = putnbr_fd_count(va_arg(args, int), 1, count);
	else if (c == 'x')
		count = putbase_fd_count(va_arg(args, unsigned int), 1,
								"0123456789abcdef", count);
	return (count);
}

int	is_specifier(char c)
{
	if (c == 's' || c == 'd' || c == 'x')
		return (1);
	return (0);
}

int	format_traversal(va_list args, char *format)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (format[i])
	{
		if (format[i] == '%' && is_specifier(format[i + 1]))
		{
			count = specifier_switch(args, format[i + 1], count);
			i += 2;
			continue ;
		}
		else
			count = putchar_fd_count(format[i], 1, count);
		i++;
	}
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int	count;
	
	if (!format)
		return (-1);
	va_start(args, (char *)format);
	count = 0;
	count = format_traversal(args, (char *) format);
	va_end(args);
	return (count);
}

// int	main(void)
// {
// 	// ft_printf("%d\n", ft_printf("Hello!"));
// 	// ft_printf("%d\n", ft_printf(" %s ", "-"));
// 	ft_printf(" %s ", "-");
// }