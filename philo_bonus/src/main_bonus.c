/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 11:39:59 by laoubaid          #+#    #+#             */
/*   Updated: 2024/05/11 17:31:29 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	semaphores_open(t_control *ctl)
{
	sem_unlink("semaphore_forks");
	ctl->forks = sem_open("semaphore_forks", O_CREAT, 0, ctl->num_of_philo / 2);
	sem_unlink("semaphore_print");
	ctl->print = sem_open("semaphore_print", O_CREAT, 0, 1);
	sem_unlink("semaphore_death");
	ctl->death = sem_open("semaphore_death", O_CREAT, 0, 1);
	sem_unlink("semaphore_overfed");
	ctl->overfed = sem_open("semaphore_overfed", O_CREAT, 0, ctl->num_of_philo);
	if (ctl->forks == SEM_FAILED || ctl->death == SEM_FAILED || \
	ctl->print == SEM_FAILED || ctl->overfed == SEM_FAILED)
	{
		printf("sem_open(3) error\n");
		free(ctl);
		exit(1);
	}
}

void	kill_cleaning(t_philo *philo, t_control *ctl, pid_t *pids)
{
	int		i;
	t_philo	*tmp;

	i = 0;
	while (i < ctl->num_of_philo)
	{
		tmp = philo->next;
		kill(pids[i], 9);
		free(philo);
		philo = tmp;
		i++;
	}
	sem_close(ctl->death);
	sem_close(ctl->forks);
	sem_close(ctl->print);
	sem_close(ctl->overfed);
	free(pids);
	free(ctl);
}

void	general_monitoring(t_control *ctl)
{
	int	i;

	i = 0;
	while (1)
	{
		if (ctl->death->__align == 0)
			break ;
		if (ctl->overfed->__align == 0)
		{
			usleep(100);
			break ;
		}
	}
}

int	main(int ac, char **av)
{
	t_control	*ctl;
	t_philo		*philo;
	pid_t		*pids;

	ctl = parsing(ac, av);
	semaphores_open(ctl);
	pids = malloc(sizeof(pid_t) * ctl->num_of_philo);
	if (!pids)
	{
		free(ctl);
		return (1);
	}
	philosophers_init(&philo, ctl);
	ft_philo(philo, ctl, pids);
	general_monitoring(ctl);
	kill_cleaning(philo, ctl, pids);
	return (0);
}
