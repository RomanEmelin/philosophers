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
# include <pthread.h>

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

typedef struct	s_args
{
	int 		philo_cnt;
	int 		time_to_die;
	int 		time_to_eat;
	int 		time_to_sleep;
	int 		noteme;
}				t_args;

typedef struct		s_philo
{
	unsigned int	number;
	int 			l_fork;
	int 			r_fork;
	long 			birth;
	long			meal;
};

long 	ft_atoi(char *str);
int		ft_strlen(char *str);
int		print_error(char *str);
int		init_philo_args(t_args *args, int ac, char **av);
int		is_digit(char c);

/*
** Error handling functions
*/

int		integer_overflow_checker(long var[5], char **av);
int		print_error(char *str);

/*
** Threads utils
*/

int		mutex_destroy(pthread_mutex_t *forks, int cnt);
int		init_forks(pthread_mutex_t *forks, t_args *args);
int		initializate_simulation(t_args *args);

#endif
