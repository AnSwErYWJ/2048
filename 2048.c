/*************************************************************************
	> File Name: 2048.c
	> Author: AnSwEr
	> Mail: 1045837697@qq.com
	> Created Time: 2015年07月10日 星期五 15时36分19秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<curses.h>
#include<sys/time.h>
#include<signal.h>
#include"2048.h"

int main()
{
    init();
    play();
    endwin();

    return 0;
}
