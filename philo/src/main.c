/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfresque <bfresque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 11:58:05 by rertzer           #+#    #+#             */
/*   Updated: 2023/06/30 13:51:35 by bfresque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
int	main(int ac, char **av)
{
	int			error;
	t_data	data;

	if (ac < 5 || ac > 6)
	{
		return_putmsg(return_msg(10));
		return (1);
	}
	error = init_data(&data, ac, av);
	if (error)
		return (return_error(&data, error));
	error = run_start(&data);
	run_join(&data);
	return (return_error(&data, error));
}
