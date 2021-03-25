/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwinter <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 16:00:42 by mwinter           #+#    #+#             */
/*   Updated: 2021/03/24 15:22:46 by mwinter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
** The function will check if a character is a digit
** @param character to check
** @return true if is digit or false if isn't
*/

int		is_digit(char c)
{
	return ('0' <= c && c <= '9');
}

/*
** The function check string length
** @param string
** @return string length
*/

int		ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

/*
** The function makes an integer from a string
** @param a string
** @return an integer from a string
*/

long	ft_atoi(char *str)
{
	int		n;
	long	res;

	n = 1;
	res = 0;
	while (IS_SPACE(*str))
		str++;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			n = -1;
	while ('0' <= *str && *str <= '9')
		if ((res = (res * 10) + (*str++ - '0')) > INT_MAX ||
				res < INT_MIN)
			return (LONG_MAX);
	return (res * n);
}
