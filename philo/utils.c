#include "../philo.h"

long long get_timestamp_ms(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);  // Get current time
    return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

void    precise_usleep(long ms)
{
    long start = get_timestamp_ms();
    while (get_timestamp_ms() - start < ms)
    {
        usleep(100);
    }
    
}