/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwinter <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 15:57:15 by mwinter           #+#    #+#             */
/*   Updated: 2021/03/14 15:57:19 by mwinter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PHILOSOPHERS_PHILOSOPHERS_H
# define PHILOSOPHERS_PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <limits.h>

/*
** Little macros to find out if it space or not
** @param char x
** @return true or false
*/
# define IS_SPACE(x) (x == ' ' || x == '\t' || x == '\n' || x == '\v' \
						|| x == '\r' || x == '\f')
/*
** A philo is a structure that contains:
** Time to eat in ms, time to die in ms, time to sleep in ms
** And Number Of Times Each Philosopher Must Eat, optional
*/

typedef struct	s_philo
{
	int 		philo_cnt;
	int 		time_to_die;
	int 		time_to_eat;
	int 		time_to_sleep;
	int 		noteme;
}				t_philo;

long 	ft_atoi(char *str);
int		ft_strlen(char *str);
int		print_error(char *str);
int		init_philo(t_philo *philo, int ac, char **av);
int		is_digit(char c);

#endif
