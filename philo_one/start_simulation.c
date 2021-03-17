/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwinter <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 21:06:11 by mwinter           #+#    #+#             */
/*   Updated: 2021/03/16 21:06:13 by mwinter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int g_die = 0;

int		take_forks(pthread_mutex_t *forks ,t_philo *philo)
{
	long time;

	if (pthread_mutex_lock(&forks[philo->l_fork]) ||
			pthread_mutex_lock(&forks[philo->r_fork]))
		return (print_error("mutex can't be locked"));
	if ((time = get_time()) == 1)
		return (1);
	time = time - philo->birth;
	printf("%ld ms %d has taken a fork\n", time, philo->id);
	return (0);
}

int 	die(t_args *args, t_philo *philo)
{
	long t;

	if (philo->limit > args->time_to_die)
	{
		t = get_time() - philo->birth;
		printf("%ld ms %d is die\n", t, philo->id);
		g_die = 1;
		return (1);
	}
	return (0);
}

int	eating(t_args *args, t_philo *philo)
{
	long t;

	t = get_time() - philo->birth;
	printf("%ld ms %d is eating\n", t, philo->id);
	philo->limit = 0;
	usleep(args->time_to_eat * 1000);
	pthread_mutex_unlock(&args->forks[philo->l_fork]);
	pthread_mutex_unlock(&args->forks[philo->r_fork]);
	return (0);
}

int		sleeping(t_args *args, t_philo *philo)
{
	long t;

	if (die(args, philo))
		return (1);
	t = get_time() - philo->birth;
	printf("%ld ms %d is sleeping\n", t, philo->id);
	usleep(args->time_to_sleep * 1000);
	return (0);
}

void	*simulation(void *pntr_on_args)
{
	t_args *args;

	args = (t_args *)pntr_on_args;
	while (1)
	{
		if (die(args, args->philosopher) || g_die)
		{
			return (NULL);
		}
		if (take_forks(args->forks, args->philosopher))
		{
			return (NULL);
		}
		if (eating(args, args->philosopher))
		{
			return (NULL);
		}
		if (sleeping(args,args->philosopher))
		{
			return (NULL);
		}long t = get_time() - args->philosopher->birth;
		printf("%ld ms %d is thinking\n", t, args->philosopher->id);
	}
	return (NULL);
}

/*
** Function create and join threads, each philosopher is a thread.
** @param pointer on philosopher array of structures, array of mutex structures
** 			argument structure
** @return 1 if error, 0 if success
*/

int start_simulation(t_args *args, t_philo *philosophers)
{
	int i;
	pthread_t thread[args->philo_cnt];

	i = 0;
	while (i < args->philo_cnt)
	{
		args->philosopher = &philosophers[i];
		if (pthread_create(&thread[i], NULL, simulation, (void *)args))
			return (print_error("%d thread can't create."));
		i++;
	}
	i = 0;
	while (i < args->philo_cnt)
	{
		if (pthread_join(thread[i], NULL))
			return (print_error("%d thread can't join."));
		i++;
	}
	mutex_destroy(args->forks, args->philo_cnt);
	return (0);
}

