/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfresque <bfresque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 15:45:38 by bfresque          #+#    #+#             */
/*   Updated: 2023/06/28 15:28:21 by bfresque         ###   ########.fr       */
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
# include <sys/time.h>
# include <pthread.h>

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
	int				id_philo;
	int				nb_eat_time;
	unsigned long	time_last_eat;
	// struct s_init	*data;
	pthread_t		thread_id;
	pthread_mutex_t	left_fork_id;
	pthread_mutex_t	right_fork_id;
}	t_philo;

typedef struct s_init
{
	int				nb_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_must_eat;
	unsigned long	start_time;
	t_philo			*philo;
	pthread_mutex_t	is_eat;
}	t_init;

typedef struct s_data
{
	t_init	*init;
	t_philo	*philo;
}	t_data;


/*********************	libft_philo.c ***********************/
int	ft_atoi_philo(char *str);

/*********************	init.c ***********************/
t_init	*init_data(t_init *data, char **av);
t_init	*init_philo(t_init *data);

int start_threads(t_init *data);

#endif