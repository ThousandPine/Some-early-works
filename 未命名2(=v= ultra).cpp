#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

int main()
{	int in=0,big=100,small=0,level=0,in2=0,big2=1000,small2=0,big666=2147483647UL,small666=-2147483648UL;
	int open1=1,open2=1,open_1=1,open3=1;
	int level_2_trigger=0,level_3_trigger=0,level_666_trigger=0;
	int level_3_trap=0;
	int choose=0,end=0;
	
	srand(time(0));
	int answer=rand()%100;
	printf("输入100到0之间的数字\n") ;
	scanf("%d",&in);
	if (in>=0 && in<=100 && open1==1) level=1;
	if (in>100 && in<=1000 && open2==1) level=2;
	if (in>1000) level=3;
	if (in<0) level=-1;
	
	
	while (in!=answer)
	{
		if (in>=0 && in<=100 && open1==1) level=1;
		if (in>100 && in<=1000 && open2==1) {level=2;open1=0;}
		if (in>1000 && open3==1) level=3;
		if (in<0 && open_1==1) level=-1;
		if(open1==0 && open2==1 && in>=0 && in<=1000) level=2;//防止触发level2（锁定level1）后从其他level输入100以内的数会同时无法回到level2和level1导致卡在该level
		
		switch (level)
		{
		
		case-2:
			printf("\n你是怎么找到这里来的？！\n\n");getch();
			printf("1.接近  2.观察四周\n(输入数字以选择)\n");fflush(stdin);scanf("%d",&choose);
				if (choose==1)
				{
					printf("等等！你不要过来啊！\n\n") ;getch();printf("1.ONE PUNCH!!!  2.停下\n") ;fflush(stdin);scanf("%d",&choose);
					if(choose==1){printf("\nawsl\n");getch();end=3;in=answer;getch();break;}                                                        //end3
					else if(choose==2){printf("\n""犹豫就会败北!""\n\n");getch();printf("你被反杀了\n");end=4;in=answer;getch();break;}             //end4
					else{printf("\n居然这时候还想着作死\n\n");getch();printf("你被反杀了\n");end=4;in=answer;getch();break;}                        //end4
				}
				else if(choose==2)
				{
					printf("诶，这是什么?\n\n");getch();printf("%d",answer);getch();printf("\n原来答案掉在这了\n");getch();printf("快输入进去\n马上就能从这里逃出去了\n\n");fflush(stdin);scanf("%d",&choose);
					if(choose==answer){printf("\n好耶！\n");getch();end=1;in=answer;getch();break;}                                                 //end1
					else{printf("李在赣神魔？\n");getch();end=2;in=answer;break;}                                                                   //end2
				}
				else {printf("\n你这是在玩火\n\n");getch();printf("接受制裁吧");end=5;in=answer;getch();break;}                                     //end5
			
		
		case -1:
			printf("请不要输入自己的长度\n\n");
			fflush(stdin);
			scanf("%d",&in);
		break;
		
		case 1:
			//answer=rand()%100;
			if (in!=answer && open1==1)
				{
				if (in>answer){
						big=in;
						printf("大于%d,小于%d\n\n",small,big) ;
						fflush(stdin);
						scanf("%d",&in);
					}else{
						small=in;
						printf("大于%d,小于%d\n\n",small,big) ;
						fflush(stdin);
						scanf("%d",&in);
						}
				}
		break;
		
		case 2:
			for(;level_2_trigger==0 && open2==1;level_2_trigger++){answer=rand()%1000;printf("\n这是你自找的!\nlevel 2!\n输入1000到0之间的数字\n\n");}
			if (in!=answer && open2==1)
				{
					if (in>answer){
						big2=in;
						printf("大于%d,小于%d\n\n",small2,big2) ;
						fflush(stdin);
						scanf("%d",&in);
					}else{
						small2=in;
						printf("大于%d,小于%d\n\n",small2,big2) ;
						fflush(stdin);
						scanf("%d",&in);
						}
				}
		break;
		
		case 3:
			while(in>1000 && open3==1)
			{
				printf("前面的区域以后再来探索吧（派蒙发言）\n\n");level_3_trigger++;fflush(stdin);scanf("%d",&in);
			}
			while(level_3_trigger>=3 && in<=1000 && open3==1 && level_3_trap<=2)
			{
				printf("后面的区域以后再来探索吧（=v=）\n\n");level_3_trap++;fflush(stdin);scanf("%d",&in);
			}
			if (level_3_trigger>=3 && level_3_trap>=2 && open3==1){level=666;open1=0;open2=0;open3=0;open_1=0;}
		break;
		
		case 666:
			for(;level_666_trigger==0;level_666_trigger++){answer=rand();printf("好奇心害死猫，不是吗？\n");getch();printf("要不然我再给你个出路\n");getch();printf("\nlevel 666!\n输入?到?之间的数字\n\n");getch();printf("啊这\n");getch();printf("看来是我把答案弄丢了\n");getch();printf("不过没关系，我会替你加油的\n\n");getch();printf("得得得 得  得得 得得得得\n【BGM】狂妄之人\n\n");getch();}
			if (in!=answer && in>=0)
				{
					if (in>answer){
						big666=in;
						printf("大于%d,小于%d\n\n",small666,big666) ;
						fflush(stdin);
						scanf("%d",&in);
					}else{
						small666=in;
						printf("大于%d,小于%d\n\n",small666,big666) ;
						fflush(stdin);
						scanf("%d",&in);
						}
				}
			if (in<0){level=-2;}
		break;
		}
			
		
	switch(end)
	{
		case 0:while(in==answer)printf(" =v= ");break;
		case 1:while(in==answer)printf(" 好耶 ");break;
		case 2:while(in==answer)printf(" ？？？ ");break;
		case 3:while(in==answer)printf(" QAQ ");break;
		case 4:while(in==answer)printf(" 0v0 ");break;
		case 5:while(in==answer)printf(" =v= ");break;
	
	}
	//while(in==answer && end==0)printf(" =v= ");
	//while(in==answer && end==1)printf(" 好耶 ");
	//while(in==answer && end==2)printf(" ？？？ ");
	//while(in==answer && end==3)printf(" QAQ ");
	//while(in==answer && end==4)printf(" 0v0 ");
	//while(in==answer && end==5)printf(" =v= ");
	
	
	}
}

	
	
	
	
	

