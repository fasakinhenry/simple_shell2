/**
 * string_to_int_conv - Converts string to integer
 * @str: String to be converted
 *
 * Return: result * the sign
 * this tells us if the integer converted to is +ve or -ve
*/

int string_to_int_conv(const char *str)
{
	int result = 0;
	int sign = 1;
	int i = 0;

	if (str[0] == '-')
	{
		sign = -1;
		i = 1;
	}

	for (; str[i] != '\0'; i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			result = (result * 10 + (str[i] - '0'));
		} else
		{
			/* Handle invalid characters here if needed */
			return (0); /* Return 0 for invalid input */
		}
	}

	return (result * sign);
}
