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
** @param programm arguments, mutexes
** @return 1 if fail, 0 if success
*/

t_philo		*init_philo(t_args *args, t_mutexes *mutexes)
{
	int		i;
	long	time;
	t_philo	*philo;

	i = -1;
	time = get_time();
	philo = (t_philo *)malloc(sizeof(t_philo) * args->philo_cnt);
	if (!philo)
	{
		print_error("can't allocate memory for philosophers.");
		return (NULL);
	}
	while (++i < args->philo_cnt)
	{
		philo[i].id = i + 1;
		philo[i].l_fork = &mutexes->m_forks[i];
		philo[i].r_fork = &mutexes->m_forks[(i + 1) % args->philo_cnt];
		philo[i].start_time = time;
		philo[i].last_eat = 0;
		philo[i].args = args;
		philo[i].mutexes = mutexes;
		pthread_mutex_init(&philo[i].m_status, NULL);
	}
	return (philo);
}

/*
** Function initialize mutex structure
** @param structure with mutex array, arguments structure
** @return 1 and print error if init is failed, 0 if success
*/

int			init_mutexes(t_mutexes *mutexes, t_args *args)
{
	int i;

	mutexes->m_forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* args->philo_cnt);
	if (!mutexes->m_forks)
		return (print_error("can't allocate memory for forks array."));
	i = -1;
	while (++i < args->philo_cnt)
		if (pthread_mutex_init(&mutexes->m_forks[i], NULL))
			return (print_error("can't initialize fork mutex."));
	if (pthread_mutex_init(&mutexes->m_died, NULL))
		return (print_error("can't initialize m_died mutex."));
	if (pthread_mutex_init(&mutexes->m_print, NULL))
		return (print_error("can't initialize m_print mutex."));
	return (0);
}

/*
** Function initialize all needed variables, as an array of philosophers,
** mutexes and etc,
** @param structure with programm arguments
** @return 1 if error, 0 if success
*/

int			initializate_simulation(t_args *args)
{
	t_philo			*philosophers;
	t_mutexes		*mutexes;

	mutexes = (t_mutexes *)malloc(sizeof(t_mutexes));
	if (!mutexes)
		return (print_error("can't allocate memory for mutexes."));
	if (init_mutexes(mutexes, args))
		return (1);
	philosophers = init_philo(args, mutexes);
	if (!philosophers)
		return (1);
	if (start_threads(args, philosophers))
		return (1);
	finish_simulation(philosophers, mutexes);
	return (0);
}
