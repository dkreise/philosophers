#include "philosophers.h"

int cur_time_ms(void)
{
    struct timeval tv;
    int ms;

    // protect it
    gettimeofday(&tv, NULL);
    ms = tv.tv_sec * 1000 + tv.tv_usec / 1000;
    return (ms);
}

int ft_usleep(int ms)
{
    int end_time;

    end_time = cur_time_ms() + ms;
    while (cur_time_ms() < end_time)
    {
        usleep(200);
    }
    return (0);
}