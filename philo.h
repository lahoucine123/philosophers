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

typedef struct s_control
{
    int num_of_philo;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int num_eat;
}   t_control;

typedef struct s_philo 
{
    int philo_id;
    int status;
    int right_fork;
    int left_fork;
    pthread_t thread;
    struct s_philo *next;
    struct s_philo *prev;
}   t_philo;

/* utils functions */
int	    ft_atoi(char *str);

/* error functions */
void    ft_usage(void);
void    ft_error(int opt);
