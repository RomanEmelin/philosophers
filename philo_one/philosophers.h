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
# include <sys/time.h>

/*
** Little macros to find out if it space or not
** @param char x
** @return true or false
*/
# define IS_SPACE(x) (x == ' ' || x == '\t' || x == '\n' || x == '\v' \
						|| x == '\r' || x == '\f')

typedef struct		s_philo
{
	unsigned int	id;
	int 			l_fork;
	int 			r_fork;
	long 			eat;
	long			birth;
	long 			limit;
}					t_philo;

/*
** A args is a structure that contains:
** Time to eat in ms, time to die in ms, time to sleep in ms and etc
** And Number Of Times Each Philosopher Must Eat, optional
*/

typedef struct		s_args
{
	int 			philo_cnt;
	int 			time_to_die;
	int 			time_to_eat;
	int 			time_to_sleep;
	int 			noteme;
	t_philo			*philosopher;
	pthread_mutex_t *forks;
}					t_args;

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
long	get_time(void);
int		set_forks(t_args *args, t_philo philosophers[]);
void 	give_forks(t_philo *philosopher, int l_fork, int r_fork);

/*
** Start simulation
*/

int		start_simulation(t_args *args, t_philo *philosophers);
void	*simulation(void *pntr_on_args);
int		take_forks(pthread_mutex_t *forks ,t_philo *philo);

#endif
