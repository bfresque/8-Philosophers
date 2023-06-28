/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfresque <bfresque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 14:33:19 by bfresque          #+#    #+#             */
/*   Updated: 2023/06/28 14:47:36 by bfresque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/philosophers.h"

t_init *init_data(t_init *data, char **av)
{
	data->philo = malloc(sizeof(t_philo) * data->nb_of_philo);
	if(data->philo == NULL)
		return(0);
	data->nb_of_philo = ft_atoi_philo(av[1]);
	data->time_to_die = ft_atoi_philo(av[2]);
	data->time_to_eat = ft_atoi_philo(av[3]);
	data->time_to_sleep = ft_atoi_philo(av[4]);
	data->number_must_eat = ft_atoi_philo(av[5]);

	printf("%s INIT DATA \n", MAGENTA);
	printf("nb_of_philo = %d\n", data->nb_of_philo);
	printf("time_to_die = %d\n", data->time_to_die);
	printf("time_to_eat = %d\n", data->time_to_eat);
	printf("time_to_sleep = %d\n", data->time_to_sleep);
	printf("nb_must_eat = %d\n", data->number_must_eat);
	printf("** END INIT DATA **\n\n%s", RESET);
	return(data);
}

t_init *init_philo(t_init *data)
{
	int i;

	i = data->nb_of_philo;
	while(i > 0)
	{
		data->philo[i].id_philo = i;
		data->philo[i].nb_eat_time = 0;
		// data->philo[i].left_fork_id = i;
		// data->philo[i].right_fork_id = (i + 1) % data->nb_of_philo;
		data->philo[i].time_last_eat = 0;

		printf("%s***** INIT PHILO nb : '%d' *****\n", BLUE, i);
		printf("philo_id = %d\n", data->philo[i].id_philo);
		printf("nb_time_eat = %d\n", data->philo[i].nb_eat_time);
		// printf("right_fork_id = %d\n", data->philo[i].left_fork_id);
		// printf("left_fork_id = %d\n", data->philo[i].right_fork_id );
		printf("time_last_eat = %ld\n", data->philo[i].time_last_eat);
		printf("i = %d\n", i);
		printf("** END INIT PHILO **\n\n%s", RESET);
		i--;
	}
	return(data);
}
