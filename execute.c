#include "main.h"

/**
 * execute_command_child - Main execution stream
 * @args: command to be executed
 * @command: The command executed
 *
 * Return: on error 0
 * else -1 is returned and the errno is set appropriately
 */

int execute_command_child(char **args, const char *command)
{
	pid_t child = fork();

	if (child == -1)
	{
		perror("problem");
		return (-1);
	}
	else if (child == 0)
	{
		execve(command, args, environ);
		perror("execve");
		_exit(EXIT_FAILURE);
	}
	else
	{
		int status, exit_status;

		waitpid(child, &status, 0);
		if ((status & 255) == 0)
			exit_status = (status >> 8) & 255;
		else
			exit_status = -1;
		return (exit_status);
	}
}

/**
 * execute_command_in_bin - handles running commands with path
 * it gives reference to the bin command like bin/ls
 * @args: the argument to be passed into the cd command
 *
 * Return: on success, 0
 * else -1 is returned and the errno is set appropriately
*/

int execute_command_in_bin(char **args)
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
		return (execute_command_child(args, path));
	if (access(path, X_OK) != 0)
	{
		write(STDOUT_FILENO, "Command not found.\n", 19);
		return (-1);
	}
	return (0);
}

/**
 * execute_command - This handles the execution of commands
 * @args: the argument determines the kind of command,
 * path or normal commands
 *
 * Return: on success, 0
 * else -1 is returned and the errno is set appropriately
*/

int execute_command(char **args)
{
	if (args[0] == NULL)
		return (0);
	if (access(args[0], X_OK) == 0)
		return (execute_command_child(args, args[0]));
	else
		return (execute_command_in_bin(args));
}
