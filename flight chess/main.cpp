#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<windows.h>
#include<conio.h>
char a[6][40]={'\0'};//作为棋盘
int Plane[4][4][3] = {0 };
//用一个4*4*3的数组记录棋子的位置,第一维表示阵营，第二维表示第几号棋子，第三维前两个元素表示在a数组中的坐标
//第三维后一个元素记录状态，0表示在场里，1表示在路上，2表示已到达终点
int player_type[4] = { 0,1,0,0 };//玩家的类型，0为电脑，1为人类
char b[4] = { 'G','Y','R','B'};//便于后续的棋盘赋值，和player统一
int player = 0;//玩家从0号开始，作为全局变量贯穿所有函数
int gamestate = -1;//-1为继续状态，对应数字表示对应玩家胜
int player_num = 0;//玩家个数，需要用户输入
int cheat = 0;//是否开启作弊模式
void invisible();
void init();
void Print();
void Move(int, int);
void Play(int);
int Judge();
int Judge_place(int, int);
int Player_state();
int Judge_place_num(int, int);
void Judge_num();
int roll_dice();
int roll_dice()
{
	if (cheat == 1) return 6;
	else return (1 + rand() % 6);
}
int main()
{
	invisible();
	srand(time(0));
	for (int i = 0; i < 13; i++) printf("*");
	printf("\n");
	printf("Flight Chess*\n");
	for (int i = 0; i < 13; i++) printf("*");
	printf("\n");
	printf("是否开启作弊模式?(0为否，1为是)：");
	scanf("%d", &cheat);
	printf("请选择玩家人数(2-4):");
	scanf("%d", &player_num);
	while (player_num < 2 || player_num>4) printf("请重新输入玩家人数："), scanf("%d", &player_num);
	for (int i = 0; i < player_num; i++) printf("请选择%d号玩家类型(0为电脑，1为玩家):", i), scanf("%d", &player_type[i]);
	init();
	Judge_num();
	Sleep(1000);
	Print();
	for (int i = 0; i < player_num; i++) printf("%d号玩家类型为%d(0为电脑，1为玩家)\n", i, player_type[i]);
	for (int i = 0; i < 13; i++) printf("*");
	printf("\n");
	system("pause");
	system("cls");
	while (gamestate == -1) {
		Sleep(1000);
		Print();
		Sleep(1000);
		int dice_num = roll_dice();
		printf("%d号玩家扔骰子扔到了%d\n", player, dice_num);
		Play(dice_num);
		Judge_num();
		Sleep(1000);
		Print();
		player = (player + 1) % player_num;
		gamestate = Judge();
		system("pause");
		system("cls");
	}
	printf("%d号玩家胜利！\n", gamestate);
	printf("游戏结束！\n");
	system("pause");
}

