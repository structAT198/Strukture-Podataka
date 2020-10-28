#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define IME_PREZIME_MAX 50
#define MAX_BB 100

typedef struct student
{
	char ime[IME_PREZIME_MAX];
	char prezime[IME_PREZIME_MAX];
	int broj_bodova;
}student;

int main()
{
	student* studenti;
	FILE* text_file;
	int student_count = 0;
	text_file = fopen("Studenti.txt", "r");
	if(text_file == NULL)
	{
		printf("\nGreska pri otvaranju!\n");
	}
	else
	{
		char temp = '\0';
		while(feof(text_file) != 1)
		{
			temp = fgetc(text_file);
			if (temp == '\n')
			{
				student_count++;
			}
		}
		printf("Nasli smo: %d studenata.\n", student_count);
		studenti = (student*) malloc (sizeof(student) * student_count);
		if(studenti == NULL)
		{
			printf("Nema memorije vise!");
		}
		else
		{
			rewind(text_file);
			int tmp = 0;
			for (int i = 0; i < student_count; i++)
			{
				tmp = fscanf(text_file, "%s %s %d", studenti[i].ime, studenti[i].prezime, & studenti[i].broj_bodova);
				printf("Student: %s %s BB Apsolutno: %d BB Relativno: %f\n", studenti[i].ime, studenti[i].prezime, studenti[i].broj_bodova, (float) studenti[i].broj_bodova / (MAX_BB * 100));
			}
			free(studenti);
			fclose(text_file);
		}
	}
	return 0;
}