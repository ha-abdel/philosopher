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

typedef struct s_args {
    int num_philos;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int must_eat_count;
}   t_args;

typedef struct data
{
    int nb_philo;
    pthread_mutex_t **forks;
    t_args          *args;
    long long       start_time;
    int             infinite;
    int             detect_death;
    int             allready;
    pthread_t       monitor;

} t_data;

typedef struct philo
{
    t_data          *data;
    pthread_mutex_t *left;
    pthread_mutex_t *right;
    pthread_mutex_t lock;
    pthread_t       thread;
    int             number;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int             must_eat;
    long            last_meal;
    int             died;
} t_philo;






/* FUNCTIONS */
void    precise_usleep(long ms, t_philo **philo);
int	check_death(t_philo **philo);
void	*monitoring(void *ptr);
int	create_thread(t_data **data, t_philo ***philos);
int	init_philos(int ac, t_data **data, t_philo ***philos);
int	init_args(t_data **data, char **av , int ac, int *invalid);
void	*routine(void *ptr);
long long get_timestamp_ms(void);
void	*ft_malloc(size_t size, int flag);
void    think(t_philo **philo);
void    ft_sleep(t_philo **philo);
void    eat(t_philo **philo);
int	ft_atoi(char *str, int *flag);
void	*ft_memset(void *b, int c, int len);
void	ft_free(t_allocs **lst);
// void	*ft_malloc(size_t size, int flag);
// void	*ft_calloc(int count, int size);

#endif