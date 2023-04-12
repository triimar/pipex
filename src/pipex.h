/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 14:49:45 by tmarts            #+#    #+#             */
/*   Updated: 2023/04/12 21:51:56 by tmarts           ###   ########.fr       */
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
# include <errno.h>
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
	int		pp[2]; 
	int		pids[2];
	char	**envp_paths;
	t_cmd	exec[2];
}	t_pipex;

int		pipex(t_pipex *s_pipex, char *envp[]);
char	**all_paths(char **envp);
char	**pipex_parser(t_cmd *s_cmd, char *input);
char	*get_right_path(char *command, char **paths);
char	*ft_free_split(char **p_p);
void	pipex_free(t_pipex *s_pipex);
char	*ft_pathjoin(char const *s1, char const *s2);
// • open, close, read, write,
// malloc, free, 

// perror,
// strerror, access, dup, dup2,
// execve, exit, fork, pipe,
// unlink, wait, waitpid

#endif