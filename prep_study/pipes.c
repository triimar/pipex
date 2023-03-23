#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <time.h>
#include <stdlib.h>
// int main(int argc, char *argv[])
// {
// 	int	fd[2];
 
// 	if (pipe(fd) == -1) 
// 	{
// 		printf("an error occurred with opening a piple\n");
// 		return (1);
// 	}
// 	int id = fork();
// 	if (id == -1)
// 	{
// 			printf("an error occurred with forking\n");
// 			return (4);
// 	}
// 	if (id == 0)
// 	{
// 		close(fd[0]); 
// 		int x;
// 		printf("input a number: ");
// 		scanf("%d", &x); //we want the x to be sent form the child process to the parent process
// 		if (write(fd[1], &x, sizeof(int)) == -1)
// 		{
// 			printf("an error occurred with writing to the pipe\n");
// 			return (2);
// 		}
// 		close(fd[1]);  
// 	}
// 	else 
// 	{
// 		close(fd[1]);
// 		int y;
// 		if (read(fd[0], &y, sizeof(int)) == -1)
// 		{
// 			printf("an error occurred with reading from the pipe\n");
// 			return (3);
// 		}
// 		close(fd[0]); 
// 		printf("got from child process %d\n", y);
// 	}
// 	return (0);

// }

// int main(int argc, char *argv[])
// {
// 	int	id;
// 	int id2;
// 	int sum;
// 	int start;
// 	int end;
// 	int arr[] = {1, 2, 3, 4, 1, 3};
// 	int arrSize = sizeof(arr) / sizeof(int);
// 	int fd[2];

// 	sum = 0;
// 	id = fork();
// 	if (id == -1)
// 		return (1);
// 	if 	(id == 0)
// 		id2 = id;
// 	if (id != 0)
// 	{
// 		id2 = fork();
// 		if (id2 == -1)
// 			return (1);
// 	}
// 	if (id !=0 && id2 != 0)
// 	{
// 		start = 0;
// 		end = arrSize / 3;
// 	}
// 	else if (id == 0 && id2 == 0)
// 	{
// 		start = arrSize / 3;
// 		end = (arrSize / 3) * 2;
// 	}
// 	else
// 	{
// 		start = (arrSize / 3) * 2;
// 		end = arrSize;
// 	}
// 	while (start < end)
// 		sum += arr[start++];

// 	printf("summa on = %d\n", sum);
// 	while (wait(NULL) != -1 || errno != ECHILD);
// 	return (0);
// }

int main(int argc, char *argv[])
{
	int p1[2]; // child to parent
	int p2[2]; // parent to child
	if (pipe(p1) == -1)
		return (1);
	if (pipe(p2) == -1)
		return (1);
	int pid = fork();
	if (pid == -1)
		return (2);
	if (pid == 0) //child process
	{
		close(p1[0]);
		close(p2[1]);
		int x;
		x = 0;
		if (read(p2[0], &x, sizeof(x)) == -1)
			return(3);
		// printf("recieved %d\n", x);
		x *= 4;
		if (write(p1[1], &x, sizeof(x)) == -1)
			return (4);
		// printf("Wrote %d\n", x);
		close(p1[1]);
		close(p2[0]);
	}
	else //parent process
	{
		close(p1[1]);
		close(p2[0]);
		srand(time(NULL));
		int y = rand() % 10;
		if (write(p2[1], &y, sizeof(y)) == -1)
			return (5);
		printf("Wrote %d\n", y);
		if (read(p1[0], &y, sizeof(y))== -1)
			return (6);
		printf("Result is %d\n", y);
		close(p1[0]);
		close(p2[1]);
		wait(NULL);
	}

	return (0);
}