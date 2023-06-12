/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 19:23:09 by htalhaou          #+#    #+#             */
/*   Updated: 2023/06/12 17:41:39 by htalhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_and_set_values(t_infos *infos, char **argv)
{
	if (ft_atoi(argv[2]) < 0 || ft_atoi(argv[3]) < 0 \
	|| ft_atoi(argv[4]) < 0 || ft_atoi(argv[1]) < 0 \
	|| (argv[5] && ft_atoi(argv[5]) < 0))
		return (1);
	infos->nb_philo = ft_atoi(argv[1]);
	infos->time_to_die = ft_atoi(argv[2]);
	infos->time_to_eat = ft_atoi(argv[3]);
	infos->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		infos->nb_of_eat = ft_atoi(argv[5]);
	else
		infos->nb_of_eat = -1;
	return (0);
}

int	init_philosophers(t_infos *infos, long long time, int *died)
{
	int	i;

	i = 0;
	(void)time;
	// time = get_time();
	infos->fin_2 = 0;
	while (i < infos->nb_philo)
	{
		infos->philos[i].id = i + 1;
		infos->philos[i].di = died;
		infos->philos[i].fin = 0;
		infos->philos[i].left_fork = i;
		infos->philos[i].right_fork = (i + 1) % infos->nb_philo;
		infos->philos[i].last_eat = get_time();
		infos->philos[i].start = get_time();
		infos->philos[i].infos = infos;
		i++;
	}
	return (0);
}

int	init_philo(t_infos *infos, char **argv, int *died)
{
	long long	time;

	time = get_time();
	if (check_and_set_values(infos, argv) == 1)
		return (1);
	return (init_philosophers(infos, time, died));
}

void	check_dead(t_infos *infos, int *died)
{
	int	i;

	i = 0;
	while (1)
	{
		if (i == infos->nb_philo)
			i = 0;
		if (is_died(&infos->philos[i], died))
			break ;
		if (check_is_fin(&infos->philos[i]) == infos->nb_philo)
		{
			pthread_mutex_lock(&infos->control);
			infos->fin_2 = 1;
			pthread_mutex_unlock(&infos->control);
			break ;
		}
		i++;
	}
}

void	help(t_philo *ph, t_infos *infos)
{
	while (*ph->di)
	{
		print_msg(ph, "is thinking");
		is_eating(ph);
		print_msg(ph, "is sleeping");
		mine_usleep(ph->infos->time_to_sleep, ph);
		pthread_mutex_lock(&ph->infos->control);
		if (infos->fin_2 == 1)
		{
			pthread_mutex_unlock(&ph->infos->control);
			break ;
		}
		pthread_mutex_unlock(&ph->infos->control);
		// pthread_mutex_lock(&ph->infos->control);
		// var = *ph->di;
		// pthread_mutex_unlock(&ph->infos->control);
	}
}
