/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsoteldo <gsoteldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 20:53:26 by gsoteldo          #+#    #+#             */
/*   Updated: 2024/02/29 21:09:22 by gsoteldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <signal.h>

# define GREEN "\x1b[32m"
# define RESET_COLOR "\x1b[0m"
# define BLUE "\x1b[34m"

static void	handler(int sig, siginfo_t *info, void *ucontext)
{
	static char		c;
	static int		count;
	static pid_t	pid;

	(void)ucontext;
	if (!pid)
		pid = info->si_pid;
	c |= (sig == SIGUSR2);
	//count++;
	if (++count == 8)
	{
		count = 0;
		if (!c)
		{
			kill(pid, SIGUSR2);
			pid = 0;
			return ;
		}
		ft_printf("%c", c);
		c = 0;
		kill(pid, SIGUSR1);
	}
	else
		c <<= 1;
}

int main(void)
{
	struct sigaction	sa;
	
	ft_printf("\x1b[34m" "Server PID: " "\x1b[0m" "%d\n\n", getpid());
	//ft_printf("----------------------------------------\n");
	sa.sa_sigaction = handler;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, 0);
	sigaction(SIGUSR2, &sa, 0);
	while (1)
		pause();
	return (0);
}

/*
int main()
{
	struct sigaction	sa;
	
	//recieve the pid of the server
	ft_printf("PID: %d\n", getpid());
	sa.sa_sigaction = handler;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, 0);
	sigaction(SIGUSR2, &sa, 0);
	while (1)
		pause();
	return (0);
}
*/