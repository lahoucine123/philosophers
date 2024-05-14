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

void write_message(long long time, t_philo *philo, char *str)
{
    if (philo->ctl->status == 0)
    {
        pthread_mutex_lock(&philo->ctl->mutex);
        printf("%lld\t%d %s\n", time, philo->philo_id, str);
        pthread_mutex_unlock(&philo->ctl->mutex);
    }
    else
        usleep(500);
}

void    first_meal(t_philo *philo, long long stime)
{
    if (philo->ctl->num_of_philo % 2)
    {
        if (philo->philo_id % 2 == 0 && philo->philo_id != philo->ctl->num_of_philo - 1)
        {
            if (philo->ctl->status)
                return ;
            pthread_mutex_lock(philo->first_fork);
            if (philo->ctl->status)
            {
                pthread_mutex_unlock(philo->first_fork);
                return ;
            }
            write_message(ft_time(stime, -1), philo, "has taken a fork");
            pthread_mutex_lock(philo->second_fork);
            if (philo->ctl->status)
            {
                pthread_mutex_unlock(philo->second_fork);
                return ;
            }
            write_message(ft_time(stime, -1), philo, "has taken a fork");
            write_message(ft_time(stime, -1), philo, "is eating");
            pthread_mutex_lock(&philo->ctl->mutex);
            philo->last_meal = ft_time(-1, -1);
            philo->eating_times++;
            pthread_mutex_unlock(&philo->ctl->mutex);
            ft_usleep(philo->ctl->time_to_eat);
            pthread_mutex_unlock(philo->second_fork);
            pthread_mutex_unlock(philo->first_fork);
            write_message(ft_time(stime, -1), philo, "is sleeping");
            ft_usleep(philo->ctl->time_to_sleep);
            write_message(ft_time(stime, -1), philo, "is thinking");
        }
    }
    else
    {
        if (philo->philo_id % 2 == 0)
        {
            pthread_mutex_lock(philo->first_fork);
            write_message(ft_time(stime, -1), philo, "has taken a fork");
            pthread_mutex_lock(philo->second_fork);
            write_message(ft_time(stime, -1), philo, "has taken a fork");
            write_message(ft_time(stime, -1), philo, "is eating");
            pthread_mutex_lock(&philo->ctl->mutex);
            philo->last_meal = ft_time(-1, -1);
            philo->eating_times++;
            pthread_mutex_unlock(&philo->ctl->mutex);
            ft_usleep(philo->ctl->time_to_eat);
            pthread_mutex_unlock(philo->second_fork);
            pthread_mutex_unlock(philo->first_fork);
            write_message(ft_time(stime, -1), philo, "is sleeping");
            ft_usleep(philo->ctl->time_to_sleep);
            write_message(ft_time(stime, -1), philo, "is thinking");
        }
    }
}

void *routine(t_philo *philo)
{
    long long stime;

    stime = philo->ctl->start_time;
    write_message(ft_time(stime, -1), philo, "is thinking");
    first_meal(philo, stime);
    usleep(500);
    while (1)
    {
        pthread_mutex_lock(philo->first_fork);
        write_message(ft_time(stime, -1), philo, "has taken a fork");
        pthread_mutex_lock(philo->second_fork);
        write_message(ft_time(stime, -1), philo, "has taken a fork");
        write_message(ft_time(stime, -1), philo, "is eating");
        pthread_mutex_lock(&philo->ctl->mutex);
        philo->last_meal = ft_time(-1, -1);
        philo->eating_times++;
        pthread_mutex_unlock(&philo->ctl->mutex);
        ft_usleep(philo->ctl->time_to_eat);
        pthread_mutex_unlock(philo->second_fork);
        pthread_mutex_unlock(philo->first_fork);
        write_message(ft_time(stime, -1), philo, "is sleeping");
        ft_usleep(philo->ctl->time_to_sleep);
        write_message(ft_time(stime, -1), philo, "is thinking");
        usleep(500);
    }
    return NULL;
}

int check_if_full(t_philo *tmp, int num)
{
    int i;

    i = 0;
    while (tmp->eating_times >= tmp->ctl->num_eat && i <= num)
    {
        i++;
        tmp = tmp->next;
    }
    if (i >= tmp->ctl->num_of_philo)
        return (1);
    return (0);
}

void monitor(t_philo *philo)
{
    long long curr_time;
    long long stime;
    t_philo *tmp_ph;

    stime = philo->ctl->start_time;
    tmp_ph = philo;

    while (1)
    {
        pthread_mutex_lock(&philo->ctl->mutex);
        if (ft_time(-1, tmp_ph->last_meal) > tmp_ph->ctl->time_to_die)
        {
            pthread_mutex_unlock(&philo->ctl->mutex);
            break ;
        }
        if (check_if_full(philo, philo->ctl->num_of_philo) && philo->ctl->num_eat != -1)
            return;
        pthread_mutex_unlock(&philo->ctl->mutex);
        tmp_ph = tmp_ph->next;
    }
    curr_time = ft_time(-1, -1);
    pthread_mutex_lock(&philo->ctl->mutex);
    philo->ctl->status = 1;
    pthread_mutex_unlock(&philo->ctl->mutex);
    printf("%lld\t%d %s\n", curr_time - stime, philo->philo_id, "died");
}

int main(int ac, char **av)
{
    int i = 0;
    t_control *control;
    t_philo *philo;
    t_philo *tmp;

    control = parsing(ac, av);
    philosophers_init(&philo, control);
    tmp = philo;
    while (i < control->num_of_philo)
    {
        pthread_create(&tmp->thread, NULL, (void *)routine, tmp);
        tmp = tmp->next;
        if (tmp->philo_id % 2 == 0)
            usleep(10);
        i++;
    }
    monitor(philo);
    int n;
    n = control->num_of_philo;
    while (i < n)
    {
        pthread_mutex_destroy(control->forks + i);
        i++;
    }
    return (0);
}
