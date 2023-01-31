#include <sys/time.h>
#include <stdio.h>
#include <limits.h>
#include <unistd.h>

typedef long	t_time;

t_time	_time(void)
{
	struct timeval	t;
	static t_time	start;

	gettimeofday(&t, NULL);
	if (!start)
	{
		start = t.tv_sec * 1000000 + t.tv_usec;
		return (0);
	}
	return (t.tv_sec * 1000000 + t.tv_usec - start);
}

void	_usleep(t_time amount)
{
	t_time	time_up;

	time_up = _time() + amount;
	while (_time() < time_up)
		usleep(100);
}

int	main(void)
{
	int	count;

	count = 100;
	_time();
	while (count--)
	{
		printf("%ld\n", _time() / 1000);
		_usleep(100000);
	}
	return (0);
}
