#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

int	main(void)
{
	int	pid1;
	int	pid2;
	int	status;

	pid1 = fork();
	if (!pid1)
		while (1);
	
	pid2 = fork();
	if (!pid2)
		while (1);
	waitpid(0, &status, 0);
	waitpid(0, &status, 0);
	
	printf("%d\n", WEXITSTATUS(status));
	//kill(pid1, SIGTERM);
	return (0);
}
