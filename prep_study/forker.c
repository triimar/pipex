#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
// #include <stdlib.h>

int main(int argc, char *argv[])
{
	int id = fork();
	if (id != 0)
		id = fork();
	printf("tere: id = %d\n", id);
	return (0);
} 

// int main(int argc, char *argv[])
// {
// 	// int id = fork();
// 	// int n;
// 	// char c;
// 	// if (id == 0)
// 	// 	n = 1;
// 	// else
// 	// 	n = 6;
// 	// wait(NULL);
// // 	// int i;
// // 	// for (i = n; i < n + 5; i++)
// // 	// {
// // 	// 	char c = i + '0';
// // 	// 	write(1, &c, 1);
// // 	// }
// // 	int i = n;
// // 	while (i < n + 5)
// // 	{
// // 		printf("%d", i);
// // 		i++;
// // 	}
// // 	if (id != 0)
// // 		printf("\n");
// // 	return (0);
// 	int id1 = fork();
// 	int id2 =  fork();
// 	while (wait(NULL) != -1 || errno != ECHILD) //wait(0) returns -1 if there is nothing to wait for 
// 		printf("waited for a child to finish\n");
// 	if (id1 == 0)
// 	{
// 		if (id2 == 0)
// 			printf("we are process y\n");
// 		else 
// 			printf("we are process x\n");		
// 	}
// 	else
// 	{
// 		if (id2 == 0)
// 			printf("we are process z\n");
// 		else
// 			printf("we are the parent process\n");
// 	}
// 	// while (wait(NULL) != -1 || errno != ECHILD) //wait(0) returns -1 if there is nothing to wait for 
// 	// 	printf("waited for a child to finish\n");
// 	return(0);

// } 
