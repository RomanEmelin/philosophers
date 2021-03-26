/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwinter <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 21:06:11 by mwinter           #+#    #+#             */
/*   Updated: 2021/03/24 15:21:54 by mwinter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
** The function check die philosopher or not
** @param void pointer on philosopher structure
** @return NULL
*/

void	*is_die(void *philo)
{
	t_philo	*p;
	long	t;

	p = philo;
	while (!p->args->died)
	{
		sem_wait(p->args->s_block[p->id - 1]);
		t = get_time() - p->start_time - p->last_eat;
		if (p->args->meal_cnt && !p->full)
			return (print_status(p, FULL, p->start_time));
		else if (t > p->args->time_to_die)
		{
			print_status(p, DIE, p->start_time);
			sem_wait(p->semaphores->s_died);
			p->args->died = DIE;
			sem_post(p->semaphores->s_died);
		}
		sem_post(p->args->s_block[p->id - 1]);
	}
	return (NULL);
}

/*
** The function simulates process of bind resources
** using semaphore
*/

void	eating(t_philo *philo)
{
	sem_wait(philo->semaphores->s_forks);
	sem_wait(philo->semaphores->s_forks);
	print_status(philo, FORK, philo->start_time);
	philo->last_eat = get_time() - philo->start_time;
	sem_wait(philo->args->s_block[philo->id - 1]);
	print_status(philo, EAT, philo->start_time);
	usleep_fix(philo->args->time_to_eat);
	sem_post(philo->args->s_block[philo->id - 1]);
	sem_post(philo->semaphores->s_forks);
	sem_post(philo->semaphores->s_forks);
}

/*
** The function puts the thread to sleep
*/

void	sleeping(t_philo *philo)
{
	print_status(philo, SLEEP, philo->start_time);
	usleep_fix(philo->args->time_to_sleep);
}

/*
** The function simulate simple philosopher life
** and create child thread where check died somebody or not
** @param void pointer to philosopher structure
** @return NULL
*/

void	*simulation(void *philosopher)
{
	t_philo		*philo;
	pthread_t	died;

	philo = philosopher;
	pthread_create(&died, NULL, &is_die, (void *)philo);
	pthread_detach(died);
	while (!philo->args->died)
	{
		eating(philo);
		if (philo->args->meal_cnt)
		{
			philo->full--;
			if (!philo->full)
				break ;
		}
		sleeping(philo);
		print_status(philo, THINK, philo->start_time);
	}
	return (NULL);
}

/*
** Function create and join threads, each philosopher is a thread.
** @param pointer on philosopher array of structures, structure with semaphores
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
		usleep(100);
	}
	i = -1;
	while (++i < args->philo_cnt)
		if (pthread_join(philo[i].thread, NULL))
			return (print_error("%d thread can't join."));
	return (0);
}
