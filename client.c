/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsoteldo <gsoteldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 20:53:16 by gsoteldo          #+#    #+#             */
/*   Updated: 2024/02/29 20:57:23 by gsoteldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <signal.h>

static void	handler(int sig)
{
	static int		count;

	if (sig == SIGUSR1)
		++count;
	else
	{
		ft_printf("%d\n", count);
		exit(0);
	}
}

static void	send_message(int signal, char *str)
{
	int		j;
	char	c;

	while (*str)
	{
		j = 8;
		c = *str++;
		while (j--)
		{
			if ((c >> j) & 1)
				kill(signal, SIGUSR2);
			else
				kill(signal, SIGUSR1);
			usleep(100);
		}
	}
	j = 8;
	while (j--)
	{
		kill(signal, SIGUSR1);
		usleep(100);
	}
}


int main(int argc, char **argv)
{
	int		pid;
	char	*str;
	//recieve the pid of the server
	if (argc != 3 || !ft_strlen(argv[2]))
	{
		ft_printf("Se necesita este formato: ./client [server_pid] \"Message\"\n");
		return (1);
	}
	pid = atoi(argv[1]);
	str = argv[2];
	ft_printf("Enviado: %d\n", ft_strlen(argv[2]));
	ft_printf("Recibido: \n");
	signal(SIGUSR2, handler);
	signal(SIGUSR1, handler);
	send_message(pid, str);
	while (1)
		pause();
	return (0);
}

/*int main(int argc, char **argv)
{
	int		pid;
	char	*str;
	//recieve the pid of the server
	if (argc != 3 || ft_strlen(argv[2]) == 0)
	{
		ft_printf("Se necesita este formato: ./client [server_pid] \"Message\"\n");
		return (1);
	}
	pid = atoi(argv[1]);
	str = argv[2];
	ft_printf("Enviado: %d\n", ft_strlen(argv[2]));
	ft_printf("Recibido: \n");
	signal(SIGUSR1, handler);
	signal(SIGUSR2, handler);
	send_message(pid, str);
	while (1)
		pause();
	return (0);
}*/