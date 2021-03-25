/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwinter <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 18:36:11 by mwinter           #+#    #+#             */
/*   Updated: 2021/03/23 18:36:13 by mwinter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void *is_full(void *philo)
{
	t_philo *p;

	p = philo;
	while(!p->args->died)
	{
		sem_wait(p->semaphores->s_full);
		p->args->full++;
		if (p->args->full == p->args->philo_cnt)
		{
			sem_post(p->semaphores->s_died);
			return (NULL);
		}
	}
	return (NULL);
}

void *is_die(void *p)
{
	t_philo *philo;

	philo = p;
	sem_wait(philo->semaphores->s_died);
	philo->args->died = DIE;
	return (NULL);
}

void *somebody_die(void *p)
{
	t_philo *philo;

	philo = p;

	sem_wait(philo->semaphores->s_one_die);
	philo->args->died = DIE;
	sem_wait(philo->semaphores->s_one_die);
	return (NULL);
}

void	wait_kill(t_philo *philo)
{
	int i;

	i = -1;
	waitpid(-1, NULL, 0);
	while (++i < philo->args->philo_cnt)
		kill(philo->pid[i], SIGTERM);
}