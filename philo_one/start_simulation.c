/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwinter <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 21:06:11 by mwinter           #+#    #+#             */
/*   Updated: 2021/03/16 21:06:13 by mwinter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*simulation(void *pntr_on_args)
{
	t_args *args;

	args = (t_args *)pntr_on_args;
	while (1)
	{
		if (take_forks())
	}
}

/*
** Function create and join threads, each philosopher is a thread.
** @param pointer on philosopher array of structures, array of mutex structures
** 			argument structure
** @return 1 if error, 0 if success
*/

int start_simulation(t_args *args)
{
	int i;
	pthread_t thread[args->philo_cnt];

	i = 0;
	while (i < args->philo_cnt)
	{
		if (pthread_create(&thread[i], NULL, simulation, (void *)args))
			return (print_error("%d thread can't create."));
		i++;
	}
	i = 0;
	while (i < args->philo_cnt)
	{
		if (pthread_join(thread[i], NULL))
			return (print_error("%d thread can't join."));
		i++;
	}
	return (0);
}

