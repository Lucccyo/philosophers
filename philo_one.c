#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <getopt.h>
#include <unistd.h>

int			g_number_of_philosophers;
double			g_time_to_die;
double			g_time_to_eat;
double			g_time_to_sleep;
int			g_number_of_time_each_philosopher_must_eat;
int			g_opt = 0;
pthread_mutex_t		*g_forks;
pthread_mutex_t		g_m_tab;
int			g_tab [] = {0, 0, 0, 0, 0};

void	*philo(void *i)
{
	long		p_num;

	p_num = ((long) i) % g_number_of_philosophers;
	printf("p%ld started to exist.\n", p_num);
	while (1)
	{
		pthread_mutex_lock(&g_m_tab);
		if (g_tab[p_num + 2])
		{
			pthread_mutex_unlock(&g_m_tab);
			printf("p%ld >> ZZZ\n", p_num);
			fflush(stdout);
		}
		else
		{
			g_tab[p_num + 1] = 1;
			g_tab[p_num] = 1;
			pthread_mutex_unlock(&g_m_tab);
			pthread_mutex_lock(&g_forks[p_num + 1]);
			pthread_mutex_lock(&g_forks[p_num]);
			printf("p%ld >> MIAM MIAM MIAM\n", p_num);
			fflush(stdout);
			printf("p%ld >> WAS GOOD\n", p_num);
			pthread_mutex_unlock(&g_forks[p_num + 1]);
			pthread_mutex_unlock(&g_forks[p_num]);
			pthread_mutex_lock(&g_m_tab);
			g_tab[p_num + 1] = 0;
			g_tab[p_num] = 0;
			pthread_mutex_unlock(&g_m_tab);
			sleep(3);
		}
	}
	fflush(stdout);
	return (NULL);
}

int	main(int argc, char *argv[])
{
	int		opt;
	int		i;
	int		new_thread;
	pthread_t	tid[];

	opt = getopt(argc, argv, "p:d:e:s:o:");
	while (opt != -1)
	{
		switch (opt)
		{
			case 'p' :
			g_number_of_philosophers = atoi(optarg);
			break ;
			case 'd' :
			g_time_to_die = atof(optarg);
			break ;
			case 'e' :
			g_time_to_eat = atof(optarg);
			break ;
			case 's' :
			g_time_to_sleep = atof(optarg);
			break ;
			case 'o' :
			g_number_of_time_each_philosopher_must_eat = atoi(optarg);
			break ;
			default :
				printf("Missing arguments\n");
		}
	}
	tid = malloc(g_number_of_philosophers * sizeof(pthread_t));
	g_forks = malloc(g_number_of_philosophers * sizeof(pthread_mutex_t));
	for (i = 0; i < g_number_of_philosophers; i++)
		g_tab[i] = 0;
	for (i = 0; i < g_number_of_philosophers; i++)
	{
		pthread_mutex_init(&g_forks[i], NULL);
	}
	for (i = 0; i < g_number_of_philosophers; i++)
	{
		new_thread = pthread_create(&tid[i], NULL, philo, (void *) i);
		if (new_thread != 0)
			exit(1);
		pthread_detach(tid[i]);
	}
	pause();
	printf("%d\n", g_number_of_philosophers);
	return (0);
}
