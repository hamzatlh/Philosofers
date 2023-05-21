/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 00:43:42 by htalhaou          #+#    #+#             */
/*   Updated: 2023/05/21 20:22:35 by htalhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <limits.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				id;
	int				nb_eat;
	int				left_fork;
	int				right_fork;
	long long		last_eat;
	long long		start;
	pthread_t		thread;
	struct s_infos	*infos;
}	t_philo;

typedef struct s_infos
{
	int				nb_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				*di;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	struct s_philo	*philos;
}	t_infos;

long long	get_time(void);
void		*philo_routine(void	*philo);
int     	init_philo(t_infos *infos, char **argv, int *died);
int			check_for_int(char **arg);
long		ft_atoi(const char *str);
void		mine_usleep(long long time);
int			is_died(t_philo *ph);
void		print_msg(t_philo *ph, char *str);
int			check_and_set_values(t_infos *infos, char **argv);
int			init_philosophers(t_infos *infos, long long time, int *died);

#endif