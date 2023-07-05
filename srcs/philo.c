/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfresque <bfresque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 14:33:27 by bfresque          #+#    #+#             */
/*   Updated: 2023/07/05 12:23:59 by bfresque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/philosophers.h"

int main(int ac, char **av)
{
	t_init *data = malloc(sizeof(t_init));
	if (data == NULL)
	{
		printf("Erreur d'allocation mémoire pour data\n");
		return 1;
	}

	if (ac != 5 && ac != 6)
	{
		printf("Error: number of arguments\n");
		free(data);
		return(0);
	}
	data = init_data(data, av);
	data = init_philo(data);
	data = init_forks(data);
	start_threads(data);
	free(data); // Libérer la mémoire une fois que vous avez terminé avec data
	return 0;
}
