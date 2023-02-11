#include"main.h"
void invisible()
{
	HANDLE Houtput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = 100;
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(Houtput, &cci);
}
void init()//根据输入的玩家个数初始化棋盘和棋子状态
{
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 38; j++) {
			a[i][j] = ' ';
		}
	}
	for (int i = 0; i < player_num; i++) {
		for (int j = 0; j < 4; j++) {
			if (i > 1) a[i + 2][j] = b[i];
			else a[i][j] = b[i];
		}
		for (int j = 32; j < 38; j++) {
			if (i > 1) a[i + 2][j] = 'D';
			else a[i][j] = 'D';
		}
	}
	for (int j = 2; j < 32; j += 2) a[2][j] = (char)257;
	for (int i = 0; i < player_num; i++) {
		for (int j = 0; j < 4; j++) {
			if (i < 2) Plane[i][j][0] = i, Plane[i][j][1] = j, Plane[i][j][2] = 0;
			else Plane[i][j][0] = i + 2, Plane[i][j][1] = j, Plane[i][j][2] = 0;
		}
	}
}
void Print()
{
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 38; j++) {
			if (i == 3 && a[i][j] == '0') printf(" ");
			else printf("%c", a[i][j]);
		}
		printf("\n");
	}
	for (int i = 0; i < 38; i++)printf("-");
	printf("\n");
}