/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 19:23:09 by htalhaou          #+#    #+#             */
/*   Updated: 2023/05/21 20:23:43 by htalhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_and_set_values(t_infos *infos, char **argv)
{
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
	return (0);
}

int	init_philosophers(t_infos *infos, long long time, int *died)
{
	int	i;

	i = 0;
	while (i < infos->nb_philo)
	{
		infos->philos[i].id = i + 1;
		infos->di = died;
		infos->philos[i].left_fork = i;
		infos->philos[i].right_fork = (i + 1) % infos->nb_philo;
		infos->philos[i].last_eat = time;
		infos->philos[i].start = time;
		infos->philos[i].infos = infos;
		i++;
	}
	return (0);
}
