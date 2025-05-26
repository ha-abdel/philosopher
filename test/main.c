// // // #include <stdio.h>
// // // #include <pthread.h>
// // // #include <stdlib.h>
// // // #include <unistd.h>
// // // #include <sys/time.h>



// // // pthread_mutex_t mutex;
// // // int         primes[10]= {0, 1, 2, 3, 5, 7, 11, 13, 17, 29};

// // // void*    func(void *value)
// // // {
// // //     // pthread_mutex_lock(&mutex);
// // //     int *val = value;
// // //     printf("inside thread %d\n", *val);
// // //     // pthread_mutex_unlock(&mutex);
// // //     return NULL;
// // // }

// // // // void    *func1(void *val)
// // // // {
// // // //     int *i;

// // // //     i = (int *)(val);
// // // //     printf("Current thread ID: %lu\n",pthread_self());

// // // //     *i = 1;
// // // //     printf("%d\n", *i);
// // // //     // pthread_exit(NULL);
// // // //     // printf("%s\n", "this will not be executed");
// // // //     return NULL;
// // // // }

// // // int main()
// // // {
// // //     pthread_t   th[4];
// // //     int         i;
    

// // //     i = 0;
// // //     // pthread_mutex_init(&mutex, NULL);
// // //     while (i < 2)
// // //     {
// // //         if(pthread_create(&th[i], NULL, func, arg) != 0)
// // //         {
// // //             printf("thread creation failed\n");
// // //         }
// // //         printf("thread %d is created\n", i);
// // //         i++;
// // //     }
// // //     i=0;
// // //     while (i < 2)
// // //     {
// // //         if(pthread_join(th[i], NULL) != 0)
// // //         {
// // //             printf("thread joining failed\n");
// // //         }
// // //         printf("thread %d is done executing\n", i);
// // //         i++;
// // //     }



// // //     printf("%s\n", "main thread is here\n");
// // //     // pthread_mutex_destroy(&mutex);
// // //     return 0;
// // // }

// // // #include <stdio.h>
// // // #include <sys/time.h>
// // // #include <unistd.h> // for usleep

// // // // Returns current time in milliseconds
// // // long get_timestamp_ms(void)
// // // {
// // //     struct timeval tv;
// // //     gettimeofday(&tv, NULL);  // Get current time
// // //     return (tv.tv_sec * 1000L) + (tv.tv_usec / 1000L);
// // // }

// // // int main(void)
// // // {
// // //     long start_time = get_timestamp_ms();
    
// // //     printf("[%ld ms] Philosopher is thinking...\n", get_timestamp_ms() - start_time);
// // //     usleep(200000);  // Think for 200ms

// // //     printf("[%ld ms] Philosopher is eating...\n", get_timestamp_ms() - start_time);
// // //     usleep(300000);  // Eat for 300ms

// // //     printf("[%ld ms] Philosopher is sleeping...\n", get_timestamp_ms() - start_time);
// // //     usleep(100000);  // Sleep for 100ms

// // //     printf("[%ld ms] Philosopher is done.\n", get_timestamp_ms() - start_time);
// // //     return 0;
// // // }


// // #include <stdio.h>     // Required for printf
// // #include <sys/time.h>  // Required for gettimeofday (time tracking)
// // #include <unistd.h>    // Required for usleep

// // // The timeval structure provides a representation for storing time:
// // // tv_sec stores the number of seconds while tv_usec stores the number of microseconds.
// // // struct timeval {
// // //     time_t      tv_sec;     // seconds
// // //     suseconds_t tv_usec;    // microseconds
// // // };

// // void usleep_glitch()
// // {
// //     // Declare two timeval structures to store the start and end timestamps.
// //     struct timeval  start_time;
// //     struct timeval  end_time;

// //     // Store the desired sleep time, in this case, 200 milliseconds or 200,000 microseconds.
// //     long requested_sleep_time = 500 * 1000;

// //     // Capture the current time and store it in start_time. This marks the beginning of our usleep.
// //     gettimeofday(&start_time, NULL);

// //     // usleep is used to pause the execution of the program.
// //     // Here, the intention is to pause for 200,000 microseconds or 200 milliseconds.
// //     usleep(requested_sleep_time);

// //     // Once usleep completes, immediately capture the current time and store it in end_time.
// //     gettimeofday(&end_time, NULL);

// //     // Calculate the actual time the program was asleep.
// //     // This is done by finding the difference between the start and end times.
// //     long actual_sleep_time = (end_time.tv_sec - start_time.tv_sec) * 1000000 + (end_time.tv_usec - start_time.tv_usec);

// //     // Print the desired sleep time and the actual sleep time.
// //     printf("Requested Sleep Time: \t\t%ld microseconds\n", requested_sleep_time);
// //     printf("Actual Sleep Time: \t\t%ld microseconds\n\n", actual_sleep_time);
// // }

// // int main()
// // {
// //     // Call the example function to demonstrate the potential inconsistency in usleep.
// //     usleep_glitch();

// //     return (0);
// // }

// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   learn.c                                            :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: ybouanan <ybouanan@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/05/25 14:42:03 by ybouanan          #+#    #+#             */
// /*   Updated: 2025/05/25 15:18:49 by ybouanan         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include <stdio.h>
// #include <pthread.h>

// int i = 0;

// void *increment(void *arg)
// {
//     int *i = (int *)arg;
//     int *ptr;
//     ptr = i;
//     (*ptr)++;
//     return NULL;
// }


// int main()
// {
    
//     pthread_t thread[100000];
//     while(i < 100000)
//     {
//         if(pthread_create(&thread[i], NULL, &increment, (void *)&i) != 0)
//         {
//             perror("Failed to create thread");
//             continue ;
//         }
//         // if(pthread_create(&thread[i + 1], NULL, &increment, (void *)&i) != 0)
//         // {
//         //     perror("Failed to create thread");
//         //     continue ;
//         // }
//         pthread_join(thread[i], NULL);
//         // pthread_join(thread[i + 1], NULL);
//         i++;
//     }

//     printf("Final value of i: %d\n", i);
//     return 0;
// }

// //I need to start coding the mandatory part of philo project, so can you help me out , direct me without give me the code . give me tips that will help me later in cleaning up and make a flexible code 
// // first let's start by parsing my program's args 
// // first I think I'll check if nb_args passed 6 or less than 5
// // then I'll check it's a valid number (integer, no comma ...)
// // check if it overflows max_int or less than 0



#include <stdio.h>
#include <pthread.h>

#define THREADS 15000
#define INCREMENTS 1000000

int counter = 0;  // Shared variable

void *increment(void *arg)
{
    counter++;  // ⚠️ NOT ATOMIC!
    sleep(100);
    return NULL;
}

int main(void)
{
    pthread_t threads[THREADS];

    for (int i = 0; i < THREADS; i++)
        pthread_create(&threads[i], NULL, increment, NULL);

    for (int i = 0; i < THREADS; i++)
        pthread_join(threads[i], NULL);

    printf("Final counter value: %d (Expected: %d)\n", counter, THREADS * INCREMENTS);
    return 0;
}
