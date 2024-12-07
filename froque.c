/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   froque.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 12:38:02 by lperis            #+#    #+#             */
/*   Updated: 2024/12/06 18:35:09 by lperis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft.h"

/*int main()
{
	pid_t pid = fork();
	int status;
	if(pid == 0)
		printf("oui\n");
	else
		printf("non\n");
	waitpid(pid, &status, 0);
	exit(WEXITSTATUS(status));
	
}*/

/*void	child_process(t_data *data)
{
	int infd = open(data->cmd[0], O_RDONLY);
	
	printf("%d", infd);
	printf("%s", data->cmd[0]);
	int pfd[2];
	int infd = open(data->cmd[0], O_RDONLY);
	dup2(infd, STDIN_FILENO);
	pipe(pfd);
	int pid1 = fork();
	if(pid1 == 0)
	{
		close(pfd[0]);
		dup2(pfd[1], STDOUT_FILENO);
		close(pfd[1]);
		execve(args1[0], args1, envp);
	}
}*/

void process(t_data *data)
{
	int infd = open(data->infile, O_RDONLY);
	if(infd < 0)
	{
		
	}
	printf("%d", infd);
	printf("%s", data->infile);
		
}

void parse_cmd(t_data *data, int n)
{
	int j = 0;
	data->cmd[n] = ft_strjoin("/", data->cmd[n]);
	while(data->path[j])
	{
			if (access(ft_strjoin(data->path[j], data->cmd[n]),X_OK) == 0)
			{
				data->cmd[n] = ft_strjoin(data->path[j], data->cmd[n]);
				break ;
			}
		j++;
	}
}

void check_file(t_data *data)
{
	if(access(data->infile, R_OK | F_OK) == 0)
	{
		
		data->in_fd = open(data->infile, O_RDONLY);
		data->in_bool = 0;
		dup2(data->in_fd, STDIN_FILENO);
	}
	else
		data->in_bool = 1;
}

void	check_command(t_data *data)
{
	int j = 0;
	int i = 0;
	while(j < data->nb_args-1)
	{
		while(data->cmd[j][i] != '\0')
		{
			if(data->cmd[j][i] == '/')
				data->f_path = 1;
			i++;
		}
		if(data->f_path != 1)
			parse_cmd(data, j);
		j++;
		i = 0;
	}
}

int main (int argc, char **argv, char **envp)
{
	t_data data;
	if (argc <= 2)
	{
		printf("larguboloss");
		return(0);
	}
	data.cmd = malloc(sizeof(char *) * argc);
	int i = 0;
	while(ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	data.path = ft_split(envp[i] + 5, ':');
	int a = 2;
	int b = 0;
	
	while(a < argc)
	{
		data.cmd[b] = argv[a];
		a++;
		b++;
	}
	data.infile = argv[1];
	data.nb_args = a-1;
	check_file(&data);
	check_command(&data);
	process(&data);
}

/*
	char **args1 = ft_split(data.cmd[0], ' ');
	char **args2 = ft_split(data.cmd[1], ' ');
	int i = 0;
	int fp = 0;
	*//*while(args[0][i])
	{
		if(args[0][i] == '/')
			fp = 1;
		i++;
	}*//*
	if(fp == 0)
	{
		args1[0] = ft_strjoin("/", args1[0]);
		printf("args1%s\n", args1[0]);
		args2[0] = ft_strjoin("/", args2[0]);
		printf("args2%s\n", args2[0]);
	}
	i = 0;
	while(ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	char **path = ft_split(envp[i]+5, ':');
	int j = 0;
	while(path[j])
	{
			if (access(ft_strjoin(path[j], args1[0]),X_OK) == 0)
			{
				args1[0] = ft_strjoin(path[j], args1[0]);
				printf("args1%s\n", args1[0]);
				break ;
			}
		j++;
	}
	j = 0;
	while(path[j])
	{
			if (access(ft_strjoin(path[j], args2[0]),X_OK) == 0)
			{
				args2[0] = ft_strjoin(path[j], args2[0]);
				printf("args2%s\n", args2[0]);
				break ;
			}
		j++;
	}
	int pfd[2];
	int infd = open("infile.txt", O_RDONLY);
	dup2(infd, STDIN_FILENO);
	pipe(pfd);
	int pid1 = fork();
	if(pid1 == 0)
	{
		close(pfd[0]);
		dup2(pfd[1], STDOUT_FILENO);
		close(pfd[1]);
		execve(args1[0], args1, envp);
	}
	
	int pid2 = fork();
	if(pid2 == 0)
	{
		close(pfd[1]);
		dup2(pfd[0], STDIN_FILENO);
		int fd = open("test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0777);
		dup2(fd, STDOUT_FILENO);
		close(pfd[0]);
		execve(args2[0], args2, envp);
	}
	//dup2(fd, pfd[0]);
	//close(fd);
}

*/
