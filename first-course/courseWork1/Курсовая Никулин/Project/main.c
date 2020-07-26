#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <locale.h>

void decryption()
{
    FILE *pN, *pB, *pC;
    int last_space, n_space = 0;
    long pos_symbol;
    char cc;

    if ((pN = fopen("../newtext.txt", "w")) == NULL)
    {
        printf("Не удалось открыть файл для записи, повторите попытку");
    }
    if ((pB = fopen("../book.txt", "r")) == NULL)
    {
        printf("Не удалось открыть книгу, повторите попытку");
    }
    if ((pC = fopen("../cipher.txt", "r")) == NULL)
    {
        printf("Не удалось открыть оригинальный текст, повторите попытку");
    }

    while (fscanf(pC, "%d%ld", &last_space, &pos_symbol) != EOF)
    {
        fseek(pB, 0, SEEK_SET);
        while (n_space < last_space-1)
        {
            fscanf(pB, "%c", &cc);
            if (cc == ' ') n_space++;
        }
        fseek(pB, pos_symbol-1, SEEK_CUR);
        fscanf(pB, "%c", &cc);
        fprintf(pN, "%c", cc);
        n_space = 0;
	}
    puts("Дешифровка завершена успешно.");

    if(fclose(pN)==EOF) perror("Input closing error");
    if(fclose(pB)==EOF) perror("Input closing error");
    if(fclose(pC)==EOF) perror("Input closing error");
}

void encryption()
{
    FILE *pO, *pB, *pC;
    long pos_last_space = 0, pos_symblol;
    char cO, cB;
    int nomerslova = 1;
    int flag = 0;

    if ((pO = fopen("../text.txt", "r")) == NULL)
    {
        printf("Не удалось открыть оригинальный текст, повторите попытку");
    }
    if ((pB = fopen("../book.txt", "r")) == NULL)
    {
        printf("Не удалось открыть книгу, повторите попытку");
    }
    if ((pC = fopen("../cipher.txt", "w")) == NULL)
    {
        printf("Не удалось открыть файл для записи, повторите попытку");
    }

    while(((cO=fgetc(pO))!=EOF))
    {
        fseek(pB, 0, SEEK_SET);
        while(((cB=fgetc(pB))!=EOF) && (flag ==0))
        {
           if(cO==cB)
           {
               pos_symblol = ftell(pB);
               fprintf(pC,"%d %ld\n", nomerslova, pos_symblol - pos_last_space);
               flag = 1;
           }
           if(cB==' ')
           {
               nomerslova+=1;
               pos_last_space = ftell(pB);
           }
        }
        flag = 0;
        nomerslova = 1;
        pos_last_space = 0;
    }
    puts("Шифровка завершена успешно.");

    if(fclose(pO)==EOF) perror("Input closing error");
    if(fclose(pB)==EOF) perror("Input closing error");
    if(fclose(pC)==EOF) perror("Input closing error");
}

int main()
{
    setlocale(LC_ALL, "RUS");
    int operation = -1;
    puts("Программа шифровки/дешифровки Книжный шифр.");
    puts("----------------");
    puts("Инструкции:");
    puts("Все текстовые файлы должны находиться на каталог выше (в родительском каталоге программы).");
    puts("Книга по которой шифруем/дешифруем должна иметь формат TXT и имя 'book'.");
	puts("----------------");
    puts("Для Шифровки:");
    puts("Текст, который должен быть зашифрован, должен находиться в TXT файле с именем 'text'.");
    puts("Код будет сохранен в TXT файл с именем 'cipher'.");
    puts("----------------");
    puts("Для Дешифровки:");
    puts("Текст, который должен быть расшифрован, должен находиться в TXT файле с именем 'cipher'.");
    puts("Расшифрованный текст будет сохранен в TXT файл с именем 'newtext'.");
    puts("----------------");
    puts("----------------");
    while(operation != 0)
    {
        puts("Выберите действие:");
        puts("1 - шифровка.");
        puts("2 - дешифровка.");
        puts("3 - Очистка консоли.");
        puts("0 - выход из программы.");
        if (scanf("%d", &operation) != 1) // если данные не удалось присвоить переменной,
            scanf("%*s"); // то выбросить их в виде строки.
        if (operation != 1 && operation != 2 && operation != 3 && operation != 0)
        {
        	puts("Выбранного действия не существует, проверьте правильность ввода и повторите попытку.");
        	operation = -1;
		}
        else if (operation == 1)
        {
            printf("Вы выбрали Шифровку\n");
            encryption();
        }
        else if (operation == 2)
        {
            printf("Вы выбрали Дешифровку\n");
            decryption();
        }
        else if (operation == 3)
        {
            system("cls");
        }
        puts("----------------");
    }

    puts("Вы вышли из программы.");
    return 0;
}
