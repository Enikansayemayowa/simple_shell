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
char *customGetLine()
{
	int BUFFER_size = BUFFER_SIZE;
    char *buffer = malloc(BUFFER_size);
    int c, i = 0;
    if (buffer == NULL) {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }
    while ((c = getchar()) != EOF && c != '\n') {
        buffer[i++] = c;
        if (i == BUFFER_size - 1) 
	{
		BUFFER_size += BUFFER_SIZE;
            buffer = realloc(buffer, BUFFER_size);
            if (buffer == NULL) {
                perror("Memory allocation error");
                exit(EXIT_FAILURE);
            }
        }
    }
    buffer[i] = '\0';

    if (c == EOF && i == 0) {
        free(buffer);
        return NULL;
    }

    return buffer;
}
 /**
 *count_Arguments - counting the number of arguments
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
