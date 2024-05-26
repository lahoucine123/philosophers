/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 18:03:48 by laoubaid          #+#    #+#             */
/*   Updated: 2024/05/11 19:26:50 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	ft_time(long long curr_time, long long last_meal)
{
	t_time		tv;
	long long	tmp;

	gettimeofday(&tv, NULL);
	tmp = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	if (curr_time == -1 && last_meal == -1)
		return (tmp);
	if (last_meal != -1)
		return (tmp - last_meal);
	return (tmp - curr_time);
}

void	ft_usleep_pro(int sleeptime, t_control *ctl)
{
	t_time		tv;
	long long	tmp;

	gettimeofday(&tv, NULL);
	tmp = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	while ((tv.tv_sec * 1000 + tv.tv_usec / 1000) - tmp < sleeptime)
	{
		pthread_mutex_lock(&ctl->mutex);
		if (ctl->status)
		{
			pthread_mutex_unlock(&ctl->mutex);
			break ;
		}
		pthread_mutex_unlock(&ctl->mutex);
		usleep(1);
		gettimeofday(&tv, NULL);
	}
}

void	ft_usleep(int sleeptime)
{
	t_time		tv;
	long long	tmp;

	gettimeofday(&tv, NULL);
	tmp = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	while ((tv.tv_sec * 1000 + tv.tv_usec / 1000) - tmp < sleeptime)
	{
		usleep(1);
		gettimeofday(&tv, NULL);
	}
}
