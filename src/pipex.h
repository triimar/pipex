/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 14:49:45 by tmarts            #+#    #+#             */
/*   Updated: 2023/04/23 20:36:50 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h> 
# include <stdio.h> 
# include <string.h> 
# include <stdlib.h> 
# include <sys/wait.h>
# include <unistd.h> 
# include "libft.h"

typedef struct s_cmd
{
	char			*cmd;
	char			**args;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_pipex
{
	int		infile;
	int		outfile;
	int		pp[2];
	int		pids[2];
	char	**envp_pths;
	t_cmd	*s_cmd_lst;
}	t_pipex;

typedef struct s_wait
{
	int		wstatus;
	int		wstatus2;
	int		status_code;
}	t_wait;

/* pipex.c */
int		pipex(t_pipex *s_pipex, char *envp[]);
/* pipex_initiate.c*/
void	open_files(t_pipex *s_pipex, char *infile, char *outfile);
int		pipex_init(t_pipex *s_pipex, char **argv, char **envp);
/* parser.c */
int		all_paths(t_pipex *s_pipex, char **envp);
int		ft_get_cmd(t_cmd *s_cmd, char *argv);
char	*get_right_path(char *command, char **paths);
/* pipex_utils.c */
void	redirect(int in_fd, int out_fd);
void	close_all(t_pipex *s_pipex);
t_cmd	*get_node(t_cmd *list, int child_nr);
void	ft_waiting(int *pids);
/* pipex_utils.c */
char	*ft_pathjoin(char const *s1, char const *s2);
/* errors.c */
void	infile_error(t_pipex *s_pipex);
void	path_error(t_pipex *s_pipex, int exit_code, char *command);
void	execve_error(t_pipex *s_pipex);
/*pipex_free.c */
void	pipex_free(t_pipex *s_pipex);

#endif