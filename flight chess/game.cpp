#include"main.h"
void Move(int plane_num, int dice_num)
{
	int x = Plane[player][plane_num][0];
	int y = Plane[player][plane_num][1];
	int state = Plane[player][plane_num][2];
	if (state == 0) {
		if (dice_num == 6) {
			printf("��ϲ������Ծ�㣬�������Ծ1-6��\n");
			int new_dice = 1 + rand() % 6;
			printf("�����Ծ%d��\n", new_dice);
			Move(plane_num, dice_num + new_dice);
			return;
		}
		else Plane[player][plane_num][0] = 2, Plane[player][plane_num][1] = 2 * dice_num, Plane[player][plane_num][2] = 1, a[x][y] = ' ';
	}
	else {
		if (y > 31) {
			if (y + dice_num > 37) Plane[player][plane_num][1] = 74 - dice_num - y;
			else if (y + dice_num == 37) Plane[player][plane_num][2] = 2;
			else Plane[player][plane_num][1] = y + dice_num;
		}
		else {
			if (y + 2 * dice_num > 31) Plane[player][plane_num][0] = ((player > 1) ? player + 2 : player), Plane[player][plane_num][1] = 16 + dice_num + y / 2;
			else {
				if (y + 2 * dice_num == 12) {
					printf("��ϲ������Ծ�㣬�������Ծ1-6��\n");
					int new_dice = 1 + rand() % 6;
					printf("�����Ծ%d��\n", new_dice);
					Move(plane_num, dice_num + new_dice);
					return;
				}
				else Plane[player][plane_num][1] = y + 2 * dice_num;
			}
			if (Plane[player][plane_num][1] == 37)  Plane[player][plane_num][2] = 2;
		}
		int now_condition = Judge_place(x, y);
		if (now_condition == -1) {
			if (y < 31) a[x][y] = (char)257;
			else a[x][y] = 'D';
		}
	}
	int newx = Plane[player][plane_num][0];
	int newy = Plane[player][plane_num][1];
	int newstate = Plane[player][plane_num][2];
	int now_condition_1 = Judge_place(newx, newy);
	if (now_condition_1 != player && now_condition_1 != -1) {
		for (int j = 0; j < 4; j++) {
			if (Plane[now_condition_1][j][0] == newx && Plane[now_condition_1][j][1] == newy) {
				Plane[now_condition_1][j][0] = ((now_condition_1 > 1) ? now_condition_1 + 2 : now_condition_1), Plane[now_condition_1][j][1] = j, Plane[now_condition_1][j][2] = 0;
				a[Plane[now_condition_1][j][0]][j] = b[now_condition_1];
				printf("%d�����%d�ŷɻ�����\n", now_condition_1, j);
			}
		}
	}
	if (newstate != 2)a[newx][newy] = b[player];
	if (Plane[player][plane_num][2] == 2) printf("%d�����%d�ŷɻ������յ�!\n", player, plane_num);
}
void Play(int dice_num)
{
	int number = 0, flag = 0, new_dice_num = dice_num, flag1 = 0;
	int state = Player_state();
	if (state == 0 && dice_num != 6) flag1 = 1, printf("���ź�������%d������޷��ƶ�\n", player);
	else if (state == 2 || (state == 0 && dice_num == 6)) {
		printf("���ֿ��ƶ��ķɻ����Ϊ��");
		for (int i = 0; i < 4; i++) if (Plane[player][i][2] == 0 || Plane[player][i][2] == 1) printf("%d ", i);
		printf("\n");
		if (player_type[player] == 1) {
			printf("��%d�����ѡ�����ƶ��ķɻ���ţ�", player), scanf("%d", &number);
			while (number>3||Plane[player][number][2] == 2) printf("��%d����Ұ���ָʾ��������ɻ���ţ�",player),scanf("%d",&number);
		}
		else {
			number = rand() % 4;
			while (Plane[player][number][2] == 2) number = rand() % 4;
		}
		printf("%d�����ѡ�����ƶ�%d�ŷɻ�\n", player, number);
		if (state == 0) new_dice_num = roll_dice(), printf("%d�������һ�������Ӳ�������%d\n", player, new_dice_num);
	}
	else if (state == 1) {
		if (dice_num != 6) flag = 1;
		printf("���ֿ��ƶ��ķɻ����Ϊ��");
		for (int i = 0; i < 4; i++) if (Plane[player][i][2] == flag) printf("%d ", i);
		printf("\n");
		if (player_type[player] == 1) {
			printf("��%d�����ѡ�����ƶ��ķɻ���ţ�", player), scanf("%d", &number);
			while (number > 3 || Plane[player][number][2] != flag) printf("��%d����Ұ���ָʾ��������ɻ���ţ�",player), scanf("%d", &number);
		}
		else {
			number = rand() % 4;
			while (Plane[player][number][2] != flag) number = rand() % 4;
		}
		printf("%d�����ѡ�����ƶ�%d�ŷɻ�\n", player, number);
		if (flag == 0) new_dice_num = roll_dice(), printf("%d�������һ�������Ӳ�������%d\n", player, new_dice_num);
	}
	if (flag1 == 0) Move(number, new_dice_num);
}