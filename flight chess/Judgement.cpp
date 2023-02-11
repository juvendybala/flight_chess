#include"main.h"
int Judge()//通过检查棋子状态判断是否有人胜利
{
	for (int i = 0; i < player_num; i++) {
		int cnt = 0;
		for (int j = 0; j < 4; j++) {
			if (Plane[i][j][2] == 2) cnt++;
		}
		if (cnt == 4) return i;
	}
	return -1;
}
int Judge_place(int x, int y)//判断某一位置的飞机种类，对应数字对应玩家，-1表示空
{
	int flag = 1;
	for (int i = 0; i < player_num; i++) {
		for (int j = 0; j < 4; j++) {
			if (Plane[i][j][2] == 1 && Plane[i][j][0] == x && Plane[i][j][1] == y) {
				if (i != player) return i;
				else flag = 0;
			}
		}
	}
	if (flag == 0) return player;
	return -1;
}
int Player_state()//判断玩家的飞机状态，2表示全部出动，1表示有出动的有没出动的(需要根据骰子是否为6分情况），0表示全没出动或除出动外均到场(必须为6才能移动)
{
	int cnt1 = 0, cnt2 = 0;
	for (int i = 0; i < 4; i++) {
		if (Plane[player][i][2] == 0) cnt1++;
		if (Plane[player][i][2] == 2) cnt2++;
	}
	if (cnt1 == 4 || cnt1 + cnt2 == 4) return 0;
	if (cnt1 > 0) return 1;
	return 2;
}
int Judge_place_num(int x, int y)
{
	int cnt = 0;
	for (int i = 0; i < player_num; i++) {
		for (int j = 0; j < 4; j++) {
			if (Plane[i][j][0] == x && Plane[i][j][1] == y && Plane[i][j][2] == 1) cnt++;
		}
	}
	return cnt;
}
void Judge_num()
{
	for (int j = 2; j < 32; j += 2) {
		if (j != 12) {
			int t = Judge_place_num(2, j);
			a[3][j] = (char)(t + (int)'0');
		}
		else {
			a[3][j] = 'J';
		}
	}
}