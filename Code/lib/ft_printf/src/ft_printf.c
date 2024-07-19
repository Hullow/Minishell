/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 15:27:06 by fallan            #+#    #+#             */
/*   Updated: 2024/07/19 15:15:00 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static int	ft_print_formatted_output(const char format_specifier, va_list ap)
{
	int					res;

	res = 0;
	if (format_specifier == 'd' || format_specifier == 'i')
		res += ft_putnbr(va_arg(ap, int), 0);
	if (format_specifier == 'u')
		res += ft_putnbr_unsigned(va_arg(ap, unsigned int), res);
	if (format_specifier == 'c')
		res += ft_putchar(va_arg(ap, int));
	if (format_specifier == 's')
		res += ft_print_string(va_arg(ap, char *));
	if (format_specifier == 'p')
		res += ft_print_pointer(va_arg(ap, unsigned long long));
	if (format_specifier == '%')
		res += write(1, "%", 1);
	if (format_specifier == 'X' || format_specifier == 'x')
		res += ft_hex(va_arg(ap, unsigned int), format_specifier);
	return (res);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	int		res;
	va_list	ap;

	va_start(ap, format);
	i = 0;
	res = 0;
	while (format[i])
	{
		if (format[i] == '%')
			res += ft_print_formatted_output(format[++i], ap);
		else
		{
			ft_putchar(format[i]);
			res++;
		}
		i++;
	}
	va_end(ap);
	return (res);
}
