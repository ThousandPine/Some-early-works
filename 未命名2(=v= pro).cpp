#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{	int in=0,big=100,small=0,level=0,in2=0,big2=1000,small2=0;
	srand(time(0));
	rand();
	int answer=rand()%100;
	printf("����100��0֮�������\n") ;
	scanf("%d",&in);
	if (in>=0 && in<=100) level=1;
	if (in>100 && in<=1000) level=2;
	if (in>1000) level=3;
	if (in<0) level=-1;
	
	
	while (in!=answer){
	
		
		if (level==-1) {
			printf("�벻Ҫ�����Լ��ĳ���\n");
			fflush(stdin);
			scanf("%d",&in);
			if (in>=0 && in<=100) level=1;
			if (in>100 && in<=1000) level=2;
			if (in>1000) level=3;
			if (in<0) level=-1;
		}
		if (level==3) {
			printf("ǰ��������Ժ�����̽���ɣ����ɷ��ԣ�\n");
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
				printf("����%d,С��%d\n",small,big) ;
				fflush(stdin);
				scanf("%d",&in);
				if (in>=0 && in<=100) level=1;
				if (in>100 && in<=1000) level=2;
				if (in>1000) level=3;
				if (in<0) level=-1;
			}
			if (in<answer){
				small=in;
				printf("����%d,С��%d\n",small,big) ;
				fflush(stdin);
				scanf("%d",&in);
				if (in>=0 && in<=100) level=1;
				if (in>100 && in<=1000) level=2;
				if (in>1000) level=3;
				if (in<0) level=-1;
			}
		}
		if (level==2) {answer=rand()%1000;printf("\n���������ҵ�!\nlevel 2!\n\n����1000��0֮�������\n");}
		while (in!=answer && level==2){
			if (in>answer){
				big2=in;
				printf("����%d,С��%d\n",small2,big2) ;
				fflush(stdin);
				scanf("%d",&in);
				if (in>100 && in<=1000) level=2;
				if (in>1000) level=3;
				if (in<0) level=-1;
			}
			if (in<answer){
				small2=in;
				printf("����%d,С��%d\n",small2,big2) ;
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

	
	
	
	
	

