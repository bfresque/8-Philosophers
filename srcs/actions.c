/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfresque <bfresque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 14:33:12 by bfresque          #+#    #+#             */
/*   Updated: 2023/08/02 11:19:11 by bfresque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/philosophers.h"

void action_think(t_init *init, t_philo *philo)
{
	check_all_deaths(init);
	check_all_eat(init);
	if(init->flag_death != 0 || init->flag_death != 0)
		return ;
	print(init, philo->id_philo, " is thinking\n");
	usleep(init->time_to_think * 1000);
}

void action_sleep(t_init *init, t_philo *philo)
{
	check_all_deaths(init);
	check_all_eat(init);
	if(init->flag_death != 0 || init->flag_death != 0)
		return ;
	print(init, philo->id_philo, " is sleeping\n");
	usleep(init->time_to_sleep * 1000);
}

void action_eat(t_init *init, t_philo *philo)
{
	print(init, philo->id_philo, " is eating\n");
	philo->time_last_eat = ft_get_time();
	pthread_mutex_lock(&(philo->eat_mutex));
	philo->nb_eat_time++;
	pthread_mutex_unlock(&(philo->eat_mutex));
	usleep(init->time_to_eat * 1000);
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
	check_all_deaths(init);
	check_all_eat(init);
	if(init->flag_death != 0 || init->flag_death != 0)
		return ;
	if(philo->id_philo % 2 == 0)
	{
		pthread_mutex_lock(&init->forks[philo->left_fork_id]);
		check_all_deaths(init);
		print(init, philo->id_philo, " has taken a fork\n");
		pthread_mutex_lock(&init->forks[philo->right_fork_id]);
		check_all_deaths(init);
		print(init, philo->id_philo, " has taken a fork\n");
		action_eat(init, philo);
	}
	else if (philo->id_philo % 2 != 0)
	{
		pthread_mutex_lock(&init->forks[philo->right_fork_id]);
		check_all_deaths(init);
		print(init, philo->id_philo, " has taken a fork\n");
		pthread_mutex_lock(&init->forks[philo->left_fork_id]);
		check_all_deaths(init);
		print(init, philo->id_philo, " has taken a fork\n");
		action_eat(init, philo);
	}	
}
