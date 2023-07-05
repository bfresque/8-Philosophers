/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfresque <bfresque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 14:02:25 by bfresque          #+#    #+#             */
/*   Updated: 2023/07/05 12:35:59 by bfresque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/philosophers.h"

void check_death(t_init *init, t_philo *philo)
{
	long long int current_time = ft_get_time();
	long long int time_since_last_eat = current_time - philo->time_last_eat;
	if (time_since_last_eat > (long long int)init->time_to_die)
	{
		print(init, philo->id_philo, " died\n");
		exit(1);
	}
}

void check_all_deaths(t_init *init)
{
	int i = 0;
	while (i < init->nb_of_philo)
	{
		check_death(init, &init->philo[i]);
		i++;
	}
}

int check_all_eat(t_init *init)
{
	int i = 0;
	init->all_philo_finished = 0;
	while (i < init->nb_of_philo)
	{
		pthread_mutex_lock(&(init->philo[i].eat_mutex));
		if (init->philo[i].nb_eat_time == init->number_must_eat)
			init->all_philo_finished++;
		pthread_mutex_unlock(&(init->philo[i].eat_mutex));
		i++;
	}
	if (init->all_philo_finished < init->nb_of_philo)
		return 0;
	else if (init->all_philo_finished == init->nb_of_philo)
	{
		exit(1);
		return 1;
	}
	return -1;
}
