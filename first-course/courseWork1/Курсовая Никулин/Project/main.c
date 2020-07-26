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
        printf("�� ������� ������� ���� ��� ������, ��������� �������");
    }
    if ((pB = fopen("../book.txt", "r")) == NULL)
    {
        printf("�� ������� ������� �����, ��������� �������");
    }
    if ((pC = fopen("../cipher.txt", "r")) == NULL)
    {
        printf("�� ������� ������� ������������ �����, ��������� �������");
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
    puts("���������� ��������� �������.");

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
        printf("�� ������� ������� ������������ �����, ��������� �������");
    }
    if ((pB = fopen("../book.txt", "r")) == NULL)
    {
        printf("�� ������� ������� �����, ��������� �������");
    }
    if ((pC = fopen("../cipher.txt", "w")) == NULL)
    {
        printf("�� ������� ������� ���� ��� ������, ��������� �������");
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
    puts("�������� ��������� �������.");

    if(fclose(pO)==EOF) perror("Input closing error");
    if(fclose(pB)==EOF) perror("Input closing error");
    if(fclose(pC)==EOF) perror("Input closing error");
}

int main()
{
    setlocale(LC_ALL, "RUS");
    int operation = -1;
    puts("��������� ��������/���������� ������� ����.");
    puts("----------------");
    puts("����������:");
    puts("��� ��������� ����� ������ ���������� �� ������� ���� (� ������������ �������� ���������).");
    puts("����� �� ������� �������/��������� ������ ����� ������ TXT � ��� 'book'.");
	puts("----------------");
    puts("��� ��������:");
    puts("�����, ������� ������ ���� ����������, ������ ���������� � TXT ����� � ������ 'text'.");
    puts("��� ����� �������� � TXT ���� � ������ 'cipher'.");
    puts("----------------");
    puts("��� ����������:");
    puts("�����, ������� ������ ���� �����������, ������ ���������� � TXT ����� � ������ 'cipher'.");
    puts("�������������� ����� ����� �������� � TXT ���� � ������ 'newtext'.");
    puts("----------------");
    puts("----------------");
    while(operation != 0)
    {
        puts("�������� ��������:");
        puts("1 - ��������.");
        puts("2 - ����������.");
        puts("3 - ������� �������.");
        puts("0 - ����� �� ���������.");
        if (scanf("%d", &operation) != 1) // ���� ������ �� ������� ��������� ����������,
            scanf("%*s"); // �� ��������� �� � ���� ������.
        if (operation != 1 && operation != 2 && operation != 3 && operation != 0)
        {
        	puts("���������� �������� �� ����������, ��������� ������������ ����� � ��������� �������.");
        	operation = -1;
		}
        else if (operation == 1)
        {
            printf("�� ������� ��������\n");
            encryption();
        }
        else if (operation == 2)
        {
            printf("�� ������� ����������\n");
            decryption();
        }
        else if (operation == 3)
        {
            system("cls");
        }
        puts("----------------");
    }

    puts("�� ����� �� ���������.");
    return 0;
}
