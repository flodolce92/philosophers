/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flo-dolc <flo-dolc@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 12:48:25 by flo-dolc          #+#    #+#             */
/*   Updated: 2024/12/22 16:58:59 by flo-dolc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_table	t_table;

typedef struct s_fork
{
	pthread_mutex_t	fork_lock;
	int				in_use;
}	t_fork;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	int				last_meal;
	size_t			eta_death;
	t_fork			*left_fork;
	t_fork			*right_fork;
	pthread_mutex_t	philo_lock;
	t_table			*table;
}	t_philo;

typedef struct s_table
{
	int				n_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_meals;
	t_philo			*philos;
	t_fork			*forks;
	int				death_flag;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	dead_lock;
}	t_table;

int		ft_atoi(const char *str);
int		isalldigit(char *arg);
size_t	now(void);
int		throw_error(char *error, t_table *table, int exit_code);
void	flip_table(t_table *table);

int		check_args(int argc, char **argv);

int		init(t_table *table, int argc, char **argv);
int		init_table(t_table *table, int argc, char **argv);
void	start_dinner(t_table *table);
int		take_fork(t_fork *fork, t_philo *philo);
void	drop_forks(t_philo *philo);
int		check_death(t_philo *philo);
int		sleep_till_death(size_t time, t_philo *philo);

int		p_eat(t_philo *philo);
int		p_sleep(t_philo *philo);
int		p_think(t_philo *philo);
void	p_death(t_philo *philo);

#endif
