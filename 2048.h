/*************************************************************************
	> File Name: 2048.h
	> Author: AnSwEr
	> Mail: 1045837697@qq.com
	> Created Time: 2015年07月10日 星期五 15时30分15秒
 ************************************************************************/

#ifndef _2048_H
#define _2048_H
int a[4][4] = {0};//4*4方格
int empty=0;//方格里的空格数量
int old_x=0,old_y=0;

void draw();
void play();
void init();
void draw_digit(int y,int x);
void cnt_value(int *new_y,int *new_x);
int game_over();
int cnt_one(int y,int x);
#endif



