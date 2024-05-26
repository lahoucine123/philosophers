/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 11:39:59 by laoubaid          #+#    #+#             */
/*   Updated: 2024/05/11 17:31:29 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_philo	*allocate_philo(int id, t_control *ctl)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->id = id;
	philo->next = NULL;
	philo->ctl = ctl;
	philo->last_meal = ctl->start_time;
	philo->eating_times = ctl->num_eat;
	return (philo);
}

void	philosophers_init(t_philo **head, t_control *ctl)
{
	int		i;
	t_philo	*tmp1;
	t_philo	*tmp2;

	i = 0;
	while (i < ctl->num_of_philo)
	{
		tmp1 = allocate_philo(i, ctl);
		if (i == 0)
		{
			tmp2 = tmp1;
			*head = tmp1;
		}
		else
		{
			tmp2->next = tmp1;
			tmp2 = tmp2->next;
		}
		i++;
	}
	tmp1->next = *head;
}

t_control	*controls_init(int ac, char **av, t_control *control)
{
	int			i;

	i = 0;
	control = malloc(sizeof(t_control));
	if (!control)
		return (NULL);
	control->num_of_philo = ft_atoi(av[1], control);
	control->time_to_die = ft_atoi(av[2], control);
	control->time_to_eat = ft_atoi(av[3], control);
	control->time_to_sleep = ft_atoi(av[4], control);
	control->num_eat = -1;
	if (ac == 6)
		control->num_eat = ft_atoi(av[5], control);
	control->start_time = ft_time(-1, -1) + 400;
	control->status = 0;
	control->forks = NULL;
	return (control);
}

t_control	*parsing(int ac, char **av)
{
	t_control	*control;

	if (ac < 5 || ac > 6)
	{
		ft_error(1);
		return (NULL);
	}
	else
		control = controls_init(ac, av, NULL);
	if (control->num_of_philo < 1)
	{
		ft_error(3);
		return (NULL);
	}
	return (control);
}
