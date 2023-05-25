#include "main.h"
/**
 * remove_custom_comments - function replaces first instance
 * @buffer: address of string
 * Return: 0;
 */
void remove_custom_comments(char *buffer)
{
	int j;

	for (j = 0; buffer[j] != '\0'; j++)
	{
		if (buffer[j] == '#' && (!j || buffer[j - 1] == ' '))
		{
			buffer[j] = '\0';
			break;
		}
	}
}

/**
 * puts_find - prints a string
 * @string: the string to be printed
 * @find: the file descriptor to write to
 * Return: int
 */
int puts_find(char *string, int find)
{
	int count = 0;
	int j = 0;
	if (!string)
		return 0;
	while (string[j] != '\0')
	{
		count += put_fd(string[j], find);
		j++;
	}
	return count;
}
/**
 * custom_atoi - string to an integer
 * @s: the string to be converted
 * Return: 0 and -1 if error occur
 */
int custom_atoi(char *string)
{
	int j = 0;
	unsigned long int output = 0;

	if (*string == '+')
		string++;
	for (j = 0; string[j] != '\0'; j++)
	{
		if (string[j] >= '0' && string[j] <= '9')
		{
			output *= 10;
			output += (string[j] - '0');
			if (output > INT_MAX)
				return (-1);
		}
		else
		{
			return (-1);
		}
	}
	return (output);
}
/**
 * custom_puts - prints a string to stdout
 * @string: the string to be printed
 * Return: NULL
 */
void custom_puts(char *string)
{
	int j = 0;

	if (!string)
		return;
	while (string[j] != '\0')
	{
		custom_putchar(string[j]);
		j++;
	}
}
/**
 * print_custom_error - prints an error message
 * @format: the parameter & return info struct
 * @string: string containing specified error type
 * Return: 0 and -1 if error occur
 */
void print_custom_error(info_t *format, char *string)
{
	custom_puts(info->fname);
	custom_puts(": ");
	print_custom_d(format->line_count, STDERR_FILENO);
	custom_puts(": ");
	custom_puts(format->argv[0]);
	custom_puts(": ");
	custom_puts(string);
}
