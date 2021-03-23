/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwinter <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 14:54:21 by mwinter           #+#    #+#             */
/*   Updated: 2021/03/21 20:03:13 by mwinter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
** The function prints the error to the second fd
** @param String with error text
** @return 1
*/

int		print_error(char *str)
{
	write(2, "Error: ", 7);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	return (1);
}

/*
** The function check integer overflow
*/

int		integer_overflow_checker(long var[5], char **av)
{
	if ((var[0] = ft_atoi(av[1])) == LONG_MAX ||
			(var[1] = ft_atoi(av[2])) == LONG_MAX ||
			(var[2] = ft_atoi(av[3])) == LONG_MAX ||
			(var[3] = ft_atoi(av[4])) == LONG_MAX)
		return (1);
	return (0);
}
