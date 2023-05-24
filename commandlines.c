#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

#define COMMAND_LENGTH 100
#define MAX_ARGUMENTS 10
#define PATH_LENGTH 100

/* handle command lines with argument */
/**
 * command_line - Handle command lines with arguments
 * @command: command to be passed
 * @path: path to the argument
 * Return: char
 */
char *command_line(char *command, char *path)
{
	char direction[PATH_LENGTH];
	char *tok;

	tok = strtok(path, ":");
	while (tok != NULL)
	{
		snprintf(direction, PATH_LENGTH, "%s/%s", tok, command);
		if (access(direction, X_OK) == 0)
			return (strdup(direction));
		tok = strtok(NULL, ":");
	}
	return (NULL);
}
/**
 * handle_cd - this is the function to handle cd command
 * @arguments: arguments to be passed
 * Return: void
 */
void handle_cd(char **arguments)
{
	char *direction = arguments[1], current_direction[PATH_LENGTH];
	char new_direction[PATH_LENGTH];
	if (direction == NULL)
	{
		direction = getenv("HOME");
		if (direction == NULL)
		{
			write(STDERR_FILENO, "cd: no home directory\n", 22);
			return;
		}
	}
	if (strcmp(direction, "_") == 0)
	{
		direction = getenv("OLDPWD");
		if (direction == NULL)
		{
			write(STDERR_FILENO, "cd: No previous direction\n", 26);
			return;
		}
	}
	if (getcwd(current_direction, sizeof(current_direction)) == NULL)
	{
		write(STDERR_FILENO, "cd: Failed to get current directory\n", 36);
		return;
	}
	if (setenv("OLDPWD", current_direction, 1) != 0)
	{
		write(STDERR_FILENO, "cd: Failed to set OLDPWD\n", 25);
		return;
	}
	if (getcwd(new_direction, sizeof(new_direction)) == NULL)
	{
		write(STDERR_FILENO, "cd: Failed to get current directory\n", 36);
		return;
	}
	if (setenv("PWD", new_direction, 1) != 0)
	{
		write(STDERR_FILENO, "cd: Failed to set PWD\n", 22);
		return;
	}
}

/**
 * file_path - Get the file path if it exists
 * @file: file to check the path for
 * Return: char
 */
char *file_path(char *file)
{
    struct stat st;
    if (stat(file, &st) == 0 && S_ISREG(st.st_mode))
        return realpath(file, NULL);
    return NULL;
}

/* handle command path */
/**
 * command_path - Handle the PATH
 * @command: command to be passed
 * @arguments: the argument to be passed
 * Return: void
 */
void command_path(char *command, char **arguments)
{
	int j = 0;
	char *tok;

	tok = strtok(command, " ");
	while (tok != NULL && j < MAX_ARGUMENTS)
	{
		arguments[j] = tok;
		tok = strtok(NULL, " ");
		j++;
	}
	arguments[j] = NULL;
}
/**
 * main - Write a UNIX command line interpreter
 * Return: 0
 */
int main(void)
{
	char command[COMMAND_LENGTH], *arguments[MAX_ARGUMENTS + 1];
	char *execArgs[3], *executable, *path;
	int status;
	pid_t pid;

	path = getenv("PATH");
	while (1)
	{
		write(STDOUT_FILENO, "cisfun# ", 8);
		if (!fgets(command, sizeof(command), stdin))
			break;
		command[strcspn(command, "\n")] = '\0';
		if (strncmp(command, "exit", 4) == 0)
			break;
		command_path(command, arguments);
		executable = command_line(arguments[0], path);
		if (executable == NULL)
		{
			write(STDOUT_FILENO, "No such file or directory\n", 26);
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
			execArgs[0] = arguments[0];
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
