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
	printf("����100��0֮�������\n") ;
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
		if(open1==0 && open2==1 && in>=0 && in<=1000) level=2;//��ֹ����level2������level1���������level����100���ڵ�����ͬʱ�޷��ص�level2��level1���¿��ڸ�level
		
		switch (level)
		{
		
		case-2:
			printf("\n������ô�ҵ��������ģ���\n\n");getch();
			printf("1.�ӽ�  2.�۲�����\n(����������ѡ��)\n");fflush(stdin);scanf("%d",&choose);
				if (choose==1)
				{
					printf("�ȵȣ��㲻Ҫ��������\n\n") ;getch();printf("1.ONE PUNCH!!!  2.ͣ��\n") ;fflush(stdin);scanf("%d",&choose);
					if(choose==1){printf("\nawsl\n");getch();end=3;in=answer;getch();break;}                                                        //end3
					else if(choose==2){printf("\n""��ԥ�ͻ�ܱ�!""\n\n");getch();printf("�㱻��ɱ��\n");end=4;in=answer;getch();break;}             //end4
					else{printf("\n��Ȼ��ʱ����������\n\n");getch();printf("�㱻��ɱ��\n");end=4;in=answer;getch();break;}                        //end4
				}
				else if(choose==2)
				{
					printf("��������ʲô?\n\n");getch();printf("%d",answer);getch();printf("\nԭ���𰸵�������\n");getch();printf("�������ȥ\n���Ͼ��ܴ������ӳ�ȥ��\n\n");fflush(stdin);scanf("%d",&choose);
					if(choose==answer){printf("\n��Ү��\n");getch();end=1;in=answer;getch();break;}                                                 //end1
					else{printf("���ڸ���ħ��\n");getch();end=2;in=answer;break;}                                                                   //end2
				}
				else {printf("\n�����������\n\n");getch();printf("�����Ʋð�");end=5;in=answer;getch();break;}                                     //end5
			
		
		case -1:
			printf("�벻Ҫ�����Լ��ĳ���\n\n");
			fflush(stdin);
			scanf("%d",&in);
		break;
		
		case 1:
			//answer=rand()%100;
			if (in!=answer && open1==1)
				{
				if (in>answer){
						big=in;
						printf("����%d,С��%d\n\n",small,big) ;
						fflush(stdin);
						scanf("%d",&in);
					}else{
						small=in;
						printf("����%d,С��%d\n\n",small,big) ;
						fflush(stdin);
						scanf("%d",&in);
						}
				}
		break;
		
		case 2:
			for(;level_2_trigger==0 && open2==1;level_2_trigger++){answer=rand()%1000;printf("\n���������ҵ�!\nlevel 2!\n����1000��0֮�������\n\n");}
			if (in!=answer && open2==1)
				{
					if (in>answer){
						big2=in;
						printf("����%d,С��%d\n\n",small2,big2) ;
						fflush(stdin);
						scanf("%d",&in);
					}else{
						small2=in;
						printf("����%d,С��%d\n\n",small2,big2) ;
						fflush(stdin);
						scanf("%d",&in);
						}
				}
		break;
		
		case 3:
			while(in>1000 && open3==1)
			{
				printf("ǰ��������Ժ�����̽���ɣ����ɷ��ԣ�\n\n");level_3_trigger++;fflush(stdin);scanf("%d",&in);
			}
			while(level_3_trigger>=3 && in<=1000 && open3==1 && level_3_trap<=2)
			{
				printf("����������Ժ�����̽���ɣ�=v=��\n\n");level_3_trap++;fflush(stdin);scanf("%d",&in);
			}
			if (level_3_trigger>=3 && level_3_trap>=2 && open3==1){level=666;open1=0;open2=0;open3=0;open_1=0;}
		break;
		
		case 666:
			for(;level_666_trigger==0;level_666_trigger++){answer=rand();printf("�����ĺ���è��������\n");getch();printf("Ҫ��Ȼ���ٸ������·\n");getch();printf("\nlevel 666!\n����?��?֮�������\n\n");getch();printf("����\n");getch();printf("�������ҰѴ�Ū����\n");getch();printf("����û��ϵ���һ�������͵�\n\n");getch();printf("�õõ� ��  �õ� �õõõ�\n��BGM������֮��\n\n");getch();}
			if (in!=answer && in>=0)
				{
					if (in>answer){
						big666=in;
						printf("����%d,С��%d\n\n",small666,big666) ;
						fflush(stdin);
						scanf("%d",&in);
					}else{
						small666=in;
						printf("����%d,С��%d\n\n",small666,big666) ;
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
		case 1:while(in==answer)printf(" ��Ү ");break;
		case 2:while(in==answer)printf(" ������ ");break;
		case 3:while(in==answer)printf(" QAQ ");break;
		case 4:while(in==answer)printf(" 0v0 ");break;
		case 5:while(in==answer)printf(" =v= ");break;
	
	}
	//while(in==answer && end==0)printf(" =v= ");
	//while(in==answer && end==1)printf(" ��Ү ");
	//while(in==answer && end==2)printf(" ������ ");
	//while(in==answer && end==3)printf(" QAQ ");
	//while(in==answer && end==4)printf(" 0v0 ");
	//while(in==answer && end==5)printf(" =v= ");
	
	
	}
}

	
	
	
	
	

