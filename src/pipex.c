/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 19:11:39 by tmarts            #+#    #+#             */
/*   Updated: 2023/03/22 20:57:38 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define PROCESS_NUM 10


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
	int pids[CHILD_NUM];
	int pipes[CHILD_NUM + 1][2];
	int i;
	int j;
	int x;
	// int y;

	i = 0;
	while (i < CHILD_NUM + 1)
	{
		if (pipe(pipes[i]) == -1)
			return(pipe_error(pipes, i));
			// return (1); //actually if the creation of pipe fails, we should falso close the prev opened pipes
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
	
	
	
	// y = 5;
	if (read(the pipe, &into what, sizeof(whatever I got from fd)))
		return (5);
	printf("Main process got %d\n", y);
	
	// if (write(pipes[0][1], &y, sizeof(int)) == -1)
	// 			return(5);
	// if (read(pipes[PROCESS_NUM][0], &y, sizeof(int)) == -1) // process num as index, not nr of pipes
	// 		return(6);
	close(pipes[0][1]);
	close(pipes[CHILD_NUM][0]);
	printf("Result is %d\n", y);
	i = 0;
	while (i++ < CHILD_NUM)
		wait(NULL); 
	return (0);
}