/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfresque <bfresque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 17:41:50 by rertzer           #+#    #+#             */
/*   Updated: 2023/06/30 13:51:35 by bfresque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
int	return_error(t_data *data, int error)
{
	int	i;

	if (error)
		return_putmsg(return_msg(error));
	i = -1;
	while (++i < data->nb_of_philo)
	{
		if (NULL != data->ware)
			pthread_mutex_destroy(&data->ware[i]);
		if (NULL != data->akademia)
			pthread_mutex_destroy(&data->akademia[i].mutex_last_meal);
	}
	pthread_mutex_destroy(&data->mutex_timeover);
	free(data->akademia);
	free(data->ware);
	return (error);
}

char	*return_msg(int error)
{
	char	*msg[MSG_NB];

	if (error > MSG_NB || error < 0)
		error = MSG_NB;
	msg[0] = "";
	msg[1] = "Error: first argument invalid";
	msg[2] = "Error: second argument invalid";
	msg[3] = "Error: third argument invalid";
	msg[4] = "Error: fourth argument invalid";
	msg[5] = "Error: fifth argument invalid";
	msg[6] = "Error: mutex init error";
	msg[7] = "Error: akademia malloc error";
	msg[8] = "Error: ware malloc error";
	msg[9] = "Error: ware mutex error";
	msg[10] = "Error: four or five arguments required";
	msg[11] = "Error: pthread_init error";
	msg[12] = "Error";
	return (msg[error]);
}

void	return_putmsg(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	write(2, str, len);
	write(2, "\n", 1);
}
