/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 22:19:38 by htalhaou          #+#    #+#             */
/*   Updated: 2023/05/16 23:17:45 by htalhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_take_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	print_status(philo, "has taken a fork");
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->eat_mutex);
	print_status(philo, "is eating");
	philo->last_eat = get_time();
	philo->eat_count++;
	pthread_mutex_unlock(philo->eat_mutex);
	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	philo_sleep(t_philo *philo)
{
	print_status(philo, "is sleeping");
	ft_usleep(philo->time_to_sleep);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		philo_take_fork(philo);
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

int	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
