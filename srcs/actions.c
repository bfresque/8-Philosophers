/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfresque <bfresque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 14:33:12 by bfresque          #+#    #+#             */
/*   Updated: 2023/08/08 13:58:56 by bfresque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_philo_sleep(unsigned long duration, t_init *init)
{
	unsigned long	start;

	start = ft_get_time();
	while (check_all_deaths(init, init->philo) == 0)
	{
		if (ft_get_time() - start >= duration)
			break ;
		usleep(init->nb_of_philo * 2);
	}
}

void	action_think(t_init *init, t_philo *philo)
{
	// if (init->nb_of_philo > 1)
	// {
		print(init, philo->id_philo, " is thinking\n");
		ft_philo_sleep((init->time_to_think), init);
	// }
}

void	action_sleep(t_init *init, t_philo *philo)
{
	// if (init->nb_of_philo > 1)
	// {
		print(init, philo->id_philo, " is sleeping\n");
		ft_philo_sleep((init->time_to_sleep), init);
	// }
}

void	action_eat(t_init *init, t_philo *philo)
{
	// if (init->nb_of_philo > 1)
	// {
		print(init, philo->id_philo, " is eating\n");
		pthread_mutex_lock(&(philo->mutex_time_last_eat));
		philo->time_last_eat = ft_get_time();
		pthread_mutex_unlock(&(philo->mutex_time_last_eat));
		pthread_mutex_lock(&(philo->eat_mutex));
		philo->nb_eat_time++;
		pthread_mutex_unlock(&(philo->eat_mutex));
		ft_philo_sleep((init->time_to_eat), init);
		if (philo->id_philo % 2 == 0)
		{
			pthread_mutex_unlock(&init->forks[philo->left_fork_id]);
			pthread_mutex_unlock(&init->forks[philo->right_fork_id]);
		}
		else if (philo->id_philo % 2 != 0)
		{
			pthread_mutex_unlock(&init->forks[philo->right_fork_id]);
			pthread_mutex_unlock(&init->forks[philo->left_fork_id]);
		}
	// }
}

void	take_fork(t_init *init, t_philo *philo)
{
	// check_all_deaths(init, philo); //a mettre pour que le philo seul meurt
	// if (init->nb_of_philo > 1)
	// {
		if (philo->id_philo % 2 == 0)
		{
			pthread_mutex_lock(&init->forks[philo->left_fork_id]);
			print(init, philo->id_philo, " has taken a fork\n");
			pthread_mutex_lock(&init->forks[philo->right_fork_id]);
			print(init, philo->id_philo, " has taken a fork\n");;
			action_eat(init, philo);
		}
		else if (philo->id_philo % 2 != 0)
		{
			pthread_mutex_lock(&init->forks[philo->right_fork_id]);
			print(init, philo->id_philo, " has taken a fork\n");
			pthread_mutex_lock(&init->forks[philo->left_fork_id]);
			print(init, philo->id_philo, " has taken a fork\n");
			action_eat(init, philo);
		}	
	// }
}
