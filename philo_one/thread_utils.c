/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwinter <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 15:53:20 by mwinter           #+#    #+#             */
/*   Updated: 2021/03/21 21:43:33 by mwinter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
** Function destroy mutex and philo, also free allocated memory
** @param Philosophers array, Structure with mutexes array and mutex
*/

void	finish_simulation(t_philo *philo, t_mutexes *mutexes)
{
	int i;

	free(philo);
	i = -1;
	while (++i < philo->args->philo_cnt)
		pthread_mutex_destroy(&mutexes->m_forks[i]);
	pthread_mutex_destroy(&mutexes->m_print);
	pthread_mutex_destroy(&mutexes->m_died);
	free(mutexes->m_forks);
}

/*
** Function create timestamp in ms
** @return current time
*/

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((long)(time.tv_sec * 1000 + time.tv_usec / 1000));
}

/*
** Fucntion print message about philosopher status
** @param philosopher, action flag, program start time
*/

void	*print_status(t_philo *philo, int flag, long start)
{
	long t;

	t = get_time() - start;
	pthread_mutex_lock(&philo->mutexes->m_print);
	if (!philo->args->died)
	{
		if (flag == DIE)
			printf("%ld ms %d died\n", t, philo->id);
		else if (flag == FORK)
			printf("%ld ms %d has taken a fork\n", t, philo->id);
		else if (flag == EAT)
			printf("%ld ms %d is eating\n", t, philo->id);
		else if (flag == SLEEP)
			printf("%ld ms %d is sleeping\n", t, philo->id);
		else if (flag == THINK)
			printf("%ld ms %d is thinking\n", t, philo->id);
		else if (flag == FULL)
			printf("%ld ms %d is full\n", t, philo->id);
	}
	pthread_mutex_unlock(&philo->mutexes->m_print);
	return (NULL);
}
