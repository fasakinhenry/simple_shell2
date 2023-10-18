#include "main.h"

/**
 * main - Entry point for the shell
 *
 * Return: On success, returns 0. On error, returns -1 and sets errno.
 */
int main(void)
{
	while (1)
	{
		char **args = get_input();

		if (args == NULL)
		{
			perror("Error occurred while getting input.");
			continue;
		}

		if (_strchr(args[0], '/') != NULL)
		{
			if (args[0] != NULL && access(args[0], X_OK) == 0)
				execute_external_command(args);
			else
				cleanup_arguments(args);
		}
		else
		{
			if (_strcmp(args[0], "exit") == 0)
			{
				handle_exit(args);
			}
			else if (_strcmp(args[0], "setenv") == 0)
			{
				setenv_builtin(args);
			}
			else if (_strcmp(args[0], "unsetenv") == 0)
			{
				unsetenv_builtin(args);
			}
			else
			{
				execute_command(args);
			}
			cleanup_arguments(args);
		}
	}
}

/**
 * execute_external_command - Execute an external command.
 * @args: The arguments for the command.
 */
void execute_external_command(char **args)
{
	pid_t child = fork();

	if (child == -1)
	{
		perror("Fork failed");
		exit(EXIT_FAILURE);
	}
	else if (child == 0)
	{
		execve(args[0], args, environ);
		perror("execve");
		cleanup_arguments(args);
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(NULL);
		cleanup_arguments(args);
	}
}

/**
 * handle_exit - Handle the "exit" command.
 * @args: The arguments for the command.
 */
void handle_exit(char **args)
{
	if (args[1] != NULL)
	{
		int exit_status = string_to_int_conv(args[1]);

		exit(exit_status);
	}
	cleanup_arguments(args);
	exit(0);
}

/**
 * cleanup_arguments - Free memory used by argument array.
 * @args: The argument array to clean up.
 */
void cleanup_arguments(char **args)
{
	int i;

	for (i = 0; args[i] != NULL; i++)
	{
		free(args[i]);
	}
	free(args);
}
