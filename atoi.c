/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhermon- <jhermon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 11:04:13 by jhermon-          #+#    #+#             */
/*   Updated: 2022/03/10 11:08:59 by jhermon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_wordcount(char const *str, char c)
{
	int	flag;
	int	count;

	count = 0;
	flag = 0;
	while (*str)
	{
		if (*str != c && flag == 0)
		{
			flag = 1;
			count ++;
		}
		else if (*str == c)
		{
			flag = 0;
		}
		str++;
	}
	return (count);
}

static char	*ft_word_copy(char const *s, int start, int finish)
{
	int		i;
	char	*word;

	i = 0;
	word = malloc(sizeof(char) * (finish - start + 1));
	if (!word)
	{
		free(word);
		return (NULL);
	}
	while (start < finish)
	{
		word[i] = s[start];
		i++;
		start++;
	}
	word[i] = 0;
	return (word);
}

char	**ft_split(char *s, char c)
{
	char	**dest;
	int		i;
	int		j;
	int		index;

	if (!s)
		return (NULL);
	dest = malloc(sizeof(char *) * (ft_wordcount(s, c) + 1));
	if (!dest)
		return (NULL);
	i = -1;
	j = 0;
	index = -1;
	while (++i <= ft_strlen(s))
	{
		if (s[i] != c && index < 0)
			index = i;
		else if ((s[i] == c || i == ft_strlen(s)) && index >= 0)
		{
			dest[j++] = ft_word_copy(s, index, i);
			index = -1;
		}
	}
	dest[j] = 0;
	return (dest);
}

int	ft_isdigit(int c)
{
	if (c > 47 && c < 58)
		return (1);
	else
		return (0);
}

long	ft_atoi(char *str)
{
	long	res;
	int		i;
	long	sign;

	res = 0;
	i = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			exit(1);
		res = (res * 10) + (str[i] - 48);
		if (res > 2147483647 || res < -2147483648)
			exit(1);
		i++;
	}
	return (sign * res);
}
