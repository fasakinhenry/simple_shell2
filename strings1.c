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

/**
 * _strcmp - compares two strings s1 and s2
 * @s1: The first string
 * @s2: The second string
 *
 * Return: 0, if strings are equal
 * if first string < second string, -1
 * if first string > second string, 1
*/

int _strcmp(const char *s1, const char *s2)
{
	while (*s1 != '\0' && *s2 != '\0')
	{
		if (*s1 != *s2)
		{
			return (*s1 - *s2);
		}
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

/**
 * _strconcat - Concatenates two strings
 * @s1: The first string
 * @s2: The second string
 *
 * Return: A newly allocated string containing the concatenated s1 and s2
 */

char *_strconcat(const char *s1, const char *s2)
{
	char *result;
	int len1 = _strlen(s1);
	int len2 = _strlen(s2);
	int i, j;

	result = malloc(len1 + len2 + 2);
	if (result == NULL)
	{
		perror("Memory allocation error");
		return (NULL);
	}

	for (i = 0; i < len1; i++)
	{
		result[i] = s1[i];
	}

	result[i] = '/';

	for (j = 0; j < len2; j++)
	{
		result[i + 1 + j] = s2[j];
	}

	result[i + 1 + j] = '\0';

	return (result);
}

/**
 * _strlen - Returns the length of a string
 * @s: The string to measure
 *
 * Return: The length of the string
 */
int _strlen(const char *s)
{
	int len = 0;

	while (s[len])
	{
		len++;
	}

	return (len);
}

/**
 * _strchr - Chceks the equality of two strings
 * @s: First string to be checked
 * @c: Second string to be checked
 *
 * Return: @s if the strings are equal
 * else NULL is returned
*/

char *_strchr(char *s, char c)
{
	while (*s != '\0')
	{
		if (*s == c)
			return (s);
		s++;
	}
	return (NULL);
}

/**
 * _strncmp - Compares the first n characters of two strings
 * @s1: The first string
 * @s2: The second string
 * @n: The number of characters to compare
 *
 * Return:
 *  - 0 if the first n characters of s1 and s2 are equal.
 *  - A positive integer if s1 is greater than s2.
 *  - A negative integer if s1 is less than s2.
 */
int _strncmp(const char *s1, const char *s2, size_t n)
{
    size_t i;
    for (i = 0; i < n; i++)
    {
        if (s1[i] == '\0' && s2[i] == '\0')
            return 0;
        if (s1[i] != s2[i])
            return (s1[i] - s2[i]);
    }
    return 0;
}
