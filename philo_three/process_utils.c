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

void *parent_state(void *p)
{
	t_philo *philo;

	philo = p;
	sem_wait(philo->semaphores->s_died);
	philo->args->died = 1;
	return (NULL);
}

void *child_state(void *p)
{
	t_philo *philo;

	philo = p;
	sem_wait(philo->semaphores->s_died);
	philo->args->died = 1;
	sem_post(philo->semaphores->s_died);
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