/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwinter <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 13:53:17 by mwinter           #+#    #+#             */
/*   Updated: 2021/03/26 18:09:40 by mwinter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_isnegativ(int n)
{
	if (n < 0)
		return (n *= -1);
	return (n);
}

static void	ft_recursion(int n, int fd)
{
	if (!n)
		return ;
	ft_recursion(n / 10, fd);
	n = ft_isnegativ(n % 10) + 48;
	write(fd, &n, 1);
}

void		ft_putnbr_fd(int n, int fd)
{
	if (!n)
	{
		write(fd, "0", 1);
		return ;
	}
	else
	{
		if (n < 0)
			write(fd, "-", 1);
		ft_recursion(n, fd);
	}
}
