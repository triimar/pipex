#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{

	char *arguments[] = {"grep", "round-trip", "pingResults.txt", NULL};
	char *envp[] = {NULL};
	// execlp("ping", "ping", "-c", "3", "google.com", NULL);
	int pid = fork();
	if (pid == -1)
		return(1);
	if (pid == 0)
	{
		if (execve("/usr/bin/grep", arguments, envp) == -1)
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

// int main(int argc, char *argv[])
// {
// 	char *arguments[] = {"ping", "-c", "3", "google.com", NULL};
// 	char *envp[] = {NULL};
// 	// execlp("ping", "ping", "-c", "3", "google.com", NULL);
// 	int pid = fork();
// 	if (pid == -1)
// 		return(1);
// 	if (pid == 0)
// 	{
// 		int file = open("pingResults.txt", O_WRONLY | O_CREAT, 0777);
// 		if (file == -1)
// 			return(2); 
// 		// int file2 = dup(file);
// 		printf("the fd to pingResults: %d\n", file);
// 		int file2 = dup2(file, STDOUT_FILENO); //will close STDOUT and open it again to the "file" fd
// 		printf("the duplicatef fd: %d\n", file2);
// 		close(file);
// 		if (execve("/sbin/ping", arguments, envp) == -1)
// 			perror("execve fail");	
// 	}
// 	else
// 	{
// 		int wstatus;
// 		wait(&wstatus);
// 		if (WIFEXITED(wstatus)) // if returns "true" then normal termination happened
// 		{
// 			int statusCode = WEXITSTATUS(wstatus);
// 			if (statusCode == 0)
// 				printf("child success\n");
// 			else
// 				printf("program failure with status code %d\n", statusCode);
// 		}
// 		printf("success!\n");
// 	}
// 	return (0);
// }