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

t_control *controls_init(int ac, char **av)
{
    t_control *control;

    control = malloc(sizeof(t_control));
    control->num_of_philo = ft_atoi(av[1]);
    control->time_to_die = ft_atoi(av[2]);
    control->time_to_eat = ft_atoi(av[3]);
    control->time_to_sleep = ft_atoi(av[4]);
    if (ac == 6)
        control->num_eat = ft_atoi(av[5]);
    else
        control->num_eat = -1;
    return (control);
}

t_control *parsing(int ac, char **av)
{
    t_control *control;
    
    if (ac < 5 || ac > 6)
    {
        ft_error(1);
        return (NULL);
    }
    else
        control = controls_init(ac, av);
    if (control->num_of_philo < 2)
    {
        ft_error(3);
        return (NULL);
    }
    return (control);
}

t_philo *allocate_philo(int id)
{
    t_philo *philo;

    philo = malloc(sizeof(t_philo));
    philo->philo_id = id;
    philo->status = 1;
    philo->right_fork = 1;
    philo->left_fork = 1;
    philo->next = NULL;
    philo->prev = NULL;
    return (philo);
}

void   philosophers_init(t_philo **head, t_control *control)
{
    int i;
    t_philo *tmp1;
    t_philo *tmp2;
    
    i = 0;
    while (i < control->num_of_philo)
    {
        tmp1 = allocate_philo(i + 1);
        if (i == 0)
        {
            tmp2 = tmp1;
            *head = tmp1;
        }
        else
        {
            tmp2->next = tmp1;
            tmp1->prev = tmp2;
            tmp2 = tmp2->next;
        }
        i++;
    }
    tmp1->next = *head;
    (*head)->prev = tmp1;
}

void *start(t_philo *philo)
{
    
}

int main(int ac, char **av)
{
    int i = 0;
    t_control *control;
    t_philo *philo;
    t_philo *tmp;

    control = parsing(ac, av);
    if (!control)
        return (1);
    philosophers_init(&philo, control);
    tmp = philo;
    while (i < control->num_of_philo)
    {
        pthread_create(&tmp->thread, NULL, (void *)start, tmp);
        tmp = tmp->next;
        i++;
    }
    i = 0;
    while (i < control->num_of_philo)
    {
        pthread_join(philo->thread, NULL);
        philo = philo->next;
        i++;
    }
    return (0);
}










// typedef struct s_param
// {
//     int wait;
//     int num;
//     pthread_mutex_t *mutex;
// } t_param;

// int sui = 0;

// void *test2(void *arg)
// {
//     int i = 0;

//     while (i < 999999)
//     {
//         pthread_mutex_lock(arg);
//         sui++;
//         pthread_mutex_unlock(arg);
//         i++;
//     }
// }

// void *test(t_param *param)
// {
//     printf("thread N'%d working\n", param->num);
//     sleep(param->wait);
//     printf("thread N'%d finish duty\n", param->num);
// }

// void* test3()
// {
//     int *res = malloc(sizeof(int));
    
//     *res = 42;
//     return (void *)res;
// }

// int main()
// {
//     pthread_t th;
//     int *res;
    
//     if (pthread_create(&th, NULL, (void *)test3, NULL))
//         return 1;
//     if (pthread_join(th, (void *)&res))
//         return 2;
//     printf("res = %d\n", *res);
//     return 0;
// }

// int main(int ac, char **av)
// {
//     int i = 0;
//     int tab[5] = {9, 6, 2, 4, 0};
//     t_param param[5];
//     pthread_t th[5];
//     pthread_mutex_t mutex;
    
//     pthread_mutex_init(&mutex, NULL);
//     while (i < 5)
//     {
//         param[i].mutex = &mutex;
//         param[i].wait = tab[i];
//         param[i].num = i + 1;
//         if (pthread_create(&th[i], NULL, (void *)test, &param[i]))
//             return 1;
//         printf("thread N'%d created and on duty\n", i + 1);
//         i++;
//     }
//     i = 0;
//     while (i < 5)
//     {
//         if (pthread_join(th[i], NULL))
//             return 2;
//         i++;
//     }
//     pthread_mutex_destroy(&mutex);
//     // printf("sui = %d\n", sui);
//     return 0;
// }