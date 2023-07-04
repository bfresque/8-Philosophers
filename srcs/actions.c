/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfresque <bfresque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 14:33:12 by bfresque          #+#    #+#             */
/*   Updated: 2023/07/04 14:24:24 by bfresque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/philosophers.h"

void action_think(t_init *init, t_philo *philo)
{
	print(init, philo->id_philo, " is thinking\n");
}

void action_sleep(t_init *init, t_philo *philo)
{
	print(init, philo->id_philo, " is sleeping\n");
	long long int start_sleep_time = ft_get_time();
	usleep(init->time_to_sleep * 1000);
	long long int end_sleep_time = ft_get_time();
	long long int sleep_duration = end_sleep_time - start_sleep_time;
	if (sleep_duration < init->time_to_sleep)
		usleep(init->time_to_sleep - sleep_duration);
}

void action_eat(t_init *init, t_philo *philo)
{
	print(init, philo->id_philo, " is eating\n");
	pthread_mutex_lock(&(philo->eat_mutex));
	philo->nb_eat_time++;
	pthread_mutex_unlock(&(philo->eat_mutex));
	philo->time_last_eat = ft_get_time();
	usleep(init->time_to_eat * 1000);
	if (philo->left_fork_id < philo->right_fork_id)
	{
		pthread_mutex_unlock(&init->forks[philo->left_fork_id]);
		pthread_mutex_unlock(&init->forks[philo->right_fork_id]);
	}
	else
	{
		pthread_mutex_unlock(&init->forks[philo->right_fork_id]);
		pthread_mutex_unlock(&init->forks[philo->left_fork_id]);
	}
}

void take_fork(t_init *init, t_philo *philo)
{
	if (philo->id_philo % 2 == 0)
	{
		pthread_mutex_lock(&init->forks[philo->right_fork_id]);
		pthread_mutex_lock(&init->forks[philo->left_fork_id]);
	}
	else
	{
		pthread_mutex_lock(&init->forks[philo->left_fork_id]);
		pthread_mutex_lock(&init->forks[philo->right_fork_id]);
	}
	print(init, philo->id_philo, " has taken a fork\n");
	print(init, philo->id_philo, " has taken a fork\n");
	action_eat(init, philo);
	pthread_mutex_unlock(&init->forks[philo->left_fork_id]);
	pthread_mutex_unlock(&init->forks[philo->right_fork_id]);
}
