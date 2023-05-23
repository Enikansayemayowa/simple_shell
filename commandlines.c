#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#define COMMAND_LENGTH 100
/**
 * main - Write a UNIX command line interpreter
 * Return: 0
 */
int main(void)
{
	char command[COMMAND_LENGTH];
	int status;
	pid_t pid;
	char *execArgs[3];

	while (1)
	{
		write(STDOUT_FILENO, "cisfun# ", 7);
		if (!fgets(command, sizeof(command), stdin))
			break;
		command[strcspn(command, "\n")] = '\0';
		if (strncmp(command, "exit", 4) == 0)
			break;
		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			execArgs[0] = command;
			execArgs[1] = NULL;
			execve(command, execArgs, NULL);
			perror("./shell");
			exit(EXIT_FAILURE);
		}
		else
		{
			waitpid(pid, &status, 0);
		}
	}
	return (0);
}
