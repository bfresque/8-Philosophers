/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfresque <bfresque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 14:33:32 by bfresque          #+#    #+#             */
/*   Updated: 2023/07/05 12:28:30 by bfresque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/philosophers.h"

void	routine_one(t_init*init, t_philo *philo)
{
	int	i;

	i = 1;
	while (i <= init->number_must_eat)
	{
		take_fork(init, philo);
		if(i == init->number_must_eat)
			break;
		check_all_deaths(init);
		check_all_eat(init);
		action_sleep(init, philo);
		check_all_deaths(init);
		action_think(init, philo);
		check_all_deaths(init);
		i++;
	}
}

void	routine_two(t_init*init, t_philo *philo)
{
	int	i;

	i = 1;
	while (i)
	{
		take_fork(init, philo);
		check_all_deaths(init);
		action_sleep(init, philo);
		check_all_deaths(init);
		action_think(init, philo);
		check_all_deaths(init);
		i++;
	}
}

void	*philo_life(void *arg)
{
	t_data *data = (t_data *)arg;

	if(data->init->number_must_eat > 0)
		routine_one(data->init, data->philo);
	else if(data->init->number_must_eat < 0)
		routine_two(data->init, data->philo);
	else
		exit(-1);
	return(NULL);
}

void	start_threads(t_init *init)
{
	int	i;
	long long int	time_init;
	t_data	*data;

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
	i = -1;
	// if(init->nb_of_philo > 1)
	// {
		while (i++ < init->nb_of_philo)
			pthread_join(init->philo[i].thread_id, NULL);
	// }
}
