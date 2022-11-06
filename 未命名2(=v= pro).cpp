#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{	int in=0,big=100,small=0,level=0,in2=0,big2=1000,small2=0;
	srand(time(0));
	rand();
	int answer=rand()%100;
	printf("输入100到0之间的数字\n") ;
	scanf("%d",&in);
	if (in>=0 && in<=100) level=1;
	if (in>100 && in<=1000) level=2;
	if (in>1000) level=3;
	if (in<0) level=-1;
	
	
	while (in!=answer){
	
		
		if (level==-1) {
			printf("请不要输入自己的长度\n");
			fflush(stdin);
			scanf("%d",&in);
			if (in>=0 && in<=100) level=1;
			if (in>100 && in<=1000) level=2;
			if (in>1000) level=3;
			if (in<0) level=-1;
		}
		if (level==3) {
			printf("前面的区域以后再来探索吧（派蒙发言）\n");
			fflush(stdin);
			scanf("%d",&in);
			if (in>=0 && in<=100) level=1;
			if (in>100 && in<=1000) level=2;
			if (in>1000) level=3;
			if (in<0) level=-1;
		}
		while (in!=answer && level==1){
			if (in>answer){
				big=in;
				printf("大于%d,小于%d\n",small,big) ;
				fflush(stdin);
				scanf("%d",&in);
				if (in>=0 && in<=100) level=1;
				if (in>100 && in<=1000) level=2;
				if (in>1000) level=3;
				if (in<0) level=-1;
			}
			if (in<answer){
				small=in;
				printf("大于%d,小于%d\n",small,big) ;
				fflush(stdin);
				scanf("%d",&in);
				if (in>=0 && in<=100) level=1;
				if (in>100 && in<=1000) level=2;
				if (in>1000) level=3;
				if (in<0) level=-1;
			}
		}
		if (level==2) {answer=rand()%1000;printf("\n这是你自找的!\nlevel 2!\n\n输入1000到0之间的数字\n");}
		while (in!=answer && level==2){
			if (in>answer){
				big2=in;
				printf("大于%d,小于%d\n",small2,big2) ;
				fflush(stdin);
				scanf("%d",&in);
				if (in>100 && in<=1000) level=2;
				if (in>1000) level=3;
				if (in<0) level=-1;
			}
			if (in<answer){
				small2=in;
				printf("大于%d,小于%d\n",small2,big2) ;
				fflush(stdin);
				scanf("%d",&in);
				if (in>100 && in<=1000) level=2;
				if (in>1000) level=3;
				if (in<0) level=-1;
			}
			
		}
}
	while(in==answer)printf(" =v= ");
	
}

	
	
	
	
	

