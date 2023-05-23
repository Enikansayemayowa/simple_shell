#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#define COMMAND_LENGTH 100
#define MAX_ARGUMENTS 10
#define PATH_LENGTH 100
/**
 * main - Write a UNIX command line interpreter
 * Return: 0
 */
int main(void)
{
	char command[COMMAND_LENGTH], *arguments[MAX_ARGUMENTS + 1];
	int status;
	pid_t pid;
	char *execArgs[3], *executable, *path;
	path = getenv("PATH");


	while (1)
	{
		write(STDOUT_FILENO, "cisfun# ", 7);
		if (!fgets(command, sizeof(command), stdin))
			break;
		command[strcspn(command, "\n")] = '\0';
		if (strncmp(command, "exit", 4) == 0)
			break;
		command_path(command, arguments);
		executable = command_line(arguments[0], path);
		if (exucutable == NULL)
		{
			write(STDOUT_FILENO, "Command not found\n", 18);
			continue;
		}
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
			execve(executable, execArgs, NULL);
			perror("execve");
			exit(EXIT_FAILURE);
		}
		else
			waitpid(pid, &status, 0);
		free(executable);
	}
	return (0);
}
/* handle command lines with argument */
/**
 * command_line - Handle command lines with arguments
 * @command: command to be passed
 * @path: path to the argument
 * Return: char
 */
char command_line(char *command, char *path)
{
	char *direction;
	char *tok;
	tok = strtok(path, ":");
	while (tok != NULL)
	{
		snprintf(dir, PATH_LENGTH, "%s/%s", tok, command);
		if (access(direction, X_OK) == 0)
			return (strdup(direction));
		tok = strtok(NULL, ":");
	}
	return (NULL);
}
/* handle command path */
/**
 * command_line - Handle the PATH
 * @command: command to be passed
 * @path: path to the argument
 * Return: void
 */
void command_path(char *command, char **arguments)
{
	int j = 0;
	char *tok = strtok(command, " ");
	while (tok != NULL && < MAX_ARGUMENTS)
	{
		arguments[j] = tok;
		tok = strtok(NULL, " ");
		j++;
	}
	arguments[j] = NULL;
}
