/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 00:43:42 by htalhaou          #+#    #+#             */
/*   Updated: 2023/05/16 23:19:04 by htalhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				id;
	int				last_eat;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				start_time;
	int				eat_count;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	*eat_mutex;
	pthread_mutex_t	*dead_mutex;
	pthread_mutex_t	*sleep_mutex;
	pthread_mutex_t	*think_mutex;
	pthread_mutex_t	*fork_mutex;
	pthread_mutex_t	*stop_mutex;
	pthread_mutex_t	*nb_eat_mutex;
	pthread_t		thread;
	struct s_philo	*next;
}	t_philo;

void	print_status(t_philo *philo, char *status);
int		init_philo(t_philo *philo, char **argv);
int		init_mutex(t_philo *philo);
int		init_thread(t_philo *philo);
int		init_philo(t_philo *philo, char **argv);
void	philo_take_fork(t_philo *philo);
void	philo_eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	philo_think(t_philo *philo);
void	philo_die(t_philo *philo);
void	*philo_routine(void *arg);
int		get_time(void);
int		ft_atoi(const char *str);
int		ft_usleep(int time);

#endif