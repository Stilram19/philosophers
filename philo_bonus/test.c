#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

int	main(void)
{
	int	pid;
	int	status;

	pid = fork();
	if (!pid)
		while (1);
	waitpid(0, &status, 0);
	printf("%d\n", WEXITSTATUS(status));
	kill(pid, SIGTERM);
	return (0);
}
