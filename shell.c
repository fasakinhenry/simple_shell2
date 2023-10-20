#include "main.h"

/**
 * run_path - This handles the running of commands with path
 * @args: the argument to be passed into the cd command
 *
 * Return: on success, 0
 * else -1 is returned and the errno is set appropriately
*/

void run_path(char **args)
{
	if (args[0] != NULL && access(args[0], X_OK) == 0)
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

/**
 * handle_exit - This handles the exit command and conditions
 * @args: the argument to be passed into the cd command
 *
 * Return: on success, 0
 * else -1 is returned and the errno is set appropriately
*/

void handle_exit(char **args)
{
	int i;

	if (args[1] != NULL)
	{
		int exit_status = string_to_int_conv(args[1]);

		for (i = 0; args[i] != NULL; i++)
		{
			free(args[i]);
		}
		free(args);
		exit(exit_status);
	}

	for (i = 0; args[i] != NULL; i++)
	{
		free(args[i]);
	}
	free(args);
	exit(0);
}

/**
 * handle_cd - This handles the cd command and conditions
 * @args: the argument to be passed into the cd command
 *
 * Return: on success, 0
 * else -1 is returned and the errno is set appropriately
*/

int handle_cd(char **args)
{
	char *new_directory = args[1], *home_directory = getenv("HOME"),
	current_directory[4096];

	if (new_directory == NULL || _strcmp(new_directory, "~") == 0)
		new_directory = home_directory;
	else if (_strcmp(new_directory, "-") == 0)
	{
		char *old_directory = getenv("OLDPWD");

		if (old_directory != NULL)
		{
			new_directory = old_directory;
		}
		else
		{
			write(STDERR_FILENO, "OLDPWD environment variable not set\n", 37);
			return (-1);
		}
	}
	if (getcwd(current_directory, sizeof(current_directory)) == NULL)
	{
		perror("getcwd");
		return (-1);
	}

	if (chdir(new_directory) != 0)
	{
		perror("cd");
		return (-1);
	}
	else
	{
		if (setenv("OLDPWD", current_directory, 1) != 0 ||
		setenv("PWD", new_directory, 1) != 0)
		{
			perror("setenv");
			return (-1);
		}
	}
	return (0);
}

/**
 * main - This is the entry point of our shell program
 *
 * Return: on success, 0
 * else -1 is returned and the errno is set appropriately
*/

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
		if (args[0] == NULL)
		{
			for (i = 0; args[i] != NULL; i++)
				free(args[i]);
			free(args);
			continue;
		}
		if (_strchr(args[0], '/') != NULL)
		{
			run_path(args);
		}
		else
		{
			if (_strcmp(args[0], "exit") == 0)
				handle_exit(args);
			else if (_strcmp(args[0], "env") == 0)
				env_builtin();
			else if (_strcmp(args[0], "setenv") == 0)
				setenv_builtin(args);
			else if (_strcmp(args[0], "unsetenv") == 0)
				unsetenv_builtin(args);
			else if (_strcmp(args[0], "cd") == 0)
				handle_cd(args);
			else
				execute_command(args);
			for (i = 0; args[i] != NULL; i++)
				free(args[i]);
			free(args);
		}
	}
}
