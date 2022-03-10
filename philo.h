/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhermon- <jhermon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 13:10:46 by jhermon-          #+#    #+#             */
/*   Updated: 2022/03/10 16:50:14 by jhermon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <math.h>

typedef struct s_data
{
	pthread_mutex_t	fork;
	pthread_mutex_t	*state;
	pthread_mutex_t	*meals;
	pthread_mutex_t	*prev;
	int				time_to_eat;
	int				time_to_die;
	int				time_to_sleep;
	long			time_start;
	long			time_begin_meal;
	int				nbr_of_meals;
	int				meal_count;
	int				nbr_philo;
	int				id;
}	t_data;

long	ft_atoi(char *str);
int		ft_strlen(char *str);
int		ft_isdigit(int c);
char	*ft_itoa(int n);
int		ft_arg_check(int argc, char **argv);
int		ft_time(void);
void	*meal_loop(void *ptr);
void	ft_usleep(int length);

#endif
