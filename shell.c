#include "main.h"

int main(void)
{
	while (1)
	{
		char *input = NULL;
		size_t len = 0;
		char *token;
		ssize_t response;

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

		token = strtok(input, " \n");
		if  (token != NULL)
		{
			pid_t child = fork();

			if (child == -1)
			{
				perror("problem");
				exit(EXIT_FAILURE);
			}
			else if (child == 0)
			{
				char *args[2];
				args[0] = token;
				args[1] = NULL;

				execve(token, args, environ);
				perror("execve");
				free(args[0]);
				exit(EXIT_FAILURE);
			}
			else
			{
				wait(NULL);
			}
		}
		free(input);
	}
}
