/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfresque <bfresque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 14:02:25 by bfresque          #+#    #+#             */
/*   Updated: 2023/07/05 16:14:51 by bfresque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/philosophers.h"

void check_death(t_init *init, t_philo *philo)
{
	long long int current_time = ft_get_time();
	long long int time_since_last_eat = current_time - philo->time_last_eat;
	if (time_since_last_eat > (long long int)init->time_to_die)
	{
		pthread_mutex_init(&(philo->death_mutex), NULL);
		pthread_mutex_lock(&(philo->death_mutex));
		print(init, philo->id_philo, " died\n");
		pthread_mutex_unlock(&(philo->death_mutex));
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
/////////////////////////////////////////////////////////////////////////////////////////////////////////

void ft_close(t_init *init)
{
    int i;

    i = 0;
    while (i < init->nb_of_philo)
    {
        pthread_mutex_destroy(&init->forks[i]);
        i++;
    }

     if (init->philo)
         free(init->philo);
     if (init->forks)
         free(init->forks);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////

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
		ft_close(init);
		exit(1);
		return 1;
	}
	return -1;
}

int help_verif_numbers(const char *str)
{
	int len = strlen(str);
	int i = 0;

	while (i < len)
	{
		if (str[i] < '0' || str[i] > '9')
			return 0;
		i++;
	}

	int num = atoi(str);
	if (num <= 0)
		return 0;
	return 1;
}

int check_numbers(int argc, char **argv)
{
	int i = 1;

	while (i < argc)
	{
		if (!help_verif_numbers(argv[i]))
			return 0;
		i++;
	}
	return 1;
}

