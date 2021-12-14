#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int		write_fd;
int		read_fd;
int		flag;

int		ft_strlen(char	*str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

void	exec(char	**cmd, int	type, char **env)
{
	int	i;
	int	pid;
	int	pip[2];

	i = 0;
	if (cmd[0] != NULL)
	{
		if (!strcmp(cmd[0], "cd"))
		{
			if (cmd[1] == NULL || cmd[2] != NULL)
				write(2, "error: cd: bad arguments\n", 25);
			else
			{
				if (chdir(cmd[1]) == -1)
				{
					write(2, "error: cd: cannot change directory to ", 38);
					write(2, cmd[1], ft_strlen(cmd[1]));
					write(2, "\n", 1);
				}
			}
		}
		else
		{
			if (flag == 1)
			{
				close (read_fd);
				read_fd = dup(pip[0]);
			}
			if (type == 1)
			{
				pipe(pip);
				close (write_fd);
				write_fd = pip[1];
				flag = 1;
			}
			else if (type == 0)
			{
				if (flag != 1)
				{
					close(read_fd);
					read_fd = dup(0);
				}
				close(write_fd);
				write_fd = dup(1);
				flag = 0;
			}
			pid = fork();
			if (pid == 0)
			{
				dup2(read_fd, 0);
				close(read_fd);
				dup2(write_fd, 1);
				close(write_fd);
				execve(cmd[0], cmd, env);
				write (2, "error: cannot execute ", 22);
				write (2, cmd[0], ft_strlen(cmd[0]));
				write (2, "\n", 1);
			}
			else
			{
				waitpid(pid, NULL, 0);
			}
		}
	}
}

int	main(int ac, char **av, char **env)
{
	char	*cmd[1024];
	int		i;
	int		k;
	int		j;

	i = -1;
	while (++i < 1024)
		cmd[i] = NULL;
	k = 0;
	flag = 0;
	read_fd = dup(0);
	write_fd = dup(1);
	i = 1;
	while (av[i - 1])
	{
		if (av[i] == NULL || !strcmp(av[i], ";"))
		{
			exec(cmd, 0, env);
			j = -1;
			while (++j < 1024)
				cmd[j] = NULL;
			k = 0;
		}
		else if (!strcmp(av[i], "|"))
		{
			exec(cmd, 1, env);
			j = -1;
			while (++j < 1024)
				cmd[j] = NULL;
			k = 0;
		}
		else
		{
			cmd[k] = av[i];
			k++;
		}
		i++;
	}
	close(write_fd);
	close(read_fd);
}