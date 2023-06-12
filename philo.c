/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 00:40:35 by htalhaou          #+#    #+#             */
/*   Updated: 2023/06/12 17:36:41 by htalhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	is_eating(t_philo *ph)
{
	pthread_mutex_lock(&(ph->infos->forks[ph->left_fork]));
	print_msg(ph, "has taken a fork");
	pthread_mutex_lock(&(ph->infos->forks[ph->right_fork]));
	print_msg(ph, "has taken a fork");
	print_msg(ph, "is eating");
	pthread_mutex_lock(&ph->infos->control);
	ph->last_eat = get_time();
	pthread_mutex_unlock(&ph->infos->control);
	ph->count_meals++;
	mine_usleep(ph->infos->time_to_eat, ph);
	pthread_mutex_lock(&ph->infos->control);
	if (ph->count_meals >= ph->infos->nb_of_eat && ph->infos->nb_of_eat != -1)
		ph->fin = 1;
	pthread_mutex_unlock(&ph->infos->control);
	pthread_mutex_unlock(&(ph->infos->forks[ph->left_fork]));
	pthread_mutex_unlock(&(ph->infos->forks[ph->right_fork]));
}

void	*philo_routine(void *philo)
{
	t_philo		*ph;
	t_infos		*infos;
	// int			var;

	ph = (t_philo *)philo;
	infos = ph->infos;
	// pthread_mutex_lock(&infos->control);
	// var = *ph->di;
	// pthread_mutex_unlock(&infos->control);
	if (ph->id % 2 == 0)
		usleep(200);
	help(ph, infos);
	return (NULL);
}

int	initialize_resources(t_infos *infos, char **argv, int *died)
{
	int	i;

	if (ft_atoi(argv[1]) < 0)
		return (printf("error\n"), 1);
	infos->forks = malloc(sizeof(pthread_mutex_t) * ft_atoi(argv[1]));
	if (!infos->forks)
		return (1);
	i = 0;
	while (i < ft_atoi(argv[1]))
		pthread_mutex_init(&(infos->forks[i++]), NULL);
	pthread_mutex_init(&infos->print, NULL);
	pthread_mutex_init(&infos->control, NULL);
	infos->philos = malloc(sizeof(t_philo) * ft_atoi(argv[1]));
	if (!infos->philos)
		return (1);
	if (init_philo(infos, argv, died) || check_for_int(argv))
	{
		free(infos->philos);
		free(infos->forks);
		return (printf("error\n"), 1);
	}
	return (0);
}

int	start_philosophers(t_infos *infos, char **argv, int *died)
{
	int	i;

	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		if (pthread_create(&(infos->philos[i].thread), NULL, \
		philo_routine, &infos->philos[i]))
			return (1);
		usleep(5);
		i++;
	}
	i = 0;
	check_dead(infos, died);
	while (i < ft_atoi(argv[1]))
	{
		pthread_mutex_destroy(&(infos->forks[i]));
		i++;
	}
	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		pthread_join(infos->philos[i].thread, NULL);
		i++;
	}
	return (free(infos->philos), free(infos->forks), 0);
}

int	main(int argc, char **argv)
{
	t_infos	infos;
	int		died;

	died = 1;
	if (argc < 5 || argc > 6)
		return (printf("error\n"), 1);
	if (initialize_resources(&infos, argv, &died))
		return (1);
	return (start_philosophers(&infos, argv, &died));
}
