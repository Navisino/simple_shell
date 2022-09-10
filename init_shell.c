#include "main.h"

/**
* main - Funtion
* prompt - Funtion 2
* handle - Function 3
* _EOF - Funtion 4
* shell_exit - Funtion 5
*
* Return - 0
*/

int main(int ac, char **av, char **env)
{
	char *buffer = NULL, **command = NULL;
	size_t buf_size = 0;
	ssize_t chars_readed = 0;
	int cicles = 0;
	(void)ac;

	while (1)
	{
		cicles++;
		prompt();
		signal(SIGINT, handle);
		chars_readed = getline(&buffer, &buf_size, stdin);
		if (chars_readed == EOF)
			_EOF(buffer);
		else if (*buffer == '\n')
			free(buffer);
		else
		{
		buffer[_strlen(buffer) - 1] = '\0';
		command = tokening(buffer, " \0");
		free(buffer);
		if (_strcmp(command[0], "exit") != 0)
			shell_exit(command);
		else if (_strcmp(command[0], "cd") != 0)
			change_dir(command[1]);
		else
			change_dir(command[1]);
		}
		fflush(stdin);
		buffer = NULL, buf_size = 0;
	}
	if (chars_readed == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void prompt(void)
{
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "Hell_Shell>> ", 13);
}

void handle(int signals)
{
	(void)signals;
	write(STDOUT_FILENO, "\nHell_Shell>> ", 14);
}

void _EOF(char *buffer)
{
	if (buffer)
	{
		free(buffer);
		buffer = NULL;
	}

	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "\n", 1);
	free(buffer);
	exit(EXIT_SUCCESS);
}

void shell_exit(char **command)
{
	int sta_tus = 0;

	if (command[1] == NULL)
	{
		free_dp(command);
		exit(EXIT_SUCCESS);
	}

	sta_tus = _atoi(command[1]);
	free_dp(command);
	exit(sta_tus);
}
