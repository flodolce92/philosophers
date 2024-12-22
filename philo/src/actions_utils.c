/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flo-dolc <flo-dolc@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:55:58 by flo-dolc          #+#    #+#             */
/*   Updated: 2024/12/22 19:23:21 by flo-dolc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	message(char *msg, t_philo *philo)
{
	pthread_mutex_lock(&philo->table->print_lock);
	printf("%lu %d %s", now(), philo->id, msg);
	pthread_mutex_unlock(&philo->table->print_lock);
}

int sleep_till_death(size_t time, t_philo *philo)
{
	size_t start;

	start = now();
	if (start + time > philo->eta_death)
	{
		// message("sleeping till death\n", philo);
		// printf("time: %lu\n", time);
		// printf("start: %lu eta_death: %lu\n", start, philo->eta_death);
		time = philo->eta_death - start;
		if (philo->eta_death < start)
		{
			time = 0;
			// printf("RESET TIME\n");
		}
		// printf("time to sleep: %lu\n", time);
		// message("DEATH BY DEATH\n", philo);
		usleep(time * 1000);
		pthread_mutex_lock(&philo->table->dead_lock);
		p_death(philo);
		pthread_mutex_unlock(&philo->table->dead_lock);
		return (message("DEATH BY TIME\n", philo) , 1);
	}
	usleep(time * 1000);
	return (0);
}

int check_death(t_philo *philo)
{
	// printf("check_death philo n. %d\n", philo->id);
	if (philo->table->death_flag == 1)
	{
		pthread_mutex_unlock(&philo->table->dead_lock);
		return (message("DEATH BY FLAG\n", philo), 1);
	}
	else if (philo->eta_death < now())
	{
		p_death(philo);
		pthread_mutex_unlock(&philo->table->dead_lock);
		return (message("DEATH BY TIME\n", philo), 1);
	}
	return (0);
}

int take_fork(t_fork *fork, t_philo *philo)
{
	while (1)
	{
		// message("trying to take a fork\n", philo);
		// printf("philo %d trying to lock mux\n", philo->id);
		pthread_mutex_lock(&fork->fork_lock);
		// message("fork locked\n", philo);
		// printf("philo %d trying to take fork %d\n", philo->id, fork->in_use);
		if (fork->in_use == 0)
		{
			fork->in_use = 1;
			pthread_mutex_unlock(&fork->fork_lock);
			break ;
		}
		pthread_mutex_unlock(&fork->fork_lock);
		// message("fork unlocked\n", philo);
		if (sleep_till_death(1, philo))
			return (message("DEATH BY FORK ABSENCE\n", philo), 1);
	}
	pthread_mutex_lock(&philo->table->dead_lock);
	if (check_death(philo))
		return (1);
	pthread_mutex_unlock(&philo->table->dead_lock);
	// pthread_mutex_lock(&philo->table->print_lock);
	// printf("%lu %d has taken a fork\n", now(), philo->id);
	message("has taken a fork\n", philo);
	// pthread_mutex_unlock(&philo->table->print_lock);
	return (0);
}

void drop_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->right_fork->fork_lock);
	philo->right_fork->in_use = 0;
	pthread_mutex_unlock(&philo->right_fork->fork_lock);
	pthread_mutex_lock(&philo->left_fork->fork_lock);
	philo->left_fork->in_use = 0;
	pthread_mutex_unlock(&philo->left_fork->fork_lock);
}
