#include "main.h"

/**
 * main - This is the main code for the shell
 *
 * Return: on success, 0
 * on error, -1 is returned and the errno is set appropriately
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

		if (_strchr(args[0], '/') != NULL)
		{
			if  (args[0] != NULL && access(args[0], X_OK) == 0)
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
		else
		{
			if (_strcmp(args[0], "exit") == 0) {
				int i;
				if (args[1] != NULL) {
					/* Normal/defualt exit status 
					int exitstatus;*/
					int exit_status = string_to_int_conv(args[1]);
					exit(exit_status);
				}
				for (i = 0; args[i] != NULL; i++) {
					free(args[i]);
				}
				free(args);
				exit(0);
            		} else if (_strcmp(args[0], "env") == 0)
        		{
                		/* Call the env_builtin function */
                		env_builtin();
            		}else if (_strcmp(args[0], "setenv") == 0)
            		{
                		setenv_builtin(args);
            		}
            		else if (_strcmp(args[0], "unsetenv") == 0)
            		{
                		unsetenv_builtin(args);
            		}
			/*
			if (execute_command(args) == -1)
			{
				write(STDOUT_FILENO, "Command not found.\n", 19);
				for (i = 0; args[i] != NULL; i++)
					free(args[i]);
				free(args);
			}*/
			execute_command(args);

			for (i = 0; args[i] != NULL; i++) {
				free(args[i]);
			}
			free(args);
			
		}
	}
}
