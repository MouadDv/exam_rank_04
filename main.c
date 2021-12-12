#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int	main(int ac, char **av, char **env)
{
	char	*cmd[1024];
	int		i;
	int		k;
	int		j;

	i = -1;
	while (++i < 1024)
		cmd[i] = NULL;
	i = 1;
	k = 0;
	while (i < ac)
	{
		if (!strcmp(av[i], ";"))
		{
			//exec(cmd, type);
			j = -1;
			while (++j < 1024)
				cmd[j] = NULL;
		}
		else if (!strcmp(av[i], "|"))
		{
			//exec(cmd, type);
			j = -1;
			while (++j < 1024)
				cmd[j] = NULL;
		}
		else
		{
			cmd[k] = av[i];
			k++;
		}
		i++;
	}
	
	
}