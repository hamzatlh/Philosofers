/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 00:40:35 by htalhaou          #+#    #+#             */
/*   Updated: 2023/05/21 20:27:26 by htalhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philo(t_infos *infos, char **argv, int *died)
{
	long long	time;

	time = get_time();
	if (check_and_set_values(infos, argv) == 1)
		return (1);
	return (init_philosophers(infos, time, died));
}

void	*philo_routine(void *philo)
{
	t_philo		*ph;
	t_infos		*infos;

	ph = (t_philo *)philo;
	infos = ph->infos;
	while (*infos->di)
	{
		print_msg(ph, "is thinking");
		pthread_mutex_lock(&(infos->forks[ph->left_fork]));
		pthread_mutex_lock(&(infos->forks[ph->right_fork]));
		print_msg(ph, "is eating");
		ph->last_eat = get_time();
		mine_usleep(ph->infos->time_to_eat);
		pthread_mutex_unlock(&(infos->forks[ph->left_fork]));
		pthread_mutex_unlock(&(infos->forks[ph->right_fork]));
		print_msg(ph, "is sleeping");
		mine_usleep(ph->infos->time_to_sleep);
	}
	return (NULL);
}

int	initialize_resources(t_infos *infos, int argc, char **argv, int *died)
{
	int	i;

	if (ft_atoi(argv[1]) < 0)
		return (printf("error\n"), 1);
	if (argc < 5 || argc > 6)
		return (1);
	infos->forks = malloc(sizeof(pthread_mutex_t) * ft_atoi(argv[1]));
	if (!infos->forks)
		return (1);
	i = 0;
	while (i < ft_atoi(argv[1]))
		pthread_mutex_init(&(infos->forks[i++]), NULL);
	pthread_mutex_init(&(infos->print), NULL);
	infos->philos = malloc(sizeof(t_philo) * ft_atoi(argv[1]));
	if (!infos->philos)
		return (1);
	if (init_philo(infos, argv, died) || check_for_int(argv))
		return (printf("error\n"), 1);
	return (0);
}

int	start_philosophers(t_infos *infos, char **argv)
{
	int	i;

	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		pthread_create(&(infos->philos[i].thread), NULL, \
		philo_routine, &infos->philos[i]);
		usleep(10);
		i++;
	}
	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		if (is_died(&infos->philos[i]))
			break ;
		i = (i + 1) % ft_atoi(argv[1]);
	}
	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		pthread_join(infos->philos[i].thread, NULL);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_infos	infos;
	int		died;

	died = 1;
	if (initialize_resources(&infos, argc, argv, &died))
		return (1);
	return (start_philosophers(&infos, argv));
}
