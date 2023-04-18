/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 14:49:45 by tmarts            #+#    #+#             */
/*   Updated: 2023/04/18 23:19:38 by tmarts           ###   ########.fr       */
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
	char		*cmd;
	char		**args;
}	t_cmd;

typedef struct s_pipex
{
	int		infile;
	int		outfile;
	int		pp[2];
	int		pids[2];
	char	**envp_pths;
	t_cmd	exec[2];
}	t_pipex;

typedef struct s_wait
{
	int		wstatus;
	int		wstatus2;
	int		status_code;
}	t_wait;

int		pipex(t_pipex *s_pipex, char *envp[]);
int		all_paths(t_pipex *s_pipex, char **envp);
char	*get_right_path(char *command, char **paths);
char	*ft_free_split(char **p_p);
void	pipex_free(t_pipex *s_pipex);
char	*ft_pathjoin(char const *s1, char const *s2);
void	infile_error(t_pipex *s_pipex);
void	path_error(t_pipex *s_pipex, int exit_code, char *command);

#endif