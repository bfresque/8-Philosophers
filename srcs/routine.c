/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfresque <bfresque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 14:33:32 by bfresque          #+#    #+#             */
/*   Updated: 2023/08/08 13:58:04 by bfresque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	routine_one(t_init *init, t_philo *philo)
{
	int	i;

	i = 1;
	while (i <= init->number_must_eat)
	{
		take_fork(init, philo);
		if (i == init->number_must_eat)
			break ;
		action_sleep(init, philo);
		action_think(init, philo);
		i++;
	}
}

void	routine_two(t_init*init, t_philo *philo)
{
	int	i;

	i = 1;
	while (i && (check_flag_died(init) == 0))
	{
		take_fork(init, philo);
		action_sleep(init, philo);
		action_think(init, philo);
		i++;
	}
}

void	*philo_life(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	if (data->init->nb_of_philo == 1)
	{
		while(check_flag_died(data->init) == 0)
			check_all_deaths(data->init, data->philo); //a mettre pour que le philo seul meurt
	}
	if (data->init->number_must_eat > 0)
		routine_one(data->init, data->philo);
	else if (data->init->number_must_eat < 0)
		routine_two(data->init, data->philo);
	return (NULL);
}

void	start_threads(t_init *init)
{
	int				i;
	int				j;
	long long int	time_init;
	t_data			*data;

	i = 0;
	j = 0;
	time_init = ft_get_time();
	data = NULL;
	while (i < init->nb_of_philo)
	{
		data = malloc(sizeof(t_data));
		if (!data)
		{
			while (j < i)
			{
				free(init->philo[j].data);
				j++;
			}
			return ;
		}
		data->init = init;
		data->philo = &init->philo[i];
		data->philo->start_time = time_init;
		pthread_mutex_lock(&(init->philo->mutex_time_last_eat));
		data->philo->time_last_eat = ft_get_time();
		pthread_mutex_unlock(&(init->philo->mutex_time_last_eat));
		init->philo[i].data = data;
		pthread_create(&init->philo[i].thread_id, NULL, philo_life, data);
		i++;
	}
	i = 0;
	while (i < init->nb_of_philo)
	{
		pthread_join(init->philo[i].thread_id, NULL);
		i++;
	}
}
