/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 11:39:59 by laoubaid          #+#    #+#             */
/*   Updated: 2024/05/11 17:31:29 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <fcntl.h>
# include <semaphore.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <string.h>

typedef struct timeval	t_time;

typedef struct s_control
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_eat;
	long long		start_time;
	int				status;
	sem_t			*forks;
	sem_t			*death;
	sem_t			*print;
	sem_t			*overfed;
}	t_control;

typedef struct s_philo
{
	int				id;
	int				eating_times;
	t_control		*ctl;
	pthread_t		th;
	struct s_philo	*next;
	long long		last_meal;
}	t_philo;

/* time and sleeping functions*/
long long	ft_time(long long curr_time, long long last_meal);
void		ft_usleep(int sleeptime);
void		sleep_until(long long start_time);

/* parsing and initialisation functions */
int			ft_atoi(char *str, t_control *ctl);
void		ft_usage(void);
void		ft_error(int opt);
t_control	*controls_init(int ac, char **av, t_control *control);
t_control	*parsing(int ac, char **av);
t_philo		*allocate_philo(int id, t_control *ctl);
void		philosophers_init(t_philo **head, t_control *ctl);
void		clean_exit(t_control *ctl);

/* algorithme main functions */
void		write_message(int id, long long time, t_control *ctl, char *str);
void		*routine(t_philo *tmp);
void		*monitor(t_philo *tmp);
void		semaphores_open(t_control *ctl);
void		ft_philo(t_philo *philo, t_control *ctl, pid_t *pids);
void		kill_cleaning(t_philo *philo, t_control *ctl, pid_t *pids);

#endif