#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define COMMAND_LENGTH
/**
 * main - Write a UNIX command line interpreter
 * Return: 0
 */
int main()
{
	char command[COMMAND_LENGTH];
	int status;
	while (1)
	{
		write(STDOUT_FILENO, "shell$ ", 7);
		if (!fgets(command, sizeof(command), stdin))
			breaks;
		command[strcspn(command, "\n")] = '\0';
		if (strncmp(command, "exit", 4) == 0)
			break;
		pid_t pid = fork();
		if (pid < 0)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			execve(command, {command, NULL}, NULL);
			perror("execve");
			exit(EXIT_FAILURE);
		}
		else
		{
			waitpid(pid, &status, 0);
		}
	}
	return (0);
}
