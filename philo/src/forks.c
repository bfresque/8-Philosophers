/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfresque <bfresque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 13:37:42 by rertzer           #+#    #+#             */
/*   Updated: 2023/06/30 13:51:35 by bfresque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
pthread_mutex_t	*forks_first(t_philo *philo)
{
	int	fork_index;

	if (philo->number % 2)
		fork_index = philo->number % philo->data->nb_of_philo;
	else
		fork_index = philo->number - 1;
	return (&philo->data->ware[fork_index]);
}

pthread_mutex_t	*forks_second(t_philo *philo)
{
	int	fork_index;

	if (philo->number % 2)
		fork_index = philo->number - 1;
	else
		fork_index = philo->number % philo->data->nb_of_philo;
	return (&philo->data->ware[fork_index]);
}
