/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:02:13 by htalhaou          #+#    #+#             */
/*   Updated: 2023/05/17 19:03:34 by htalhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_for_int(char **arg)
{
	int	i;
	int	j;

	if (!arg)
		return (1);
	i = 1;
	while (arg[i])
	{
		j = 0;
		while (arg[i][j])
		{
			if (!(arg[i][j] >= '0' && arg[i][j] <= '9') && (arg[i][j] != '+'))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
