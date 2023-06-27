/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfresque <bfresque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 15:45:38 by bfresque          #+#    #+#             */
/*   Updated: 2023/06/27 17:06:54 by bfresque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# include <stdio.h>
# include <stdint.h>
# include <string.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>

# define RESET "\033[0m"
# define BLACK "\033[30m"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN "\033[36m"
# define WHITE "\033[37m"

typedef struct s_philo
{
	int	id_philo;
	int	time_of_eat;
	int	left_fork_id;
	int	right_fork_id;
	long long	time_last_eat;
}	t_philo;

typedef struct s_init
{
	int	nb_of_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int number_must_eat;
	t_philo *philo;
}	t_init;

/*********************	libft_philo.c ***********************/
int	ft_atoi_philo(char *str);

/*********************	init.c ***********************/
t_init	*init_data(t_init *data, char **av);
t_init	*init_philo(t_init *data);

#endif