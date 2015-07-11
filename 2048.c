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

/*绘制数字*/
void draw_digit(int y,int x)
{
    int i,m,k,j;
    char c[4]={'0','0','0','0'};

    i = a[y][x];
    m = 0;
    do{
        j = i % 10;
        c[m++] = j + '0';
        i = i / 10; 
    }while(i > 0);
    m = 0;
    k = (x+1)*5-1;
    while(c[m] != '0')
    {
        move(2*y+1,k);
        addch(c[m++]);
        k--;
    }
}

/*绘制方格*/
void draw()
{
    int n,m,x,y;
    clear();
    for(n = 0;n < 9;n += 2) 
    for(m = 0;m < 21;m++)
    {
        move(n,m);
        addch('-');
        refresh();
    }
    for(m = 0;m < 22;m +=5)
    for(n = 1;n < 8;n++)
    {
        move(n,m);
        addch('|');
        refresh();
    }
    for(y = 0;y < 4;y++)
    for(x = 0;x < 4;x++)
    {
        draw_digit(y,x);
    }

}
/*初始化屏幕，在方格中生成一个位置放入数字2*/
void init()
{
    int x,y;

    initscr();//初始化，进入ncurses模式
    cbreak();//除了delete和ctrl，接受其他所有字符输入
    noecho();//关闭回显模式
    curs_set(0);//光标设置为不可见

    empty = 15;
    srand((unsigned)time(NULL));
    x = rand()%4;
    y = rand()%4;
    a[y][x] = 2;
    draw();
}

/*用wsad表示上下左右*/
void play()
{
    int x, y, i, new_x, new_y, tmp;
    int old_empty, move;
    char ch;

    while(1) 
    {
        move = 0;
        old_empty = empty;
        //draw();
        ch = getch();
        switch(ch) 
        {
            case 'A':
            case 'a':
            //从左向右消去相同方块
            for(y = 0; y < 4; y++)
            for(x = 0; x < 4; ) 
            {
                if(a[y][x] == 0) 
                {
                    x++;
                    continue;
                } 
                else 
                {
                    for(i = x + 1; i < 4; i++) 
                    {
                        if(a[y][i] == 0) 
                        {
                            continue;
                        }
                        else 
                        {
                            if(a[y][x] == a[y][i]) 
                            {
                                a[y][x] += a[y][i];
                                a[y][i] = 0;
                                x = i + 1;
                                empty++;
                                break;
                            }
                            else 
                            {
                                x = i;
                                break;
                            }
                        }
                    }
                    x = i;
                }
            }
            //向左移动方块
            for(y = 0; y < 4; y++)
            for(x = 0; x < 4; x++) 
            {
                if(a[y][x] == 0) 
                {
                    continue;
                } 
                else 
                {
                    for(i = x; (i > 0) && (a[y][i-1] == 0); i--) 
                    {
                        a[y][i-1] = a[y][i];
                        a[y][i] = 0;
                        move = 1;
                    }
                }
            }
break;
            case 'D':
                case 'd':
                    //从右向左消去相同方块
                    for(y = 0; y < 4; y++)
                    for(x = 3; x >= 0; ) 
                    {
                        if(a[y][x] == 0) 
                        {
                            x--;
                            continue;
                        } else 
                        {
                            for(i = x - 1; i >= 0; i--) 
                            {
                                if(a[y][i] == 0) 
                                {
                                    continue;
                                } 
                                else if(a[y][x] == a[y][i]) 
                                {
                                    a[y][x] += a[y][i];
                                    a[y][i] = 0;
                                    x = i - 1;
                                    empty++;
                                    break;
                                } 
                                else 
                                {
                                    x = i;
                                    break;
                                }
                            }
                            x = i;
                        }
                    }
                    //向右移动方块
                    for(y = 0; y < 4; y++)
                    for(x = 3; x >= 0; x--) 
                    {
                        if(a[y][x] == 0) 
                        {
                            continue;
                        } 
                        else 
                        {
                            for(i = x; (i < 3) && (a[y][i+1] == 0); i++) 
                            {
                                a[y][i+1] = a[y][i];
                                a[y][i] = 0;
                                move = 1;
                            }
                        }
                    }
                    break;
            case 'W':
                case 'w':
                    //从上向下消去相同方块
                    for(x = 0; x < 4; x++)
                    for(y = 0; y < 4; ) 
                    {
                        if(a[y][x] == 0) 
                        {
                            y++;
                            continue;
                        } 
                        else 
                        {
                            for(i = y + 1; i < 4; i++) 
                            {
                                if(a[i][x] == 0) 
                                {
                                    continue;
                                } 
                                else if(a[y][x] == a[i][x]) 
                                {
                                    a[y][x] += a[i][x];
                                    a[i][x] = 0;
                                    y = i + 1;
                                    empty++;
                                    break;
                                } 
                                else 
                                {
                                    y = i;
                                    break;
                                }
                            }
                            y = i;
                        }
                    }
                    //向上移动方块
                    for(x = 0; x < 4; x++)
                    for(y = 0; y < 4; y++) 
                    {
                        if(a[y][x] == 0) 
                        {
                            continue;
                        } 
                        else 
                        {
                            for(i = y; (i > 0) && (a[i-1][x] == 0); i--) 
                            {
                                a[i-1][x] = a[i][x];
                                a[i][x] = 0;
                                move = 1;
                            }
                        }
                    }
                    break;
            case 'S':
                case 's':
                    //从下向上消去相同方块
                    for(x = 0; x < 4; x++)
                    for(y = 3; y >= 0; ) 
                    {
                        if(a[y][x] == 0) 
                        {
                            y--;
                            continue;
                        } 
                        else 
                        {
                            for(i = y - 1; i >= 0; i--) 
                            {
                                if(a[i][x] == 0) 
                                {
                                    continue;
                                } 
                                else if(a[y][x] == a[i][x]) 
                                {
                                    a[y][x] += a[i][x];
                                    a[i][x] = 0;
                                    y = i -1;
                                    empty++;
                                    break;
                                } 
                                else 
                                {
                                    y = i;
                                    break;
                                }
                            }
                            y = i;
                        }
                    }
                    //向下移动方块
                    for(x = 0; x < 4; x++)
                    for(y = 3; y >= 0; y--) 
                    {
                        if(a[y][x] == 0) 
                        {
                            continue;
                        } 
                        else 
                        {
                            for(i = y; (i < 3) && (a[i+1][x] == 0); i++) 
                            {
                                a[i+1][x] = a[i][x];
                                a[i][x] = 0;
                                move = 1;
                            }
                        }
                    }
                    break;
            case 'Q':
                case 'q':
                    game_over();
                    break;
            default:
                continue;
            break;
        }

        if(empty <= 0)
        game_over();
        draw();
        //生成新方块
        if((empty != old_empty) || (move == 1)) 
        {//修复了不移动或消除方块也生成新方块的bug
         do {
             new_x = rand() % 4;
             new_y = rand() % 4;
         }while(a[new_y][new_x] != 0);

         cnt_value(&new_y, &new_x);

         do {
             tmp = rand() % 4;
         }while(tmp == 0 || tmp == 2);
         a[new_y][new_x] = tmp + 1;
         empty--;

         draw_digit(new_y, new_x);
        }
    }
}

/*生成新数字的位置*/
int cnt_one(int y,int x)
{
    int value = 1;

    if(y - 1 > 0)  
    a[y-1][x] ? 0 : value++;
    if(y + 1 < 4)
    a[y+1][x] ? 0 : value++;
    if(x - 1 >= 0)
    a[y][x-1] ? 0 : value++;
    if(x + 1 < 4)
    a[y][x+1] ? 0 : value++;
    if(y - 1 >= 0 && x - 1 >= 0)
    a[y-1][x-1] ? 0 : value++;
    if(y - 1 >= 0 && x + 1 < 4)
    a[y-1][x+1] ? 0 : value++;
    if(y + 1 < 4 && x - 1 >= 0)
    a[y+1][x-1] ? 0 : value++;
    if(y + 1 < 4 && x + 1 < 4)
    a[y+1][x+1] ? 0 : value++;

    return value;
}
void cnt_value(int *new_y,int *new_x)
{
    int max_x, max_y, x, y, value;
    int max = 0;

    max = cnt_one(*new_y, *new_x);
    for(y = 0; y < 4; y++)
    for(x = 0; x < 4; x++) 
    {
        if(!a[y][x]) 
        {
            value = cnt_one(y, x);
            if(value > max && old_y != y && old_x != x) 
            { 
                //避免在同一位置反复出现新方块
                *new_y = y;
                *new_x = x;
                old_x = x;
                old_y = y;
                break;
            }
        }
    }
}

/*游戏结束*/
int game_over()
{
    sleep(1);
    endwin();
    exit(0);
}

int main()
{
    init();
    play();
    endwin();//推出ncurses模式

    return 0;
}
