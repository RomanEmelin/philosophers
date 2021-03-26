/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwinter <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 13:58:44 by mwinter           #+#    #+#             */
/*   Updated: 2021/03/26 18:12:37 by mwinter          ###   ########.fr       */
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

	if (!(philo = (t_philo *)malloc(sizeof(t_philo))))
	{
		print_error("can't allocate memory for philosophers.");
		return (NULL);
	}
	if (!(philo->pid = (pid_t *)malloc(sizeof(pid_t) * args->philo_cnt)))
	{
		print_error("can't allocate memory for pids.");
		return (NULL);
	}
	time = get_time();
	philo->start_time = time;
	philo->last_eat = time;
	philo->args = args;
	philo->semaphores = semaphores;
	philo->full = 0;
	philo->fulling = 0;
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
	sem_unlink("full");
	sem_unlink("one die");
	semaphores->s_forks = sem_open("forks", O_CREAT, 0644, args->philo_cnt);
	if (semaphores->s_forks == SEM_FAILED)
		return (print_error("can't init forks semaphore."));
	semaphores->s_print = sem_open("print", O_CREAT, 0644, 1);
	if (semaphores->s_print == SEM_FAILED)
		return (print_error("can't init print semaphore"));
	semaphores->s_died = sem_open("died", O_CREAT, 0644, 0);
	if (semaphores->s_died == SEM_FAILED)
		return (print_error("can't init died semaphore"));
	semaphores->s_full = sem_open("full", O_CREAT, 0644, 0);
	if (semaphores->s_full == SEM_FAILED)
		return (print_error("can't init full semaphore"));
	semaphores->s_one_die = sem_open("one die", O_CREAT, 0644, 0);
	if (semaphores->s_one_die == SEM_FAILED)
		return (print_error("can't init one die semaphore"));
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
	t_semaphore		*sems;

	sems = (t_semaphore *)malloc(sizeof(t_semaphore));
	if (!sems)
		return (print_error("can't allocate memory for semaphores."));
	if (init_semaphores(sems, args))
		return (1);
	philosophers = init_philo(args, sems);
	if (!philosophers)
		return (1);
	if (get_block(philosophers))
		return (print_error("can't open block semaphores."));
	if (start_processes(args, philosophers))
		return (1);
	return (0);
}
