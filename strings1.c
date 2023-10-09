#include "main.h"

/**
 * _strcpy - Copies one string to another
 * @dest: DESTINATION
 * @src: SOURCE
 *
 * Return: Pointer to destination
 */
char *_strcpy(char *dest, const char *src)
{
	size_t i;

	for (i = 0; src[i] != '\0'; i++)
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}

