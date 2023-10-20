#include "main.h"

/**
 * parse_input - This handles the cd command and conditions
 * @input: the input to be parsed
 * @arg_count: Number of arguments passed
 *
 * Return: on success, 0
 * else -1 is returned and the errno is set appropriately
*/

char **parse_input(char *input, size_t *arg_count)
{
	char **args = NULL;
	char *token = _strtok(input, " \n");

	while (token != NULL)
	{
		char **temp = realloc(args, (*arg_count + 1) * sizeof(char *));

		if (temp == NULL)
		{
			perror("bash: realloc");
			exit(EXIT_FAILURE);
		}

		args = temp;
		args[*arg_count] = malloc(strlen(token) + 1);

		if (args[*arg_count] == NULL)
		{
			perror("bash: malloc:");
			exit(EXIT_FAILURE);
		}

		_strcpy(args[*arg_count], token);
		(*arg_count)++;
		token = _strtok(NULL, " \n");
	}

	return (args);
}


/**
 * get_input - This function prints the prompt
 * and also gets the user's input (Command and Arguments)
 * Return: An array containing the command as the first item (args[0]),
 * and the arguments as separate items
 */

char **get_input(void)
{
	ssize_t response;
	size_t arg_count = 0, len = 0;
	char *input = NULL, **args = NULL;

	write(STDOUT_FILENO, "$ ", 2);
	response = _getline(&input, &len, stdin);

	if (response == (ssize_t)-1)
	{
		free(input);
		exit(EXIT_FAILURE);
	}
	else if (response == 0)
	{
		printf("EOF detected. Exiting the shell.\n");
		free(input);
		exit(EXIT_SUCCESS);
	}

	args = parse_input(input, &arg_count);

	free(input);

	return (args);
}
