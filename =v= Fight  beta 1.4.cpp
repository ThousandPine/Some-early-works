#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>

void initialization(int* a, int n, int k);//��ʼ�����飨����, ��С��Ŀ��ֵ��
void display(int type,int n);//��ʾ�������������ͣ������� 0������ 1������(��β����)���� 2:�ո�(��β�޻���)

int main()
{
	//���
		//����:
				//��ս��������		 Զ����������       ��������    ������ħ������       ��������          ħ������       ����������     ��ʱ������
		const int weapon_short_n = 4, weapon_long_n = 2, prop_n = 7, enchantment_n = 4, weapon_magic_n = 3, magic_n = 4, levelbook_n = 3, timer_n = 7;

		//��һ�������:
					//  Ѫ��          ����             ������        ������          ̽������ֵ   ����ֵ           
					int p_hp = 1000, p_strength = 100, p_dodge = 10, p_critical = 20, p_luck = 0, p_VIT = 100, \
						//��ս��������                Զ�̹�������           �ƶ��ٶ�        ħ��
						p_attack_range_short = 70, p_attack_range_long = 0, p_speed = 20, p_magic = 100;	
					//  ������׼ֵ						�����ʻ�׼ֵ
					int p_strength_origin = p_strength, p_critical_origin = p_critical, p_hp_max = p_hp;

		//װ��: 
				//��ս����                       Զ������                        ����              ������ħ��                     
			int weapon_short[weapon_short_n], weapon_long[weapon_long_n], prop[prop_n], enchantment[enchantment_n], \
				//����                           ħ��                ������
				weapon_magic[weapon_magic_n], magic[magic_n], levelbook[levelbook_n];

		//Ч��:	
			// ��غ�Ч��������  װ����Զ������      װ���Ľ�ս����        ��ս����������         ��ս������������      ��ս����������			 ħ������
			int timer[timer_n], weapon_long_mod = 0, weapon_short_mod = 0, buff_short_damage = 0, buff_short_range = 0, buff_short_critical = 0, buff_magic = 0, \
				//Զ�̹���������      Զ�̹�����������		Զ�̱���������         �佣����Ч��				    �ѻ�ǹ����Ч��				  װ���ĸ�ħ		   װ���ķ���
				buff_long_damage = 0, buff_long_range = 0, buff_long_critical = 0, weapon_special_judge_0 = 30, weapon_special_judge_1 = 130, enchantment_mod = 0, weapon_magic_mod = 0, \
				//��ս����Ч��           һ������Ч��			�ػ���֮��:��������
				enchatment_judge_0 = 0, enchatment_judge_1 = 0, k = 1;
	
	//BOSS
		//BOSS��������:
				//  Ѫ��          ������            ������       ������           ��������              �ƶ��ٶ�
				int b_hp = 10000, b_strength = 20, b_dodge = 20, b_critical = 20, b_attack_range = 100, b_speed = 35;
				
				int boss_special = 1, b_hp_max = b_hp;

	//����
				int range = 0;		//����
				int damage = 0;	//�˺�
				int in;				//����
				int back = 0;		//����

	//��ʼ��
	initialization(weapon_short, weapon_short_n,0);		//��ʼ�� ��ս����	-> 0
	initialization(weapon_long, weapon_long_n,0);		//��ʼ�� Զ������	-> 0
	initialization(prop, prop_n,0);						//��ʼ�� ����		-> 0
	initialization(enchantment, enchantment_n,0);		//��ʼ�� ������ħ�� -> 0
	initialization(weapon_magic, weapon_magic_n,0);		//��ʼ�� ����		-> 0
	initialization(magic, magic_n,0);					//��ʼ�� ħ��		-> 0
	initialization(levelbook, levelbook_n, 0);			//��ʼ�� ������		-> 0
	initialization(timer, timer_n, 0);					//��ʼ�� ��ʱ��		-> 0
	

	while (p_hp > 0 && b_hp > 0)
	{
		srand(time(NULL));//�������������
		//��һغϿ�ʼ
	menue0:
		display(0, 50);
		display(1, 20);
		printf("��Ļغ�\n\n����ֵ:%d ����ֵ:%d ����:%d\n\n1.���� 2.�ж� 3.���� 4.װ��\n", p_hp, p_VIT, range);
		display(1, 20);
		do {
			back = 0;
			in = getch();
			switch (in)
			{
			case '1':	//ѡ��--1.����
				damage = 0;
				display(0, 50);
				display(1, 20);
				if (p_attack_range_short + buff_short_range >= range)				//��ս
				{
					p_strength = p_strength_origin + buff_short_damage; 
					if (timer[2]) { p_strength *= 1.3; timer[2]--; }	//����Ч��:����ҩˮ
					if (enchantment_mod==3 && range < weapon_special_judge_0)p_strength *= 1.5;	//��ħЧ��:�̿�֮��
					else if (enchantment_mod == 4 && range > weapon_special_judge_1)p_strength *= 1.5;	//��ħЧ��:�ѻ��ֵ����
					p_critical = p_critical_origin + buff_short_critical;
					if (weapon_short_mod == 2 && range < weapon_special_judge_0)p_strength *= 3;	//�佣�����˺�
					//��ͨ����
					if (rand() % 100 + 1 <= b_dodge && timer[0] == 0)	//������
					{
						damage = 0;
						printf("=v=�㿪����Ĺ���\n");
					}
					else								//δ������
					{
						printf("��=v=�����˽�ս����\n\n");
						if (enchantment_mod)	//��ħ��ʾ
						{
							if (enchantment_mod == 1)	//��ħ��ʾ:��ս����
							{printf("#��ս����:%d%%\n\n", enchatment_judge_0);}
							else if (enchantment_mod == 2)	//��ħ��ʾ:һ������
							{printf("#һ������:%d%%\n\n", enchatment_judge_1);}
							else if (enchantment_mod == 3 && range < weapon_special_judge_0)	//��ħ��ʾ:�̿�֮��
							{printf("#�̿�֮��\n\n");}
							else if (enchantment_mod == 4 && range > weapon_special_judge_1)	//��ħ��ʾ:�ѻ��ֵ����
							{printf("#�ѻ��ֵ����\n\n");}
						}
						printf("\n");
						if (rand() % 100 + 1 <= p_critical)	//�����ж�
						{
							damage = 2 * p_strength;
							printf("�����˱���:");
						}
						else
						{
							damage = p_strength;
						}
					}
					if (damage)	//��ħЧ��
					{
						if (enchantment_mod == 1)	//��ħЧ��:��ս����
						{
							damage *= 1.0 * enchatment_judge_0 / 100;
							if (enchatment_judge_0 < 150)enchatment_judge_0 += 10;
						}
						else if (enchantment_mod == 2)	//��ħЧ��:һ������
						{
							damage *= 1.0 * enchatment_judge_1 / 100;
							if (enchatment_judge_1 > 80)enchatment_judge_1 -= 10;
						}
						printf("�����%d�˺�\n", damage);
					}
					b_hp -= damage;	//������ͨ�����˺�

					//��������Ч��
					if (weapon_short_mod && damage)		
					{
						if (weapon_short_mod == 1)		//��ì:����
						{
							if (rand() % 100 + 1 <= 25)
							{
								damage = b_hp * 0.15;
								b_hp -= damage;
								printf("\n*����:���%d���˺�\n", damage);
							}
						}
						else if (weapon_short_mod == 2 && range < weapon_special_judge_0)	//�洫���佣:�����˺�
						{
							printf("\n*����:�����˺�\n");
						}
						else if (weapon_short_mod == 3)	//�㶾ذ��:�����˺�
						{
							timer[6] = 3;
							printf("\n* =v=�ж���\n");
						}
						else if (weapon_short_mod == 4)	//��Ѫ��:��Ѫ
						{
							damage /= 10;
							p_hp += damage;
							printf("\n*��Ѫ:�ظ���%d������ֵ\n",damage);
						}
					}
				}
				else if (weapon_long_mod && p_attack_range_long + buff_long_range >= range - p_attack_range_short - buff_short_range)	//Զ��
				{
					p_strength = p_strength_origin + buff_long_damage;
					if (timer[2]) { p_strength *= 1.3; timer[2]--; }	//����Ч��:����ҩˮ
					if (enchantment_mod == 3 && range < weapon_special_judge_0)p_strength *= 1.5;	//��ħЧ��:�̿�֮��
					else if (enchantment_mod == 4 && range > weapon_special_judge_1)p_strength *= 1.5;	//��ħЧ��:�ѻ��ֵ����
					p_critical = p_critical_origin + buff_long_critical;
					int i = 1;
					if (weapon_long_mod == 1)//����:˫�ش��
					{
						i = 2;
						printf("*˫�ش��\n\n");
					}
					for (; i; i--)
					{
						int t_strength = p_strength;
						if (weapon_long_mod == 1)//����:���ι���
						{
							if (i == 2)t_strength *= 0.6;
							if (i == 1)t_strength *= 0.7;
						}
						if (rand() % 100 + 1 <= b_dodge && timer[0] == 0)	//������
						{
							damage = 0;
							printf("=v=�㿪����Ĺ���\n");
						}
						else								//δ������
						{
							printf("��=v=������Զ�̹���\n\n");
							if (enchantment_mod)	//��ħ��ʾ
							{
								if (enchantment_mod == 1)	//��ħ��ʾ:��ս����
								{
									printf("#��ս����:%d%%\n\n", enchatment_judge_0);
								}
								else if (enchantment_mod == 2)	//��ħ��ʾ:һ������
								{
									printf("#һ������:%d%%\n\n", enchatment_judge_1);
								}
								else if (enchantment_mod == 3 && range < weapon_special_judge_0)	//��ħ��ʾ:�̿�֮��
								{
									printf("#�̿�֮��\n\n");
								}
								else if (enchantment_mod == 4 && range > weapon_special_judge_1)	//��ħ��ʾ:�ѻ��ֵ����
								{
									printf("#�ѻ��ֵ����\n\n");
								}
							}
							printf("\n");
							if (rand() % 100 + 1 <= p_critical)		//�����ж�
							{
								damage = 2 * t_strength;
								printf("�����˱���:");
							}
							else
							{
								damage = t_strength;
							}
						}
						if (damage && weapon_long_mod == 2 && range > weapon_special_judge_1)	//�ѻ�ǹ:��׼���
							damage *= 2;
						if (damage)	//��ħЧ��
						{
							if (enchantment_mod == 1)	//��ħЧ��:��ս����
							{
								damage *= 1.0 * enchatment_judge_0 / 100;
								if (enchatment_judge_0 < 150)enchatment_judge_0 += 10;
							}
							else if (enchantment_mod == 2)	//��ħЧ��:һ������
							{
								damage *= 1.0 * enchatment_judge_1 / 100;
								if (enchatment_judge_1 > 80)enchatment_judge_1 -= 10;
							}
							printf("�����%d�˺�\n", damage);
						}
						b_hp -= damage;		//������ͨ�����˺�
						if (i == 2)printf("\n");
						
					}
					if (damage && weapon_long_mod == 2 && range > weapon_special_judge_1)		//�ѻ�ǹ
					{
						printf("\n*��׼���\n");
					}
				}
				else	//�������벻��
				{
					printf("����=v=̫Զ��\n");
				}
				display(1, 20);
				getch();
				break;

			case '2':	//ѡ��--2.�ж�
			menue2:
				display(0, 50);
				display(1, 20);
				printf("�ж�\n\n1.�鿴 2.̽�� 3.���� 4.��Ϣ\n\nZ.����\n");
				display(1, 20);
				do {
					back = 0;
					in = getch();
					switch (in)
					{
					case '1':	//ѡ��--2.1�鿴
						display(0, 50);
						display(1, 20);
						if (p_VIT < 10)//��������
						{
							printf("*������Ҫ10������\n");
							display(1, 20);
							getch();
							goto menue2;
						}
						printf("���:\n\n����:%d  ħ��:%d%%   ������(��ս):%d%%   ������(Զ��):%d%%\n\n��������(��ս):%d   ��������(Զ��):%d   ������:%d%%   �ƶ��ٶ�:%d\n\n\n"\
							, p_strength_origin, p_magic+buff_magic, p_critical_origin + buff_short_critical, p_critical_origin + buff_long_critical, p_attack_range_short+buff_short_range, p_attack_range_long+buff_long_range, p_dodge, p_speed);
						printf("=v=:\n\n����ֵ:%d   ������:%d  ������:%d%%  ������:%d%%\n\n��������:%d  �ƶ��ٶ�:%d\n"\
							, b_hp,b_strength,b_critical,b_dodge,b_attack_range,b_speed);
						if (weapon_magic_mod != 1)
						{
							printf("\n\n*����-10");
							p_VIT -= 10;
						}
						display(1, 20);
						getch();
						goto menue2;
						break;
					case '2':	//ѡ��--2.2̽��
					menue2_2:
						if (p_VIT >= 20||timer[1])
						{
							display(0, 50);
							display(1, 20);
							printf("1.����                  �ٶ�Ҫ��:20\n\n");
							printf("2.������                �ٶ�Ҫ��:30\n\n");
							printf("3.��ع�                �ٶ�Ҫ��:50\n\n");
							printf("4.�����е�Ů��С��      �ٶ�Ҫ��:80\n\n\n");
							printf("*��ǰ�ƶ��ٶ�:%d\n\n", p_speed);
							printf("Z.����\n");
							display(1, 20);
							do {
								back = 0;
								in = getch();
								int judge;
								switch (in)
								{
								case '1':		//ѡ��--2.2.1.����
									if (p_speed < 20)
									{
										back = 1;
										break;
									}
									display(0, 50);
									display(1, 20);
									if (p_VIT < 20 && timer[1] == 0)	//��������
									{
										printf("*������Ҫ20������\n");
										display(1, 20);
										getch();
										goto menue2_2;
									}
									printf("����+20");
									if (timer[1] == 0)printf("  ����-20");
									else printf("  �������ػغ�ʣ��:%d", timer[1]-1);
									printf("\n\n");
									if (timer[1])timer[1]--;
									else p_VIT -= 20;
									range += 20;
									judge = rand() % 100 + 1;
									if (judge <= 95)//�ջ�
									{
										printf("���:");
										judge = rand() % 100 + 1;
										if (judge <= 70)	//����
										{
											judge = rand() % 100 + 1;
											if (judge <= 30) { prop[0]++; printf("����ҩˮ\n"); }
											else if (judge <= 50) { prop[1]++; printf("����ҩˮ\n"); }
											else if (judge <= 60) { prop[2]++; printf("��˯���\n"); }
											else if (judge <= 65) { prop[3]++; printf("��������\n"); }
											else if (judge <= 75) { prop[4]++; printf("��������\n"); }
											else if (judge <= 85) { prop[5]++; printf("����ҩˮ\n"); }
											else if (judge <= 100) { prop[6]++; printf("����ҩˮ\n"); }
										}
										else if (judge <= 100)	//������
										{
											judge = rand() % 100 + 1;
											if (judge <= 30) { levelbook[0]++; printf("��֥ʿ����_ _!��\n"); }
											else if (judge <= 90) { levelbook[1]++; printf("������:�����ŵ�������\n"); }
											else if (judge <= 100) { levelbook[2]++; printf("����ϵ���⿷�ʽ��\n"); }
										}
									}
									else//һ������
									{printf("*һ������\n");}
									display(1, 20);
									getch();
									break;
								case '2':		//ѡ��--2.2.2.������ 
									if (p_speed < 30)
									{
										back = 1;
										break;
									}
									display(0, 50);
									display(1, 20);
									if (p_VIT < 30 && timer[1] == 0)	//��������
									{
										printf("*������Ҫ30������\n");
										display(1, 20);
										getch();
										goto menue2_2;
									}
									printf("����+30");
									if (timer[1] == 0)printf("  ����-30");
									else printf("  �������ػغ�ʣ��:%d", timer[1]-1);
									printf("\n\n");
									if (timer[1])timer[1]--;
									else p_VIT -= 30;
									range += 30;
									judge = rand() % 100 + 1;
									if (judge <= 90)//�ջ�
									{
										
										printf("���:");
										judge = rand() % 100 + 1;
										if (judge <= 30)	//����
										{
											judge = rand() % 100 + 1;
											if (judge <= 30) { prop[0]++; printf("����ҩˮ\n"); }
											else if (judge <= 50) { prop[1]++; printf("����ҩˮ\n"); }
											else if (judge <= 70) { prop[4]++; printf("��������\n"); }
											else if (judge <= 90) { prop[5]++; printf("����ҩˮ\n"); }
											else if (judge <= 100) { prop[6]++; printf("����ҩˮ\n"); }
										}
										else if (judge <= 50)	//Զ������
										{
											judge = rand() % 100 + 1;
											if (judge <= 60) { weapon_long[0]++; printf("����\n"); }
											else if (judge <= 100) { weapon_long[1]++; printf("�ѻ�ǹ\n"); }
										}
										else if (judge <= 80)	//��ս����
										{
											judge = rand() % 100 + 1;
											if (judge <= 30) { weapon_short[0]++; printf("��ì\n"); }
											else if(judge <= 50) { weapon_short[1]++; printf("�洫���佣\n"); }
											else if (judge <= 80) { weapon_short[2]++; printf("�㶾ذ��\n"); }
											else if (judge <= 100) { weapon_short[3]++; printf("��Ѫ��\n"); }
										}
										else if (judge <= 100)	//������
										{
											judge = rand() % 100 + 1;
											if (judge <= 50) { levelbook[0]++; printf("��֥ʿ����_ _!��\n"); }
											else if (judge <= 90) { levelbook[1]++; printf("������:�����ŵ�������\n"); }
											else if (judge <= 100) { levelbook[2]++; printf("����ϵ���⿷�ʽ��\n"); }
										}
									}
									else//һ������
									{printf("*һ������\n");}
									display(1, 20);
									getch();
									break;
								case '3':		//ѡ��--2.2.3.��ع�
									if (p_speed < 50)
									{
										back = 1;
										break;
									}
									display(0, 50);
									display(1, 20);
									if (p_VIT < 35 && timer[1] == 0)	//��������
									{
										printf("*������Ҫ35������\n");
										display(1, 20);
										getch();
										goto menue2_2;
									}
									printf("����+50");
									if (timer[1] == 0)printf("  ����-35");
									else printf("  �������ػغ�ʣ��:%d", timer[1]-1);
									printf("\n\n");
									if (timer[1])timer[1]--;
									else p_VIT -= 35;
									range += 50;
									judge = rand() % 100 + 1;
									if (judge <= 80)//�ջ�
									{
										printf("���:");
										judge = rand() % 100 + 1;
										if (judge <= 10)	//����
										{
											judge = rand() % 100 + 1;
											if (judge <= 50) { prop[2]++; printf("��˯���\n"); }
											else if (judge <= 100) { prop[3]++; printf("��������\n"); }
										}
										else if (judge <= 40)	//��ħ��
										{
											judge = rand() % 100 + 1;
											if (judge <= 30) { enchantment[0]++; printf("��ս����\n"); }
											else if (judge <= 65) { enchantment[1]++; printf("һ������\n"); }
											else if (judge <= 85) { enchantment[2]++; printf("�̿�֮��\n"); }
											else if (judge <= 100) { enchantment[3]++; printf("�ѻ��ֵ����\n"); }
										}
										else if (judge <= 70)	//������
										{
											judge = rand() % 100 + 1;
											if (judge <= 25) { levelbook[0]++; printf("��֥ʿ����_ _!��\n"); }
											else if (judge <= 50) { levelbook[1]++; printf("������:�����ŵ�������\n"); }
											else if (judge <= 100) { levelbook[2]++; printf("����ϵ���⿷�ʽ��\n"); }
										}
										else if (judge <= 80)	//����
										{
											judge = rand() % 100 + 1;
											if (judge <= 40) { weapon_magic[0]++; printf("����֮��\n"); }
											else if (judge <= 75) { weapon_magic[1]++; printf("֧Ԯ����\n"); }
											else if (judge <= 100) { weapon_magic[2]++; printf("�ػ���֮��\n"); }
										}
										else if (judge <= 100)	//����
										{
											judge = rand() % 100 + 1;
											if (judge <= 15) { magic[0]++; printf("��Ը\n"); }
											else if (judge <= 35) { magic[1]++; printf("�͸�\n"); }
											else if (judge <= 70) { magic[2]++; printf("����\n"); }
											else if (judge <= 100) { magic[3]++; printf("����\n"); }
										}
									}
									else//һ������
									{printf("*һ������\n");}
									display(1, 20);
									getch();
									break;
								case '4':		//ѡ��--2.2.4.�����е�Ů��С��
									if (p_speed < 80)
									{
										back = 1;
										break;
									}
									display(0, 50);
									display(1, 20);
									if (p_VIT < 50 && timer[1] == 0)	//��������
									{
										printf("*������Ҫ50������\n");
										display(1, 20);
										getch();
										goto menue2_2;
									}
									printf("����+80");
									if (timer[1] == 0)printf("  ����-50");
									else printf("  �������ػغ�ʣ��:%d", timer[1]-1);
									printf("\n\n");
									if (timer[1])timer[1]--;
									else p_VIT -= 50;
									judge = rand() % 100 + 1;
									if (judge <= 70)//�ջ�
									{
										printf("���:");
										judge = rand() % 100 + 1;
										if (judge <= 10)	//����
										{
											prop[3]++; printf("��������\n");
										}
										else if (judge <= 50)	//����
										{
											judge = rand() % 100 + 1;
											if (judge <= 25) { magic[0]++; printf("��Ը\n"); }
											else if (judge <= 50) { magic[1]++; printf("�͸�\n"); }
											else if (judge <= 75) { magic[2]++; printf("����\n"); }
											else if (judge <= 100) { magic[3]++; printf("����\n"); }
										}
										else if (judge <= 80)	//����
										{
											judge = rand() % 100 + 1;
											if (judge <= 40) { weapon_magic[0]++; printf("����֮��\n"); }
											else if (judge <= 65) { weapon_magic[1]++; printf("֧Ԯ����\n"); }
											else if (judge <= 100) { weapon_magic[2]++; printf("�ػ���֮��\n"); }
										}
										else if (judge <= 90)	//��ħ��
										{
											judge = rand() % 100 + 1;
											if (judge <= 25) { enchantment[0]++; printf("��ս����\n"); }
											else if (judge <= 50) { enchantment[1]++; printf("һ������\n"); }
											else if (judge <= 75) { enchantment[2]++; printf("�̿�֮��\n"); }
											else if (judge <= 100) { enchantment[3]++; printf("�ѻ��ֵ����\n"); }
										}
										else if (judge <= 100)	//������
										{
											judge = rand() % 100 + 1;
											if (judge <= 5) { levelbook[0]++; printf("��֥ʿ����_ _!��\n"); }
											else if (judge <= 20) { levelbook[1]++; printf("������:�����ŵ�������\n"); }
											else if (judge <= 100) { levelbook[2]++; printf("����ϵ���⿷�ʽ��\n"); }
										}
									}
									else//һ������
									{printf("*һ������\n");}
									display(1, 20);
									getch();
									judge = rand() % 100 + 1;//�����ж�
									if (judge <= 30)
									{
										display(0, 50);
										display(1, 20);
										printf("�뿪ʱ�㴥����Ů�׵�ħ������\n");
										if(p_magic+buff_magic<200)
										{
											printf("\n�ܵ���%.lf���˺�\n",70-70.0*(p_magic+buff_magic-100)/100);
											if (p_magic + buff_magic < 100) { printf("\n\n*���ħ���˽���٣������ڶ����ܵ���%.lf���˺�\n", -70.0 * (p_magic + buff_magic - 100) / 100); }
											if (p_magic + buff_magic > 100) { printf("\n\n*��ħ��������ʹ�㼰ʱ����ħ������%.lf���˺�\n", 70.0 * (p_magic + buff_magic - 100) / 100); }
											p_hp -= 70 - 70.0 * (p_magic + buff_magic - 100) / 100;
										}
										else if (p_magic + buff_magic == 200)
										{
											printf("\n��ħ��������ʹ�㼰ʱ����ħ������ȫ���˺�\n");
										}
										else
										{
											printf("\n��Ϊ��ħ��ʦ�������־ͽ������ջ�Ϊ����\n\n\n*����ֵ+%.lf",70.0*(p_magic + buff_magic-200)/100);
											p_hp += 70.0 * (p_magic + buff_magic - 200) / 100;
										}
										display(1, 20);
										getch();
									}
									break;
								case 'z':
									goto menue2;
									break;
								case 'Z':
									goto menue2;
									break;
								default:
									back = 1;
									break;
								}
							} while (back);

						}
						else	//��������
						{
							display(0, 50);
							display(1, 20);
							printf("��������,��ǰ����%d\n\n\n*������Ҫ20������\n", p_VIT);
							display(1, 20);
							getch();
							goto menue2;
						}
						break;
					case '3':	//ѡ��--2.3����
						range -= p_speed;
						if (range < 0)range = 0;
						display(0, 50);
						display(1, 20);
						printf("��ô˵�������Ŷ\n\n����-%d\n\n\n*��ǰ����:%d\n",p_speed,range);
						display(1, 20);
						getch();
						break;
					case '4':	//ѡ��--2.4��Ϣ
						p_VIT += 60;
						display(0, 50);
						display(1, 20);
						printf("ƣ������Ȼ����\n\n�����������Ϣһ��\n\n\n*����+60\n");
						display(1, 20);
						getch();
						break;
					case 'z':
						goto menue0;
						break;
					case 'Z':
						goto menue0;
						break;
					default:
						back = 1;
						break;
					}
				} while (back);
				break;

			case '3':	//ѡ��--3.����
			menue3:
				display(0, 50);
				display(1, 20);
				printf("����\n\n1.���� 2.���� 3.������ 4.��ħ��\n\nZ.����\n");
				display(1, 20);
				do {
					back = 0;
					int i = 0;
					in = getch();
					switch (in)
					{
					case '1':	//ѡ��--3.1����
					menue3_1:
						i = 0;
						display(0, 50);				//���߲˵�
						display(1, 20);
						printf("����\n\n");
						if (prop[0]) { printf("1.����ҩˮx%d  ", prop[0]); i++; }
						if (prop[1]) { printf("2.����ҩˮx%d  ", prop[1]); i++; }
						if (prop[2]) { printf("3.��˯���x%d  ", prop[2]); i++; }
						if (prop[3]) { printf("4.��������x%d  ", prop[3]); i++; }
						if (prop[4]) { if (i == 4)printf("\n\n"); printf("5.��������x%d  ", prop[4]); i++; }
						if (prop[5]) { if (i == 4)printf("\n\n"); printf("6.����ҩˮx%d  ", prop[5]); i++; }
						if (prop[6]) { if (i == 4)printf("\n\n"); printf("7.����ҩˮx%d  ", prop[6]); i++; }
						if (i == 0)
						{
							printf("�������һ��\n");
							display(1, 20);
							getch();
							goto menue3;
						}
						printf("\n\nZ.����\n");
						display(1, 20);
						do {						//ѡ�����
							back = 0;
							in = getch();
							switch (in)	
							{
							case '1':						//ѡ��--3.1.1����ҩˮ
								if (prop[in - 49])
								{
									display(0, 50);
									display(1, 20);
									printf("����ҩˮ\n\n�ָ�150������ֵ\n\n\nX.ʹ�� Z.����\n");
									display(1, 20);
									do {
										back = 0;
										in = getch();
										if (in == 'x' || in == 'X')		//X.ʹ��
										{
											prop[0]--;
											p_hp += 150;
											display(0, 50);
											display(1, 20);
											printf("��ʹ��������ҩˮ\n\n����ֵ+150\n");
											display(1, 20);
											getch();
										}
										else if (in == 'z' || in == 'Z') goto menue3_1;	//Z.����
										else back = 1;
									} while (back);
								}
								else back = 1;
								break;
							case '2':						//ѡ��--3.1.2����ҩˮ
								if (prop[in - 49])
								{
									display(0, 50);
									display(1, 20);
									printf("����ҩˮ\n\n�ָ�90������ֵ\n\n\nX.ʹ�� Z.����\n");
									display(1, 20);
									do {
										back = 0;
										in = getch();
										if (in == 'x' || in == 'X')		//X.ʹ��
										{
											prop[1]--;
											p_VIT += 90;
											display(0, 50);
											display(1, 20);
											printf("��ʹ��������ҩˮ\n\n����ֵ+90\n");
											display(1, 20);
											getch();
										}
										else if (in == 'z' || in == 'Z') goto menue3_1;	//Z.����
										else back = 1;
									} while (back);
								}
								else back = 1;
								break;
							case '3':						//ѡ��--3.1.3��˯���
								if (prop[in - 49])
								{
									display(0, 50);
									display(1, 20);
									printf("��˯���\n\nʹ=v=������3�غ��޷��ж�\n\n\n*�·��ܴ������п��������ߵ�����\n\n\nX.ʹ�� Z.����\n");
									display(1, 20);
									do {
										back = 0;
										in = getch();
										if (in == 'x' || in == 'X')		//X.ʹ��
										{
											prop[2]--;
											timer[0] = 3;
											display(0, 50);
											display(1, 20);
											printf("=v=:ZZZzzz...\n\n*������3�غ�=v=�޷��ж�\n");
											display(1, 20);
											getch();
										}
										else if (in == 'z' || in == 'Z') goto menue3_1;	//Z.����
										else back = 1;
									} while (back);
								}
								else back = 1;
								break;
							case '4':						//ѡ��--3.1.4��������
								if (prop[in - 49])
								{
									display(0, 50);
									display(1, 20);
									printf("��������\n\n�����г�����������ĵ��������������Ϊ0~9\n\n\nX.ʹ�� Z.����\n");
									display(1, 20);
									do {
										back = 0;
										in = getch();
										if (in == 'x' || in == 'X')		//X.ʹ��
										{
											prop[3]--;
											for (int i = 0; i < prop_n; i++)
												if(i!=3)prop[i] = rand() % 10;
											display(0, 50);
											display(1, 20);
											printf("��ʹ������������\n\n�����ˣ�ҡ��9�ӳ���\n");
											display(1, 20);
											getch();
										}
										else if (in == 'z' || in == 'Z') goto menue3_1;	//Z.����
										else back = 1;
									} while (back);
								}
								else back = 1;
								break;
							case '5':						//ѡ��--3.1.5��������
								if (prop[in - 49])
								{
									display(0, 50);
									display(1, 20);
									printf("��������\n\n������3��̽������������\n\n*�ɵ���\n\n\nX.ʹ�� Z.����\n");
									display(1, 20);
									do {
										back = 0;
										in = getch();
										if (in == 'x' || in == 'X')		//X.ʹ��
										{
											prop[4]--;
											timer[1] += 3;
											display(0, 50);
											display(1, 20);
											printf("��ʹ������������\n\n*��ʹ������˾���\n");
											display(1, 20);
											getch();
										}
										else if (in == 'z' || in == 'Z') goto menue3_1;	//Z.����
										else back = 1;
									} while (back);
								}
								else back = 1;
								break;
							case '6':						//ѡ��--3.1.6����ҩˮ
								if (prop[in - 49])
								{
									display(0, 50);
									display(1, 20);
									printf("����ҩˮ\n\n������3�ι�����������30%%\n\n\nX.ʹ�� Z.����\n");
									display(1, 20);
									do {
										back = 0;
										in = getch();
										if (in == 'x' || in == 'X')		//X.ʹ��
										{
											prop[5]--;
											timer[2] = 3;
											display(0, 50);
											display(1, 20);
											printf("�����������ҩˮ\n\n�о�����֥ʿ��ζ��\n");
											display(1, 20);
											getch();
										}
										else if (in == 'z' || in == 'Z') goto menue3_1;	//Z.����
										else back = 1;
									} while (back);
								}
								else back = 1;
								break;
							case '7':						//ѡ��--3.1.7����ҩˮ
								if (prop[in - 49])
								{
									display(0, 50);
									display(1, 20);
									printf("����ҩˮ\n\n������5�غ�=v=�Ĺ���������30%%\n\n\nX.ʹ�� Z.����\n");
									display(1, 20);
									do {
										back = 0;
										in = getch();
										if (in == 'x' || in == 'X')		//X.ʹ��
										{
											prop[6]--;
											timer[3] = 5;
											display(0, 50);
											display(1, 20);
											printf("��ʹ��������ҩˮ\n\n=v=�е��ⲻס��\n");
											display(1, 20);
											getch();
										}
										else if (in == 'z' || in == 'Z') goto menue3_1;	//Z.����
										else back = 1;
									} while (back);
								}
								else back = 1;
								break;
							case 'z':
								goto menue3;
								break;
							case 'Z':
								goto menue3;
								break;
							default:
								back = 1;
								break;
							}
						} while (back);
						break;
					case '2':	//ѡ��--3.2����
					menue3_2:
						i = 0;
						display(0, 50);				//�����˵�
						display(1, 20);
						printf("����\n\n");
						if (magic[0]) { printf("1.��Ըx%d  ", magic[0]); i++; }
						if (magic[1]) { printf("2.�͸�x%d  ", magic[1]); i++; }
						if (magic[2]) { printf("3.����x%d  ", magic[2]); i++; }
						if (magic[3]) { printf("4.����x%d  ", magic[3]); i++; }
						if (i == 0)
						{
							printf("�������һ��\n");
							display(1, 20);
							getch();
							goto menue3;
						}
						printf("\n\nZ.����\n");
						display(1, 20);
						do {
							back = 0;
							in = getch();
							switch (in)
							{
							case '1':		//ѡ��--3.2.1��Ը
								if (magic[in - 49])
								{
									display(0, 50);
									display(1, 20);
									printf("��Ը\n\n��Һ�=v=������ֵͬʱ����%.lf%%\n\n\nX.ʹ�� Z.����\n",0.4*(p_magic+buff_magic));
									display(1, 20);
									do {
										back = 0;
										in = getch();
										if (in == 'x' || in == 'X')		//X.ʹ��
										{
											magic[0]--;
											
											display(0, 50);
											display(1, 20);
											printf("���·������ʥ��\n\n*�������ֵ+%.lf  =v=������ֵ+%.lf\n", p_hp* (0.4 * (p_magic + buff_magic) / 100), b_hp* (0.4 * (p_magic + buff_magic) / 100));
											p_hp += p_hp*(0.4 * (p_magic + buff_magic) / 100);
											b_hp += b_hp*(0.4 * (p_magic + buff_magic) / 100);
											display(1, 20);
											getch();
										}
										else if (in == 'z' || in == 'Z') goto menue3_2;	//Z.����
										else back = 1;
									} while (back);
								}
								else back = 1;
								break;
							case'2':		//ѡ��--3.2.2.�͸�
								if (magic[in - 49])
								{
									display(0, 50);
									display(1, 20);
									printf("�͸�\n\nÿ�غ�����%.lf%%����ֵ������3�غ�\n\n\nX.ʹ�� Z.����\n",0.1*(p_magic + buff_magic));
									display(1, 20);
									do {
										back = 0;
										in = getch();
										if (in == 'x' || in == 'X')		//X.ʹ��
										{
											magic[1]--;
											timer[4] = 3;
											display(0, 50);
											display(1, 20);
											printf("*��о������˲���\n");
											display(1, 20);
											getch();
										}
										else if (in == 'z' || in == 'Z') goto menue3_2;	//Z.����
										else back = 1;
									} while (back);
								}
								else back = 1;
								break;
							case '3':		//ѡ��--3.2.3.����
								if (magic[in - 49])
								{
									display(0, 50);
									display(1, 20);
									printf("����\n\n����Һ�=v=�������ֵ%.lf%%���˺�\n\n*��˵����Ҳ�Ǵ�ħ����һ��������ʽ\n\n\nX.ʹ�� Z.����\n",0.2*(p_magic + buff_magic));
									display(1, 20);
									do {
										back = 0;
										in = getch();
										if (in == 'x' || in == 'X')		//X.ʹ��
										{
											magic[2]--;
											display(0, 50);
											display(1, 20);
											printf("��ʹ��������\n\n*���������%.lf���˺�  ��=v=�����%.lf���˺�\n", p_hp* (0.2 * (p_magic + buff_magic) / 100), b_hp* (0.2 * (p_magic + buff_magic) / 100));
											p_hp -= p_hp * (0.2 * (p_magic + buff_magic) / 100);
											b_hp -= b_hp * (0.2 * (p_magic + buff_magic) / 100);
											display(1, 20);
											getch();
										}
										else if (in == 'z' || in == 'Z') goto menue3_2;	//Z.����
										else back = 1;
									} while (back);
								}
								else back = 1;
								break;
							case '4':		//ѡ��--3.2.4.����
								if (magic[in - 49])
								{
									display(0, 50);
									display(1, 20);
									printf("����\n\nÿ�غ϶�=v=�������ֵ%.lf%%���˺�������5�غ�\n\n*�����ϵ�����������һ������ֵ����֡�114514����\n\n\nX.ʹ�� Z.����\n",0.05*(p_magic + buff_magic));
									display(1, 20);
									do {
										back = 0;
										in = getch();
										if (in == 'x' || in == 'X')		//X.ʹ��
										{
											magic[3]--;
											timer[5] = 5;
											display(0, 50);
											display(1, 20);
											printf("��ʹ���˶���\n");
											display(1, 20);
											getch();
										}
										else if (in == 'z' || in == 'Z') goto menue3_2;	//Z.����
										else back = 1;
									} while (back);
								}
								else back = 1;
								break;
							case 'z':
								goto menue3;
								break;
							case 'Z':
								goto menue3;
								break;
							default:
								back = 1;
								break;
							}
						} while (back);
						break;
					case '3':	//ѡ��--3.3������
					menue3_3:
						i = 0;
						display(0, 50);				//������˵�
						display(1, 20);
						printf("������\n\n");
						if (levelbook[0]) { printf("1.��֥ʿ����_ _!��x%d   ", levelbook[0]); i++; }
						if (levelbook[1]) { printf("2.������:�����ŵ�������x%d   ", levelbook[1]); i++; }
						if (levelbook[2]) { if (i == 2)printf("\n\n"); printf("3.����ϵ���⿷�ʽ��x%d   ", levelbook[2]); i++; }
						if (i == 0)
						{
							printf("�������һ��\n");
							display(1, 20);
							getch();
							goto menue3;
						}
						printf("\n\nZ.����\n");
						display(1, 20);
						do {
							back = 0;
							in = getch();
							switch (in)
							{
							case '1':		//ѡ��--3.3.1.��֥ʿ����_ _!��
								if (levelbook[in - 49])
								{
									display(0, 50);
									display(1, 20);
									printf("��֥ʿ����_ _!��\n\n\nX.�Ķ� Z.����\n");
									display(1, 20);
									do {
										back = 0;
										in = getch();
										if (in == 'x' || in == 'X')		//X.ʹ��
										{
											levelbook[0]--;
											p_strength_origin += 20;
											display(0, 50);
											display(1, 20);
											printf("��������ֻ��һ������⣬����·����������������\n\n*����+20\n");
											display(1, 20);
											getch();
										}
										else if (in == 'z' || in == 'Z') goto menue3_3;	//Z.����
										else back = 1;
									} while (back);
								}
								else back = 1;
								break;
							case '2':		//ѡ��--3.3.2.������:�����ŵ�������
								if (levelbook[in - 49])
								{
									display(0, 50);
									display(1, 20);
									printf("������:�����ŵ�������\n\n\nX.�Ķ� Z.����\n");
									display(1, 20);
									do {
										back = 0;
										in = getch();
										if (in == 'x' || in == 'X')		//X.ʹ��
										{
											levelbook[1]--;
											p_speed += 10;
											p_dodge += 1;
											display(0, 50);
											display(1, 20);
											printf("�����ƺ���һ������ʮ���ơ�������֪Ϊ��ֻʣ�������һ��\n\n*�ƶ��ٶ�+10  *������+1%%\n");
											display(1, 20);
											getch();
										}
										else if (in == 'z' || in == 'Z') goto menue3_3;	//Z.����
										else back = 1;
									} while (back);
								}
								else back = 1;
								break;
							case '3':		//ѡ��--3.3.3.����ϵ���⿷�ʽ��
								if (levelbook[in - 49])
								{
									display(0, 50);
									display(1, 20);
									printf("����ϵ���⿷�ʽ��\n\n\nX.�Ķ� Z.����\n");
									display(1, 20);
									do {
										back = 0;
										in = getch();
										if (in == 'x' || in == 'X')		//X.ʹ��
										{
											levelbook[2]--;
											p_magic += 10;
											display(0, 50);
											display(1, 20);
											printf("����������ϵ��³�֮���㲻�����˸���������������Ŭ����ѧϰħ��\n\n*ħ��+10%%\n");
											display(1, 20);
											getch();
										}
										else if (in == 'z' || in == 'Z') goto menue3_3;	//Z.����
										else back = 1;
									} while (back);
								}
								else back = 1;
								break;
							case 'z':
								goto menue3;
								break;
							case 'Z':
								goto menue3;
								break;
							default:
								back = 1;
								break;
							}
						} while (back);
						break;
					case '4':	//ѡ��--3.4��ħ��
					menue3_4:
						i = 0;
						display(0, 50);				//��ħ��˵�
						display(1, 20);
						printf("��ħ��\n\n");
						if (enchantment[0]) { printf("1.��ս����x%d  ", enchantment[0]); i++; }
						if (enchantment[1]) { printf("2.һ������x%d  ", enchantment[1]); i++; }
						if (enchantment[2]) { printf("3.�̿�֮��x%d  ", enchantment[2]); i++; }
						if (enchantment[3]) { printf("4.�ѻ��ֵ����x%d  ", enchantment[3]); i++; }
						if (i == 0)
						{
							printf("�������һ��\n");
							printf("\n��ǰ��ħ--");//��ǰ��ħ��ʾ
							if (enchantment_mod == 0)printf("��\n");
							else if (enchantment_mod == 1)printf("#��ս����:%d%%\n",enchatment_judge_0);
							else if (enchantment_mod == 2)printf("#һ������:%d%%\n",enchatment_judge_1);
							else if (enchantment_mod == 3)printf("#�̿�֮��:%d\n",weapon_special_judge_0);
							else if (enchantment_mod == 4)printf("#�ѻ��ֵ����:%d\n",weapon_special_judge_1);
							display(1, 20);
							getch();
							goto menue3;
						}
						printf("\n\n\n��ǰ��ħ--");//��ǰ��ħ��ʾ
						if (enchantment_mod == 0)printf("��\n");
						else if (enchantment_mod == 1)printf("#��ս����:%d%%\n",enchatment_judge_0);
						else if (enchantment_mod == 2)printf("#һ������:%d%%\n",enchatment_judge_1);
						else if (enchantment_mod == 3)printf("#�̿�֮��:%d\n",weapon_special_judge_0);
						else if (enchantment_mod == 4)printf("#�ѻ��ֵ����:%d\n",weapon_special_judge_1);
						printf("\nZ.����\n");
						display(1, 20);
						do{
							back = 0;
							in = getch();
							switch (in)
							{
							case '1':		//ѡ��--3.4.1.��ս����
								if (enchantment[in - 49])
								{
									display(0, 50);
									display(1, 20);
									printf("��ս����\n\n�������70%%���˺���ÿ�غ�����10%%\n\n*����Ϊ150%%  �ɱ�������ħ����\n\n\nX.ʹ�� Z.����\n");
									display(1, 20);
									do {
										back = 0;
										in = getch();
										if (in == 'x' || in == 'X')		//X.ʹ��
										{
											enchantment[0]--;
											enchantment_mod = 1;
											enchatment_judge_0 = 70;
											display(0, 50);
											display(1, 20);
											printf("��Ҫͣ�°�\n");
											display(1, 20);
											getch();
										}
										else if (in == 'z' || in == 'Z') goto menue3_4;	//Z.����
										else back = 1;
									} while (back);
								}
								else back = 1;
								break;
							case '2':		//ѡ��--3.4.2.һ������
								if (enchantment[in - 49])
								{
									display(0, 50);
									display(1, 20);
									printf("һ������\n\n�������160%%���˺���ÿ�غϼ���10%%\n\n*����Ϊ80%%  �ɱ�������ħ����\n\n\nX.ʹ�� Z.����\n");
									display(1, 20);
									do {
										back = 0;
										in = getch();
										if (in == 'x' || in == 'X')		//X.ʹ��
										{
											enchantment[1]--;
											enchantment_mod = 2;
											enchatment_judge_1 = 160;
											display(0, 50);
											display(1, 20);
											printf("���ٶ�˥�������ߡ�\n");
											display(1, 20);
											getch();
										}
										else if (in == 'z' || in == 'Z') goto menue3_4;	//Z.����
										else back = 1;
									} while (back);
								}
								else back = 1;
								break;
							case '3':		//ѡ��--3.4.3.�̿�֮��
								if (enchantment[in - 49])
								{
									display(0, 50);
									display(1, 20);
									printf("�̿�֮��\n\n����С��%dʱ��������50%%\n\n\nX.ʹ�� Z.����\n", weapon_special_judge_0);
									display(1, 20);
									do {
										back = 0;
										in = getch();
										if (in == 'x' || in == 'X')		//X.ʹ��
										{
											enchantment[2]--;
											enchantment_mod = 3;
											display(0, 50);
											display(1, 20);
											printf("���佣����Ŷ\n");
											display(1, 20);
											getch();
										}
										else if (in == 'z' || in == 'Z') goto menue3_4;	//Z.����
										else back = 1;
									} while (back);
								}
								else back = 1;
								break;
							case '4':		//ѡ��--3.4.4.�ѻ��ֵ����
								if (enchantment[in - 49])
								{
									display(0, 50);
									display(1, 20);
									printf("�ѻ��ֵ����\n\n�������%dʱ��������50%%\n\n\nX.ʹ�� Z.����\n",weapon_special_judge_1);
									display(1, 20);
									do {
										back = 0;
										in = getch();
										if (in == 'x' || in == 'X')		//X.ʹ��
										{
											enchantment[3]--;
											enchantment_mod = 4;
											display(0, 50);
											display(1, 20);
											printf("�;ѻ�ǹ����Ŷ\n");
											display(1, 20);
											getch();
										}
										else if (in == 'z' || in == 'Z') goto menue3_4;	//Z.����
										else back = 1;
									} while (back);
								}
								else back = 1;
								break;
							case 'z':
								goto menue3;
								break;
							case 'Z':
								goto menue3;
								break;
							default:
								back = 1;
								break;
							}
						} while (back);
						break;
					case 'z':
						goto menue0;
						break;
					case 'Z':
						goto menue0;
						break;
					default:
						back = 1;
						break;
					}
				} while (back);
				break;
			case '4':	//ѡ��--4.װ��
			menue4:
				display(0, 50);
				display(1, 20);
				printf("1.��ս 2.Զ�� 3.����\n\nZ.����\n");
				display(1, 20);
				do {
					int i = 0;
					back = 0;
					in = getch();
					switch (in)
					{
					case '1':	//ѡ��--4.1.��ս
					menue4_1:
						i = 0;
						display(0, 50);
						display(1, 20);
						printf("��ս����\n\n");
						if (weapon_short[0]) { printf("1.��ì  "); i++; }
						if (weapon_short[1]) { printf("2.�洫���佣  "); i++; }
						if (weapon_short[2]) { printf("3.�㶾ذ��  "); i++; }
						if (weapon_short[3]) { printf("4.��Ѫ��  "); i++; }
						if (i == 0)
						{
							printf("�������һ��\n");
							display(1, 20);
							getch();
							goto menue4;
						}
						printf("\n\n\n*��ǰװ��:");//��ǰװ����ʾ
						if (weapon_short_mod == 0)printf("��\n");
						else if (weapon_short_mod == 1)printf("��ì\n");
						else if (weapon_short_mod == 2)printf("�洫���佣\n");
						else if (weapon_short_mod == 3)printf("�㶾ذ��\n");
						else if (weapon_short_mod == 4)printf("��Ѫ��\n");
						printf("\nZ.����\n");
						display(1, 20);
						do {
							back = 0;
							in = getch();
							switch (in)
							{
							case '1':		//ѡ��--4.1.1.��ì
								if (weapon_short[in - 49])
								{
									display(0, 50);
									display(1, 20);
									printf("��ì\n\n��ս������+100 ��ս��������+50\n\n*����:25%%�����������ֵ15%%�Ķ����˺�\n\n\nX.װ�� Z.����\n");
									display(1, 20);
									do {
										back = 0;
										in = getch();
										if (in == 'x' || in == 'X')		//X.ʹ��
										{
											weapon_short_mod = 1;
											buff_short_damage = 100;
											buff_short_range = 50;
											buff_short_critical = 0;
											display(0, 50);
											display(1, 20);
											printf("*��װ���˳�ì\n");
											display(1, 20);
											getch();
											goto menue0;
										}
										else if (in == 'z' || in == 'Z') goto menue4_1;	//Z.����
										else back = 1;
									} while (back);
								}
								else back = 1;
								break;
							case '2':		//ѡ��--4.1.2.�洫���佣
								if (weapon_short[in - 49])
								{
									display(0, 50);
									display(1, 20);
									printf("�洫���佣\n\n��ս������+200 ��ս������+20%% ��ս��������-30\n\n*����:����С��%dʱ��������˺�\n\n\n�������Ǹϵ�ˮ��ʱ��ֻʣ���������\n\n\nX.װ�� Z.����\n", weapon_special_judge_0);
									display(1, 20);
									do {
										back = 0;
										in = getch();
										if (in == 'x' || in == 'X')		//X.ʹ��
										{
											weapon_short_mod = 2;
											buff_short_damage = 200;
											buff_short_critical = 20;
											buff_short_range = -30;
											display(0, 50);
											display(1, 20);
											printf("*��װ�����洫���佣\n");
											display(1, 20);
											getch();
											goto menue0;
										}
										else if (in == 'z' || in == 'Z') goto menue4_1;	//Z.����
										else back = 1;
									} while (back);
								}
								else back = 1;
								break;
							case '3':		//ѡ��--4.1.3.�㶾ذ��
								if (weapon_short[in - 49])
								{
									display(0, 50);
									display(1, 20);
									printf("�㶾ذ��\n\n��ս������+300 ��ս��������+10\n\n*�綾:������3�غ���ÿ�غ����160���˺�\n\n\nX.װ�� Z.����\n");
									display(1, 20);
									do {
										back = 0;
										in = getch();
										if (in == 'x' || in == 'X')		//X.ʹ��
										{
											weapon_short_mod = 3;
											buff_short_damage = 300;
											buff_short_range = 10;
											buff_short_critical = 0;
											if (rand() % 100 + 1 <= 5)
											{
												display(0, 50);
												display(1, 20);
												printf("��ѵ�����Ϳ�˶���(��)\n");
												display(1, 20);
												getch();
												display(0, 50);
												display(1, 20);
												printf("������!\n\n\n=v=:���������ⱨӦ�˰�\n");
												display(1, 20);
												getch();
												return 0;
											}
											display(0, 50);
											display(1, 20);
											printf("*װ���˴㶾ذ��\n");
											display(1, 20);
											getch();
											goto menue0;
										}
										else if (in == 'z' || in == 'Z') goto menue4_1;	//Z.����
										else back = 1;
									} while (back);
								}
								else back = 1;
								break;
							case '4':		//ѡ��--4.1.4.��Ѫ��
								if (weapon_short[in - 49])
								{
									display(0, 50);
									display(1, 20);
									printf("��Ѫ��\n\n��ս������+350 ��ս��������+30 ��ս������-20%%\n\n*��Ѫ:�ָ��˺�10%%������ֵ\n\n\nX.װ�� Z.����\n");
									display(1, 20);
									do {
										back = 0;
										in = getch();
										if (in == 'x' || in == 'X')		//X.ʹ��
										{
											weapon_short_mod = 4;
											buff_short_damage = 350;
											buff_short_range = 30;
											buff_short_critical = -20;
											display(0, 50);
											display(1, 20);
											printf("*��װ������Ѫ��\n");
											display(1, 20);
											getch();
											goto menue0;
										}
										else if (in == 'z' || in == 'Z') goto menue4_1;	//Z.����
										else back = 1;
									} while (back);
								}
								else back = 1;
								break;
							case 'z':
								goto menue4;
								break;
							case 'Z':
								goto menue4;
								break;
							default:
								back = 1;
								break;
							}
						} while (back);
						break;
					case '2':	//ѡ��--4.2.Զ��
					menue4_2:
						i = 0;
						display(0, 50);
						display(1, 20);
						printf("Զ������\n\n");
						if (weapon_long[0]) { printf("1.����  "); i++; }
						if (weapon_long[1]) { printf("2.�ѻ�ǹ  "); i++; }
						if (i == 0)
						{
							printf("�������һ��\n");
							display(1, 20);
							getch();
							goto menue4;
						}
						printf("\n\n\n*��ǰװ��:");//��ǰװ����ʾ
						if (weapon_long_mod == 0)printf("��\n");
						else if (weapon_long_mod == 1)printf("����\n");
						else if (weapon_long_mod == 2)printf("�ѻ�ǹ\n");
						printf("\nZ.����\n");
						display(1, 20);
						do {
							back = 0;
							in = getch();
							switch (in)
							{
							case '1':		//ѡ��--4.2.1.����
								if (weapon_long[in - 49])
								{
									display(0, 50);
									display(1, 20);
									printf("����\n\nԶ�̹����˺�+150 Զ�̹�������+100 Զ�̱�����+10\n\n*˫�ش��:������Ϊ���Σ����60%%��70%%���˺�\n\n\nX.װ�� Z.����\n");
									display(1, 20);
									do {
										back = 0;
										in = getch();
										if (in == 'x' || in == 'X')		//X.ʹ��
										{
											weapon_long_mod = 1;
											buff_long_damage = 150;
											buff_long_range = 100;
											buff_long_critical = 10;
											display(0, 50);
											display(1, 20);
											printf("*��װ��������\n");
											display(1, 20);
											getch();
											goto menue0;
										}
										else if (in == 'z' || in == 'Z') goto menue4_2;	//Z.����
										else back = 1;
									} while (back);
								}
								else back = 1;
								break;
							case '2':		//ѡ��--4.2.2.�ѻ�ǹ
								if (weapon_long[in - 49])
								{
									display(0, 50);
									display(1, 20);
									printf("�ѻ�ǹ\n\nԶ�̹�����+300 Զ�̹�������+200 ������-20%%\n\n*��׼���:�������%dʱԶ�̹������200%%�˺�\n\n\nX.װ�� Z.����\n", weapon_special_judge_1);
									display(1, 20);
									do {
										back = 0;
										in = getch();
										if (in == 'x' || in == 'X')		//X.ʹ��
										{
											weapon_long_mod = 2;
											buff_long_damage = 300;
											buff_long_range = 200;
											buff_long_critical = -20;
											display(0, 50);
											display(1, 20);
											printf("*��װ���˾ѻ�ǹ -��4750\n");
											display(1, 20);
											getch();
											goto menue0;
										}
										else if (in == 'z' || in == 'Z') goto menue4_2;	//Z.����
										else back = 1;
									} while (back);
								}
								else back = 1;
								break;
							case 'z':
								goto menue4;
								break;
							case 'Z':
								goto menue4;
								break;
							default:
								back = 1;
								break;
							}
						} while (back);
						break;
					case '3':	//ѡ��--4.3.����
					menue4_3:
						i = 0;
						display(0, 50);
						display(1, 20);
						printf("����\n\n");
						if (weapon_magic[0]) { printf("1.����֮��  "); i++; }
						if (weapon_magic[1]) { printf("2.֧Ԯ����  "); i++; }
						if (weapon_magic[2]) { printf("3.�ػ���֮��  "); i++; }
						if (i == 0)
						{
							printf("�������һ��\n");
							display(1, 20);
							getch();
							goto menue4;
						}
						printf("\n\n\n*��ǰװ��:");//��ǰװ����ʾ
						if (weapon_magic_mod == 0)printf("��\n");
						else if (weapon_magic_mod == 1)printf("����֮��\n");
						else if (weapon_magic_mod == 2)printf("֧Ԯ����\n");
						else if (weapon_magic_mod == 3)printf("�ػ���֮��\n");
						printf("\nZ.����\n");
						display(1, 20);
						do {
							back = 0;
							in = getch();
							switch (in)
							{
							case '1':		//ѡ��--4.3.1.����֮��
								if (weapon_magic[in - 49])
								{
									display(0, 50);
									display(1, 20);
									printf("����֮��\n\nħ��+45%%\n\n*����:ʹ�á��鿴��ʱ����������\n\n\nX.װ�� Z.����\n");
									display(1, 20);
									do {
										back = 0;
										in = getch();
										if (in == 'x' || in == 'X')		//X.ʹ��
										{
											weapon_magic_mod = 1;
											buff_magic = 45;
											display(0, 50);
											display(1, 20);
											printf("*��װ���˶���֮��\n");
											display(1, 20);
											getch();
											goto menue0;
										}
										else if (in == 'z' || in == 'Z') goto menue4_3;	//Z.����
										else back = 1;
									} while (back);
								}
								else back = 1;
								break;
							case '2':		//ѡ��--4.3.2.֧Ԯ����
								if (weapon_magic[in - 49])
								{
									display(0, 50);
									display(1, 20);
									printf("֧Ԯ����\n\nħ��+30%%\n\n*����:�غϽ��������Ӿ��뷢��һ�������������%.lf���˺�\n\n\nX.װ�� Z.����\n", 100.0 * (p_magic + buff_magic) / 100);
									display(1, 20);
									do {
										back = 0;
										in = getch();
										if (in == 'x' || in == 'X')		//X.ʹ��
										{
											weapon_magic_mod = 2;
											buff_magic = 40;
											display(0, 50);
											display(1, 20);
											printf("*��װ����֧Ԯ����\n");
											display(1, 20);
											getch();
											goto menue0;
										}
										else if (in == 'z' || in == 'Z') goto menue4_3;	//Z.����
										else back = 1;
									} while (back);
								}
								else back = 1;
								break;
							case '3':		//ѡ��--4.3.3.�ػ���֮��
								if (weapon_magic[in - 49])
								{
									display(0, 50);
									display(1, 20);
									printf("�ػ���֮��\n\nħ��+20%%\n\n*����:�غϽ���������ֵ+%.lf ����ֵ+%.lf\n\n*��������:����ֵ����70ʱ�ָ���200(��һ��)\n\n\nX.װ�� Z.����\n",25.0*(p_magic+buff_magic)/100,6.0*(p_magic+buff_magic)/100);
									display(1, 20);
									do {
										back = 0;
										in = getch();
										if (in == 'x' || in == 'X')		//X.ʹ��
										{
											weapon_magic_mod = 3;
											buff_magic = 20;
											display(0, 50);
											display(1, 20);
											printf("*��װ�����ػ���֮��\n");
											display(1, 20);
											getch();
											goto menue0;
										}
										else if (in == 'z' || in == 'Z') goto menue4_3;	//Z.����
										else back = 1;
									} while (back);
								}
								else back = 1;
								break;
							case 'z':
								goto menue4;
								break;
							case 'Z':
								goto menue4;
								break;
							default:
								back = 1;
								break;
							}
						} while (back);
						break;
					case 'z':
						goto menue0;
						break;
					case 'Z':
						goto menue0;
						break;
					default:
						back = 1;
						break;
					}
				} while (back);
				break;
			default:
				back = 1;
				break;
			}
		} while (back);		//��Ҳ�������
		display(0, 50);
		display(1, 20);
		printf("�غϽ���\n");
		display(1, 20);
		getch();

		if (p_hp > 0 && b_hp > 0)	//����Ч��
		{
			display(0, 50);
			display(1, 20);
			p_VIT += 10;
			printf("����+10\n");	//�Զ��ظ�����
			if (timer[4]) { timer[4]--; printf("�͸�:�ָ�%.lf������ֵ\n", \
				0.1 * (p_magic + buff_magic)); p_hp += p_hp * 0.1 * (p_magic + buff_magic)/100;}				//����:�͸�
			if (timer[5]) {timer[5]--; printf("����:���%.lf���˺�\n", \
				b_hp*0.05 * (p_magic + buff_magic)/100); b_hp -= b_hp * 0.05 * (p_magic + buff_magic) / 100;}		//����:����
			if (timer[6]) { timer[6]--; printf("*�綾:���160���˺�\n"); b_hp -= 160; }							//����:�㶾ذ��
			if (weapon_magic_mod == 2) { printf("*����:���%.lf���˺�\n", \
				100.0 * (p_magic + buff_magic) / 100); b_hp -= 100.0 * (p_magic + buff_magic) / 100; }			//֧Ԯ����:����
			if (weapon_magic_mod == 3) { printf("*����:����ֵ+%.lf  ����+%.lf\n", \
				25.0 * (p_magic + buff_magic) / 100, 6.0 * (p_magic + buff_magic) / 100); p_hp += 25.0 * (p_magic + buff_magic) / 100, p_VIT += 6.0 * (p_magic + buff_magic) / 100; }	//�ػ���֮��:����
			if (weapon_magic_mod == 3 && p_hp < 70 && k) { p_hp = 200; k = 0; printf("*������������,����ֵ�ָ���200\n"); }	//�ػ���֮��:��������
			display(1, 20);
			getch();
		}
		if (p_hp > p_hp_max)p_hp = p_hp_max;//�������Ѫ�����
		if (b_hp > b_hp_max)b_hp = b_hp_max;//����BOSSѪ�����
		if (p_dodge > 70)p_dodge = 70;		//��������������
		if (p_hp > 0 && b_hp > 0)	//BOSS�غ�
		{
			display(0, 50);
			display(1, 20);
			printf("=v=�Ļغ�\n");
			display(1, 20);
			getch();
			display(0, 50);
			display(1, 20);
			if (timer[0])	//����:��˯���
			{
				timer[0]--;
				printf("=v=˯����\n");
			}
			else	//BOSS�ж�
			{
				if (boss_special && p_hp * 1.5 >= b_hp)	//���⼼��:��ˮһս
				{
					boss_special = 0;
					printf("*=v=���������⼼��:��ˮһս\n\n\n");
					printf("����ֵ%+d  ������%+.lf  �ƶ��ٶ�%+.lf  ������+%d%% ��������%+d\n", p_hp * 5 - b_hp, b_strength * 1.5 - b_strength, 60 - b_speed, 30, b_attack_range * 1.5 - b_attack_range);
					b_hp = 5 * p_hp;
					b_strength = 1.5 * b_strength;
					b_speed = 60;
					b_dodge += 30;
					b_attack_range = b_attack_range * 1.5;
				}
				else if (b_hp <= 1.5 * p_hp || b_hp >=3 * p_hp)	//����
				{
					if (range <= b_attack_range)	//�����㹻--����
					{
						printf("=v=������һ��\n\n");
						if (rand() % 100 + 1 <= p_dodge)
							printf("*��㿪��\n");
						else
						{
							if (rand() % 100 + 1 <= b_critical)	//����
							{
								printf("�����˱���:");
								damage = 2 * b_strength;
							}
							else damage = b_strength;	//δ����
							if (timer[3])	//����:����ҩˮ
							{
								damage *= 0.7;
								timer[3]--;
							}
							p_hp -= damage;	//�����չ��˺�
							printf("�����%d���˺�\n", damage);
						}
					}
					else if (range >= b_attack_range)	//���벻��--׷��
					{
						range -= b_speed;
						if (range <= 0)range = 0;
						printf("=v=�����˳��,����-%d \n\n*��ǰ����:%d\n", b_speed, range);
						b_hp += 50;
						printf("*=v=����ֵ+50\n");
					}
				}
				else if (b_hp > 2 * p_hp && b_hp < 3 * p_hp)	//����
				{
					printf("���Ӥ������衱\n=v=�����ˣ�����+%d\n\n",b_speed);
					range += b_speed;
					printf("*��ǰ����:%d\n*=v=����ֵ+150\n",range);
					b_hp += 150;
				}
				b_strength++;	//boss����������
			}
			if (b_hp > b_hp_max)b_hp = b_hp_max;//����BOSSѪ�����
			if (b_dodge > 70)b_dodge = 70;		//����BOSS�������
			display(1, 20);
			getch();
		}//BOSS�غϽ���
	}//��Ϸ����
	//��ʾ���
	display(0, 50);
	display(1, 20);
	if (b_hp <= 0 && p_hp > 0)	//BOSS����  ��Ҵ��
	{
		if (p_magic + buff_magic > 200)	//��ħ��ʦ:���ߴ�����
		{
			printf("=v=�ڵ���ǰ�ų���*���ߴ�����\n\n�������������ֵ105%%���˺�\n\n*����ֵ-%.lf\n", p_hp * 1.05);
			p_hp -= p_hp * 1.05;
			display(1, 20);
			getch();
			display(0, 50);
			display(1, 20);
			if (p_hp > b_hp)printf("�㻹��ȡ����ʤ��\n\n");
			else if (p_hp < b_hp)printf("=v=�ó���\n\n");
			else printf("�������Ǵ����ƽ��\n\n");
			printf("*�������ֵ:%d\n*=v=������ֵ:%d\n", p_hp, b_hp);
		}
		else
		{
			printf("=v=������...\n");
			display(1, 20);
			display(0, 50);
			display(1, 20);
			printf("��Ҫͣ������!\n");
		}
	}
	else if (b_hp > 0 && p_hp <= 0)	//BOSS���	��ҵ���
	{
		printf("��Ү ���������Ү\n\n��֪������˭���ϴ����\n");
	}
	else if (b_hp <= 0 && p_hp <= 0)	//BOSS����Ҷ�����
	{
		printf("�ǣ�û�뵽����������Ľ��\n\n*����=v=��������\n");
	}
	else printf("Ӧ�ò��������������...?\n");
	display(1, 20);
	getch();


	return 0;
}


void initialization(int* a, int n, int k)//��ʼ�����飨����, ��С��Ŀ��ֵ��
{
	for (int i = 0; i < n; a[i++] = k);
}
void display(int type,int n)//��ʾ�������������ͣ������� 0������ 1������(��β����)���� 2:�ո�(��β�޻���)
{
	switch (type)
	{
	case 0:		//0.����
		if (n == 50)	//�����Ż�
		{
			printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\
				\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
			break;
		}

		for (int i = 0; i < n; i++)
			printf("\n");
		break;
	case 1:		//1.����
		
		if (n == 20)	//�����Ż�
		{
			printf("\n��������������������������������������������������������������������������������\n\n");
			break;
		}

		printf("\n");
		for (int i = 0; i < n; i++)
			printf("����");
		printf("\n\n");
		break;
	case 2:		//2.�ո�
		for (int i = 0; i < n; i++)
			printf(" ");
		break;
	default:
		break;
	}
}
