
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

// int	main(int argc, char *argv[])
// {
// 	int	fd[2];
// 	int	pid1;
// 	int	pid2;

// 	if (pipe(fd) == -1)
// 		return (1);
// 	pid1 = fork();
// 	if (pid1 < 0)
// 		return (2);
// 	if (pid1 == 0) //child proccess for first executable (ping)
// 	{
// 		dup2(fd[1], STDOUT_FILENO);
// 		close (fd[0]);
// 		close(fd[1]);
// 		execlp("ping", "ping", "-c", "5", "google.com", NULL);
// 	}
// 	pid2 = fork();
// 	if (pid2 < 0)
// 		return (3);
// 	if (pid2 == 0) //child process 2, grep
// 	{ 
// 		dup2(fd[0], STDIN_FILENO); //until when to keep reading? until all the writers are done;
// 		close(fd[0]);
// 		close(fd[1]);
// 		execlp("grep", "grep", "round-trip", NULL);
// 	}
// 	close(fd[0]);
// 	close(fd[1]);
// 	waitpid(pid1, NULL, 0);
// 	waitpid(pid2, NULL, 0);
// 	return (0);
// }

// int	main(int argc, char *argv[]) //hardcoded function for only/specifically 3 processes
// {
// 	int fd[3][2];
// 	int i;
// 	int pid1;
// 	int	pid2;
// 	int x;

// 	i = 0;
// 	while (i < 3)
// 	{
// 		if (pipe(fd[i]) < 0)
// 			return (1); //actually if the creation of pipe fails, we should falso close the prev opened pipes
// 		i++;
// 	}
// 	pid1 = fork();
// 	if (pid1 < 0)
// 		return (2);
// 	if (pid1 == 0) //child process 1, needs fd[0][0] amd fd[1][1] open
// 	{
// 		close(fd[0][1]);
// 		close(fd[1][0]);
// 		close(fd[2][0]);
// 		close(fd[2][1]);
// 		if(read(fd[0][0], &x, sizeof(int)) < 0)
// 			return (3);
// 		x+=5;
// 		if (write(fd[1][1], &x, sizeof(int)) < 0)
// 			return (4);
// 		close(fd[0][0]);
// 		close(fd[1][1]);
// 		return (0);
// 	}
// 	pid2 = fork();
// 	if (pid1 < 0)
// 		return (5);
// 	if (pid2 == 0) //child 2, needs fd[1][0], fd[2][1]
// 	{
// 		close(fd[0][0]);
// 		close(fd[0][1]);
// 		close(fd[1][1]);
// 		close(fd[2][0]);
// 		if(read(fd[1][0], &x, sizeof(int)) < 0)
// 			return (6);
// 		x+=5;
// 		if (write(fd[2][1], &x, sizeof(int)) < 0)
// 			return (4);
// 		close(fd[1][0]);
// 		close(fd[2][1]);
// 		return (0);
// 	}
// 	close(fd[0][0]); //parent needs fd[0][1], fd[2][0];
// 	close(fd[1][0]);
// 	close(fd[1][1]);
// 	close(fd[2][1]);
// 	x = 3;
// 	if (write(fd[0][1], &x, sizeof(int)) < 0)
// 		return (7);
// 	if(read(fd[2][0], &x, sizeof(int)) < 0)
// 		return (8);
// 	printf("result is %d\n", x);
// 	close(fd[0][1]);
// 	close(fd[2][0]);
// 	waitpid(pid1, NULL, 0);
// 	waitpid(pid2, NULL, 0);
// 	return (0);
// }

#define CHILD_NUM 10


int	main(int argc, char *argv[])
{
	int pids[CHILD_NUM];
	int pipes[CHILD_NUM + 1][2];
	int i;
	int j;
	int x;
	int y;

	i = 0;
	while (i < CHILD_NUM + 1)
	{
		if (pipe(pipes[i]) == -1)
			return (1); //actually if the creation of pipe fails, we should falso close the prev opened pipes
		i++;
	}
	i = 0;
	while (i < CHILD_NUM)
	{
		pids[i] = fork();
		if (pids[i] == -1)
			return (2);
		if (pids[i] == 0) //we are in child
		{
			j = 0;
			while (j < CHILD_NUM + 1) // each process needs to close tha pipes it is not using
			{
				if (i != j)
					close(pipes[j][0]); //read end
				if (i + 1 != j)
					close(pipes[j][1]);
				j++;
			}
			if (read(pipes[i][0], &x, sizeof(int)) == -1)
				return(3);
			printf("(%d) Got: %d\n", i, x);
			x++; 
			if (write(pipes[i + 1][1], &x, sizeof(int)) == -1)
				return(4);
			printf("(%d) Sent: %d\n", i, x);
			close(pipes[i][0]);
			close(pipes[i + 1][0]);
			return (0); //the child won't continue the while loop, also "break" can be used
		} 
		i++;
	}
	//main process
	j = 0;
	while (j < CHILD_NUM + 1) // each process needs to close tha pipes it is not using
	{
		if (j != CHILD_NUM)
			close(pipes[j][0]);
		if (j != 0)
			close(pipes[j][1]);
		j++;
	}
	y = 5;
	printf("Main process sent %d\n", y);
	if (write(pipes[0][1], &y, sizeof(int)) == -1)
				return(5);
	if (read(pipes[CHILD_NUM][0], &y, sizeof(int)) == -1) // process num as index, not nr of pipes
			return(6);
	close(pipes[0][1]);
	close(pipes[CHILD_NUM][0]);
	printf("Result is %d\n", y);
	i = 0;
	while (i++ < CHILD_NUM)
		wait(NULL); 
	return (0);
}