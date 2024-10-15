/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l <tjorge-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:03:55 by tjorge-l          #+#    #+#             */
/*   Updated: 2024/10/15 13:20:17 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>

int	putchar_fd_count(char c, int fd, int count);
int	putbase_fd_count(unsigned int nbr, int fd, char *base, int count);
int	putnbr_fd_count(long nbr, int fd, int count);
int	putstr_fd_count(char *str, int fd, int count);
int	specifier_switch(va_list args, char c, int count);
int	is_specifier(char c);
int	format_traversal(va_list args, char *format);
int	ft_printf(const char *format, ...);