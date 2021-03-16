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
	while (cnt--)
		pthread_mutex_destroy(&forks[cnt]);
	return (1);
}

/*
** Function create timestamp in ms
** @return 1 and print error if gettimeofday return -1 and time if success
*/

long get_birth_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) < 0)
		return(print_error("time error."));
	return ((long)(time.tv_sec * 1000 + time.tv_usec * 0.001));
}