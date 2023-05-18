/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 00:40:35 by htalhaou          #+#    #+#             */
/*   Updated: 2023/05/18 13:24:32 by htalhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philo(t_moad *moad, char **argv)
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
	moad->nb_philo = ft_atoi(argv[1]);
	moad->time_to_die = var2;
	moad->time_to_eat = var3;
	moad->time_to_sleep = var4;
	i = 0;
	while (i < moad->nb_philo)
	{
		moad->philos[i].id = i + 1;
		moad->philos[i].left_fork = i;
		moad->philos[i].right_fork = (i + 1) % moad->nb_philo;
		moad->philos[i].last_eat = 0; // get_time();
		moad->philos[i].moad = moad;
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
	printf("philo %d is died\n", ph->id);
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_moad	moad;
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
	moad.philos = malloc(sizeof(t_philo) * var);
	if (!moad.philos)
		return (1);
	if (init_philo(&moad, argv) || check_for_int(argv))
	{
		printf("error\n");
		return (1);
	}
	i = 0;
	while (i < var)
	{
		pthread_create(&(moad.philos[i].thread), NULL, \
		philo_routine, &moad.philos[i]);
		i++;
	}
	i = 0;
	while (i < var)
	{
		pthread_join(moad.philos[i].thread, NULL);
		i++;
	}
	return (0);
}
