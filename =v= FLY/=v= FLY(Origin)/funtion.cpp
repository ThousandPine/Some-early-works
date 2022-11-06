#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>

int getin(void) //读取输入 (通过测试)
{
    char c = getch();
    int n = 0;
    int k = 0; //方向键判定
    c = c == -32 ? (k = 1, getch()) : c;
    switch (c)
    {
    //退出 -1
    case '=':
        n = -1;
        break;
    //上 1
    case 'H':
        if (!k) //非方向键
        {
            n = 0;
            break;
        }
    case 'W':
    case 'w':
        n = 1;
        break;
    //下 2
    case 'P':
        if (!k) //非方向键
        {
            n = 0;
            break;
        }
    case 'S':
    case 's':
        n = 2;
        break;
    //左 3
    case 'K':
        if (!k) //非方向键
        {
            n = 0;
            break;
        }
    case 'A':
    case 'a':
        n = 3;
        break;
    //右 4
    case 'M':
        if (!k) //非方向键
        {
            n = 0;
            break;
        }
    case 'D':
    case 'd':
        n = 4;
        break;
    //选中 5
    case 13:
        n = 5;
        break;
    //未定义 0
    default:
        n = 0;
        break;
    }

    return n;
}

int read(void) //读取数字 (通过测试)
{
    char c = getchar(), sign;
    int n = 0;
    while (c > '9' || c < '0')
        sign = c, c = getchar();
    while (c <= '9' && c >= '0')
        n = (n << 1) + (n << 3) + (c ^ '0'), c = getchar();
    while (c != '\n')
        c = getchar();
    return sign == '-' ? -n : n;
}

void gets_n(char *s, int n) //读取字符串 (通过设置)
{
    int t = 0;
    char c = getchar();
    while (c != '\n' && t < n)
    {
        s[t++] = c;
        c = getchar();
    }
    s[t] = '\0';
    while (c != '\n')
        c = getchar();

    return;
}

char **Calloc_Graph(int x, int y) //创建二维数组(char) (通过测试)
{
    char **s;
    s = (char **)calloc(x, sizeof(char *));
    for (int i = 0; i < x; i++)
        s[i] = (char *)calloc(y, sizeof(char));

    return s;
}

void Put_String_Mid(char *s) //将字符串居中输出 (通过测试)
{
    // 旧版
    // for (int i = (Setting.MAP_COLS - strlen(s)) >> 1; i; i--)
    //     putchar(' ');
    // puts(s);
    //新版
    // char *space = Set_String(' ', Setting.MAP_COLS - strlen(s) >> 1);
    // printf("%s%s\n", space, s);
    // free(space);
    //更新版
    char Mid[10];
    sprintf(Mid, "%%%ds\n", Setting.MAP_COLS + strlen(s) >> 1);
    printf(Mid, s);

    return;
}

void Put_Graph(Graph *p) //输出图像 (通过测试)
{
    // system("cls");
    if (p)
    {
        for (int i = 0, t = p->rows; t; t--, i++)
        {
            puts(p->graph[i]);
        }
    }
    else
        puts("图像不存在");
    // getch();
    return;
}

int Set_Window(int rows, int cols) //修改控制台窗体大小 {-1:未成功, 0:成功} (有崩溃记录)
{
    char *temp = (char *)malloc(sizeof(char) * 50);             //自动恢复的bug点（可能是受当时Set_String的bug影响）
    sprintf(temp, "mode con cols=%d lines=%d", cols, rows + 1); //根据地图大小修改窗口(要留一行给状态栏)
    int result = system(temp);
    free(temp);

    return result;
}

char *Set_String(char sign, int len) //生成指定长度的重复字符串 (有崩溃记录)
{
    char *s = (char *)calloc(len + 1, sizeof(char));    //(已修复的BUG)额外加一位，防止在某下长度下(比如40)会在free(temp)时崩溃
    char *temp = (char *)calloc(len * 2, sizeof(char)); //(已修复的BUG)采用快速幂，需要申请两倍长度防止溢出
    sprintf(temp, "%c", sign);
    for (int i = len; i; i >>= 1)
    {
        if (i & 1)
        {
            sprintf(s, "%s%s", s, temp);
        }
        sprintf(temp, "%s%s", temp, temp);
    }
    free(temp);

    return s;
}

void Set_Menu(int pos, char option[][50], int Option_NUM, const char *title) //生成菜单 (通过测试)
{
    static char *space = NULL; //间隔
    int len = (Setting.MAP_ROWS) / (Option_NUM + 3) - 1;
    space = (space && len == strlen(space)) ? space : Set_String('\n', len); //防止频繁申请内存导致崩溃
    system("cls");
    //上分界线
    printf("%s", space);
    puts(title);
    puts(Setting.line);
    printf("%s", space);
    //选项
    for (int i = 0; i < Option_NUM; i++)
    {
        if (i == pos)
        {
            char s[50];
            sprintf(s, "*%s*", option[pos]);
            Put_String_Mid(s);
        }
        else
        {
            Put_String_Mid(option[i]);
        }
        printf("%s", space);
    }
    //下分界线
    puts(Setting.line);

    return;
}

Graph *Add_Graph(void) //添加图形 {创建成功返回地址, 否则返回NULL} (通过测试)
{
    Graph *p = (Graph *)malloc(sizeof(Graph));
    puts("输入图像尺寸");
    printf("行:");
    p->rows = read();
    printf("列:");
    p->cols = read();
    //输入不在范围内
    if (p->rows < 1 || p->cols < 1 || p->rows > Graph_MAX_ROWS || p->cols > Graph_MAX_COLS)
    {
        puts("\n你在想什么...");
        free(p);
        return NULL;
    }
    //创建图像
    printf("     ");
    char c = '1';
    for (int t = p->cols; t; t--) //提示栏
    {
        putchar(c);
        c = c == '9' ? 'x' : c + 1;
        c = c == 'x' + 1 ? '1' : c;
    }
    puts("\n");
    for (int i = 0; i < p->rows; i++) //输入图像
    {
        printf("%2d:  ", i + 1);
        gets_n(p->graph[i], p->cols);
    }
    return p;
}

Graph *Find_Graph(int n) //定位指定1~N序号的图像 {成功返回地址, 失败返回NULL} (通过测试)
{
    Graph *p = Setting.head;
    while (p && --n)
        p = p->next;
    return p;
}

int Delete_Grapg(int n) //删除指定1~N序号的图像 {0:失败, 1:成功}
{
    Graph *p1, *pre;
    p1 = Find_Graph(n);
    if (p1) // p1存在
    {
        if (n == 1) //删除头
            Setting.head = p1->next;
        else
        {
            pre = Find_Graph(n - 1);
            pre->next = p1->next;
            Setting.tail = (n == Setting.GRAPH_NUM) ? pre : Setting.tail;
        }
        free(p1);
        Setting.GRAPH_NUM--;
        return 1;
    }
    return 0;
}

void Set_Pos(short x, short y) //控制控制台光标位置 (此函数来源于https://www.pianshen.com/article/5107919485/)
{

    COORD point = {x, y};                             //光标要设置的位置x,y
    HANDLE HOutput = GetStdHandle(STD_OUTPUT_HANDLE); //使用GetStdHandle(STD_OUTPUT_HANDLE)来获取标准输出的句柄
    SetConsoleCursorPosition(HOutput, point);         //设置光标位置
}