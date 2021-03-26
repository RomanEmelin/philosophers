/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphore_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwinter <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 14:03:24 by mwinter           #+#    #+#             */
/*   Updated: 2021/03/26 18:18:07 by mwinter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
** Function create name for semaphore
** @param number of char in semaphore name
** @return name of semaphore
*/

char		*get_name(int i)
{
	char	*name;
	int		k;

	if (!(name = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	k = 0;
	while (k < i)
		name[k++] = 'x';
	name[k] = '\0';
	return (name);
}

/*
** Function create semaphores array
** @param structure with semaphores array
** @return 1 if error, 0 if success
*/

int			get_block(t_philo *philo)
{
	int		i;
	char	*name;

	philo->s_block = (sem_t **)malloc(sizeof(sem_t *) * philo->args->philo_cnt);
	if (!philo->s_block)
		return (1);
	i = -1;
	while (++i < philo->args->philo_cnt)
	{
		if (!(name = get_name(i + 1)))
			return (1);
		sem_unlink(name);
		philo->s_block[i] = sem_open(name, O_CREAT, 0644, 1);
		if (philo->s_block[i] == SEM_FAILED)
			return (1);
		free(name);
	}
	return (0);
}

/*
** Function close semaphores array
** @param structure with semaphores array
*/

void		close_block(t_philo *philo)
{
	int		i;
	char	*name;

	i = -1;
	while (++i < philo->args->philo_cnt)
	{
		name = get_name(i + 1);
		sem_unlink(name);
		sem_close(philo->s_block[i]);
		free(name);
	}
	free(philo->s_block);
}
