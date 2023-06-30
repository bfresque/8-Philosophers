/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfresque <bfresque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 11:37:47 by rertzer           #+#    #+#             */
/*   Updated: 2023/06/30 13:49:33 by bfresque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>
# include <string.h>
# include <limits.h>

/* define */
# define MSG_NB 13

struct	s_philo;

typedef struct s_data
{
	int				nb_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_think;
	int				must_eat;
	int				timeover;
	long int		time_start;
	struct s_philo	*akademia;
	pthread_mutex_t	mutex_timeover;
	pthread_mutex_t	*ware;
}	t_data;

typedef struct s_philo
{
	int				number;
	int				must_eat;
	long int		last_meal;
	pthread_mutex_t	mutex_last_meal;
	pthread_t		pthread;
	t_data		*data;
}	t_philo;

/* main */
/* parsing */
int				parsing_atoi(int *n, char *str);
int				parsing_safeadd(int *a, int b);
/* run */
int				run_start(t_data *data);
void			run_join(t_data *data);
void			run_trial(t_data *data);
/* philo */
void			*philo_start(void *void_philo);
void			*philo_soliloquy(t_philo *philo);
void			*philo_quit(t_philo *philo, int i);
void			*philo_symposium(t_philo *philo);
/* philo life */
int				philo_thinking(t_philo *philo);
int				philo_eating(t_philo *philo);
int				philo_sleeping(t_philo *philo);
void			philo_dying(t_philo *philo);
/* forks */
pthread_mutex_t	*forks_first(t_philo *philo);
pthread_mutex_t	*forks_second(t_philo *philo);
/* clock */
long int		clock_timestamp(t_data *data);
void			clock_down(t_data *data);
int				clock_running(t_data *data);
/* init */
int				init_data(t_data *data, int ac, char **av);
int				init_data_etc(t_data *data);
int				init_akademia(t_data *data);
int				init_philo(t_data *data, int i);
int				init_ware(t_data *data);
/* return */
int				return_error(t_data *data, int error);
char			*return_msg(int error);
void			return_putmsg(char *str);
/* utils */
int				utils_printmsg(t_data *data, int nb, char *str);
#endif
