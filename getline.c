#include "main.h"

void *_realloc(void *ptr, unsigned int old, unsigned int new);
void set_pointer(char **lineptr, size_t *n, char *buffer, size_t b);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);

/**
 * _realloc - Reallocates a memory block using malloc and free.
 * @ptr: A pointer to the memory previously allocated.
 * @old: The size in bytes of the allocated space for ptr.
 * @new: The size in bytes for the new memory block.
 *
 * Return: If new == old - ptr.
 *         If new == 0 and ptr is not NULL - NULL.
 *         Otherwise - a pointer to the reallocated memory block.
 */
void *_realloc(void *ptr, unsigned int old, unsigned int new)
{
	void *mem;
	char *ptr_copy, *filler;
	unsigned int index;

	if (new == old)
		return (ptr);

	if (ptr == NULL)
	{
		mem = malloc(new);
		if (mem == NULL)
			return (NULL);

		return (mem);
	}

	if (new == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}

	ptr_copy = ptr;
	mem = malloc(sizeof(*ptr_copy) * new);
	if (mem == NULL)
	{
		free(ptr);
		return (NULL);
	}

	filler = mem;

	for (index = 0; index < old && index < new; index++)
		filler[index] = *ptr_copy++;

	free(ptr);
	return (mem);
}

/**
 * set_pointer - sets the line pointer
 * @lineptr: A buffer for input
 * @n: The size of the pointer
 * @buffer: The string to assign
 * @b: The size of the buffer
 */
void set_pointer(char **lineptr, size_t *n, char *buffer, size_t b)
{
	if (*lineptr == NULL)
	{
		if (b > 120)
			*n = b;
		else
			*n = 120;
		*lineptr = buffer;
	}
	else if (*n < b)
	{
		if (b > 120)
			*n = b;
		else
			*n = 120;
		*lineptr = buffer;
	}
	else
	{
		_strcpy(*lineptr, buffer);
		free(buffer);
	}
}

/**
 * _getline - Reads input from a stream
 * @lineptr: A buffer for input
 * @n: The size of the pointer
 * @stream: The stream
 *
 * Return: number of bytes read
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	static ssize_t input;
	ssize_t ret;
	char c = 'x', *buffer;
	int r;

	if (input == 0)
		fflush(stream);
	else
		return (-1);
	input = 0;

	buffer = malloc(sizeof(char) * 120);
	if (!buffer)
		return (-1);

	while (c != '\n')
	{
		r = read(STDIN_FILENO, &c, 1);
		if (r == -1 || (r == 0 && input == 0))
		{
			free(buffer);
			return (-1);
		}
		if (r == 0 && input != 0)
		{
			input++;
			break;
		}

		if (input >= 120)
			buffer = _realloc(buffer, input, input + 1);

		buffer[input] = c;
		input++;
	}
	buffer[input] = '\0';

	set_pointer(lineptr, n, buffer, input);

	ret = input;
	if (r != 0)
		input = 0;
	return (ret);
}
