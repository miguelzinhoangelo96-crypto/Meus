#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main()
{
	int i;
	int robo;

	printf(" Digite um numero de 0 a 10: ");
	scanf("%d", &i);

	srand(time(NULL));
	robo= (rand() %11);
	

	while (i != robo )
	{

		if (i >= robo)
		{
			printf("Sua escolha: %d -> O numero correto é MAIOR.\n", i);
			scanf("%d", &i);
			printf("\n");
		}

		else
		{
			printf("Sua escolha: %d -> O numero correto é MENOR.\n", i);
			scanf("%d", &i);
			printf("\n");
		}

		sleep(1);
	}

	printf("Voce acertou, o numero era %d.", robo);

	return 0;
}