/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 22:19:38 by htalhaou          #+#    #+#             */
/*   Updated: 2023/06/13 17:46:56 by htalhaou         ###   ########.fr       */
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

void	mine_usleep(long long time, t_philo	*ph)
{
	long long	start;

	start = get_time();
	while (get_time() - start < time)
	{
		pthread_mutex_lock(&ph->infos->print);
		if (*ph->di == 0 || ph->infos->fin_2 == 1)
		{
			pthread_mutex_unlock(&ph->infos->print);
			break ;
		}
		pthread_mutex_unlock(&ph->infos->print);
		usleep(200);
	}
}

int	is_died(t_philo *ph, int *died)
{
	long		var;

	pthread_mutex_lock(&ph->infos->print);
	var = get_time() - ph->last_eat;
	pthread_mutex_unlock(&ph->infos->print);
	if (var >= ph->infos->time_to_die)
	{
		pthread_mutex_lock(&ph->infos->print);
		*died = 0;
		pthread_mutex_unlock(&ph->infos->print);
		pthread_mutex_lock(&ph->infos->print);
		printf("%lld %d %s\n", (get_time() - ph->start), ph->id, "died");
		pthread_mutex_unlock((&ph->infos->print));
		if (ph->infos->nb_philo == 1)
			pthread_mutex_unlock(&(ph->infos->forks[ph->left_fork]));
		return (1);
	}
	return (0);
}

void	print_msg(t_philo *ph, char *str)
{
	pthread_mutex_lock(&ph->infos->print);
	if (*ph->di)
		printf("%lld %d %s\n", (get_time() - ph->start), ph->id, str);
	pthread_mutex_unlock(&(ph->infos->print));
}

int	check_is_fin(t_philo *ph)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < ph->infos->nb_philo)
	{
		pthread_mutex_lock(&ph->infos->print);
		if (ph->infos->philos[i].fin == 1)
			count++;
		pthread_mutex_unlock(&ph->infos->print);
		i++;
	}
	return (count);
}
