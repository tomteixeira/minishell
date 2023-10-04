int	main(int argc, char **argv, char **env)
{
	int i = 0;
	(void)argc;
	(void)argv;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
	return 0;
}