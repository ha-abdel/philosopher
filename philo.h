#ifndef PHILO_H

#define PHILO_H

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

#define SUCCESS 0
#define FAILURE 1

typedef struct s_allocs
{
	void			*ptr;
	struct s_allocs	*next;
}					t_allocs;



typedef struct philo
{
    pthread_t   phil;
    pthread_mutex_t *left;
    pthread_mutex_t *right;
    pthread_mutex_t lock;
    int number;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int must_eat;
} t_philo;


typedef struct data
{
    int nb_philo;
    pthread_mutex_t **forks;
    t_philo         **philos;

} t_data;


/* FUNCTIONS */
void    think(t_philo **philo);
void    sleep(t_philo **philo);
void    eat(t_philo **philo);
int	ft_atoi(char *str, int *flag);
void	*ft_memset(void *b, int c, int len);
void	ft_free(t_allocs **lst);
void	*ft_malloc(size_t size, int flag);
void	*ft_calloc(int count, int size);
void    precise_usleep(long ms);
long get_timestamp_ms(void);

#endif