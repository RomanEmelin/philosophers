/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwinter <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 15:53:20 by mwinter           #+#    #+#             */
/*   Updated: 2021/03/24 15:23:27 by mwinter          ###   ########.fr       */
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

	i = -1;
	while (++i < philo->args->philo_cnt)
		pthread_mutex_destroy(&philo[i].m_status);
	i = -1;
	while (++i < philo->args->philo_cnt)
		pthread_mutex_destroy(&mutexes->m_forks[i]);
	free(philo);
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
** Function print message about philosopher status
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
			printing(" died\n", t, philo->id);
		else if (flag == FORK)
			printing(" has taken a fork\n", t, philo->id);
		else if (flag == EAT)
			printing(" is eating\n", t, philo->id);
		else if (flag == SLEEP)
			printing(" is sleeping\n", t, philo->id);
		else if (flag == THINK)
			printing(" is thinking\n", t, philo->id);
		else if (flag == FULL)
			printing(" is full\n", t, philo->id);
	}
	pthread_mutex_unlock(&philo->mutexes->m_print);
	return (NULL);
}

void	printing(char *str, long time, int id)
{
	ft_putnbr_fd(time, 1);
	write(1, " ms ", 4);
	ft_putnbr_fd(id, 1);
	write(1, str, ft_strlen(str));
}

void usleep_fix(long time)
{
	long t;

	t = get_time();
	while (get_time() - t < time)
		usleep(1);
}
