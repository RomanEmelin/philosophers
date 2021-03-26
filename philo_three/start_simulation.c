/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwinter <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 21:06:11 by mwinter           #+#    #+#             */
/*   Updated: 2021/03/26 18:15:06 by mwinter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
** The function check die philosopher or full
** @param void pointer on philosopher structure
** @return NULL
*/

void	*state_process(void *philo)
{
	t_philo	*p;
	long	t;

	p = philo;
	while (!p->args->died && !p->full)
	{
		sem_wait(p->s_block[p->id - 1]);
		t = get_time() - p->start_time - p->last_eat;
		if (p->args->meal_cnt && p->fulling == p->args->meal_cnt)
		{
			p->full = 1;
			print_status(p, FULL, p->start_time);
			sem_post(p->semaphores->s_full);
		}
		else if (t > p->args->time_to_die)
		{
			print_status(p, DIE, p->start_time);
			p->args->died = DIE;
			sem_post(p->semaphores->s_one_die);
			sem_post(p->semaphores->s_died);
		}
		sem_post(p->s_block[p->id - 1]);
	}
	return (NULL);
}

/*
** The function simulates process of bind resources
** using semaphores
*/

void	eating(t_philo *philo)
{
	sem_wait(philo->semaphores->s_forks);
	sem_wait(philo->semaphores->s_forks);
	print_status(philo, FORK, philo->start_time);
	sem_wait(philo->s_block[philo->id - 1]);
	philo->last_eat = get_time() - philo->start_time;
	print_status(philo, EAT, philo->start_time);
	usleep_fix(philo->args->time_to_eat);
	sem_post(philo->s_block[philo->id - 1]);
	sem_post(philo->semaphores->s_forks);
	sem_post(philo->semaphores->s_forks);
	if (philo->args->meal_cnt)
		philo->fulling++;
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

void	simulation(t_philo *philo)
{
	pthread_t	state;
	pthread_t	die;

	pthread_create(&state, NULL, &state_process, (void *)philo);
	pthread_detach(state);
	pthread_create(&die, NULL, &somebody_die, (void *)philo);
	pthread_detach(die);
	while (!philo->args->died && !philo->full)
	{
		eating(philo);
		if (philo->args->meal_cnt && philo->fulling == philo->args->meal_cnt)
		{
			usleep_fix(1);
			continue ;
		}
		sleeping(philo);
		print_status(philo, THINK, philo->start_time);
	}
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
	pthread_t	full;

	i = -1;
	while (++i < args->philo_cnt)
	{
		if ((philo->pid[i] = fork()) == -1)
			return (print_error("can't create process."));
		else if (philo->pid[i] == 0)
		{
			philo->id = i + 1;
			simulation(philo);
			exit(0);
		}
	}
	pthread_create(&die, NULL, &is_die, philo);
	if (philo->args->meal_cnt)
	{
		pthread_create(&full, NULL, &is_full, philo);
		pthread_join(full, NULL);
	}
	pthread_join(die, NULL);
	return (0);
}
