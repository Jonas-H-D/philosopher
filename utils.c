/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhermon- <jhermon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 13:36:19 by jhermon-          #+#    #+#             */
/*   Updated: 2022/03/10 16:51:27 by jhermon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(char *s)
{
	int	len;

	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}

int ft_arg_check(int argc, char **argv)
{
  int i;
  int j;
  
  if (argc != 5 && argc != 6)
  {
    write (2, "wrong nbr of arguments\n", 23);
    return (0);
  }
  i = 1;
  while (i < argc)
  {
    j = 0;
    while (argv[i][j])
    {
      if (ft_isdigit(argv[i][j]) == 0)
			{
        write (2, "wrong argument type\n", 20);
        return (0);
      }
      j++;
    }
    i++;
  }
  return (1);
}

int	ft_time(void)
{
	struct timeval	te;

	gettimeofday(&te, NULL);
	return (te.tv_sec * 1000 + te.tv_usec / 1000);
}

void  *meal_loop(void *ptr)
{
  t_data  *data;
  int     i;

  data = (t_data *)ptr;
  i = 0;
  if (data->nbr_of_meals != 0)
    pthread_mutex_lock(data->meals);
  while (data->nbr_of_meals != 0 && i < data->nbr_philo)
  {
    pthread_mutex_lock(data->meals);
    i++;
  }
  printf("%ld Everyone has eaten enough !\n", (ft_time() - data->time_start));
	pthread_mutex_unlock(data->state);
	return (NULL);
}

void	ft_usleep(int length)
{
	long	time;

	time = ft_time();
	while (ft_time() < time + length)
		usleep(length);
}
