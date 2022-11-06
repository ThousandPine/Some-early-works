#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
int Initialize_Setting(void) //重置设置 (施工中)
{
    Setting.HP = Default_PLAYER_HP;                   //血量
    strcpy(Setting.name, Default_PLAYER_NAME);        //名称
    Setting.MAP_ROWS = Default_MAP_ROWS;              //地图 行
    Setting.MAP_COLS = Default_MAP_COLS;              //地图 列
    Setting.BUFFER_ROWS = Default_BUFFER_ROWS;        //缓冲区 行
    Setting.damage = Default_DAMAGE;                  //碰撞伤害
    Setting.RATE = Default_RATE;                      //难度
    Setting.Background = Default_Sign_Background;     //背景符号
    Setting.Obstacle = Default_Sign_Obstacle;         //障碍符号
    Setting.line = Set_String('-', Setting.MAP_COLS); //界面分界线
    Set_Window(Setting.MAP_ROWS, Setting.MAP_COLS);   //窗口尺寸
    // Setting.x = Default_PLAYER_POS_X;                 //坐标 x(改为游戏开始时计算)
    // Setting.y = Default_PLAYER_POS_Y;                 //坐标 y(改为游戏开始时计算)
    // Setting.GRAPH_NUM = Default_GRAPH_NUM;            //障碍数量(改为图像设置中读取)
    // Setting.name = Setting.name ? Setting.name : (char *)malloc(sizeof(char) * 51); //名称 申请内存(已停用)
    return 1; //用于兼容三目运算符
}

int Initialize_Graph(void) //重置图像 (通过测试)
{
    Setting.GRAPH_NUM = Default_GRAPH_NUM; //障碍数量
    //图像1
    Graph *p = (Graph *)malloc(sizeof(Graph));
    p->rows = 3, p->cols = 1;
    strcpy(p->graph[0], "**");
    strcpy(p->graph[1], "*");
    strcpy(p->graph[2], "*");
    Setting.head = Setting.tail = p;
    //图像2
    p = (Graph *)malloc(sizeof(Graph));
    p->rows = 3, p->cols = 3;
    strcpy(p->graph[0], "***");
    strcpy(p->graph[1], "***");
    strcpy(p->graph[2], " *");
    Setting.tail->next = p, Setting.tail = p;
    //图像3
    p = (Graph *)malloc(sizeof(Graph));
    p->rows = 3, p->cols = 3;
    strcpy(p->graph[0], " *");
    strcpy(p->graph[1], "***");
    strcpy(p->graph[2], " *");
    Setting.tail->next = p, Setting.tail = p;

    Setting.tail->next = NULL;
    return 1; //用于兼容三目运算符
}

void Enter_SettingMenu(void) //进入设置菜单 (施工中)
{
    //进入菜单
    for (int option = 0, pos = 0;;)
    {
        Display_SettingMenu(pos); //显示设置菜单
        option = getin();
        switch (option)
        {
        //返回上级菜单
        case -1:
            return;
        //上一个选项
        case 1:
            pos--;
            pos = pos < 0 ? Setting_OPTION - 1 : pos;
            break;
        //下一个选项
        case 2:
            pos++;
            pos = pos >= Setting_OPTION ? 0 : pos;
            break;
        //选中
        case 5:
            switch (pos)
            {
            //场景设置
            case 0:
                Enter_0_SettingMenu();
                break;
            //玩家设置
            case 1:
                Enter_1_SettingMenu();
                break;
            case 2:
                puts("这将会使所有设置恢复到默认状态\n确定要这样做吗?\n(回车确定 其他键返回)");
                if (getin() == 5)
                {
                    //初始化设置
                    Initialize_Setting();
                    //初始化图像
                    //......
                    puts("初始化完成");
                    getch();
                }
                break;
            //未定义
            default:
                puts("未定义2");
                break;
            }
            break;
        //未定义
        default:
            puts("未定义1");
            break;
        }
        // test
        // printf("option=%d\n", option);
    }
}

void Display_SettingMenu(int pos) //显示设置菜单 (通过测试)
{
    static char option[Setting_OPTION][50] = {"场景设置", "玩家设置", "恢复默认"};
    Set_Menu(pos, option, Setting_OPTION, "游戏设置");

    return;
}

void Enter_0_SettingMenu(void) //进入场景设置菜单 (施工中)
{
    //进入菜单
    for (int option = 0, pos = 0;;)
    {
        Display_0_SettingMenu(pos); //显示设置菜单
        option = getin();
        switch (option)
        {
        //返回上级菜单
        case -1:
            return;
        //上一个选项
        case 1:
            pos--;
            pos = pos < 0 ? Setting_0_OPTION - 1 : pos;
            break;
        //下一个选项
        case 2:
            pos++;
            pos = pos >= Setting_0_OPTION ? 0 : pos;
            break;
        //选中
        case 5:
            system("cls");
            switch (pos)
            {
            //地图尺寸
            case 0:
            {
                printf("当前大小:%d %d\n", Setting.MAP_ROWS, Setting.MAP_COLS);
                int rows, cols, fail;
                printf("输入行数:");
                rows = read();
                printf("输入列数:");
                cols = read();
                fail = Set_Window(rows, cols);
                if (!fail)
                {
                    Setting.MAP_ROWS = rows;
                    Setting.MAP_COLS = cols;
                    free(Setting.line);
                    Setting.line = Set_String('-', Setting.MAP_COLS);
                    puts("\n修改成功");
                }
                break;
            }
            //缓冲区长度
            case 1:
            {
                printf("当前长度:%d\n", Setting.BUFFER_ROWS);
                printf("输入长度:");
                int rows = read();
                if (rows > 0)
                {
                    Setting.BUFFER_ROWS = rows;
                    puts("\n修改成功");
                }
                else
                    puts("\n进不去,怎么想我都进不去吧");
                break;
            }
            //添加障碍
            case 2:
            {
                printf("当前序号%d\n\n", Setting.GRAPH_NUM + 1);
                Graph *p = Add_Graph();
                if (p)
                {
                    //添加到链表
                    if (!Setting.head)
                        Setting.head = Setting.tail = p;
                    else
                        Setting.tail = Setting.tail->next = p;
                    Setting.tail->next = NULL;
                    Setting.GRAPH_NUM++;
                    //写入文件
                    Write_GraphFile();
                    puts("添加成功");
                    Put_Graph(Find_Graph(Setting.GRAPH_NUM));
                }
                break;
            }
            //查看障碍
            case 3:
            {
                //循环输入序号查看{-N~-0:退出, =:删除(经过确认), 1~N:查看}
                int n;
                Graph *p;
                do
                {
                    system("cls");
                    printf("\n查看序号为1~%d的障碍(输入0退出)\n",Setting.GRAPH_NUM);
                    printf("输入序号:");
                    n = read();
                    if (n > 0)
                    {
                        p = Find_Graph(n);
                        printf("当前序号%d\n\n", n);
                        Put_Graph(p);
                        if (p)
                        {
                            puts("\n任意键继续, '='删除");
                            if (getin() == -1) //删除
                            {
                                puts("\n(回车确定) (其他键返回)");
                                if (getin() == 5)
                                    puts(Delete_Grapg(n) ? "删除成功" : "删除失败"), getch();
                                n = 1;
                            }
                        }
                        else
                            getch();
                    }
                } while (n > 0);
                //......
                Write_GraphFile();
                puts("\n退出成功");
                break;
            }
            //修改符号(已禁用)
            case 4:
                puts("该功能已被禁用");
                break;
                printf("当前障碍符号:'%c'\n当前背景符号:'%c'\n\n", Setting.Obstacle, Setting.Background);
                printf("输入障碍符号:");
                Setting.Obstacle = getchar();
                while (Setting.Obstacle == '\n')
                    Setting.Obstacle = getchar();
                printf("输入背景符号:");
                Setting.Background = getchar();
                while (Setting.Background == '\n')
                    Setting.Background = getchar();
                puts(Setting.Background == Setting.Obstacle ? "\n你开心就好" : "\n修改成功");
                break;
            //未定义
            default:
                puts("未定义2");
                break;
            }
            getch();
            break;
        //未定义
        default:
            puts("未定义1");
            break;
        }
        // test
        // printf("option=%d\n", option);
    }
}

void Display_0_SettingMenu(int pos) //显示场景设置菜单 (通过测试)
{
    static char option[Setting_0_OPTION][50] = {"地图尺寸", "缓冲区长度", "添加障碍", "查看障碍", "修改符号"};
    Set_Menu(pos, option, Setting_0_OPTION, "场景设置");

    return;
}

void Enter_1_SettingMenu(void) //进入玩家设置菜单 (通过测试)
{
    //进入菜单
    for (int option = 0, pos = 0;;)
    {
        Display_1_SettingMenu(pos); //显示设置菜单
        option = getin();
        switch (option)
        {
        //返回上级菜单
        case -1:
            return;
        //上一个选项
        case 1:
            pos--;
            pos = pos < 0 ? Setting_1_OPTION - 1 : pos;
            break;
        //下一个选项
        case 2:
            pos++;
            pos = pos >= Setting_1_OPTION ? 0 : pos;
            break;
        //选中
        case 5:
            system("cls");
            switch (pos)
            {
            //玩家名称
            case 0:
                printf("当前名称:%s\n", Setting.name);
                printf("输入名称:");
                gets_n(Setting.name, 50);
                puts("修改成功");
                break;
            //初始生命值
            case 1:
                printf("当前生命值:%d\n", Setting.HP);
                printf("修改后的生命值:");
                Setting.HP = read();
                puts(Setting.HP == 114514 ? "\n这么臭的生命值,真的还有活下去的必要吗" : "\n修改成功");
                break;
            //碰撞伤害
            case 2:
                printf("当前碰撞伤害:%d\n", Setting.damage);
                printf("输入碰撞伤害:");
                Setting.damage = read();
                puts(Setting.damage > 0 ? "\n修改成功" : "\n恭喜解锁成就 \"无尽模式\"");
                break;
            //刷新速率
            case 3:
                printf("当前速率:%d\n", Setting.RATE);
                printf("修改后的速率:");
                Setting.RATE = read();
                puts(Setting.RATE>=0?"\n修改成功":"\nthe world!");
                break;
            //未定义
            default:
                puts("未定义2");
                break;
            }
            getch();
            break;
        //未定义
        default:
            puts("未定义1");
            break;
        }
        // test
        // printf("option=%d\n", option);
    }
}

void Display_1_SettingMenu(int pos) //显示玩家设置菜单 (通过测试)
{
    static char option[Setting_1_OPTION][50] = {"玩家名称", "初始生命值", "碰撞伤害", "刷新速率"};
    Set_Menu(pos, option, Setting_1_OPTION, "玩家设置");

    return;
}