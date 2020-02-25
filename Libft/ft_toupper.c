int ft_toupper(int c)
{
	if ('a' <= c && c <= 'z')
		return (c + ('A' - 'a'));
	return (c);
}
