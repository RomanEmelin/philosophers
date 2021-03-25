/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwinter <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 15:57:15 by mwinter           #+#    #+#             */
/*   Updated: 2021/03/24 15:20:08 by mwinter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <semaphore.h>
# define DIE 1
# define FORK 2
# define EAT 3
# define SLEEP 4
# define THINK 5
# define FULL 6

/*
** Little macros to find out if it space or not
** @param char x
** @return true or false
*/

# define IS_SPACE(x) (x==' '||x =='\t'||x =='\n'||x=='\v'||x =='\r'||x =='\f')

typedef struct		s_semaphore
{
	sem_t			*s_forks;
	sem_t			*s_print;
	sem_t			*s_died;
}					t_semaphore;

/*
** A args is a structure that contains:
** Time to eat in ms, time to die in ms, time to sleep in ms and etc
** And Number Of Times Each Philosopher Must Eat, optional
** Count of philosophers, and their status, such as died and full(optional)
*/

typedef struct		s_args
{
	long			philo_cnt;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			meal_cnt;
	int				died;
}					t_args;

typedef struct		s_philo
{
	unsigned int	id;
	t_semaphore		*semaphores;
	int				full;
	sem_t			*s_status;
	t_args			*args;
	pthread_t		thread;
	long			start_time;
	long			last_eat;
}					t_philo;

long				ft_atoi(char *str);
int					ft_strlen(char *str);
int					print_error(char *str);
int					init_philo_args(t_args *args, int ac, char **av);
int					is_digit(char c);
void				ft_putnbr_fd(int n, int fd);
void				printing(char *str, long time, int id);

/*
** Init arguments
*/

int					init_philo_args(t_args *args, int ac, char **av);
int					validation(char **av);
int					init_semaphores(t_semaphore *semaphores, t_args *args);

/*
** Error handling functions
*/

int					integer_overflow_checker(long var[5], char **av);
int					print_error(char *str);

/*
** Threads utils
*/

int					initializate_simulation(t_args *args);
long				get_time(void);
t_philo				*init_philo(t_args *args, t_semaphore *semaphores);
void				*print_status(t_philo *philo, int flag, long start);
void				finish_simulation(t_philo *philo, t_semaphore *sems);
void				usleep_fix(long sleep_time);

/*
** Start simulation
*/

int					start_threads(t_args *args, t_philo *philosophers);
void				*simulation(void *philosopher);
void				*is_die(void *philo);
void				eating(t_philo *philo);
void				sleeping(t_philo *philo);

#endif
