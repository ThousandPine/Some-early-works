#include "main.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
int Read_SettingFile(void) //读入文件的设置 {0:失败 1:成功} (通过测试)
{
    FILE *fp = fopen(FILE_Setting, "rb");
    if (fp)
    {
        //读入文件
        fseek(fp, 0, SEEK_SET);
        fread(&Setting, sizeof(Setting), 1, fp);
        fclose(fp);
        //单独特殊处理
        Setting.line = Set_String('-', Setting.MAP_COLS); //界面分界线
        Set_Window(Setting.MAP_ROWS, Setting.MAP_COLS);   //窗口尺寸
        return 1;
    }
    return 0;
}

void Write_SettingFile(void) //将设置写入文件 (通过测试)
{
    FILE *fp = fopen(FILE_Setting, "wb+");
    if (fp)
    {
        fseek(fp, 0, SEEK_SET);
        fwrite(&Setting, sizeof(Setting), 1, fp);
        fclose(fp);
    }
    return;
}

int Read_GraphFile(void) //读入文件的图像 {0:失败 1:成功} (通过测试)
{
    FILE *fp = fopen(FILE_Graph, "rb");
    if (fp)
    {
        //读入图像数量
        fseek(fp, 0, SEEK_SET);
        fread(&(Setting.GRAPH_NUM), sizeof(int), 1, fp);
        Setting.head=NULL;
        //读入图像
        Graph *p;
        for (int i = Setting.GRAPH_NUM, t = 0; i > 0; i--, t++)
        {
            //读入结构体
            p = (Graph *)malloc(sizeof(Graph));
            fseek(fp, sizeof(int) + sizeof(Graph) * t, SEEK_SET);
            fread(p, sizeof(Graph), 1, fp);
            //加入链表
            if (!t) //首位
                Setting.head = Setting.tail = p;
            else
                Setting.tail = Setting.tail->next = p;
            Setting.tail->next = NULL;
        }
        return 1;
    }
    return 0;
}

void Write_GraphFile(void) //将图像写入文件 (通过测试)
{
    FILE *fp = fopen(FILE_Graph, "wb+");
    if (fp)
    {
        //写入图像数量
        fseek(fp, 0, SEEK_SET);
        fwrite(&(Setting.GRAPH_NUM), sizeof(int), 1, fp); //(已修复的BUG){取10写入后会出现读取值异常,改成二进制打开后解决}
        //写入图像
        Graph *p = Setting.head;
        for (int t = 0; p; p = p->next, t++)
        {
            fseek(fp, sizeof(int) + sizeof(Graph) * t, SEEK_SET);
            fwrite(p, sizeof(Graph), 1, fp);
        }
        fclose(fp);
    }
    return;
}