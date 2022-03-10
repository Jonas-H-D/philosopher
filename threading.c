/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhermon- <jhermon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 15:10:40 by jhermon-          #+#    #+#             */
/*   Updated: 2022/03/10 17:08:59 by jhermon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*death_loop(void *ptr)
{
	t_data	*data;

	data = (t_data *)ptr;
	while (1)
	{
		if (ft_time() - data->time_begin_meal > data->time_to_die)
		{
			printf("%ld %d has died\n", ft_time() - data->time_start, data->id);
			pthread_mutex_unlock(data->state);
			return (NULL);
		}
		else if (data->nbr_of_meals != -1 && data->meal_count >= data->nbr_of_meals)
		{
			ft_usleep(data->id);
			pthread_mutex_unlock(data->meals);
			return(NULL);
		}
	}
	return (NULL);
}

void	*ft_philosopher(void *ptr)
{
	pthread_t	tid;
	t_data	*data;

	data = (t_data *)ptr;
  pthread_create(&tid, NULL, death_loop, data);
  if (data->id % 2 == 0)
    ft_usleep((float)data->time_to_eat * 0.9 + 1);
  while (data->nbr_of_meals == -1 || data->nbr_of_meals > data->meal_count)
  {
    pthread_mutex_lock(&data->fork);
    printf("%ld %d has taken a fork\n", (ft_time() - data->time_start), data->id);
    pthread_mutex_lock(data->prev);
    printf("%ld %d has taken a fork\n", (ft_time() - data->time_start), data->id);
    data->time_begin_meal = ft_time();
    printf("%ld %d is eating\n", (ft_time() - data->time_start), data->id);
    ft_usleep(data->time_to_eat);
    pthread_mutex_unlock(&data->fork);
    pthread_mutex_unlock(data->prev);
    data->meal_count++;
    printf("%ld %d is sleeping\n", (ft_time() - data->time_start), data->id);
    ft_usleep(data->time_to_sleep);
    printf("%ld %d is thinking\n", (ft_time() - data->time_start), data->id);
  }
  return (NULL);
}

void  ft_first_philo(t_data *data)
{
  pthread_mutex_t state;
  pthread_mutex_t meals;
  pthread_t tid;
  int i;

  data[0].prev = &data[data[0].nbr_philo - 1].fork;
  pthread_mutex_init(&state, NULL);
  pthread_mutex_init(&meals, NULL);
  pthread_mutex_lock(&state);
  i = 0;
  while (i < data[0].nbr_philo)
  {
    data[i].state = &state;
    data[i].meals = &meals;
    pthread_create(&tid, NULL, ft_philosopher, &data[i]);
    i++;
  }
  if (data[0].nbr_of_meals > -1)
    pthread_create(&tid, NULL, meal_loop, &data[0]);
  pthread_mutex_lock(&state);
  i = 0;
  while (i < data[0].nbr_philo)
    pthread_mutex_destroy(&data[i++].fork);
  pthread_mutex_destroy(&state);
  pthread_mutex_destroy(&meals);
  free (data);
}

int main(int argc, char **argv)
{
  t_data  *data;
  int     i;
  
  if (ft_arg_check(argc, argv) == 0)
    return (1);
  if (!(data = malloc(sizeof(t_data) * ft_atoi(argv[1]))))
    return (1);
  i = 0;
  while (i < ft_atoi(argv[1]))
  {
    pthread_mutex_init(&data[i].fork, NULL);
    if (i != 0)
      data[i].prev = &data[i - 1].fork;
    else
      data[i].prev = NULL;
    data[i].nbr_philo = ft_atoi(argv[1]);
    data[i].time_to_die = ft_atoi(argv[2]);
    data[i].time_to_eat = ft_atoi(argv[3]);
    data[i].time_to_sleep = ft_atoi(argv[4]);
    data[i].time_start = ft_time();
    if (argc == 6)
      data->nbr_of_meals = ft_atoi(argv[5]);
    else 
      data->nbr_of_meals = -1;
    data[i].time_begin_meal = data[i].time_start;
    data[i].meal_count = 0;
    data[i].id = i + 1;
    i++;
  }
	// sleep(2);
	// printf("ft_time = %ld\n", (ft_time() - data->time_start));
  ft_first_philo(data);
  return (0);
}
