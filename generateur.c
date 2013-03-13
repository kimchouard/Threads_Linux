#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main (int argc, char* argv[])
{
	uint64_t number;
	uint32_t* word = (void*) &number;
	uint64_t* previous_numbers;
	int quantity = 20;
	int magnitude=64;
	int redundancy=50;
	int i;

	//Cb de nombres à générer ?	
	if (argc > 1) quantity=atoi(argv[1]);
	
	//magnitude max en bits	
	if (argc>2) magnitude=atoi(argv[2]);
	
	//% de redondance	
	if (argc>3) redundancy=atoi(argv[3]);

	srandom(0);

	previous_numbers = malloc(quantity*sizeof(uint64_t));

	FILE* fichier;
	fichier=fopen("numbers.txt", "w");
	if (fichier!=NULL)
	{
		for (i=0; i< quantity; i++)
		{
			if (i==0 || random()%100 > redundancy)
			{
				word[0]=random();
				word[1]=random();

				number>>=64-magnitude;
			}
			else number=previous_numbers[random()%i];
			previous_numbers[i]=number;
			printf("%llu\n",(long long) number); 			
			//fprintf(fichier,"%llu\n", number);
		}
		fclose(fichier);
	}

	return 0;
}
