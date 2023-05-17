/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 00:40:35 by htalhaou          #+#    #+#             */
/*   Updated: 2023/05/17 19:23:39 by htalhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philo(t_philo *philo, char **argv)
{
	int	i;
	int	var2;
	int	var3;
	int	var4;

	var2 = ft_atoi(argv[2]);
	var3 = ft_atoi(argv[3]);
	var4 = ft_atoi(argv[4]);
	if (var2 < 0 || var3 < 0 || var4 < 0)
	{
		printf("error\n");
		return (1);
	}
	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		philo[i].id = i + 1;
		philo[i].time_to_die = ft_atoi(argv[2]);
		philo[i].time_to_eat = ft_atoi(argv[3]);
		philo[i].time_to_sleep = ft_atoi(argv[4]);
		i++;
	}
	return (0);
}

void	*philo_routine(void	*philo)
{
	t_philo	*ph;

	ph = (void *)philo;
	printf("philo %d is thinking\n", ph->id);
	printf("philo %d is eating\n", ph->id);
	printf("philo %d is sleeping\n", ph->id);
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_philo	*philo;
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
	philo = malloc(sizeof(t_philo) * var);
	if (!philo)
		return (1);
	if (init_philo(philo, argv) || check_for_int(argv))
	{
		printf("error\n");
		return (1);
	}
	i = 0;
	while (i < var)
	{
		pthread_create(&(philo[i].thread), NULL, philo_routine, &philo[i]);
		i++;
	}
	i = 0;
	while (i < var)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	return (0);
}
