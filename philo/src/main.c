/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 11:39:59 by laoubaid          #+#    #+#             */
/*   Updated: 2024/05/11 17:31:29 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(t_philo *philo)
{
	long long	stime;

	stime = philo->ctl->start_time;
	write_message(ft_time(stime, -1), philo, "is thinking");
	first_meal(philo, stime);
	usleep(500);
	pthread_mutex_lock(&philo->ctl->mutex);
	while (philo->ctl->status == 0)
	{
		pthread_mutex_unlock(&philo->ctl->mutex);
		philo_cycle(philo, stime);
		usleep(500);
		pthread_mutex_lock(&philo->ctl->mutex);
	}
	pthread_mutex_unlock(&philo->ctl->mutex);
	ft_usleep(500);
	return (NULL);
}

void	monitor(t_philo *philo, long long stime)
{
	t_philo		*tmp;

	tmp = philo;
	while (1)
	{
		pthread_mutex_lock(&philo->ctl->mutex);
		if (ft_time(-1, tmp->last_meal) > tmp->ctl->time_to_die)
		{
			pthread_mutex_unlock(&philo->ctl->mutex);
			break ;
		}
		if (check_if_full(philo) && philo->ctl->num_eat != -1)
		{
			philo->ctl->status = 1;
			pthread_mutex_unlock(&philo->ctl->mutex);
			return ;
		}
		pthread_mutex_unlock(&philo->ctl->mutex);
		tmp = tmp->next;
	}
	pthread_mutex_lock(&philo->ctl->mutex);
	philo->ctl->status = 1;
	pthread_mutex_unlock(&philo->ctl->mutex);
	printf("%lld\t%d %s\n", ft_time(-1, -1) - stime, tmp->philo_id + 1, "died");
}

void	ft_philo(t_control *ctl, t_philo *philo)
{
	int			i;
	t_philo		*tmp;

	i = 0;
	tmp = philo;
	if (ctl->num_of_philo == 1)
		pthread_create(&philo->thread, NULL, (void *)one, philo);
	else
		multi_threads(philo, ctl->num_of_philo);
	tmp = philo->next;
	monitor(philo, ctl->start_time);
	while (i < ctl->num_of_philo)
	{
		pthread_join(tmp->thread, NULL);
		tmp = tmp->next;
		i++;
	}
	ft_clean(philo, ctl, ctl->num_of_philo);
}

int	main(int ac, char **av)
{
	t_control	*control;
	t_philo		*philo;

	control = parsing(ac, av);
	if (!control)
		return (1);
	if (control->num_eat == 0)
	{
		free(control->forks);
		free(control);
		return (0);
	}
	philosophers_init(&philo, control);
	ft_philo(control, philo);
	return (0);
}
