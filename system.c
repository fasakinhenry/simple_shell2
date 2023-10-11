#include "main.h"

/** 
 *
 * getenv - gets the environment variables
 */

char *_getenv(const char *name)
{
	char** env = environ;

	while (*env != NULL)
	{
		int name_len = 0;
		while ((*env)[name_len] != '=' && (*env)[name_len] != '\0')
			name_len++;

		if (_strcmp(*env, name) == 0 && (*env)[name_len] == '=')
		{
			return (*env + name_len + 1);
		}

		env++;
	}

	return (NULL);
}
