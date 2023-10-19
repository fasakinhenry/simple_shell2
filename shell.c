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

		if (args[0] == NULL)
		{
			for (i = 0; args[i] != NULL; i++)
				free(args[i]);
			free(args);
			continue;
		}

		if (_strchr(args[0], '/') != NULL)
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
		else
		{
			if (_strcmp(args[0], "exit") == 0)
			{
				int i;
				if (args[1] != NULL)
				{
					/* Normal/defualt exit status
					int exitstatus;*/
					int exit_status = string_to_int_conv(args[1]);
					exit(exit_status);
				}
				for (i = 0; args[i] != NULL; i++)
				{
					free(args[i]);
				}
				free(args);
				exit(0);
			}
			else if (_strcmp(args[0], "env") == 0)
			{
				/* Call the env_builtin function */
				env_builtin();
			}
			else if (_strcmp(args[0], "setenv") == 0)
			{
				setenv_builtin(args);
			}
			else if (_strcmp(args[0], "unsetenv") == 0)
			{
				unsetenv_builtin(args);
			}
			else if (_strcmp(args[0], "cd") == 0)
			{
				char *new_directory = args[1];
				char *home_directory = getenv("HOME");
				char current_directory[4096];

				if (new_directory == NULL || _strcmp(new_directory, "~") == 0)
				{
					new_directory = home_directory;
				}
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
						continue;
					}
				}

				if (getcwd(current_directory, sizeof(current_directory)) == NULL)
				{
					perror("getcwd");
					continue;
				}

				if (chdir(new_directory) != 0)
				{
					perror("cd");
				}
				else
				{
					if (setenv("OLDPWD", current_directory, 1) != 0)
					{
						perror("setenv");
					}
					if (setenv("PWD", new_directory, 1) != 0)
					{
						perror("setenv");
					}
				}
			}
			else
			{

				/*
				if (execute_command(args) == -1)
				{
					write(STDOUT_FILENO, "Command not found.\n", 19);
					for (i = 0; args[i] != NULL; i++)
						free(args[i]);
					free(args);
				}*/
				execute_command(args);

				for (i = 0; args[i] != NULL; i++)
				{
					free(args[i]);
				}
				free(args);
			}
		}
	}
}
