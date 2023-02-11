#include"main.h"
void Move(int plane_num, int dice_num)
{
	int x = Plane[player][plane_num][0];
	int y = Plane[player][plane_num][1];
	int state = Plane[player][plane_num][2];
	if (state == 0) {
		if (dice_num == 6) {
			printf("恭喜到达跳跃点，可随机跳跃1-6格\n");
			int new_dice = 1 + rand() % 6;
			printf("随机跳跃%d格\n", new_dice);
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
					printf("恭喜到达跳跃点，可随机跳跃1-6格\n");
					int new_dice = 1 + rand() % 6;
					printf("随机跳跃%d格\n", new_dice);
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
				printf("%d号玩家%d号飞机返场\n", now_condition_1, j);
			}
		}
	}
	if (newstate != 2)a[newx][newy] = b[player];
	if (Plane[player][plane_num][2] == 2) printf("%d号玩家%d号飞机到达终点!\n", player, plane_num);
}
void Play(int dice_num)
{
	int number = 0, flag = 0, new_dice_num = dice_num, flag1 = 0;
	int state = Player_state();
	if (state == 0 && dice_num != 6) flag1 = 1, printf("很遗憾，本轮%d号玩家无法移动\n", player);
	else if (state == 2 || (state == 0 && dice_num == 6)) {
		printf("本轮可移动的飞机编号为：");
		for (int i = 0; i < 4; i++) if (Plane[player][i][2] == 0 || Plane[player][i][2] == 1) printf("%d ", i);
		printf("\n");
		if (player_type[player] == 1) {
			printf("请%d号玩家选择本轮移动的飞机编号：", player), scanf("%d", &number);
			while (number>3||Plane[player][number][2] == 2) printf("请%d号玩家按照指示重新输入飞机编号：",player),scanf("%d",&number);
		}
		else {
			number = rand() % 4;
			while (Plane[player][number][2] == 2) number = rand() % 4;
		}
		printf("%d号玩家选择了移动%d号飞机\n", player, number);
		if (state == 0) new_dice_num = roll_dice(), printf("%d号玩家又一次掷骰子并掷到了%d\n", player, new_dice_num);
	}
	else if (state == 1) {
		if (dice_num != 6) flag = 1;
		printf("本轮可移动的飞机编号为：");
		for (int i = 0; i < 4; i++) if (Plane[player][i][2] == flag) printf("%d ", i);
		printf("\n");
		if (player_type[player] == 1) {
			printf("请%d号玩家选择本轮移动的飞机编号：", player), scanf("%d", &number);
			while (number > 3 || Plane[player][number][2] != flag) printf("请%d号玩家按照指示重新输入飞机编号：",player), scanf("%d", &number);
		}
		else {
			number = rand() % 4;
			while (Plane[player][number][2] != flag) number = rand() % 4;
		}
		printf("%d号玩家选择了移动%d号飞机\n", player, number);
		if (flag == 0) new_dice_num = roll_dice(), printf("%d号玩家又一次掷骰子并掷到了%d\n", player, new_dice_num);
	}
	if (flag1 == 0) Move(number, new_dice_num);
}