/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfresque <bfresque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 10:12:33 by rertzer           #+#    #+#             */
/*   Updated: 2023/06/30 13:51:35 by bfresque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
int	philo_thinking(t_philo *philo)
{
	if (utils_printmsg(philo->data, philo->number, "is thinking"))
		return (1);
	usleep(philo->data->time_to_think * 1000);
	return (0);
}

int	philo_eating(t_philo *philo)
{
	int	satiated;

	satiated = 0;
	if (utils_printmsg(philo->data, philo->number, "is eating"))
		return (1);
	pthread_mutex_lock(&philo->mutex_last_meal);
	philo->last_meal = clock_timestamp(philo->data);
	pthread_mutex_unlock(&philo->mutex_last_meal);
	if (philo->must_eat > 0)
		philo->must_eat--;
	if (philo->must_eat == 0)
	{
		clock_down(philo->data);
		satiated = 1;
	}
	usleep(philo->data->time_to_eat * 1000);
	return (satiated);
}

int	philo_sleeping(t_philo *philo)
{
	if (utils_printmsg(philo->data, philo->number, "is sleeping"))
		return (1);
	usleep(philo->data->time_to_sleep * 1000);
	return (0);
}

void	philo_dying(t_philo *philo)
{		
	pthread_mutex_lock(&philo->data->mutex_timeover);
	philo->data->timeover = 0;
	printf("%ld %d died\n", clock_timestamp(philo->data), philo->number);
	pthread_mutex_unlock(&philo->data->mutex_timeover);
}
