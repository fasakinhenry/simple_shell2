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

	if (name == NULL)
		return (NULL);

	for (; environ[i] != NULL; i++)
	{
		if (_strcmp(environ[i], name) == 0)
		{
			return (environ[i] + _strlen(name) + 1);
		}
	}
	return (NULL);
}

/**
 * _setenv - Initialize a new environment variable or modify an existing one.
 * @name: The name of the environment variable.
 * @value: The value to set for the environment variable.
 * @overwrite: If 1, overwrite the variable if it exists; if 0, do not overwrite.
 *
 * Return: 0 on success, -1 on failure.
 */
int _setenvs(const char *name, const char *value, int overwrite)
{
	char **new_environ = NULL;
	int env_size = 0;
	int i;

	if (!name || !value)
	{
		errno = EINVAL;
		return -1; /* Invalid arguments */
	}

	/* Check if the variable already exists */
	for (i = 0; environ[i] != NULL; i++)
	{
		if (strncmp(name, environ[i], strlen(name)) == 0)
		{
			if (overwrite)
			{
				char *new_env = (char *)malloc(strlen(name) + strlen(value) + 2);
				if (new_env == NULL)
				{
					perror("malloc");
					return -1; /* Memory allocation error */
				}
				free(environ[i]);
				environ[i] = new_env;
				strcpy(environ[i], name);
				strcat(environ[i], "=");
				strcat(environ[i], value);
				return 0;
			}
			else
			{
				return 0; /* Variable already exists, no overwrite */
			}
		}
	}

	/* If the variable doesn't exist, add it to the environment */
	while (environ[env_size] != NULL)
	{
		env_size++;
	}

	new_environ = (char **)malloc((env_size + 2) * sizeof(char *));

	if (new_environ == NULL)
	{
		perror("malloc");
		return -1; /* Memory allocation error */
	}

	/* Copy the old environment variables */
	for (i = 0; i < env_size; i++)
	{
		new_environ[i] = strdup(environ[i]);
		if (new_environ[i] == NULL)
		{
			perror("malloc");
			free(new_environ);
			return -1; /* Memory allocation error */
		}
	}

	/* Add the new environment variable */
	new_environ[env_size] = (char *)malloc(strlen(name) + strlen(value) + 2);
	if (new_environ[env_size] == NULL)
	{
		perror("malloc");
		free(new_environ);
		return -1; /* Memory allocation error */
	}
	strcpy(new_environ[env_size], name);
	strcat(new_environ[env_size], "=");
	strcat(new_environ[env_size], value);
	new_environ[env_size + 1] = NULL;

	/* Replace the old environment with the new one */
	free(environ);
	environ = new_environ;

	return 0;
}

int _strlen(const char *str)
{
	int len = 0;
	while (str[len] != '\0')
	{
		len++;
	}
	return len;
}

int _strcompare(const char *str1, const char *str2, int n)
{
	int i = 0;
	while (i < n)
	{
		if (str1[i] != str2[i])
		{
			return str1[i] - str2[i];
		}
		if (str1[i] == '\0')
		{
			return 0;
		}
		i++;
	}
	return 0;
}

char *_strconcats(const char *str1, const char *str2)
{
	int len1 = _strlen(str1);
	int len2 = _strlen(str2);
	char *result = malloc(len1 + len2 + 2);
	int i = 0;
	int j = 0;
	if (result == NULL)
	{
		return NULL;
	}
	while (i < len1)
	{
		result[i] = str1[i];
		i++;
	}
	result[i] = '=';
	i++;
	while (j < len2)
	{
		result[i] = str2[j];
		i++;
		j++;
	}
	result[i] = '\0';
	return result;
}

int _setenv(const char *name, const char *value, int overwrite)
{
	int index = -1;
	int i = 0;
	/* Count the number of environment variables */
	int env_count = 0;
	char **new_environ = malloc((env_count + 2) * sizeof(char *));
	if (name == NULL || value == NULL)
	{
		return -1; /* Invalid input*/
	}
	for (i = 0; environ[i] != NULL; i++)
	{
		if (_strcompare(environ[i], name, _strlen(name)) == 0)
		{
			index = i;
			break;
		}
	}

	if (index >= 0)
	{
		if (overwrite)
		{
			free(environ[index]);
			environ[index] = _strconcats(name, value);
		}
	}
	else
	{
		int i = 0;
		while (environ[env_count] != NULL)
		{
			env_count++;
		}
		if (new_environ == NULL)
		{
			return -1; /* Memory allocation error */
		}

		/* Copy the existing environment variables */
		for (; i < env_count; i++)
		{
			new_environ[i] = environ[i];
		}

		new_environ[env_count] = _strconcats(name, value);
		new_environ[env_count + 1] = NULL;

		free(environ);
		environ = new_environ;
	}

	return 0;
}
