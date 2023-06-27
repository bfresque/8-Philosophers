/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfresque <bfresque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 14:33:27 by bfresque          #+#    #+#             */
/*   Updated: 2023/06/27 17:05:05 by bfresque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/philosophers.h"

int main(int ac, char **av)
{
	t_init *data;
	data = malloc(sizeof(t_init));  // Allouer de la mémoire pour data
	if (data == NULL) {
		printf("Erreur d'allocation mémoire pour data\n");
		return 1;
	}
	data = init_data(data, av);
	data = init_philo(data);
	free(data);  // Libérer la mémoire une fois que vous avez terminé avec data
	(void)ac;
	return 0;
}
