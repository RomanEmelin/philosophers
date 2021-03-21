/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwinter <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 21:06:11 by mwinter           #+#    #+#             */
/*   Updated: 2021/03/21 21:48:42 by mwinter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*is_die(void *philo)
{
	t_philo *p;

	p = philo;
	while (!p->args->died)
	{
		if (get_time() - p->start_time - p->last_eat > p->args->time_to_die)
		{
			print_status(p, DIE, p->start_time);
			pthread_mutex_lock(&p->mutexes->m_died);
			p->args->died = DIE;
			pthread_mutex_unlock(&p->mutexes->m_died);
			break ;
		}
	}
	return (NULL);
}

/*
** The function simulates proccess of bind resources
** using mutex
*/

void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	print_status(philo, FORK, philo->start_time);
	pthread_mutex_lock(philo->r_fork);
	print_status(philo, FORK, philo->start_time);
	print_status(philo, EAT, philo->start_time);
	philo->last_eat = get_time() - philo->start_time;
	usleep(philo->args->time_to_eat * 1000L);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

/*
** The fucntion puts the thread to sleep
*/

void	sleeping(t_philo *philo)
{
	print_status(philo, SLEEP, philo->start_time);
	usleep(philo->args->time_to_sleep * 1000L);
}

/*
** The fucntion simulate simple philosopher life
** and create child thread where check died somebody or not
** @param void pointer to philosopher structure
** @return NULL
*/

void	*simulation(void *philosopher)
{
	t_philo		*philo;
	pthread_t	died;
	int			i;

	philo = philosopher;
	pthread_create(&died, NULL, &is_die, (void *)philo);
	pthread_detach(died);
	if (philo->id % 2)
		usleep(philo->args->time_to_eat * 1000L);
	i = 0;
	while (!philo->args->died)
	{
		eating(philo);
		if (philo->args->meal_cnt)
		{
			i++;
			if (i == philo->args->meal_cnt)
				return (print_status(philo, FULL, philo->start_time));
		}
		sleeping(philo);
		print_status(philo, THINK, philo->start_time);
	}
	return (NULL);
}

/*
** Function create and join threads, each philosopher is a thread.
** @param pointer on philosopher array of structures, array of mutex structures
** 			argument structure
** @return 1 if error, 0 if success
*/

int		start_threads(t_args *args, t_philo *philo)
{
	int			i;

	i = -1;
	while (++i < args->philo_cnt)
	{
		if (pthread_create(&philo[i].thread, NULL, simulation, &philo[i]))
			return (print_error("%d thread can't create."));
		usleep(20);
	}
	i = -1;
	while (++i < args->philo_cnt)
		if (pthread_join(philo[i].thread, NULL))
			return (print_error("%d thread can't join."));
	return (0);
}
