/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfresque <bfresque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 14:33:32 by bfresque          #+#    #+#             */
/*   Updated: 2023/06/29 11:01:47 by bfresque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/philosophers.h"

unsigned long int ft_get_time()
{
	struct timeval	tv;

	if(gettimeofday(&tv, NULL))
		return(-1);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	print(t_init *init, int id_phil, char *str)
{
	printf("%ld %d %s", (ft_get_time() - init->start_time), id_phil, str);
}

void	take_fork(t_init *init, t_philo *philo)
{
	pthread_mutex_lock(&(init->forks[philo->right_fork_id]));
	pthread_mutex_lock(&(init->forks[philo->left_fork_id]));
	print(init, philo->id_philo, " has taken a fork\n");
	print(init, philo->id_philo, " has taken a fork\n");
}

void	action_eat(t_init *init, t_philo *philo)
{
	print(init, philo->id_philo, " is eating\n");
	philo[philo->id_philo].time_last_eat = ft_get_time();
	philo[philo->id_philo].nb_eat_time++;
	// usleep(init->time_to_eat * 1000);
	
	pthread_mutex_unlock(&init->forks[philo->right_fork_id]);
	pthread_mutex_unlock(&init->forks[philo->left_fork_id]);
}

void action_sleep(t_init *init, t_philo *philo)
{
	print(init, philo->id_philo, " is sleeping\n");
	// usleep(init->time_to_sleep * 1000);
	// printf("id philo = %d\n", philo->id_philo);
}

void	action_think(t_init *init, t_philo *philo)
{
	print(init, philo->id_philo, " is thinking\n");
}

static void *philo_life(void *arg)
{
	t_data *data;
	
	data = (t_data *)arg;
	take_fork(data->init, data->philo);
	action_eat(data->init, data->philo);
	action_sleep(data->init, data->philo);
	action_think(data->init, data->philo);
	return (NULL);
}

int start_threads(t_init *init)
{
	int					i;
	t_data				*data;
	unsigned long int	time_init;

	time_init = ft_get_time();

	i = init->nb_of_philo - 1;
	while(i >= 0)
	{
		data = malloc(sizeof(t_data));
		if(!data)
			return(0);
		data->init = init;
		data->philo = &init->philo[i];
		data->init->start_time = time_init;
		pthread_create(&init->philo[i].thread_id, NULL, philo_life, data);
		i--;
	}
	return(0);
}
