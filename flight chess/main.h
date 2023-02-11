#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<Windows.h>
#include<conio.h>
extern char a[6][40];
extern int Plane[4][4][3];
extern int player_type[4];
extern char b[4];
extern int player;
extern int gamestate ;
extern int player_num;
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
