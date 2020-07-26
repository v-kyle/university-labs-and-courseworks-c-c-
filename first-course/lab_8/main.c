#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#define MAX 1000
#define MS 80

struct ZNAK2 {
	char Name[MS];
	char ZOD[MS];
	int DATE[3];
};

int main() {
	struct ZNAK2 temp;
	struct ZNAK2 MASS2[MAX];

	int lc_1, lc_2;
	char zodiac[MS];
	int find = 0;

	setlocale(LC_ALL, "RUS");
	FILE* pF = fopen("input.txt", "r");

	if(pF != NULL) {

		char text[1024];
		int t = 0;
		while(fgets(text, 1024, pF)) {
			int q = 0;
			char *lexeme = strtok (text, ",\n");
			while(lexeme != NULL){
				if(q == 0) {
					strcpy(MASS2[t].Name, lexeme);
				}
				else if(q == 1) {
                    strcpy(MASS2[t].ZOD, lexeme);
				}
				else if(q == 2) {
					MASS2[t].DATE[0] = atoi(lexeme);
				}
				else if(q == 3) {
					MASS2[t].DATE[1] = atoi(lexeme);
				}
				else if(q == 4) {
					MASS2[t].DATE[2] = atoi(lexeme);
				}
				lexeme = strtok(NULL, ",\n");
				q++;
			}
			t++;
		}

		for (int i = 0; i < t - 1; i++) {
			for (int j = 0; j < t - i - 1; j++) {
				lc_1 = MASS2[j].DATE[0] * 10000 + MASS2[j].DATE[1] * 100 + MASS2[j].DATE[2];
				lc_2 = MASS2[j + 1].DATE[0] * 10000 + MASS2[j + 1].DATE[1] * 100 + MASS2[j + 1].DATE[2];
				if (lc_1 > lc_2) {
					temp = MASS2[j];
					MASS2[j] = MASS2[j + 1];
					MASS2[j + 1] = temp;
				}
			}
		}

		printf("Sorted List:\n");
		for (int i = 0; i < t; i++) {
			printf("Name: %s ZOD: %s Date: %d:%d:%d\n", MASS2[i].Name, MASS2[i].ZOD, MASS2[i].DATE[0], MASS2[i].DATE[1], MASS2[i].DATE[2]);
		}

		printf("\nEnter znak of zodiac:\n");
		scanf("%s", zodiac);
		for (int i = 0; i < t; i++) {
			if(strcmp(zodiac, MASS2[i].ZOD) == 0) {
				printf("Name: %s, ZOD: %s, Date: %d:%d:%d\n", MASS2[i].Name, MASS2[i].ZOD, MASS2[i].DATE[0], MASS2[i].DATE[1], MASS2[i].DATE[2]);
				find = 1;
			}
		}
		if(find == 0)
			printf("Not Found");
	}

	else {
		printf("Opening Error");
	}
	if(fclose(pF)==EOF) perror("Input closing error");

	return 0;
}
