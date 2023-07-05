/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfresque <bfresque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 14:33:12 by bfresque          #+#    #+#             */
/*   Updated: 2023/07/05 11:03:10 by bfresque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/philosophers.h"

void action_think(t_init *init, t_philo *philo)
{
	print(init, philo->id_philo, " is thinking\n");
	usleep(init->time_to_think * 1000);
}

void action_sleep(t_init *init, t_philo *philo)
{
	long long int start_sleep_time;
	long long int end_sleep_time;
	long long int sleep_duration;

	print(init, philo->id_philo, " is sleeping\n");
	start_sleep_time = ft_get_time();
	usleep(init->time_to_sleep * 1000);
	end_sleep_time = ft_get_time();
	sleep_duration = end_sleep_time - start_sleep_time;
	if (sleep_duration < init->time_to_sleep)
		usleep(init->time_to_sleep - sleep_duration);
}

void action_eat(t_init *init, t_philo *philo)
{
	print(init, philo->id_philo, " is eating\n");
	philo->time_last_eat = ft_get_time();
	pthread_mutex_lock(&(philo->eat_mutex));//ne pas toucher
	philo->nb_eat_time++;
	pthread_mutex_unlock(&(philo->eat_mutex)); //ne pas toucher

	usleep(init->time_to_eat * 1000); //mit a la fin ca marche super mais cest interdit 
	if(philo->id_philo % 2 == 0)
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
	// if (philo->id_philo % 2 == 0)
	// {
	// 	usleep(50);
	// }
	if(philo->id_philo % 2 == 0)
	{
		pthread_mutex_lock(&init->forks[philo->left_fork_id]);
		pthread_mutex_lock(&init->forks[philo->right_fork_id]);
	}
	else
	{
		pthread_mutex_lock(&init->forks[philo->right_fork_id]);
		pthread_mutex_lock(&init->forks[philo->left_fork_id]);
	}
	print(init, philo->id_philo, " has taken a fork\n");
	print(init, philo->id_philo, " has taken a fork\n");
	action_eat(init, philo);
}
