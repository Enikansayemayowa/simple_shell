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

#define BUFFER_SIZE 1024

char buffer[BUFFER_SIZE];
int buffer_pos = 0;
int buffer_size = 0;

/**
 * handleExit - function to handle exit
 * @status: check for the status
 * Return: void
 */
void handleExit(char *status) 
{
	int exit_status = atoi(status);

	exit(exit_status);
}

/**
 * handle_Set_env - Implement the setenv builtin commands
 * @argument: shell arguments
 * Return: void
 */
void handle_Set_env(char **arguments)
{
	if (arguments[1] == NULL || arguments[2] == NULL)
	{
		write(STDERR_FILENO, "setenv: Invalid arguments\n", 26);
		return;
	}
	if (setenv(arguments[1], arguments[2], 1) != 0)
	{
		write(STDERR_FILENO, "setenv: Failed to set environment variable\n", 43);
	}
}
/**
 * handle_Unsetenv - Implement the unsetenv builtin commands
 * @argument: shell arguments
 * Return: void
 */

void handle_Unsetenv(char **arguments)
{
	if (arguments[1] == NULL)
	{
		write(STDERR_FILENO, "unsetenv: Invalid arguments\n", 28);
		return;
	}
	if (unsetenv(arguments[1]) != 0)
	{
		write(STDERR_FILENO, "unsetenv: Failed to unset environment variable\n", 47);
	}

}
/**
 * custom_Get_Line - Write your own getline function
 * Return: char
 */
char* customGetLine()
{
	char* line = NULL, current_char;
	int line_pos = 0;
	int line_size = BUFFER_SIZE;

	while (1)
	{
		if (buffer_pos >= buffer_size)
		{
			buffer_size = read(STDIN_FILENO, buffer, BUFFER_SIZE);
			buffer_pos = 0;
			if (buffer_size == 0)
				break;
		}
		current_char = buffer[buffer_pos++];
		if (current_char == '\n' || current_char == '\0')
		{
			line[line_pos] = '\0';
			break;
		}
		line[line_pos++] = current_char;
		if (line_pos >= line_size)
		{
			line_size += BUFFER_SIZE;
			line = realloc(line, line_size);
		}
	}
	return line;
}
/**
 * count_Arguments - counting the number of arguments
 * @command: argument command
 * Return: int
 */
int countArguments(char *command)
{
	int count = 0;
	int length = strlen(command);
	int j = 0;

	while (j < length)
	{
		while (j < length && (command[j] == ' ' || command[j] == '\t'))
			j++;
		if (j < length && (command[j] != ' ' && command[j] != '\t'))
			count++;
		while (j < length && (command[j] != ' ' && command[j] != '\t'))
			j++;
	}
	return count;
}
