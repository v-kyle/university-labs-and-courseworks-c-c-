#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>

int main()
{
 float xa, ya, xb, yb, xc, yc, xd, yd, xT, yT, S, xM,yM, dd;
 int o1,o2,o;
 setlocale(LC_ALL,"Rus");
 puts("����� 1�� �����");
 scanf ("%f%f", &xa, &ya); // ������ ���������� ����� A
 puts("����� 2�� �����");
 scanf ("%f%f", &xb, &yb); // ������ ���������� ����� B
 puts("����� 3�� �����");
 scanf ("%f%f", &xc, &yc); // ������ ���������� ����� C
 puts("����� 4�� �����");
 scanf ("%f%f", &xd, &yd); // ������ ���������� ����� D
puts("����� ���������� �����");
 scanf ("%f%f", &xT, &yT); // ������ ���������� ����� T

 if ((((xT - xa)*(yb-ya)-(yT-ya)*(xb-xa))*((xc - xa)*(yb-ya)-(yc-ya)*(xb-xa)) >= 0) &&
 (((xT - xb)*(yc-yb)-(yT-yb)*(xc-xb))*((xa - xb)*(yc-yb)-(ya-yb)*(xc-xb)) >= 0) &&
 (((xT - xc)*(ya-yc)-(yT-yc)*(xa-xc))*((xb - xc)*(ya-yc)-(yb-yc)*(xa-xc)) >= 0 ))
 {
    o1=1;
 } else {
    o1=0;
 }

 if ((((xT - xa)*(yd-ya)-(yT-ya)*(xd-xa))*((xc - xa)*(yd-ya)-(yc-ya)*(xd-xa)) >= 0) &&
 (((xT - xd)*(yc-yd)-(yT-yd)*(xc-xd))*((xa - xd)*(yc-yd)-(ya-yd)*(xc-xd)) >= 0) &&
 (((xT - xc)*(ya-yc)-(yT-yc)*(xa-xc))*((xd - xc)*(ya-yc)-(yd-yc)*(xa-xc)) >= 0 ))
 {
    o2=1;
 } else {
    o2=0;
 }

o=(o1+o2)>0;
if (o>0)
printf("������ ����������������\n");
else printf("��� ����������������\n");

S=abs((xa*yb-ya*xb)+(xb*yc-yb*xc)+(xc*yd-yc*xd)+(xd*ya-yd*xa))/2;
puts("�������:");
printf("%f\n",S);

xM=(xa+xb+xc+xd)/4;
yM=(ya+yb+yc+yd)/4;
dd=sqrt((xT-xM)*(xT-xM)+(yT-yM)*(yT-yM));
printf("���������� �� ����� �� ������ �������: %.2f",dd);

 return 0;
}
