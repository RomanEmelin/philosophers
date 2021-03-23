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

/*
** The function check die philosopher or not
** @param void pointer on philosopher structure
** @return NULL
*/

void	*is_die(void *philo)
{
	t_philo *p;
	long t;

	p = philo;
	while (!p->args->died)
	{
		t = get_time() - p->start_time - p->last_eat;
		sem_wait(p->s_status);
		if (t > p->args->time_to_die)
		{
			print_status(p, DIE, p->start_time);
			p->args->died = DIE;
			sem_post(p->semaphores->s_died);
			sem_post(p->s_status);
			break ;
		}
		sem_post(p->s_status);
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
	sem_wait(philo->s_status);
	print_status(philo, EAT, philo->start_time);
	usleep(philo->args->time_to_eat * 1000L);
	sem_post(philo->s_status);
	sem_post(philo->semaphores->s_forks);
	sem_post(philo->semaphores->s_forks);
}

/*
** The function puts the thread to sleep
*/

void	sleeping(t_philo *philo)
{
	print_status(philo, SLEEP, philo->start_time);
	usleep(philo->args->time_to_sleep * 1000L);
}

/*
** The function simulate simple philosopher life
** and create child thread where check died somebody or not
** @param void pointer to philosopher structure
** @return NULL
*/

void	*simulation(t_philo *philo)
{
	pthread_t	died;
	int			i;

	pthread_create(&died, NULL, &is_die, (void *)philo);
	pthread_detach(died);
	pthread_create(&died, NULL, &child_state, (void *)philo);
	pthread_detach(died);
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
** Function fork processes, each philosopher is a process.
** @param pointer on philosopher array of structures, structure with semaphores
** @return 1 if error, 0 if success
*/

int		start_processes(t_args *args, t_philo *philo)
{
	int			i;
	pthread_t	die;

	i = -1;
	while (++i < args->philo_cnt)
	{
		printf("here\n");
		philo->pid[i] = fork();
		philo->id = i + 1;
		if (philo->pid[i]== -1)
			return (print_error("can't fork process."));
		if (!philo->pid[i])
		{
			simulation(philo);
			exit(0);
		}
	}
	pthread_create(&die, NULL, &parent_state, philo);
	pthread_join(die, NULL);
	wait_kill(philo);
	return (0);
}
