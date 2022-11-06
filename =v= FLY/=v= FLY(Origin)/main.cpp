#include "main.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

char **MAP = NULL;   //地图
GameSetting Setting; //设置
Player user;         //玩家

int main() //(施工中)
{
    //初始化内容
    Read_SettingFile() ? NULL : Initialize_Setting();
    Read_GraphFile() ? NULL : Initialize_Graph();
    //进入程序
    for (int option = 0, pos = 0;;)
    {
        Display_MainMenu(pos); //显示主菜单
        option = getin();
        switch (option)
        {
        //上一个选项
        case 1:
            pos--;
            pos = pos < 0 ? MAIN_OPTION - 1 : pos;
            break;
        //下一个选项
        case 2:
            pos++;
            pos = pos >= MAIN_OPTION ? 0 : pos;
            break;
        //选中
        case 5:
            switch (pos)
            {
            //开始游戏
            case 0:
            {
                int score = Enter_Game();
                static char option[3][50]={"寄!"};
                sprintf(option[1],"\"%s\"",Setting.name);
                sprintf(option[2],"分数:%d",score);
                Set_Menu(-1,option,3,"游戏结束");
                getch();
                break;
            }
            //游戏设置
            case 1:
                Enter_SettingMenu();
                Write_SettingFile();
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

    return 0;
}