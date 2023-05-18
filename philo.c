/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 00:40:35 by htalhaou          #+#    #+#             */
/*   Updated: 2023/05/18 17:35:08 by htalhaou         ###   ########.fr       */
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
		infos->philos[i].last_eat = start;
		infos->philos[i].start = start;
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
		printf("%lld %d is thinking\n", (get_time() - start), ph->id);
		printf("%lld %d is eating\n", (get_time() - start), ph->id);
		usleep(500000);
		printf("%lld %d is sleeping\n", (get_time() - start), ph->id);
		usleep(500000);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_infos	infos;
	int		i;
	int		var;

	var = ft_atoi(argv[1]);
	if (var < 0)
	{
		printf("error\n");
		return (1);
	}
	if (argc < 5 || argc > 6)
		return (1);
	infos.philos = malloc(sizeof(t_philo) * var);
	if (!infos.philos)
		return (1);
	if (init_philo(&infos, argv) || check_for_int(argv))
	{
		printf("error\n");
		return (1);
	}
	i = 0;
	while (i < var)
	{
		pthread_create(&(infos.philos[i].thread), NULL, \
		philo_routine, &infos.philos[i]);
		i++;
	}
	i = 0;
	while (i < var)
	{
		pthread_join(infos.philos[i].thread, NULL);
		i++;
	}
	return (0);
}
