/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 00:43:42 by htalhaou          #+#    #+#             */
/*   Updated: 2023/05/18 13:22:49 by htalhaou         ###   ########.fr       */
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
	pthread_t		thread;
	struct s_moad	*moad;
}	t_philo;

typedef struct s_moad
{
	int				nb_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	pthread_mutex_t	*forks;
	struct s_philo	*philos;
}	t_moad;


void	*philo_routine(void	*philo);
int		init_philo(t_moad *moad, char **argv);
int		check_for_int(char **arg);
long	ft_atoi(const char *str);

#endif