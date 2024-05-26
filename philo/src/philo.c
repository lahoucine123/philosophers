/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 18:03:48 by laoubaid          #+#    #+#             */
/*   Updated: 2024/05/11 17:22:33 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_message(long long time, t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->ctl->mutex);
	if (philo->ctl->status == 0)
	{
		printf("%lld\t%d %s\n", time, philo->philo_id + 1, str);
		pthread_mutex_unlock(&philo->ctl->mutex);
	}
	else
	{
		pthread_mutex_unlock(&philo->ctl->mutex);
		usleep(50);
	}
}

void	philo_cycle(t_philo *tmp, long long stime)
{
	pthread_mutex_lock(tmp->first_fork);
	write_message(ft_time(stime, -1), tmp, "has taken a fork");
	pthread_mutex_lock(tmp->second_fork);
	write_message(ft_time(stime, -1), tmp, "has taken a fork");
	write_message(ft_time(stime, -1), tmp, "is eating");
	pthread_mutex_lock(&tmp->ctl->mutex);
	if (tmp->ctl->status)
	{
		pthread_mutex_unlock(tmp->second_fork);
		pthread_mutex_unlock(tmp->first_fork);
		pthread_mutex_unlock(&tmp->ctl->mutex);
		return ;
	}
	tmp->last_meal = ft_time(-1, -1);
	tmp->eating_times++;
	pthread_mutex_unlock(&tmp->ctl->mutex);
	ft_usleep_pro(tmp->ctl->time_to_eat, tmp->ctl);
	pthread_mutex_unlock(tmp->second_fork);
	pthread_mutex_unlock(tmp->first_fork);
	write_message(ft_time(stime, -1), tmp, "is sleeping");
	ft_usleep_pro(tmp->ctl->time_to_sleep, tmp->ctl);
	write_message(ft_time(stime, -1), tmp, "is thinking");
}

void	first_meal(t_philo *philo, long long stime)
{
	int	n;

	n = philo->ctl->num_of_philo;
	if (n % 2)
	{
		if (philo->philo_id % 2 == 0 && philo->philo_id != n - 1)
			philo_cycle(philo, stime);
	}
	else
	{
		if (philo->philo_id % 2 == 0)
			philo_cycle(philo, stime);
	}
}

void	one(t_philo *tmp)
{
	long long	stime;

	stime = tmp->ctl->start_time;
	write_message(ft_time(stime, -1), tmp, "has taken a fork");
}

void	multi_threads(t_philo *tmp, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		if (pthread_create(&tmp->thread, NULL, (void *)routine, tmp))
		{
			printf("Error: pthread_create failed!\n");
			return ;
		}
		tmp = tmp->next;
		i++;
	}
}
