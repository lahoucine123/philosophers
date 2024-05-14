/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 18:03:48 by laoubaid          #+#    #+#             */
/*   Updated: 2024/05/11 17:22:33 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <sys/time.h>

typedef struct s_control
{
	int		num_of_philo;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		num_eat;
	int				status;
	long long		start_time;
	pthread_mutex_t	mutex;
	pthread_mutex_t	*forks;
}	t_control;

typedef struct s_philo 
{
	int				philo_id;
	int				eating_times;
	long long		last_meal;
	pthread_t		thread;
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;
	t_control		*ctl;
	struct s_philo	*next;
}	t_philo;

typedef struct timeval	t_time;


/* utils functions */
int			ft_atoi(char *str);

/* error functions */
void		ft_usage(void);
void		ft_error(int opt);

/* time functions */
long long	ft_time(long long start_time, long long last_meal);
void		ft_usleep(int sleeptime);

/* initialization functions */
t_philo *allocate_philo(int id, t_control *ctl);
void philosophers_init(t_philo **head, t_control *ctl);
t_control *controls_init(int ac, char **av);
t_control *parsing(int ac, char **av);
