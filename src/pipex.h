/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 14:49:45 by tmarts            #+#    #+#             */
/*   Updated: 2023/04/10 19:37:51 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h> //open
# include <stdio.h> //perror
# include <string.h> //strerror
# include <stdlib.h> //malloc
# include <sys/wait.h>
# include <unistd.h> //access, fork, write, read, dup&2, execve
# include "libft.h"

typedef struct s_cmd
{
	char	*cmd;
	char	**arguments;
}	t_cmd;

typedef struct s_pipex
{
	int		infile;
	int		outfile;
	int		n_forks;
	int		pp[2];
	int		pids[2];
	char	**paths;
	char	*cmd_path;
	t_cmd	**exec;
}	t_pipex;

int		pipex(t_pipex *s_pipex);
char	**all_paths(char **envp);
char	*get_right_path(char *command, char **paths);
char	*ft_free_split(char **p_p);
// • open, close, read, write,
// malloc, free, perror,
// strerror, access, dup, dup2,
// execve, exit, fork, pipe,
// unlink, wait, waitpid

#endif