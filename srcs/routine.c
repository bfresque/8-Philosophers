/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfresque <bfresque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 14:33:32 by bfresque          #+#    #+#             */
/*   Updated: 2023/07/04 14:11:08 by bfresque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/philosophers.h"

void *philo_life(void *arg)
{
	t_data *data = (t_data *)arg;

	int i = 1;
	if(data->init->number_must_eat > 0)
	{
		while (i <= data->init->number_must_eat)
		{
			take_fork(data->init, data->philo);
			if(i == data->init->number_must_eat)
				break;
			check_all_deaths(data->init);
			check_all_eat(data->init);
			action_sleep(data->init, data->philo);
			check_all_deaths(data->init);
			action_think(data->init, data->philo);
			check_all_deaths(data->init);
			i++;
		}
	}
	else if(data->init->number_must_eat < 0)
	{
		while (i)
		{
			take_fork(data->init, data->philo);
			check_all_deaths(data->init);
			action_sleep(data->init, data->philo);
			check_all_deaths(data->init);
			action_think(data->init, data->philo);
			check_all_deaths(data->init);
			i++;
		}
	}
	else
		exit(-1);
	return(NULL);
}

void start_threads(t_init *init)
{
	int i;
	long long int time_init;
	t_data *data;

	time_init = ft_get_time();

	i = 0;
	while (i < init->nb_of_philo)
	{
		data = malloc(sizeof(t_data));
		if (!data)
			return;
		data->init = init;
		data->philo = &init->philo[i];
		data->init->philo->start_time = time_init;
		data->philo->time_last_eat = ft_get_time();
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
