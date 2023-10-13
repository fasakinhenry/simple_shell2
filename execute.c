#include "main.h"



int execute_command(char **args)
{
	char *path = _getenv("PATH");
	char *delim = ":";

	char *dir = _strtok(path, delim);
	while (dir != NULL)
	{
		char *path_with_slash = _strconcat(dir, "/");
		char *full_path = _strconcat(path_with_slash, args[0]);
		
		printf("Checking path: %s\n", full_path);

		if (path_with_slash != NULL && full_path != NULL)
		{
			printf("Neither of these are null.");
			if (access(full_path, X_OK) == 0)
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
					execve(full_path, args, environ);
					perror("execute_command: execve");
					free(path_with_slash);
					free(full_path);
					exit(EXIT_FAILURE);
				}
				else
				{
					wait(NULL);

					for (i = 0; args[i] != NULL; i++)
					{
						free(args[i]);
					}
					free(args);
				}
			}

			free(path_with_slash);
			free(full_path);
		}

		dir = _strtok(NULL, delim);
	}

	return -1;
}
