/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwinter <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 15:57:15 by mwinter           #+#    #+#             */
/*   Updated: 2021/03/26 18:14:28 by mwinter          ###   ########.fr       */
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
# include <signal.h>

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
	sem_t			*s_full;
	sem_t			*s_one_die;
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
	int				full;
	int				died;
}					t_args;

typedef struct		s_philo
{
	int				id;
	sem_t			**s_block;
	t_semaphore		*semaphores;
	t_args			*args;
	pid_t			*pid;
	int				full;
	int				fulling;
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
** Threads and process utils
*/

int					initializate_simulation(t_args *args);
long				get_time(void);
t_philo				*init_philo(t_args *args, t_semaphore *semaphores);
void				*print_status(t_philo *philo, int flag, long start);
void				finish_simulation(t_philo *philo, t_semaphore *sems);
void				usleep_fix(long time);
void				*somebody_die(void *p);
void				wait_kill(t_philo *philo);
void				*is_full(void *philo);
void				*fuller(void *p);
void				*is_die(void *p);
int					get_block(t_philo *philo);
char				*get_name(int i);
void				close_block(t_philo *philo);

/*
** Start simulation
*/

int					start_processes(t_args *args, t_philo *philo);
void				simulation(t_philo *philo);
void				*state_process(void *philo);
void				eating(t_philo *philo);
void				sleeping(t_philo *philo);

#endif
