/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfresque <bfresque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 14:33:32 by bfresque          #+#    #+#             */
/*   Updated: 2023/08/04 13:32:42 by bfresque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	routine_one(t_init *init, t_philo *philo)
{
	int	i;

	i = 1;
	// printf(" philo : %d\n", philo->id_philo);//

	while (i <= init->number_must_eat &&  (init->flag_death == 0))
	{
		// printf("%s je boulce une ?\n%s", MAGENTA, RESET);//
		take_fork(init, philo);
		if (i == init->number_must_eat)
			break ;
		// printf("%s j'ai fini fourchette ?\n%s", MAGENTA, RESET);//

		action_sleep(init, philo);
		// printf("%s j'ai fini dodo ?\n%s", MAGENTA, RESET);//

		// if (check_all_deaths(init))
			// return ;
		action_think(init, philo);
		// if (check_all_deaths(init))
			// return ;
		check_all_deaths(init);
		i++;
	}
}

void	routine_two(t_init*init, t_philo *philo)
{
	int	i;

	i = 1;
	while (i && (init->flag_death == 0))
	{
		// printf("%s je boulce deux ?\n%s", MAGENTA, RESET);//
		take_fork(init, philo);
		// if (check_all_deaths(init) == 0)
			// return ;
		action_sleep(init, philo);
		// if (check_all_deaths(init) == 0)
			// return ;
		action_think(init, philo);
		// if (check_all_deaths(init) == 0)
			// return ;
		check_all_deaths(init);
		i++;
	}
}

void	*philo_life(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
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
		data->philo->time_last_eat = ft_get_time();
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
	i = 0;
}
