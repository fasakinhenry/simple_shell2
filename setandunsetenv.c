#include "main.h"

/**
 * setenv_builtin - Set or modify an environment variable
 * @args: An array containing the command and arguments
 */
void setenv_builtin(char **args)
{
	if (args[1] == NULL || args[2] == NULL)
	{
		char error_msg[] = "Usage: setenv VARIABLE VALUE\n";

		write(STDERR_FILENO, error_msg, 29);
		return;
	}

	if (args[3] != NULL)
	{
		char error_msg[] = "setenv: Too many arguments\n";

		write(STDERR_FILENO, error_msg, 24);
		return;
	}

	if (setenv(args[1], args[2], 1) == -1)
	{
		char error_msg[] = "setenv: Error while setting environment variable\n";

		write(STDERR_FILENO, error_msg, 46);
	}
}

/**
 * unsetenv_builtin - Remove an environment variable
 * @args: An array containing the command and arguments
 */
void unsetenv_builtin(char **args)
{
	if (args[1] == NULL)
	{
		char error_msg[] = "Usage: unsetenv VARIABLE\n";

		write(STDERR_FILENO, error_msg, 27);
		return;
	}

	if (args[2] != NULL)
	{
		char error_msg[] = "unsetenv: Too many arguments\n";

		write(STDERR_FILENO, error_msg, 22);
		return;
	}

	if (unsetenv(args[1]) == -1)
	{
		char error_msg[] = "unsetenv: Error while unsetting environment variable\n";

		write(STDERR_FILENO, error_msg, 53);
	}
}

/**
 * custom_getenv - Custom implementation of getenv
 * @name: Name of the environment variable to retrieve
 *
 * Return: A pointer to the value of the environment variable,
 * or NULL if not found.
 */
char *custom_getenv(const char *name)
{
	int i = 0;
	int name_length = _strlen(name);

	if (name == NULL)
		return (NULL);

	for (; environ[i] != NULL; i++)
	{
		char *env_var = environ[i];

		printf("Checking environ[%d]: %s\n", i, environ[i]);
		if (strncmp(env_var, name, name_length) == 0)
		{
			char *value = strchr(env_var, '=');

			if (value != NULL)
			{
				printf("Found a match for %s! Returning its value.\n", name);
				return (environ[i] + _strlen(name) + 1);
			}
		}
	}
	printf("No match found for %s. Returning NULL.\n", name);
	return (NULL);
}
