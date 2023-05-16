/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 00:40:35 by htalhaou          #+#    #+#             */
/*   Updated: 2023/05/16 23:34:48 by htalhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(t_philo *philo, char *status)
{
	pthread_mutex_lock(philo->print_mutex);
	printf("%d %d %s\n", get_time() - philo->start_time, philo->id, status);
	pthread_mutex_unlock(philo->print_mutex);
}

int	init_philo(t_philo *philo, char **argv)
{
	int	i;

	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		philo[i].id = i + 1;
		philo[i].time_to_die = ft_atoi(argv[2]);
		philo[i].time_to_eat = ft_atoi(argv[3]);
		philo[i].time_to_sleep = ft_atoi(argv[4]);
		philo[i].eat_count = 0;
		philo[i].last_eat = 0;
		philo[i].start_time = get_time();
		philo[i].eat_mutex = malloc(sizeof(pthread_mutex_t));
		philo[i].left_fork = malloc(sizeof(pthread_mutex_t));
		philo[i].right_fork = malloc(sizeof(pthread_mutex_t));
		philo[i].print_mutex = malloc(sizeof(pthread_mutex_t));
		if (!philo[i].eat_mutex || !philo[i].left_fork || !philo[i].right_fork
			|| !philo[i].print_mutex)
			return (1);
		pthread_mutex_init(philo[i].eat_mutex, NULL);
		pthread_mutex_init(philo[i].left_fork, NULL);
		pthread_mutex_init(philo[i].right_fork, NULL);
		pthread_mutex_init(philo[i].print_mutex, NULL);
		i++;
	}
	return (0);
}

void	philo_think(t_philo *philo)
{
	print_status(philo, "is thinking");
}

int	ft_usleep(int time)
{
	int	start;

	start = get_time();
	while (get_time() - start < time)
		usleep(100);
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo	*philo;
	int		i;

	if (argc < 5 || argc > 6)
		return (1);
	philo = malloc(sizeof(t_philo) * ft_atoi(argv[1]));
	if (!philo)
		return (1);
	if (init_philo(philo, argv))
		return (1);
	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		pthread_create(&philo[i].thread, NULL, philo_routine, &philo[i]);
		i++;
	}
	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	return (0);
}
