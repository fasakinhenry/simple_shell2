#include "main.h"

/**
 * get_input - This function prints the prompt and gets the user's input (Command and Arguments)
 * Return: An array containing the command as the first item (args[0]), and the arguments as separate items
 */

char **get_input(void)
{
	char *input = NULL;
	size_t len = 0;
	ssize_t response;
	char **args = NULL;
	size_t arg_count = 0;
	char *token = NULL;
	char **temp;

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

	token = _strtok(input, " \n");
	while (token != NULL)
	{
		char **temp = realloc(args, (arg_count + 1) * sizeof(char *));
		if (temp == NULL)
		{
			perror("bash: realloc");
			exit(EXIT_FAILURE);
		}

		args = temp;

		args[arg_count] = malloc(strlen(token) + 1);
		if (args[arg_count] == NULL)
		{
			perror("bash: malloc:");
			exit(EXIT_FAILURE);
		}

		_strcpy(args[arg_count], token);

		arg_count++;

		token = _strtok(NULL, " \n");
	}

	temp = realloc(args, (arg_count + 1) * sizeof(char *));
	if (temp == NULL)
	{
		perror("realloc");
		exit(EXIT_FAILURE);
	}
	args = temp;
	args[arg_count] = NULL;

	free(input);

	return(args);
}
