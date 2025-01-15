#include <stdio.h>

int	main(void)
{
	char	*msg_erro;

	msg_erro = "Ai, ai! Que erro";
	perror(msg_erro);
	printf("After the error message.\n");
}