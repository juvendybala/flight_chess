#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<windows.h>
#include<conio.h>
char a[6][40]={'\0'};//��Ϊ����
int Plane[4][4][3] = {0 };
//��һ��4*4*3�������¼���ӵ�λ��,��һά��ʾ��Ӫ���ڶ�ά��ʾ�ڼ������ӣ�����άǰ����Ԫ�ر�ʾ��a�����е�����
//����ά��һ��Ԫ�ؼ�¼״̬��0��ʾ�ڳ��1��ʾ��·�ϣ�2��ʾ�ѵ����յ�
int player_type[4] = { 0,1,0,0 };//��ҵ����ͣ�0Ϊ���ԣ�1Ϊ����
char b[4] = { 'G','Y','R','B'};//���ں��������̸�ֵ����playerͳһ
int player = 0;//��Ҵ�0�ſ�ʼ����Ϊȫ�ֱ����ᴩ���к���
int gamestate = -1;//-1Ϊ����״̬����Ӧ���ֱ�ʾ��Ӧ���ʤ
int player_num = 0;//��Ҹ�������Ҫ�û�����
int cheat = 0;//�Ƿ�������ģʽ
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
	printf("�Ƿ�������ģʽ?(0Ϊ��1Ϊ��)��");
	scanf("%d", &cheat);
	printf("��ѡ���������(2-4):");
	scanf("%d", &player_num);
	while (player_num < 2 || player_num>4) printf("�������������������"), scanf("%d", &player_num);
	for (int i = 0; i < player_num; i++) printf("��ѡ��%d���������(0Ϊ���ԣ�1Ϊ���):", i), scanf("%d", &player_type[i]);
	init();
	Judge_num();
	Sleep(1000);
	Print();
	for (int i = 0; i < player_num; i++) printf("%d���������Ϊ%d(0Ϊ���ԣ�1Ϊ���)\n", i, player_type[i]);
	for (int i = 0; i < 13; i++) printf("*");
	printf("\n");
	system("pause");
	system("cls");
	while (gamestate == -1) {
		Sleep(1000);
		Print();
		Sleep(1000);
		int dice_num = roll_dice();
		printf("%d������������ӵ���%d\n", player, dice_num);
		Play(dice_num);
		Judge_num();
		Sleep(1000);
		Print();
		player = (player + 1) % player_num;
		gamestate = Judge();
		system("pause");
		system("cls");
	}
	printf("%d�����ʤ����\n", gamestate);
	printf("��Ϸ������\n");
	system("pause");
}

