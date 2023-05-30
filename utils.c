/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 22:19:38 by htalhaou          #+#    #+#             */
/*   Updated: 2023/05/30 19:54:46 by htalhaou         ###   ########.fr       */
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
	while (get_time() - start <= time)
		usleep(100);
}

int	is_died(t_philo *ph)
{
	int			i;

	pthread_mutex_lock((ph->infos->print));
	if (get_time() - ph->last_eat >= ph->infos->time_to_die)
	{
		pthread_mutex_lock(&(ph->infos->die));
		*ph->infos->di = 0;
		pthread_mutex_unlock(&(ph->infos->die));
		printf("%lld %d %s\n", (get_time() - ph->start), ph->id, "died");
		pthread_mutex_unlock((ph->infos->print));
		if (ph->infos->nb_philo == 1)
			pthread_mutex_unlock(&(ph->infos->forks[ph->left_fork]));
		i = 0;
		while (i < ph->infos->nb_philo)
		{
			pthread_mutex_unlock(&(ph->infos->forks[i]));
			i++;
		}
		return (1);
	}
	pthread_mutex_unlock((ph->infos->print));
	return (0);
}

void	print_msg(t_philo *ph, char *str)
{
	int	var;

	pthread_mutex_lock(&(ph->infos->die));
	var = *ph->infos->di;
	pthread_mutex_unlock(&(ph->infos->die));
	pthread_mutex_lock((ph->infos->print));
	if (var)
	{
		// pthread_mutex_unlock((ph->infos->print));
		printf("%lld %d %s\n", (get_time() - ph->start), ph->id, str);
		// pthread_mutex_unlock((ph->infos->print));
	}
	pthread_mutex_unlock((ph->infos->print));
}
