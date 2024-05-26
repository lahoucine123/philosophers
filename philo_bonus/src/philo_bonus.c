/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 11:39:59 by laoubaid          #+#    #+#             */
/*   Updated: 2024/05/11 17:31:29 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	write_message(int id, long long time, t_control *ctl, char *str)
{
	sem_wait(ctl->print);
	if (ctl->status == 0)
	{
		printf("%lld\t%d %s\n", time, id + 1, str);
		sem_post(ctl->print);
		return ;
	}
	else
	{
		sem_post(ctl->print);
		sleep(10);
	}
}

void	sleep_until(long long start_time)
{
	while (ft_time(-1, -1) < start_time)
		usleep(10);
}

void	*routine(t_philo *tmp)
{
	long long	stime;
	long long	tmp_time;

	stime = tmp->ctl->start_time;
	sleep_until(stime);
	while (1)
	{
		write_message(tmp->id, ft_time(stime, -1), tmp->ctl, "is thinking");
		sem_wait(tmp->ctl->forks);
		tmp_time = ft_time(stime, -1);
		write_message(tmp->id, tmp_time, tmp->ctl, "has taken a fork");
		write_message(tmp->id, tmp_time, tmp->ctl, "has taken a fork");
		sem_wait(tmp->ctl->print);
		tmp->last_meal = ft_time(-1, -1);
		tmp->eating_times -= 1;
		sem_post(tmp->ctl->print);
		write_message(tmp->id, tmp_time, tmp->ctl, "is eating");
		ft_usleep(tmp->ctl->time_to_eat);
		sem_post(tmp->ctl->forks);
		write_message(tmp->id, ft_time(stime, -1), tmp->ctl, "is sleeping");
		ft_usleep(tmp->ctl->time_to_sleep);
		usleep(200);
	}
	return (NULL);
}

void	*monitor(t_philo *tmp)
{
	long long	stime;

	stime = tmp->ctl->start_time;
	sem_wait(tmp->ctl->print);
	while (ft_time(-1, -1) - tmp->last_meal < tmp->ctl->time_to_die)
	{
		if (tmp->eating_times == 0)
		{
			sem_wait(tmp->ctl->overfed);
			tmp->eating_times = -1;
		}
		sem_post(tmp->ctl->print);
		sem_wait(tmp->ctl->print);
	}
	tmp->ctl->status = 1;
	sem_wait(tmp->ctl->death);
	printf("%lld\t%d %s\n", ft_time(stime, -1), tmp->id + 1, "died");
	exit(0);
}

void	ft_philo(t_philo *philo, t_control *ctl, pid_t *pids)
{
	int	i;

	i = 0;
	while (i < ctl->num_of_philo)
	{
		pids[i] = fork();
		if (!pids[i])
		{
			free(pids);
			pthread_create(&philo->th, NULL, (void *)monitor, philo);
			pthread_detach(philo->th);
			routine(philo);
			sem_close(ctl->death);
			sem_close(ctl->forks);
			free(ctl);
			free(philo);
			exit(0);
		}
		philo = philo->next;
		i++;
	}
}
