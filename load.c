#include "philo.h"

void	ft_philo_load(t_program *prog)
{
	int	counter;

	prog->philos = malloc(sizeof(t_philo) * prog->size);
	if (!prog->philos)
		return ;
	prog->forks = malloc (sizeof(int) * prog->size);
	if (!prog->forks)
		return ;
	counter = -1;
	prog->start = ft_get_time();
	while (++counter < prog->size)
	{
		prog->philos[counter].prog = prog;
		prog->philos[counter].pos = counter + 1;
		prog->philos[counter].die = 0;
		prog->philos[counter].last = prog->start;
		prog->philos[counter].times_eat = 0;
		prog->philos[counter].forks = 0;
		prog->forks[counter] = 1;
	}
	prog->exit = 0;
}

void	ft_philo_start(t_program *prog)
{
	int	counter;

	counter = -1;
	pthread_mutex_init(&prog->mutex, NULL);
	pthread_mutex_init(&prog->forks_mutex, NULL);
	counter = -1;
	while (++counter < prog->size)
	{
		if (pthread_create(&prog->philos[counter].thread, NULL,
			ft_philo_actions, &prog->philos[counter]) != 0)
			return ;
	}
}

void	ft_philo_end(t_program *prog)
{
	int     counter;

	counter = -1;
	while (++counter < prog->size)
	{
		if (pthread_join(prog->philos[counter].thread, NULL) != 0)
			return ;
	}
	counter = -1;
	pthread_mutex_destroy(&prog->mutex);
	pthread_mutex_destroy(&prog->forks_mutex);
}
