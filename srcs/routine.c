/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfresque <bfresque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 14:33:32 by bfresque          #+#    #+#             */
/*   Updated: 2023/06/28 15:49:18 by bfresque         ###   ########.fr       */
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

void action_sleep(t_init *init, t_philo *philo)
{
	// pthread_mutex_lock(&data->philo.right_fork_id);
	// print(philo, "has taken a fork\n");
	// pthread_mutex_lock(&data->philo.left_fork_id);
	// print(philo, "has taken a fork\n");
	// print(philo, "is eating\n");
	// data->philo[i].time_last_eat = ft_get_time();
	// ft_usleep(&data->time_to_eat);
	// data->philo[i].nb_eat_time++;
	// pthread_mutex_unlock(&data->philo[i].right_fork_id);
	// pthread_mutex_unlock(&data->philo[i].left_fork_id);
	print(init, philo->id_philo, " is sleeping\n");
	usleep(init->time_to_sleep * 1000);
	// print(philo, " is thinking\n");
}

static void *philo_life(void *arg)
{
	t_data *data;
	
	data = (t_data *)arg;
	action_sleep(data->init, data->philo);
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
