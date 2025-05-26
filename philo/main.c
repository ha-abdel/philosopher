
#include "../philo.h"



void    handle_even_thread(t_philo **philo)
{
    pthread_mutex_lock((*philo)->left);
    precise_usleep(100);
    pthread_mutex_lock((*philo)->right);
    
    eat(philo);
    sleep(philo);
    think(philo);

    pthread_mutex_unlock((*philo)->left);
    pthread_mutex_unlock((*philo)->right);
}
void    handle_odd_thread(t_philo **philo)
{
    pthread_mutex_lock((*philo)->right);
    precise_usleep(100);
    pthread_mutex_lock((*philo)->left);

    pthread_mutex_unlock((*philo)->right);
    pthread_mutex_unlock((*philo)->left);
}

void    *routine(void *ptr)
{
    t_philo *philo;

    philo = ptr;
    if(philo->number % 2 == 0)
    {
        handle_even_thread(&philo);
        
    }
    else
    {
        handle_even_thread(&philo);
        
    }
}

int    init_philos(char **av, t_data **data)
{
    int i = 0;
    int invalid = 0;

    while (i < (*data)->nb_philo)
    {
        if(pthread_create(&(*data)->philos[i]->phil, NULL, routine, (*data)->philos + i) != 0)
            return FAILURE;
        (*data)->philos[i]->number = i + 1;
        (*data)->philos[i]->time_to_die = ft_atoi(av[2], &invalid);
        (*data)->philos[i]->time_to_eat = ft_atoi(av[3], &invalid);
        (*data)->philos[i]->time_to_sleep = ft_atoi(av[4], &invalid);
        (*data)->philos[i]->left = (*data)->forks[i];
        (*data)->philos[i]->right = (*data)->forks[i + 1];
        if(av[5])
            (*data)->philos[i]->must_eat = ft_atoi(av[5], &invalid);
        if(invalid)
            return FAILURE;
        pthread_mutex_init(&(*data)->philos[i]->lock, NULL);
        pthread_mutex_init(&(*data)->forks[i], NULL);
        i++;
    }
    return SUCCESS; 
}

int parse_args(int ac, char **av, t_data **data)
{
    if(ac < 1 || ac < 5 || ac > 7)
    {
        printf("invalid args");
    }
    (*data)->nb_philo = av[1];
    (*data)->philos = ft_malloc(sizeof(t_philo *) * ((*data)->nb_philo + 1), 1);
    (*data)->forks = ft_malloc(sizeof(pthread_mutex_t *) * ((*data)->nb_philo + 1), 1);
    if(!(*data)->philos || !(*data)->forks)
        return FAILURE;
    if(init_philos(av, data))
        return FAILURE;
}


int main(int ac, char **av)
{
    t_data *data;

    data = ft_malloc(sizeof(t_data), 1);
    if(!data)
        return 1;
    parse_args(ac, av, &data);
}