#include "main.h"

/**
 * env_builtin - Implement the env built-in, which prints the current environment.
 *
 * Return: Always returns 0.
 */
int env_builtin(void)
{
	int i;
	/* Access the current environment variables */
	extern char **environ; 

	for (i = 0; environ[i] != NULL; i++)
	{
		write(STDOUT_FILENO, environ[i], _strlen(environ[i]));
		write(STDOUT_FILENO, "\n", 1);
	}

	return (0);
}
