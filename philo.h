/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 00:43:42 by htalhaou          #+#    #+#             */
/*   Updated: 2023/05/17 19:09:38 by htalhaou         ###   ########.fr       */
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

typedef struct philo
{
	int				id;
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_eat;
	pthread_mutex_t	*forks;
	pthread_t		thread;
	// struct s_philo	*next;
}					t_philo;

void	*philo_routine(void	*philo);
int		init_philo(t_philo *philo, char **argv);
int		check_for_int(char **arg);
long	ft_atoi(const char *str);

#endif