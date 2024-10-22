#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>

int	putchar_fd_count(char c, int fd, int count)
{
	write(fd, &c, 1);
	return (++count);
}

int	putstr_fd_count(char *str, int fd, int count)
{
	int	i;

	if (!str)
		return (count);
	i = 0;
	while (str[i])
	{
		count = putchar_fd_count(str[i], 1, count);
		i++;
	}
	return (count);
}

int	putnbr_fd_count(int nbr, int fd, int count)
{
	long	nbr_ll;
	nbr_ll = (long)nbr;

	if (nbr_ll < 0)
	{
		count = putchar_fd_count('-', 1, count);
		nbr_ll *= -1;
	}
	if (nbr_ll > 10)
	{
		count = putnbr_fd_count(nbr_ll / 10, 1, count);
		count = putnbr_fd_count(nbr_ll % 10, 1, count);
	}
	else
		count = putchar_fd_count(nbr_ll + 48, 1, count);
	return (count);
}

int	puthex_fd_count(unsigned int nbr, char *base, int fd, int count)
{
	if (nbr > 16)
	{
		count = puthex_fd_count(nbr / 16, base, 1, count);
		count = puthex_fd_count(nbr % 16, base, 1, count);
	}
	else
		count = putchar_fd_count(base[nbr], 1, count);
	return (count);
}

int	specifier_switch(char *str, char c, va_list args, int count)
{
	if (c == 'd')
		count = putnbr_fd_count(va_arg(args, int), 1, count);
	else if (c == 's')
		count = putstr_fd_count(va_arg(args, char *), 1, count);
	else if (c == 'x')
		count = puthex_fd_count(va_arg(args, unsigned int), "0123456789abcdef", 1 , count);
	return (count);
}

int	format_traversal(char *format, va_list args)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (format[i])
	{
		if (format[i] == '%' && is_specifier(format[i + 1]))
		{
			count = specifier_switch(format, format[i + 1], args, count);
			i += 2;
			continue ;
		}
		else
			 count = putchar_fd_count(format[i], 1, count);
		i++;
	}
	return (count);
}

int	ft_printf(char *format, ...)
{
	int	i;

	i = 0;
	va_list args;
	if (!format)
		return (-1);
	va_start(args, format);
	i = format_traversal(format, args);
	va_end(args);
	return (i);
}