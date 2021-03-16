/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwinter <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 13:58:44 by mwinter           #+#    #+#             */
/*   Updated: 2021/03/15 13:58:45 by mwinter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
** Function set forks id for philosopher
** @param Philosopher structure, left fork id, right fork id
** @return 1 if time function return error, 0 if success
*/

int 		give_forks(t_philo *philosopher, int l_fork, int r_fork)
{
	philosopher->id = l_fork + 1;
	if (!(l_fork % 2))
	{
		philosopher->l_fork = r_fork;
		philosopher->r_fork = l_fork;
	}
	else
	{
		philosopher->l_fork = l_fork;
		philosopher->r_fork = r_fork;
	}
	if ((philosopher->birth = get_birth_time()) == 1)
		return (1);
	philosopher->meal = philosopher->birth;
	return (0);
}

/*
** Set forks id for each philosopher
** @param Structure with program arguments, pointer on philosophers array
** @return 1 if fail, 0 if success
*/

int 		set_forks(t_args *args, t_philo []philosophers)
{
	int i;

	i = 0;
	while (i < args->philo_cnt)
	{
		if ((give_forks(&philosophers[i], i, (i + 1) % args->philo_cnt)))
			return (1);
		i++;
	}
	return (0);
}

/*
** Function initialize mutex array
** @param mutex array, arguments structure
** @return 1 if init is failed, 0 if success
*/

int			init_forks(pthread_mutex_t *forks, t_args *args)
{
	int i;

	i = 0;
	while (i < args->philo_cnt)
	{
		if (pthread_mutex_init(&forks[i], NULL))
			return (print_error("can't mutex init."));
		i++;
	}
	return (0);
}

int			initializate_simulation(t_args *args)
{
	t_philo			philosophers[args->philo_cnt];
	pthread_mutex_t forks[args->philo_cnt];

	if (init_forks(forks, args))
		return (mutex_destroy(forks, args->philo_cnt));
	if (set_forks(forks, args, philosophers))
		return (1);
	args->philosophers = philosophers;
	args->forks = forks;
	return (start_simulation(args));
}