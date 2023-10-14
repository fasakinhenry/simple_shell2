#include "main.h"

/**
 * execute_command - execute commands if command is detected
 * @args: command to be executed
 */

int execute_commands(char **args)
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

int execute_command(char **args)
{
	if (args[0] == NULL)
		return (0);
	if (_strcmp(args[0], "cd") == 0)
	{
		if (args[1] != NULL)
		{
			if (chdir(args[1]) != 0)
			{
				perror("cd");
				return (-1);
			}
		}
		return (0);
	}
	if (access(args[0], X_OK) == 0)
	{
		pid_t child = fork();

		if (child == -1)
		{
			perror("problem");
			return (-1);
		} else if (child == 0)
		{
			execve(args[0], args, environ);
			perror("execve");
			exit(EXIT_FAILURE);
		} else
		{
			int status, exit_status;

			waitpid(child, &status, 0);
			if ((status & 255) == 0)
				exit_status = (status >> 8) & 255;
			else
				exit_status = -1;
			return (exit_status);
		}
	} else
	{
		char path[256], *binDirectory = "/bin/";
		int i = 0, j = 0;

		while (binDirectory[i] != '\0')
		{
			path[i] = binDirectory[i];
			i++;
		}

		while (args[0][j] != '\0')
		{
			path[i] = args[0][j];
			i++;
			j++;
		}

		path[i] = '\0';
		if (access(path, X_OK) == 0)
		{
			pid_t child = fork();

			if (child == -1)
			{
				perror("problem");
				return (-1);
			} else if (child == 0)
			{
				execve(path, args, environ);
				perror("execve");
				exit(EXIT_FAILURE);
			} else
			{
				int status;
				int exit_status;

				waitpid(child, &status, 0);
				if ((status & 255) == 0)
					exit_status = (status >> 8) & 255;
				else
					exit_status = -1;
				return (exit_status);

			}
		} else
		{
			write(STDOUT_FILENO, "Command not found.\n", 19);
			return (-1);
		}
	}
}
