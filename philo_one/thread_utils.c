/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwinter <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 15:53:20 by mwinter           #+#    #+#             */
/*   Updated: 2021/03/15 15:53:23 by mwinter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
** Function destroy mutex if mutex_init failed
** @param forks array, forks count
** @return 1
*/

int mutex_destroy(pthread_mutex_t *forks, int cnt)
{
	while (cnt)
		pthread_mutex_destroy(&forks[cnt--]);
	return (1);
}