/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfresque <bfresque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 14:33:32 by bfresque          #+#    #+#             */
/*   Updated: 2023/07/03 11:58:12 by bfresque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/philosophers.h"

long long ft_get_time()
{
	struct timeval current_time;

	if (gettimeofday(&current_time, NULL))
		return (-1);

	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

void print(t_init *init, int id_phil, char *str)
{
	printf("%lld %d %s", (ft_get_time() - init->philo->start_time), id_phil, str);
}

void action_sleep(t_init *init, t_philo *philo)
{
	print(init, philo->id_philo, " is sleeping\n");
	long long int start_sleep_time = ft_get_time();
	usleep(init->time_to_sleep);
	long long int end_sleep_time = ft_get_time();
	long long int sleep_duration = end_sleep_time - start_sleep_time;
	if (sleep_duration < init->time_to_sleep)
		usleep(init->time_to_sleep - sleep_duration);
}

void action_think(t_init *init, t_philo *philo)
{
	print(init, philo->id_philo, " is thinking\n");
}

void check_death(t_init *init, t_philo *philo)
{
	unsigned long int current_time = ft_get_time();
	unsigned long int time_since_last_eat = current_time - philo->time_last_eat;
	if (time_since_last_eat > (unsigned long int)init->time_to_die)
	{
		print(init, philo->id_philo, " has died\n");
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

void action_eat(t_init *init, t_philo *philo)
{
	print(init, philo->id_philo, " is eating\n");
	usleep(init->time_to_eat);

	if (philo->left_fork_id < philo->right_fork_id)
	{
		pthread_mutex_unlock(&init->forks[philo->left_fork_id]);
		pthread_mutex_unlock(&init->forks[philo->right_fork_id]);
	}
	else
	{
		pthread_mutex_unlock(&init->forks[philo->right_fork_id]);
		pthread_mutex_unlock(&init->forks[philo->left_fork_id]);
	}
	philo[philo->id_philo].nb_eat_time++;
	philo[philo->id_philo].time_last_eat = ft_get_time();


}

int verif_if_all_eat(t_init *init)
{
	int i = 0;
	init->all_philo_finished = 0;
	while (i < init->nb_of_philo)
	{
		if ((init->philo[i].nb_eat_time) == (init->number_must_eat))
		{
			printf("%lld %d %s", (ft_get_time() - init->philo->start_time), init->philo[i].id_philo, "a fini de manger tout ses repas\n");
			init->all_philo_finished++;
		}
		i++;
	}
	if(init->all_philo_finished < init->nb_of_philo)
		return(0);
	else if ((init->all_philo_finished) == (init->nb_of_philo))
	{
		printf("all philo has finish\n");
		exit(1);
		return(1);
	}
	return(-1);
}

void take_fork(t_init *init, t_philo *philo)
{
	if (philo->id_philo % 2 == 0)
	{
		pthread_mutex_lock(&init->forks[philo->right_fork_id]);
		pthread_mutex_lock(&init->forks[philo->left_fork_id]);
	}
	else
	{
		pthread_mutex_lock(&init->forks[philo->left_fork_id]);
		pthread_mutex_lock(&init->forks[philo->right_fork_id]);
	}
	print(init, philo->id_philo, " has taken a fork\n");
	print(init, philo->id_philo, " has taken a fork\n");
	pthread_mutex_unlock(&init->is_eat);
	action_eat(init, philo);
	pthread_mutex_unlock(&init->forks[philo->left_fork_id]);
	pthread_mutex_unlock(&init->forks[philo->right_fork_id]);
}


static void *philo_life(void *arg)
{
	t_data *data = (t_data *)arg;

	int i = 1;
	while (i <= data->init->number_must_eat)
	{
		take_fork(data->init, data->philo);
		check_all_deaths(data->init);
		action_sleep(data->init, data->philo);
		check_all_deaths(data->init);
		action_think(data->init, data->philo);
		// verif_if_all_eat(data->init);
		i++;
	}
	return NULL;
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
		// if (init->philo[i].nb_eat_time < init->number_must_eat)
		// {
			// printf("id philo %d\n", init->philo[i].id_philo);
			// printf("nombre de repas mange par lui %d\n", init->philo[i].nb_eat_time);
			pthread_create(&init->philo[i].thread_id, NULL, philo_life, data);
		// }
		i++;
	}
	i = 0;
	while (i < init->nb_of_philo)
	{
		pthread_join(init->philo[i].thread_id, NULL);
		i++;
	}
}
