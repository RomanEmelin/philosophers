/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwinter <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 13:58:44 by mwinter           #+#    #+#             */
/*   Updated: 2021/03/21 20:13:52 by mwinter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
** Function initialize each philosopher
** @param program arguments, semaphores
** @return 1 if fail, 0 if success
*/

t_philo		*init_philo(t_args *args, t_semaphore *semaphores)
{
	long	time;
	t_philo	*philo;

	philo = (t_philo *)malloc(sizeof(t_philo));
	if (!philo)
	{
		print_error("can't allocate memory for philosophers.");
		return (NULL);
	}
	philo->pid = (pid_t *)malloc(sizeof(pid_t) * args->philo_cnt);
	if (!philo->pid)
	{
		print_error("can't allocate memory for pids.");
		return (NULL);
	}
	time = get_time();
	philo->start_time = time;
	philo->last_eat = time;
	philo->args = args;
	philo->semaphores = semaphores;
	return (philo);
}

/*
** Function initialize semaphore structure
** @param structure with semaphores, arguments structure
** @return 1 and print error if init is failed, 0 if success
*/

int			init_semaphores(t_semaphore *semaphores, t_args *args)
{
	sem_unlink("forks");
	sem_unlink("print");
	sem_unlink("died");
	semaphores->s_forks = sem_open("forks", O_CREAT, 0644, args->philo_cnt);
	if (semaphores->s_forks == SEM_FAILED)
		return (print_error("can't init forks semaphore."));
	semaphores->s_print = sem_open("print", O_CREAT, 0644, 1);
	if (semaphores->s_print == SEM_FAILED)
		return (print_error("can't init print semaphore"));
	semaphores->s_died = sem_open("died", O_CREAT, 0644, 1);
	if (semaphores->s_died == SEM_FAILED)
		return (print_error("can't init died semaphore"));
	return (0);
}

/*
** Function initialize all needed variables, as an array of philosophers,
** semaphores and etc,
** @param structure with program arguments
** @return 1 if error, 0 if success
*/

int			initializate_simulation(t_args *args)
{
	t_philo			*philosophers;
	t_semaphore 	*sems;

	sems = (t_semaphore *)malloc(sizeof(t_semaphore));
	if (!sems)
		return (print_error("can't allocate memory for semaphores."));
	if (init_semaphores(sems, args))
		return (1);
	philosophers = init_philo(args, sems);
	if (!philosophers)
		return (1);
	if (start_processes(args, philosophers))
		return (1);
	finish_simulation(philosophers, sems);
	return (0);
}