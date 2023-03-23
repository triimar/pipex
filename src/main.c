/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 20:39:27 by tmarts            #+#    #+#             */
/*   Updated: 2023/03/22 22:00:12 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int	pipe_error(int **pipes, int index)
{
	int i;

	i = 0;
	while (i < index)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
	}
	return(1);
}

int	main(int argc, char *argv[])
{
	int pids[2];
	int pipes[3][2];
	int i;
	int j;
	int x;
	int y;

	i = 0;
	while (i < 3)
	{
		if (pipe(pipes[i]) == -1)
			// return(pipe_error(pipes, i));
			return (1); //actually if the creation of pipe fails, we should falso close the prev opened pipes
		i++;
	}
	i = 0;
	while (i < 3)
	{
		pids[i] = fork();
		if (pids[i] == -1)
			return (2);
		if (pids[i] == 0) //we are in child
		{
			j = 0;
			while (j < 3) // each process needs to close tha pipes it is not using
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
	while (j < 3) // each process needs to close tha pipes it is not using
	{
		if (j != 2)
			close(pipes[j][0]);
		if (j != 0)
			close(pipes[j][1]);
		j++;
	}
	y = 5;
	// if (read(the pipe, &into what, sizeof(whatever I got from fd)))
	// 	return (5);
	// printf("Main process got %d\n", y);
	
	if (write(pipes[0][1], &y, sizeof(int)) == -1)
				return(5);
	if (read(pipes[2][0], &y, sizeof(int)) == -1) // process num as index, not nr of pipes
			return(6);
	close(pipes[0][1]);
	close(pipes[2][0]);
	printf("Result is %d\n", y);
	i = 0;
	while (i++ < 3)
		wait(NULL); 
	return (0);
}

int main(int argc, char *argv[])
{
	char *arguments[] = {"wc", "pingResults.txt", NULL};
	char *envp[] = {NULL};
	// execlp("ping", "ping", "-c", "3", "google.com", NULL);
	int pid = fork();
	if (pid == -1)
		return(1);
	if (pid == 0)
	{
		int file = open("outfile.txt", O_WRONLY | O_CREAT, 0755);
		if (file == -1)
			return(2); 
		// int file2 = dup(file);
		printf("the fd to pingResults: %d\n", file);
		int file2 = dup2(file, STDOUT_FILENO); //will close STDOUT and open it again to the "file" fd
		printf("the duplicatef fd: %d\n", file2);
		close(file);
		if (execve("/usr/bin/wc", arguments, envp) == -1)
			perror("execve fail");	
	}
	else
	{
		int wstatus;
		wait(&wstatus);
		if (WIFEXITED(wstatus)) // if returns "true" then normal termination happened
		{
			int statusCode = WEXITSTATUS(wstatus);
			if (statusCode == 0)
				printf("child success\n");
			else
				printf("program failure with status code %d\n", statusCode);
		}
		printf("success!\n");
	}
	return (0);
}