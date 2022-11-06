#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>
int Enter_Game(void) //开始游戏 (施工中)
{
    //初始化
    user.HP = Setting.HP;
    user.x = (Setting.BUFFER_ROWS + Setting.MAP_ROWS) - 2;
    user.y = (Setting.MAP_COLS >> 1) - 1;
    srand(time(NULL));
    clock_t time, time1;
    int score;
    //重置地图
    {
        //申请内存
        MAP = Calloc_Graph(Setting.MAP_ROWS + Setting.BUFFER_ROWS, Setting.MAP_COLS + 1);
        //填充背景
        char *temp = Set_String(Setting.Background, Setting.MAP_COLS);
        for (int i = Setting.MAP_ROWS + Setting.BUFFER_ROWS - 1; i >= 0; i--)
        {
            strcpy(MAP[i], temp);
        }
        free(temp);
    }
    //开始
    time = clock();
    while (user.HP > 0)
    {
        time1 = clock();
        //刷新地图内容
        Refresh_Map();
        //玩家输入
        if (kbhit())
        {
            switch (getin())
            {
            //上
            case 1:
                user.x > Setting.BUFFER_ROWS ? user.x-- : NULL;
                break;
            //下
            case 2:
                user.x < Setting.BUFFER_ROWS + Setting.MAP_ROWS - 1 ? user.x++ : NULL;
                break;
            //左
            case 3:
                user.y > 0 ? user.y-- : NULL;
                break;
            //右
            case 4:
                user.y < Setting.MAP_COLS - 1 ? user.y++ : NULL;
                break;
            //退出
            case -1:
                return score;
                break;

            default:
                break;
            }
        }
        //输出地图
        // MAP[user.x][user.y] = Default_Sign_Player;
        Display_Map();
        //输出玩家(用光标移动函数)
        Set_Pos(user.y, user.x - Setting.BUFFER_ROWS);
        putchar(Default_Sign_Player);
        Set_Pos(0, Setting.MAP_ROWS);
        //碰撞判定
        user.HP -= Get_Collison(user.x, user.y);
        //输出状态栏
        printf("生命值:%d score:%d fps:%d rate:", user.HP, score = (clock() - time) / CLOCKS_PER_SEC, CLOCKS_PER_SEC / (clock() - time1));
        //......
        //等待间隔时间
        while (CLOCKS_PER_SEC / (clock() - time1) > Setting.RATE)
            ;
        printf("%d", CLOCKS_PER_SEC / (clock() - time1));
    }
    //结束
    //释放地图内存
    for (int i = Setting.MAP_ROWS + Setting.BUFFER_ROWS - 1; i >= 0; i--)
        free(MAP[i]);
    free(MAP);

    return score;
}

void Display_MainMenu(int pos) //显示主菜单 (通过测试)
{
    // system("cls");
    // char *temp = Set_String('\n', (Setting.MAP_ROWS) / (MAIN_OPTION + 3) - 1); //(已修复的BUG)静态变量，可以防止过于频繁的申请内存导致崩溃
    static char option[MAIN_OPTION][50] = {"开始游戏", "游戏设置"};
    Set_Menu(pos, option, MAIN_OPTION, "主菜单");
    //旧版
    //上分界线
    // printf("%s", temp);
    // puts(Setting.line);
    // printf("%s", temp);
    // //选项
    // for (int i = 0; i < MAIN_OPTION; i++)
    // {
    //     if (i == pos)
    //     {
    //         char s[50];
    //         sprintf(s, "*%s*", option[pos]);
    //         Push_String_Mid(s);
    //     }
    //     else
    //     {
    //         Push_String_Mid(option[i]);
    //     }
    //     printf("%s", temp);
    // }
    // //下分界线
    // puts(Setting.line);

    return;
}

void Display_Map(void) //显示地图 (有崩溃记录)
{
    system("cls"); //(已修复的BUG){取40并且列小于30时会出现崩溃情况,但是先前的cls并无此问题,为地图额外申请一列空间后解决}
    for (int i = Setting.BUFFER_ROWS, t = 1; t < Setting.MAP_ROWS; i++, t++)
    {
        puts(MAP[i]);
    }
    //防止最后一行因为put自带的换行而越界
    printf("%s", MAP[Setting.BUFFER_ROWS + Setting.MAP_ROWS - 1]);
    return;
}

void Refresh_Map(void) //刷新地图内容(包括缓冲区) (通过测试)
{
    //插入图形
    if (rand() % 10 > 4)
    {
        Graph *p;
        p = Find_Graph(1 + rand() % Setting.GRAPH_NUM);
        Insert_Graph(rand() % (Setting.BUFFER_ROWS >> 1), rand() % Setting.MAP_COLS, p);
    }
    //刷新
    for (int i = Setting.MAP_ROWS + Setting.BUFFER_ROWS - 1; i; i--)
    {
        strcpy(MAP[i], MAP[i - 1]);
    }
    char *temp = Set_String(Setting.Background, Setting.MAP_COLS);
    strcpy(MAP[0], temp);
    free(temp);
}

int Insert_Graph(int x, int y, Graph *p) //插入图形 (通过测试)
{
    if (p)
    {
        int cut = 0;
        for (int t1 = 0, len; t1 < p->rows && x < Setting.BUFFER_ROWS; t1++, x++)
        {
            len = strlen(p->graph[t1]);
            len + y <= Setting.MAP_COLS ? strncpy(MAP[x] + y, p->graph[t1], len) : (cut++, strncpy(MAP[x] + y, p->graph[t1], Setting.MAP_COLS - y));
        }
        return cut; //裁剪次数
    }
    return -1;
}

int Get_Collison(int x, int y) //碰撞判定
{
    if (MAP[x][y] && MAP[x][y] != Setting.Background)
    {
        // MAP[x][y]==Setting.Background;
        return Setting.damage;
    }
    return 0;
}