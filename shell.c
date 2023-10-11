#include "main.h"

int main(void)
{
	while (1)
	{
		char **args = get_input();
		int i;

		if (args == NULL)
		{
			write(STDOUT_FILENO, "Error occurred while getting input.\n", 36);
			continue;
		}

		if (_strchr(args[0], '/') != NULL)
		{
			if  (args[0] != NULL && access(args[0], X_OK) == 0)
			{
				pid_t child = fork();
				int i;

				if (child == -1)
				{
					perror("problem");
					exit(EXIT_FAILURE);
				}
			       	else if (child == 0)
				{
					execve(args[0], args, environ);
					perror("execve");
					for (i = 0; args[i] != NULL; i++)
						free(args[i]);
					free(args);
					exit(EXIT_FAILURE);
				}
				else
				{
					wait(NULL);
					for (i = 0; args[i] != NULL; i++)
						free(args[i]);
					free(args);
				}
			}
			else
			{
				int i;
				for (i = 0; args[i] != NULL; i++)
				{
					free(args[i]);
				}
				free(args);
			}
		}
		else
		{
			if (execute_command(args) == -1)
			{
				write(STDOUT_FILENO, "Command not found.\n", 19);
				for (i = 0; args[i] != NULL; i++)
					free(args[i]);
				free(args);
			}
		}
	}
}
