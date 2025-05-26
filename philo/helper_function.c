#include "../philo.h"

int	ft_atoi(char *str, int *flag)
{
	long	nb;
	int		sign;
	int		i;

	nb = 0;
	sign = 1;
	i = 0;
	while (str && str[i])
	{
        if((str[i] < '0' && str[i] > '9') || nb > __INT_MAX__)
        {
            flag = 1;
            return 0;
        }
		nb = nb * 10 + str[i] - '0';
		i++;
	}
	nb = nb * sign;
	return (nb);
}
