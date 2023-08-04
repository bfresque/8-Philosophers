/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfresque <bfresque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 14:33:27 by bfresque          #+#    #+#             */
/*   Updated: 2023/08/03 14:37:00 by bfresque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int ac, char **av)
{
	t_init	*data;

	if (ac != 5 && ac != 6)
	{
		printf("Error: number of arguments\n");
		return (0);
	}
	if (!check_numbers(ac, av))
	{
		printf("Error: All arguments must be positive integers.\n");
		return (0);
	}
	data = malloc(sizeof(t_init));
	if (data == NULL)
		return (1);
	data = init_data(data, av);
	data = init_philo(data);
	data = init_forks(data);
	start_threads(data);
	return (0);
}
