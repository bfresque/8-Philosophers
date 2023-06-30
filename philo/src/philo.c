/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfresque <bfresque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 12:58:56 by rertzer           #+#    #+#             */
/*   Updated: 2023/06/30 13:51:35 by bfresque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
void	*philo_start(void *void_philo)
{
	t_philo	*philo;

	philo = (t_philo *)void_philo;
	if (-1 == philo->data->time_to_think)
		return (philo_soliloquy(philo));
	return (philo_symposium(philo));
}

void	*philo_soliloquy(t_philo *philo)
{
	while (clock_running(philo->data))
		usleep(100);
	return (NULL);
}

void	*philo_quit(t_philo *philo, int i)
{
	if (i == 2)
		pthread_mutex_unlock(forks_second(philo));
	pthread_mutex_unlock(forks_first(philo));
	return (NULL);
}

void	*philo_symposium(t_philo *philo)
{
	while (clock_running(philo->data))
	{
		pthread_mutex_lock(forks_first(philo));
		if (utils_printmsg(philo->data, philo->number, "has taken a fork"))
			return (philo_quit(philo, 1));
		pthread_mutex_lock(forks_second(philo));
		if (utils_printmsg(philo->data, philo->number, "has taken a fork"))
			return (philo_quit(philo, 2));
		if (philo_eating(philo))
			return (philo_quit(philo, 2));
		pthread_mutex_unlock(forks_second(philo));
		pthread_mutex_unlock(forks_first(philo));
		if (philo_sleeping(philo))
			return (NULL);
		if (philo_thinking(philo))
			return (NULL);
	}
	return (NULL);
}
