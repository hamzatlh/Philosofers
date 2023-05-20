/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 00:40:35 by htalhaou          #+#    #+#             */
/*   Updated: 2023/05/20 22:39:27 by htalhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philo(t_infos *infos, char **argv)
{
	int	i;
	int	start;

	if (ft_atoi(argv[2]) < 0 || ft_atoi(argv[3]) < 0 \
	|| ft_atoi(argv[4]) < 0 || ft_atoi(argv[1]) < 0)
	{
		printf("error\n");
		return (1);
	}
	infos->nb_philo = ft_atoi(argv[1]);
	infos->time_to_die = ft_atoi(argv[2]);
	infos->time_to_eat = ft_atoi(argv[3]);
	infos->time_to_sleep = ft_atoi(argv[4]);
	i = 0;
	start = get_time();
	while (i < infos->nb_philo)
	{
		infos->philos[i].id = i + 1;
		infos->philos[i].left_fork = i;
		infos->philos[i].right_fork = (i + 1) % infos->nb_philo;
		infos->philos[i].last_eat = get_time();
		infos->philos[i].start = get_time();
		infos->philos[i].infos = infos;
		i++;
	}
	return (0);
}

void	*philo_routine(void *philo)
{
	t_philo		*ph;
	t_infos		*infos;
	long long	start;
	int			i;

	ph = (t_philo *)philo;
	start = get_time();
	infos = ph->infos;
	i = 1;
	while (1)
	{
		pthread_mutex_lock(&(infos->print));
		printf("%lld %d is thinking\n", (get_time() - start), ph->id);
		pthread_mutex_unlock(&(infos->print));
		pthread_mutex_lock(&(infos->forks[ph->left_fork]));
		pthread_mutex_lock(&(infos->forks[ph->right_fork]));
		pthread_mutex_lock(&(infos->print));
		if (infos->is_died)
			exit(0);
		printf("%lld %d is eating\n", (get_time() - start), ph->id);
		pthread_mutex_unlock(&(infos->print));
		ph->last_eat = get_time();
		if (infos->is_died)
			exit(0);
		mine_usleep(200);
		pthread_mutex_unlock(&(infos->forks[ph->right_fork]));
		pthread_mutex_unlock(&(infos->forks[ph->left_fork]));
		pthread_mutex_lock(&(infos->print));
		printf("%lld %d is sleeping\n", (get_time() - start), ph->id);
		pthread_mutex_unlock(&(infos->print));
		if (infos->is_died)
			exit(0);
		mine_usleep(200);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_infos	infos;
	int		i;

	if (ft_atoi(argv[1]) < 0)
	{
		printf("error\n");
		return (1);
	}
	if (argc < 5 || argc > 6)
		return (1);
	infos.philos = malloc(sizeof(t_philo) * ft_atoi(argv[1]));
	if (!infos.philos)
		return (1);
	infos.is_died = 0;
	if (init_philo(&infos, argv) || check_for_int(argv))
	{
		printf("error\n");
		return (1);
	}
	infos.forks = malloc(sizeof(pthread_mutex_t) * infos.nb_philo);
	if (!infos.forks)
		return (1);
	i = 0;
	while (i < infos.nb_philo)
	{
		pthread_mutex_init(&(infos.forks[i]), NULL);
		i++;
	}
	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		pthread_create(&(infos.philos[i].thread), NULL, \
		philo_routine, &infos.philos[i]);
		usleep(100);
		i++;
	}
	while (1)
	{
		i = 0;
		while (i < ft_atoi(argv[1]))
		{
			if (is_died(&infos.philos[i]))
				return (0);
			i++;
		}
	}
	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		pthread_join(infos.philos[i].thread, NULL);
		i++;
	}
	return (0);
}
