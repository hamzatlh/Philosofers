/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 22:19:38 by htalhaou          #+#    #+#             */
/*   Updated: 2023/05/21 20:27:47 by htalhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time(void)
{
	struct timeval	time;
	int				var;

	var = gettimeofday(&time, NULL);
	if (var == -1)
		return (-1);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	mine_usleep(long long time)
{
	long long	start;

	start = get_time();
	while (get_time() - start < time)
		usleep(100);
}

int	is_died(t_philo *ph)
{
	t_infos		*infos;
	int			i;

	infos = ph->infos;
	if (get_time() - ph->last_eat > ph->infos->time_to_die)
	{
		print_msg(ph, "died");
		*infos->di = 0;
		if (infos->nb_philo == 1)
			pthread_mutex_unlock(&(infos->forks[ph->left_fork]));
		i = 0;
		while (i < infos->nb_philo)
		{
			pthread_mutex_unlock(&(infos->forks[i]));
			i++;
		}
		return (1);
	}
	return (0);
}

void	print_msg(t_philo *ph, char *str)
{
	if (*ph->infos->di)
	{
		pthread_mutex_lock(&(ph->infos->print));
		printf("%lld %d %s\n", (get_time() - ph->start), ph->id, str);
		pthread_mutex_unlock(&(ph->infos->print));
	}
}
