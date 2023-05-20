/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 22:19:38 by htalhaou          #+#    #+#             */
/*   Updated: 2023/05/20 22:45:17 by htalhaou         ###   ########.fr       */
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

	infos = ph->infos;
	if (get_time() - ph->last_eat >= ph->infos->time_to_die)
	{
		pthread_mutex_lock(&(infos->print));
		printf("%lld %d died\n", (get_time() - ph->start), ph->id);
		pthread_mutex_unlock(&(infos->print));
		infos->is_died = 1;
		return (1);
	}
	return (0);
}
