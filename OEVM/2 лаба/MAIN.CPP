#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <dos.h>
//keyb ru 866 for russian
void scroll (int local_S, int direction, char left_row, char left_column, char right_row, char right_column, char attr);

const char* COLOURS[] =
{
	"����",
	"�����",
	"������",
	"����",
	"����",
	"�������",
	"���筥��",
	"���⫮���",
	"��������",
	"���⫮ᨭ��",
	"���⫮������",
	"����� 樠�",
	"���⫮����",
	"���⫠� ������",
	"�����",
	"����"
};

int main()
{
	int i, j;
	int direction = 7;
	const int x_one = 25,
		  y_one = 8,
		  x_two = 55,
		  y_two = 18,
		  S = 2;
	const float T = 1.2 * 1000;

	clrscr();
	window (x_one, y_one, x_two, y_two);

   for (j = 0; j < 16; j++)//��� ���������� ������
   for (i = 0; i < 16; i++)
   {
      gotoxy(1, 1);
      textcolor(i);
      textbackground(j);
     /* cprintf("�����"); //����� ������ � ���� �������
      textcolor(WHITE);
      textbackground(BLUE); */
      cprintf("txt:%s bg:%s", COLOURS[i], COLOURS[j]);
      delay(T);//��������
      scroll(S, direction, y_one, x_one, y_two, x_two, 0x07);
   }

	return 0;
}

void scroll (int local_S, int direction, char left_row, char left_column, char right_row, char right_column, char attr)
{
	union REGS r;
	if(direction == 7)
	{
		r.h.al = local_S;
		r.h.ah = direction;
	}
	else
	{
		r.h.al = 0;
		r.h.ah = 6;
	}
	r.h.ch =  left_row - 1;
	r.h.cl= left_column - 1;
	r.h.dh = right_row - 1;
	r.h.dl= right_column - 1;
	r.h.bh = attr;
	int86(0x10, &r, &r);
}
