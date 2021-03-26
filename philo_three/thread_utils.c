/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwinter <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 15:53:20 by mwinter           #+#    #+#             */
/*   Updated: 2021/03/26 18:11:45 by mwinter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
** Function destroy semaphores and philo, also free allocated memory
** @param Philosopher structure, Structure with semaphores
*/

void	finish_simulation(t_philo *philo, t_semaphore *sems)
{
	close_block(philo);
	sem_unlink("print");
	sem_unlink("died");
	sem_unlink("forks");
	sem_unlink("full");
	sem_unlink("one_die");
	sem_close(sems->s_one_die);
	sem_close(sems->s_forks);
	sem_close(sems->s_died);
	sem_close(sems->s_print);
	sem_close(sems->s_full);
	free(sems);
	free(philo->pid);
	free(philo);
}

/*
** Function create timestamp in ms
** @return current time
*/

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((long)(time.tv_sec * 1000 + time.tv_usec / 1000));
}

/*
** Function print message about philosopher status
** @param philosopher, action flag, program start time
*/

void	*print_status(t_philo *philo, int flag, long start)
{
	long t;

	t = get_time() - start;
	sem_wait(philo->semaphores->s_print);
	if (!philo->args->died)
	{
		if (flag == DIE)
		{
			sem_close(philo->semaphores->s_print);
			printing(" died\n", t, philo->id);
			return (NULL);
		}
		else if (flag == FORK)
			printing(" has taken a fork\n", t, philo->id);
		else if (flag == EAT)
			printing(" is eating\n", t, philo->id);
		else if (flag == SLEEP)
			printing(" is sleeping\n", t, philo->id);
		else if (flag == THINK)
			printing(" is thinking\n", t, philo->id);
		else if (flag == FULL)
			printing(" is full\n", t, philo->id);
	}
	sem_post(philo->semaphores->s_print);
	return (NULL);
}

void	printing(char *str, long time, int id)
{
	ft_putnbr_fd(time, 1);
	write(1, " ms ", 4);
	ft_putnbr_fd(id, 1);
	write(1, str, ft_strlen(str));
}

void usleep_fix(long time)
{
	long t;

	t = get_time();
	while (get_time() - t < time)
		usleep(1);
}