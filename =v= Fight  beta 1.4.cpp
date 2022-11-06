#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>

void initialization(int* a, int n, int k);//初始化数组（数组, 大小，目标值）
void display(int type,int n);//显示操作（操作类型，次数） 0：换行 1：横线(结尾换行)—— 2:空格(结尾无换行)

int main()
{
	//玩家
		//数量:
				//近战武器数量		 远程武器数量       道具数量    武器附魔书数量       法杖数量          魔法数量       经验书数量     计时器数量
		const int weapon_short_n = 4, weapon_long_n = 2, prop_n = 7, enchantment_n = 4, weapon_magic_n = 3, magic_n = 4, levelbook_n = 3, timer_n = 7;

		//玩家基本属性:
					//  血量          力量             闪避率        暴击率          探索幸运值   体力值           
					int p_hp = 1000, p_strength = 100, p_dodge = 10, p_critical = 20, p_luck = 0, p_VIT = 100, \
						//近战攻击距离                远程攻击距离           移动速度        魔法
						p_attack_range_short = 70, p_attack_range_long = 0, p_speed = 20, p_magic = 100;	
					//  力量基准值						暴击率基准值
					int p_strength_origin = p_strength, p_critical_origin = p_critical, p_hp_max = p_hp;

		//装备: 
				//近战武器                       远程武器                        道具              武器附魔书                     
			int weapon_short[weapon_short_n], weapon_long[weapon_long_n], prop[prop_n], enchantment[enchantment_n], \
				//法杖                           魔法                经验书
				weapon_magic[weapon_magic_n], magic[magic_n], levelbook[levelbook_n];

		//效果:	
			// 多回合效果计数器  装备的远程武器      装备的近战武器        近战攻击力增益         近战攻击距离增益      近战暴击率增益			 魔法增益
			int timer[timer_n], weapon_long_mod = 0, weapon_short_mod = 0, buff_short_damage = 0, buff_short_range = 0, buff_short_critical = 0, buff_magic = 0, \
				//远程攻击力增益      远程攻击距离增益		远程暴击率增益         袖剑特殊效果				    狙击枪特殊效果				  装备的附魔		   装备的法杖
				buff_long_damage = 0, buff_long_range = 0, buff_long_critical = 0, weapon_special_judge_0 = 30, weapon_special_judge_1 = 130, enchantment_mod = 0, weapon_magic_mod = 0, \
				//愈战愈勇效果           一鼓作气效果			守护者之杖:救主灵刃
				enchatment_judge_0 = 0, enchatment_judge_1 = 0, k = 1;
	
	//BOSS
		//BOSS基本属性:
				//  血量          攻击力            闪避率       暴击率           攻击距离              移动速度
				int b_hp = 10000, b_strength = 20, b_dodge = 20, b_critical = 20, b_attack_range = 100, b_speed = 35;
				
				int boss_special = 1, b_hp_max = b_hp;

	//其他
				int range = 0;		//距离
				int damage = 0;	//伤害
				int in;				//输入
				int back = 0;		//返回

	//初始化
	initialization(weapon_short, weapon_short_n,0);		//初始化 近战武器	-> 0
	initialization(weapon_long, weapon_long_n,0);		//初始化 远程武器	-> 0
	initialization(prop, prop_n,0);						//初始化 道具		-> 0
	initialization(enchantment, enchantment_n,0);		//初始化 武器附魔书 -> 0
	initialization(weapon_magic, weapon_magic_n,0);		//初始化 法杖		-> 0
	initialization(magic, magic_n,0);					//初始化 魔法		-> 0
	initialization(levelbook, levelbook_n, 0);			//初始化 经验书		-> 0
	initialization(timer, timer_n, 0);					//初始化 计时器		-> 0
	

	while (p_hp > 0 && b_hp > 0)
	{
		srand(time(NULL));//重置随机数种子
		//玩家回合开始
	menue0:
		display(0, 50);
		display(1, 20);
		printf("你的回合\n\n生命值:%d 体力值:%d 距离:%d\n\n1.攻击 2.行动 3.背包 4.装备\n", p_hp, p_VIT, range);
		display(1, 20);
		do {
			back = 0;
			in = getch();
			switch (in)
			{
			case '1':	//选项--1.攻击
				damage = 0;
				display(0, 50);
				display(1, 20);
				if (p_attack_range_short + buff_short_range >= range)				//近战
				{
					p_strength = p_strength_origin + buff_short_damage; 
					if (timer[2]) { p_strength *= 1.3; timer[2]--; }	//道具效果:力量药水
					if (enchantment_mod==3 && range < weapon_special_judge_0)p_strength *= 1.5;	//附魔效果:刺客之刃
					else if (enchantment_mod == 4 && range > weapon_special_judge_1)p_strength *= 1.5;	//附魔效果:狙击手的矜持
					p_critical = p_critical_origin + buff_short_critical;
					if (weapon_short_mod == 2 && range < weapon_special_judge_0)p_strength *= 3;	//袖剑三倍伤害
					//普通攻击
					if (rand() % 100 + 1 <= b_dodge && timer[0] == 0)	//被闪避
					{
						damage = 0;
						printf("=v=躲开了你的攻击\n");
					}
					else								//未被闪避
					{
						printf("对=v=发起了近战攻击\n\n");
						if (enchantment_mod)	//附魔显示
						{
							if (enchantment_mod == 1)	//附魔显示:愈战愈勇
							{printf("#愈战愈勇:%d%%\n\n", enchatment_judge_0);}
							else if (enchantment_mod == 2)	//附魔显示:一鼓作气
							{printf("#一鼓作气:%d%%\n\n", enchatment_judge_1);}
							else if (enchantment_mod == 3 && range < weapon_special_judge_0)	//附魔显示:刺客之刃
							{printf("#刺客之刃\n\n");}
							else if (enchantment_mod == 4 && range > weapon_special_judge_1)	//附魔显示:狙击手的矜持
							{printf("#狙击手的矜持\n\n");}
						}
						printf("\n");
						if (rand() % 100 + 1 <= p_critical)	//暴击判定
						{
							damage = 2 * p_strength;
							printf("触发了暴击:");
						}
						else
						{
							damage = p_strength;
						}
					}
					if (damage)	//附魔效果
					{
						if (enchantment_mod == 1)	//附魔效果:愈战愈勇
						{
							damage *= 1.0 * enchatment_judge_0 / 100;
							if (enchatment_judge_0 < 150)enchatment_judge_0 += 10;
						}
						else if (enchantment_mod == 2)	//附魔效果:一鼓作气
						{
							damage *= 1.0 * enchatment_judge_1 / 100;
							if (enchatment_judge_1 > 80)enchatment_judge_1 -= 10;
						}
						printf("造成了%d伤害\n", damage);
					}
					b_hp -= damage;	//结算普通攻击伤害

					//武器特殊效果
					if (weapon_short_mod && damage)		
					{
						if (weapon_short_mod == 1)		//长矛:穿刺
						{
							if (rand() % 100 + 1 <= 25)
							{
								damage = b_hp * 0.15;
								b_hp -= damage;
								printf("\n*穿刺:造成%d点伤害\n", damage);
							}
						}
						else if (weapon_short_mod == 2 && range < weapon_special_judge_0)	//祖传的袖剑:三倍伤害
						{
							printf("\n*背刺:三倍伤害\n");
						}
						else if (weapon_short_mod == 3)	//淬毒匕首:持续伤害
						{
							timer[6] = 3;
							printf("\n* =v=中毒了\n");
						}
						else if (weapon_short_mod == 4)	//饮血剑:吸血
						{
							damage /= 10;
							p_hp += damage;
							printf("\n*吸血:回复了%d点生命值\n",damage);
						}
					}
				}
				else if (weapon_long_mod && p_attack_range_long + buff_long_range >= range - p_attack_range_short - buff_short_range)	//远程
				{
					p_strength = p_strength_origin + buff_long_damage;
					if (timer[2]) { p_strength *= 1.3; timer[2]--; }	//道具效果:力量药水
					if (enchantment_mod == 3 && range < weapon_special_judge_0)p_strength *= 1.5;	//附魔效果:刺客之刃
					else if (enchantment_mod == 4 && range > weapon_special_judge_1)p_strength *= 1.5;	//附魔效果:狙击手的矜持
					p_critical = p_critical_origin + buff_long_critical;
					int i = 1;
					if (weapon_long_mod == 1)//连弩:双重打击
					{
						i = 2;
						printf("*双重打击\n\n");
					}
					for (; i; i--)
					{
						int t_strength = p_strength;
						if (weapon_long_mod == 1)//连弩:两段攻击
						{
							if (i == 2)t_strength *= 0.6;
							if (i == 1)t_strength *= 0.7;
						}
						if (rand() % 100 + 1 <= b_dodge && timer[0] == 0)	//被闪避
						{
							damage = 0;
							printf("=v=躲开了你的攻击\n");
						}
						else								//未被闪避
						{
							printf("对=v=发起了远程攻击\n\n");
							if (enchantment_mod)	//附魔显示
							{
								if (enchantment_mod == 1)	//附魔显示:愈战愈勇
								{
									printf("#愈战愈勇:%d%%\n\n", enchatment_judge_0);
								}
								else if (enchantment_mod == 2)	//附魔显示:一鼓作气
								{
									printf("#一鼓作气:%d%%\n\n", enchatment_judge_1);
								}
								else if (enchantment_mod == 3 && range < weapon_special_judge_0)	//附魔显示:刺客之刃
								{
									printf("#刺客之刃\n\n");
								}
								else if (enchantment_mod == 4 && range > weapon_special_judge_1)	//附魔显示:狙击手的矜持
								{
									printf("#狙击手的矜持\n\n");
								}
							}
							printf("\n");
							if (rand() % 100 + 1 <= p_critical)		//暴击判定
							{
								damage = 2 * t_strength;
								printf("触发了暴击:");
							}
							else
							{
								damage = t_strength;
							}
						}
						if (damage && weapon_long_mod == 2 && range > weapon_special_judge_1)	//狙击枪:精准打击
							damage *= 2;
						if (damage)	//附魔效果
						{
							if (enchantment_mod == 1)	//附魔效果:愈战愈勇
							{
								damage *= 1.0 * enchatment_judge_0 / 100;
								if (enchatment_judge_0 < 150)enchatment_judge_0 += 10;
							}
							else if (enchantment_mod == 2)	//附魔效果:一鼓作气
							{
								damage *= 1.0 * enchatment_judge_1 / 100;
								if (enchatment_judge_1 > 80)enchatment_judge_1 -= 10;
							}
							printf("造成了%d伤害\n", damage);
						}
						b_hp -= damage;		//结算普通攻击伤害
						if (i == 2)printf("\n");
						
					}
					if (damage && weapon_long_mod == 2 && range > weapon_special_judge_1)		//狙击枪
					{
						printf("\n*精准打击\n");
					}
				}
				else	//攻击距离不足
				{
					printf("距离=v=太远了\n");
				}
				display(1, 20);
				getch();
				break;

			case '2':	//选项--2.行动
			menue2:
				display(0, 50);
				display(1, 20);
				printf("行动\n\n1.查看 2.探索 3.靠近 4.休息\n\nZ.返回\n");
				display(1, 20);
				do {
					back = 0;
					in = getch();
					switch (in)
					{
					case '1':	//选项--2.1查看
						display(0, 50);
						display(1, 20);
						if (p_VIT < 10)//体力不足
						{
							printf("*至少需要10点体力\n");
							display(1, 20);
							getch();
							goto menue2;
						}
						printf("玩家:\n\n力量:%d  魔法:%d%%   暴击率(近战):%d%%   暴击率(远程):%d%%\n\n攻击距离(近战):%d   攻击距离(远程):%d   闪避率:%d%%   移动速度:%d\n\n\n"\
							, p_strength_origin, p_magic+buff_magic, p_critical_origin + buff_short_critical, p_critical_origin + buff_long_critical, p_attack_range_short+buff_short_range, p_attack_range_long+buff_long_range, p_dodge, p_speed);
						printf("=v=:\n\n生命值:%d   攻击力:%d  暴击率:%d%%  闪避率:%d%%\n\n攻击距离:%d  移动速度:%d\n"\
							, b_hp,b_strength,b_critical,b_dodge,b_attack_range,b_speed);
						if (weapon_magic_mod != 1)
						{
							printf("\n\n*体力-10");
							p_VIT -= 10;
						}
						display(1, 20);
						getch();
						goto menue2;
						break;
					case '2':	//选项--2.2探索
					menue2_2:
						if (p_VIT >= 20||timer[1])
						{
							display(0, 50);
							display(1, 20);
							printf("1.货舱                  速度要求:20\n\n");
							printf("2.军备库                速度要求:30\n\n");
							printf("3.典藏馆                速度要求:50\n\n");
							printf("4.沼泽中的女巫小屋      速度要求:80\n\n\n");
							printf("*当前移动速度:%d\n\n", p_speed);
							printf("Z.返回\n");
							display(1, 20);
							do {
								back = 0;
								in = getch();
								int judge;
								switch (in)
								{
								case '1':		//选项--2.2.1.货舱
									if (p_speed < 20)
									{
										back = 1;
										break;
									}
									display(0, 50);
									display(1, 20);
									if (p_VIT < 20 && timer[1] == 0)	//体力不足
									{
										printf("*至少需要20点体力\n");
										display(1, 20);
										getch();
										goto menue2_2;
									}
									printf("距离+20");
									if (timer[1] == 0)printf("  体力-20");
									else printf("  肾上腺素回合剩余:%d", timer[1]-1);
									printf("\n\n");
									if (timer[1])timer[1]--;
									else p_VIT -= 20;
									range += 20;
									judge = rand() % 100 + 1;
									if (judge <= 95)//收获
									{
										printf("获得:");
										judge = rand() % 100 + 1;
										if (judge <= 70)	//道具
										{
											judge = rand() % 100 + 1;
											if (judge <= 30) { prop[0]++; printf("生命药水\n"); }
											else if (judge <= 50) { prop[1]++; printf("体力药水\n"); }
											else if (judge <= 60) { prop[2]++; printf("昏睡红茶\n"); }
											else if (judge <= 65) { prop[3]++; printf("命运骰子\n"); }
											else if (judge <= 75) { prop[4]++; printf("肾上腺素\n"); }
											else if (judge <= 85) { prop[5]++; printf("力量药水\n"); }
											else if (judge <= 100) { prop[6]++; printf("虚弱药水\n"); }
										}
										else if (judge <= 100)	//经验书
										{
											judge = rand() % 100 + 1;
											if (judge <= 30) { levelbook[0]++; printf("《芝士就是_ _!》\n"); }
											else if (judge <= 90) { levelbook[1]++; printf("《盗窃:从入门到入狱》\n"); }
											else if (judge <= 100) { levelbook[2]++; printf("《麻瓜的烹饪方式》\n"); }
										}
									}
									else//一无所获
									{printf("*一无所获\n");}
									display(1, 20);
									getch();
									break;
								case '2':		//选项--2.2.2.军备库 
									if (p_speed < 30)
									{
										back = 1;
										break;
									}
									display(0, 50);
									display(1, 20);
									if (p_VIT < 30 && timer[1] == 0)	//体力不足
									{
										printf("*至少需要30点体力\n");
										display(1, 20);
										getch();
										goto menue2_2;
									}
									printf("距离+30");
									if (timer[1] == 0)printf("  体力-30");
									else printf("  肾上腺素回合剩余:%d", timer[1]-1);
									printf("\n\n");
									if (timer[1])timer[1]--;
									else p_VIT -= 30;
									range += 30;
									judge = rand() % 100 + 1;
									if (judge <= 90)//收获
									{
										
										printf("获得:");
										judge = rand() % 100 + 1;
										if (judge <= 30)	//道具
										{
											judge = rand() % 100 + 1;
											if (judge <= 30) { prop[0]++; printf("生命药水\n"); }
											else if (judge <= 50) { prop[1]++; printf("体力药水\n"); }
											else if (judge <= 70) { prop[4]++; printf("肾上腺素\n"); }
											else if (judge <= 90) { prop[5]++; printf("力量药水\n"); }
											else if (judge <= 100) { prop[6]++; printf("虚弱药水\n"); }
										}
										else if (judge <= 50)	//远程武器
										{
											judge = rand() % 100 + 1;
											if (judge <= 60) { weapon_long[0]++; printf("连弩\n"); }
											else if (judge <= 100) { weapon_long[1]++; printf("狙击枪\n"); }
										}
										else if (judge <= 80)	//近战武器
										{
											judge = rand() % 100 + 1;
											if (judge <= 30) { weapon_short[0]++; printf("长矛\n"); }
											else if(judge <= 50) { weapon_short[1]++; printf("祖传的袖剑\n"); }
											else if (judge <= 80) { weapon_short[2]++; printf("淬毒匕首\n"); }
											else if (judge <= 100) { weapon_short[3]++; printf("饮血剑\n"); }
										}
										else if (judge <= 100)	//经验书
										{
											judge = rand() % 100 + 1;
											if (judge <= 50) { levelbook[0]++; printf("《芝士就是_ _!》\n"); }
											else if (judge <= 90) { levelbook[1]++; printf("《盗窃:从入门到入狱》\n"); }
											else if (judge <= 100) { levelbook[2]++; printf("《麻瓜的烹饪方式》\n"); }
										}
									}
									else//一无所获
									{printf("*一无所获\n");}
									display(1, 20);
									getch();
									break;
								case '3':		//选项--2.2.3.典藏馆
									if (p_speed < 50)
									{
										back = 1;
										break;
									}
									display(0, 50);
									display(1, 20);
									if (p_VIT < 35 && timer[1] == 0)	//体力不足
									{
										printf("*至少需要35点体力\n");
										display(1, 20);
										getch();
										goto menue2_2;
									}
									printf("距离+50");
									if (timer[1] == 0)printf("  体力-35");
									else printf("  肾上腺素回合剩余:%d", timer[1]-1);
									printf("\n\n");
									if (timer[1])timer[1]--;
									else p_VIT -= 35;
									range += 50;
									judge = rand() % 100 + 1;
									if (judge <= 80)//收获
									{
										printf("获得:");
										judge = rand() % 100 + 1;
										if (judge <= 10)	//道具
										{
											judge = rand() % 100 + 1;
											if (judge <= 50) { prop[2]++; printf("昏睡红茶\n"); }
											else if (judge <= 100) { prop[3]++; printf("命运骰子\n"); }
										}
										else if (judge <= 40)	//附魔书
										{
											judge = rand() % 100 + 1;
											if (judge <= 30) { enchantment[0]++; printf("愈战愈勇\n"); }
											else if (judge <= 65) { enchantment[1]++; printf("一鼓作气\n"); }
											else if (judge <= 85) { enchantment[2]++; printf("刺客之刃\n"); }
											else if (judge <= 100) { enchantment[3]++; printf("狙击手的矜持\n"); }
										}
										else if (judge <= 70)	//经验书
										{
											judge = rand() % 100 + 1;
											if (judge <= 25) { levelbook[0]++; printf("《芝士就是_ _!》\n"); }
											else if (judge <= 50) { levelbook[1]++; printf("《盗窃:从入门到入狱》\n"); }
											else if (judge <= 100) { levelbook[2]++; printf("《麻瓜的烹饪方式》\n"); }
										}
										else if (judge <= 80)	//法杖
										{
											judge = rand() % 100 + 1;
											if (judge <= 40) { weapon_magic[0]++; printf("洞察之杖\n"); }
											else if (judge <= 75) { weapon_magic[1]++; printf("支援法杖\n"); }
											else if (judge <= 100) { weapon_magic[2]++; printf("守护者之杖\n"); }
										}
										else if (judge <= 100)	//法术
										{
											judge = rand() % 100 + 1;
											if (judge <= 15) { magic[0]++; printf("祈愿\n"); }
											else if (judge <= 35) { magic[1]++; printf("赐福\n"); }
											else if (judge <= 70) { magic[2]++; printf("天雷\n"); }
											else if (judge <= 100) { magic[3]++; printf("毒雾\n"); }
										}
									}
									else//一无所获
									{printf("*一无所获\n");}
									display(1, 20);
									getch();
									break;
								case '4':		//选项--2.2.4.沼泽中的女巫小屋
									if (p_speed < 80)
									{
										back = 1;
										break;
									}
									display(0, 50);
									display(1, 20);
									if (p_VIT < 50 && timer[1] == 0)	//体力不足
									{
										printf("*至少需要50点体力\n");
										display(1, 20);
										getch();
										goto menue2_2;
									}
									printf("距离+80");
									if (timer[1] == 0)printf("  体力-50");
									else printf("  肾上腺素回合剩余:%d", timer[1]-1);
									printf("\n\n");
									if (timer[1])timer[1]--;
									else p_VIT -= 50;
									judge = rand() % 100 + 1;
									if (judge <= 70)//收获
									{
										printf("获得:");
										judge = rand() % 100 + 1;
										if (judge <= 10)	//道具
										{
											prop[3]++; printf("命运骰子\n");
										}
										else if (judge <= 50)	//法术
										{
											judge = rand() % 100 + 1;
											if (judge <= 25) { magic[0]++; printf("祈愿\n"); }
											else if (judge <= 50) { magic[1]++; printf("赐福\n"); }
											else if (judge <= 75) { magic[2]++; printf("天雷\n"); }
											else if (judge <= 100) { magic[3]++; printf("毒雾\n"); }
										}
										else if (judge <= 80)	//法杖
										{
											judge = rand() % 100 + 1;
											if (judge <= 40) { weapon_magic[0]++; printf("洞察之杖\n"); }
											else if (judge <= 65) { weapon_magic[1]++; printf("支援法杖\n"); }
											else if (judge <= 100) { weapon_magic[2]++; printf("守护者之杖\n"); }
										}
										else if (judge <= 90)	//附魔书
										{
											judge = rand() % 100 + 1;
											if (judge <= 25) { enchantment[0]++; printf("愈战愈勇\n"); }
											else if (judge <= 50) { enchantment[1]++; printf("一鼓作气\n"); }
											else if (judge <= 75) { enchantment[2]++; printf("刺客之刃\n"); }
											else if (judge <= 100) { enchantment[3]++; printf("狙击手的矜持\n"); }
										}
										else if (judge <= 100)	//经验书
										{
											judge = rand() % 100 + 1;
											if (judge <= 5) { levelbook[0]++; printf("《芝士就是_ _!》\n"); }
											else if (judge <= 20) { levelbook[1]++; printf("《盗窃:从入门到入狱》\n"); }
											else if (judge <= 100) { levelbook[2]++; printf("《麻瓜的烹饪方式》\n"); }
										}
									}
									else//一无所获
									{printf("*一无所获\n");}
									display(1, 20);
									getch();
									judge = rand() % 100 + 1;//陷阱判定
									if (judge <= 30)
									{
										display(0, 50);
										display(1, 20);
										printf("离开时你触发了女巫的魔法陷阱\n");
										if(p_magic+buff_magic<200)
										{
											printf("\n受到了%.lf点伤害\n",70-70.0*(p_magic+buff_magic-100)/100);
											if (p_magic + buff_magic < 100) { printf("\n\n*你对魔法了解过少，以至于额外受到了%.lf点伤害\n", -70.0 * (p_magic + buff_magic - 100) / 100); }
											if (p_magic + buff_magic > 100) { printf("\n\n*对魔法的掌握使你及时地用魔法格挡了%.lf点伤害\n", 70.0 * (p_magic + buff_magic - 100) / 100); }
											p_hp -= 70 - 70.0 * (p_magic + buff_magic - 100) / 100;
										}
										else if (p_magic + buff_magic == 200)
										{
											printf("\n对魔法的掌握使你及时地用魔法格挡了全部伤害\n");
										}
										else
										{
											printf("\n身为大魔法师的你随手就将其吸收化为己用\n\n\n*生命值+%.lf",70.0*(p_magic + buff_magic-200)/100);
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
						else	//体力不足
						{
							display(0, 50);
							display(1, 20);
							printf("体力不足,当前体力%d\n\n\n*至少需要20点体力\n", p_VIT);
							display(1, 20);
							getch();
							goto menue2;
						}
						break;
					case '3':	//选项--2.3靠近
						range -= p_speed;
						if (range < 0)range = 0;
						display(0, 50);
						display(1, 20);
						printf("这么说，你很勇哦\n\n距离-%d\n\n\n*当前距离:%d\n",p_speed,range);
						display(1, 20);
						getch();
						break;
					case '4':	//选项--2.4休息
						p_VIT += 60;
						display(0, 50);
						display(1, 20);
						printf("疲惫感油然而生\n\n于是你打算休息一会\n\n\n*体力+60\n");
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

			case '3':	//选项--3.背包
			menue3:
				display(0, 50);
				display(1, 20);
				printf("背包\n\n1.道具 2.法术 3.经验书 4.附魔书\n\nZ.返回\n");
				display(1, 20);
				do {
					back = 0;
					int i = 0;
					in = getch();
					switch (in)
					{
					case '1':	//选项--3.1道具
					menue3_1:
						i = 0;
						display(0, 50);				//道具菜单
						display(1, 20);
						printf("道具\n\n");
						if (prop[0]) { printf("1.生命药水x%d  ", prop[0]); i++; }
						if (prop[1]) { printf("2.体力药水x%d  ", prop[1]); i++; }
						if (prop[2]) { printf("3.昏睡红茶x%d  ", prop[2]); i++; }
						if (prop[3]) { printf("4.命运骰子x%d  ", prop[3]); i++; }
						if (prop[4]) { if (i == 4)printf("\n\n"); printf("5.肾上腺素x%d  ", prop[4]); i++; }
						if (prop[5]) { if (i == 4)printf("\n\n"); printf("6.力量药水x%d  ", prop[5]); i++; }
						if (prop[6]) { if (i == 4)printf("\n\n"); printf("7.虚弱药水x%d  ", prop[6]); i++; }
						if (i == 0)
						{
							printf("这里空无一物\n");
							display(1, 20);
							getch();
							goto menue3;
						}
						printf("\n\nZ.返回\n");
						display(1, 20);
						do {						//选择道具
							back = 0;
							in = getch();
							switch (in)	
							{
							case '1':						//选项--3.1.1生命药水
								if (prop[in - 49])
								{
									display(0, 50);
									display(1, 20);
									printf("生命药水\n\n恢复150点生命值\n\n\nX.使用 Z.返回\n");
									display(1, 20);
									do {
										back = 0;
										in = getch();
										if (in == 'x' || in == 'X')		//X.使用
										{
											prop[0]--;
											p_hp += 150;
											display(0, 50);
											display(1, 20);
											printf("你使用了生命药水\n\n生命值+150\n");
											display(1, 20);
											getch();
										}
										else if (in == 'z' || in == 'Z') goto menue3_1;	//Z.返回
										else back = 1;
									} while (back);
								}
								else back = 1;
								break;
							case '2':						//选项--3.1.2体力药水
								if (prop[in - 49])
								{
									display(0, 50);
									display(1, 20);
									printf("体力药水\n\n恢复90点体力值\n\n\nX.使用 Z.返回\n");
									display(1, 20);
									do {
										back = 0;
										in = getch();
										if (in == 'x' || in == 'X')		//X.使用
										{
											prop[1]--;
											p_VIT += 90;
											display(0, 50);
											display(1, 20);
											printf("你使用了体力药水\n\n体力值+90\n");
											display(1, 20);
											getch();
										}
										else if (in == 'z' || in == 'Z') goto menue3_1;	//Z.返回
										else back = 1;
									} while (back);
								}
								else back = 1;
								break;
							case '3':						//选项--3.1.3昏睡红茶
								if (prop[in - 49])
								{
									display(0, 50);
									display(1, 20);
									printf("昏睡红茶\n\n使=v=接下来3回合无法行动\n\n\n*仿佛能从名字中看出饮用者的命运\n\n\nX.使用 Z.返回\n");
									display(1, 20);
									do {
										back = 0;
										in = getch();
										if (in == 'x' || in == 'X')		//X.使用
										{
											prop[2]--;
											timer[0] = 3;
											display(0, 50);
											display(1, 20);
											printf("=v=:ZZZzzz...\n\n*接下来3回合=v=无法行动\n");
											display(1, 20);
											getch();
										}
										else if (in == 'z' || in == 'Z') goto menue3_1;	//Z.返回
										else back = 1;
									} while (back);
								}
								else back = 1;
								break;
							case '4':						//选项--3.1.4命运骰子
								if (prop[in - 49])
								{
									display(0, 50);
									display(1, 20);
									printf("命运骰子\n\n将所有除命运骰子外的道具数量随机重置为0~9\n\n\nX.使用 Z.返回\n");
									display(1, 20);
									do {
										back = 0;
										in = getch();
										if (in == 'x' || in == 'X')		//X.使用
										{
											prop[3]--;
											for (int i = 0; i < prop_n; i++)
												if(i!=3)prop[i] = rand() % 10;
											display(0, 50);
											display(1, 20);
											printf("你使用了命运骰子\n\n拜托了，摇个9从出来\n");
											display(1, 20);
											getch();
										}
										else if (in == 'z' || in == 'Z') goto menue3_1;	//Z.返回
										else back = 1;
									} while (back);
								}
								else back = 1;
								break;
							case '5':						//选项--3.1.5肾上腺素
								if (prop[in - 49])
								{
									display(0, 50);
									display(1, 20);
									printf("肾上腺素\n\n接下来3次探索不消耗体力\n\n*可叠加\n\n\nX.使用 Z.返回\n");
									display(1, 20);
									do {
										back = 0;
										in = getch();
										if (in == 'x' || in == 'X')		//X.使用
										{
											prop[4]--;
											timer[1] += 3;
											display(0, 50);
											display(1, 20);
											printf("你使用了肾上腺素\n\n*这使你充满了决心\n");
											display(1, 20);
											getch();
										}
										else if (in == 'z' || in == 'Z') goto menue3_1;	//Z.返回
										else back = 1;
									} while (back);
								}
								else back = 1;
								break;
							case '6':						//选项--3.1.6力量药水
								if (prop[in - 49])
								{
									display(0, 50);
									display(1, 20);
									printf("力量药水\n\n接下来3次攻击力量提升30%%\n\n\nX.使用 Z.返回\n");
									display(1, 20);
									do {
										back = 0;
										in = getch();
										if (in == 'x' || in == 'X')		//X.使用
										{
											prop[5]--;
											timer[2] = 3;
											display(0, 50);
											display(1, 20);
											printf("你喝下了力量药水\n\n感觉像是芝士的味道\n");
											display(1, 20);
											getch();
										}
										else if (in == 'z' || in == 'Z') goto menue3_1;	//Z.返回
										else back = 1;
									} while (back);
								}
								else back = 1;
								break;
							case '7':						//选项--3.1.7虚弱药水
								if (prop[in - 49])
								{
									display(0, 50);
									display(1, 20);
									printf("虚弱药水\n\n接下来5回合=v=的攻击力降低30%%\n\n\nX.使用 Z.返回\n");
									display(1, 20);
									do {
										back = 0;
										in = getch();
										if (in == 'x' || in == 'X')		//X.使用
										{
											prop[6]--;
											timer[3] = 5;
											display(0, 50);
											display(1, 20);
											printf("你使用了虚弱药水\n\n=v=有点遭不住了\n");
											display(1, 20);
											getch();
										}
										else if (in == 'z' || in == 'Z') goto menue3_1;	//Z.返回
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
					case '2':	//选项--3.2法术
					menue3_2:
						i = 0;
						display(0, 50);				//法术菜单
						display(1, 20);
						printf("法术\n\n");
						if (magic[0]) { printf("1.祈愿x%d  ", magic[0]); i++; }
						if (magic[1]) { printf("2.赐福x%d  ", magic[1]); i++; }
						if (magic[2]) { printf("3.天雷x%d  ", magic[2]); i++; }
						if (magic[3]) { printf("4.毒雾x%d  ", magic[3]); i++; }
						if (i == 0)
						{
							printf("这里空无一物\n");
							display(1, 20);
							getch();
							goto menue3;
						}
						printf("\n\nZ.返回\n");
						display(1, 20);
						do {
							back = 0;
							in = getch();
							switch (in)
							{
							case '1':		//选项--3.2.1祈愿
								if (magic[in - 49])
								{
									display(0, 50);
									display(1, 20);
									printf("祈愿\n\n玩家和=v=的生命值同时增加%.lf%%\n\n\nX.使用 Z.返回\n",0.4*(p_magic+buff_magic));
									display(1, 20);
									do {
										back = 0;
										in = getch();
										if (in == 'x' || in == 'X')		//X.使用
										{
											magic[0]--;
											
											display(0, 50);
											display(1, 20);
											printf("身后仿佛出现了圣光\n\n*你的生命值+%.lf  =v=的生命值+%.lf\n", p_hp* (0.4 * (p_magic + buff_magic) / 100), b_hp* (0.4 * (p_magic + buff_magic) / 100));
											p_hp += p_hp*(0.4 * (p_magic + buff_magic) / 100);
											b_hp += b_hp*(0.4 * (p_magic + buff_magic) / 100);
											display(1, 20);
											getch();
										}
										else if (in == 'z' || in == 'Z') goto menue3_2;	//Z.返回
										else back = 1;
									} while (back);
								}
								else back = 1;
								break;
							case'2':		//选项--3.2.2.赐福
								if (magic[in - 49])
								{
									display(0, 50);
									display(1, 20);
									printf("赐福\n\n每回合增加%.lf%%生命值，持续3回合\n\n\nX.使用 Z.返回\n",0.1*(p_magic + buff_magic));
									display(1, 20);
									do {
										back = 0;
										in = getch();
										if (in == 'x' || in == 'X')		//X.使用
										{
											magic[1]--;
											timer[4] = 3;
											display(0, 50);
											display(1, 20);
											printf("*你感觉轻松了不少\n");
											display(1, 20);
											getch();
										}
										else if (in == 'z' || in == 'Z') goto menue3_2;	//Z.返回
										else back = 1;
									} while (back);
								}
								else back = 1;
								break;
							case '3':		//选项--3.2.3.天雷
								if (magic[in - 49])
								{
									display(0, 50);
									display(1, 20);
									printf("天雷\n\n对玩家和=v=造成生命值%.lf%%的伤害\n\n*据说发誓也是此魔法的一种吟唱方式\n\n\nX.使用 Z.返回\n",0.2*(p_magic + buff_magic));
									display(1, 20);
									do {
										back = 0;
										in = getch();
										if (in == 'x' || in == 'X')		//X.使用
										{
											magic[2]--;
											display(0, 50);
											display(1, 20);
											printf("你使用了天雷\n\n*对你造成了%.lf点伤害  对=v=造成了%.lf点伤害\n", p_hp* (0.2 * (p_magic + buff_magic) / 100), b_hp* (0.2 * (p_magic + buff_magic) / 100));
											p_hp -= p_hp * (0.2 * (p_magic + buff_magic) / 100);
											b_hp -= b_hp * (0.2 * (p_magic + buff_magic) / 100);
											display(1, 20);
											getch();
										}
										else if (in == 'z' || in == 'Z') goto menue3_2;	//Z.返回
										else back = 1;
									} while (back);
								}
								else back = 1;
								break;
							case '4':		//选项--3.2.4.毒雾
								if (magic[in - 49])
								{
									display(0, 50);
									display(1, 20);
									printf("毒雾\n\n每回合对=v=造成生命值%.lf%%的伤害，持续5回合\n\n*卷轴上的吟唱咒语是一长串奇怪的数字“114514…”\n\n\nX.使用 Z.返回\n",0.05*(p_magic + buff_magic));
									display(1, 20);
									do {
										back = 0;
										in = getch();
										if (in == 'x' || in == 'X')		//X.使用
										{
											magic[3]--;
											timer[5] = 5;
											display(0, 50);
											display(1, 20);
											printf("你使用了毒雾\n");
											display(1, 20);
											getch();
										}
										else if (in == 'z' || in == 'Z') goto menue3_2;	//Z.返回
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
					case '3':	//选项--3.3经验书
					menue3_3:
						i = 0;
						display(0, 50);				//经验书菜单
						display(1, 20);
						printf("经验书\n\n");
						if (levelbook[0]) { printf("1.《芝士就是_ _!》x%d   ", levelbook[0]); i++; }
						if (levelbook[1]) { printf("2.《盗窃:从入门到入狱》x%d   ", levelbook[1]); i++; }
						if (levelbook[2]) { if (i == 2)printf("\n\n"); printf("3.《麻瓜的烹饪方式》x%d   ", levelbook[2]); i++; }
						if (i == 0)
						{
							printf("这里空无一物\n");
							display(1, 20);
							getch();
							goto menue3;
						}
						printf("\n\nZ.返回\n");
						display(1, 20);
						do {
							back = 0;
							in = getch();
							switch (in)
							{
							case '1':		//选项--3.3.1.《芝士就是_ _!》
								if (levelbook[in - 49])
								{
									display(0, 50);
									display(1, 20);
									printf("《芝士就是_ _!》\n\n\nX.阅读 Z.返回\n");
									display(1, 20);
									do {
										back = 0;
										in = getch();
										if (in == 'x' || in == 'X')		//X.使用
										{
											levelbook[0]--;
											p_strength_origin += 20;
											display(0, 50);
											display(1, 20);
											printf("整本书里只有一道填空题，但你仿佛可以听到他的声音\n\n*力量+20\n");
											display(1, 20);
											getch();
										}
										else if (in == 'z' || in == 'Z') goto menue3_3;	//Z.返回
										else back = 1;
									} while (back);
								}
								else back = 1;
								break;
							case '2':		//选项--3.3.2.《盗窃:从入门到入狱》
								if (levelbook[in - 49])
								{
									display(0, 50);
									display(1, 20);
									printf("《盗窃:从入门到入狱》\n\n\nX.阅读 Z.返回\n");
									display(1, 20);
									do {
										back = 0;
										in = getch();
										if (in == 'x' || in == 'X')		//X.使用
										{
											levelbook[1]--;
											p_speed += 10;
											p_dodge += 1;
											display(0, 50);
											display(1, 20);
											printf("里面似乎是一本《三十六计》，但不知为何只剩下了最后一计\n\n*移动速度+10  *闪避率+1%%\n");
											display(1, 20);
											getch();
										}
										else if (in == 'z' || in == 'Z') goto menue3_3;	//Z.返回
										else back = 1;
									} while (back);
								}
								else back = 1;
								break;
							case '3':		//选项--3.3.3.《麻瓜的烹饪方式》
								if (levelbook[in - 49])
								{
									display(0, 50);
									display(1, 20);
									printf("《麻瓜的烹饪方式》\n\n\nX.阅读 Z.返回\n");
									display(1, 20);
									do {
										back = 0;
										in = getch();
										if (in == 'x' || in == 'X')		//X.使用
										{
											levelbook[2]--;
											p_magic += 10;
											display(0, 50);
											display(1, 20);
											printf("看到书中麻瓜的下场之后你不禁打了个寒颤，决定更加努力地学习魔法\n\n*魔法+10%%\n");
											display(1, 20);
											getch();
										}
										else if (in == 'z' || in == 'Z') goto menue3_3;	//Z.返回
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
					case '4':	//选项--3.4附魔书
					menue3_4:
						i = 0;
						display(0, 50);				//附魔书菜单
						display(1, 20);
						printf("附魔书\n\n");
						if (enchantment[0]) { printf("1.愈战愈勇x%d  ", enchantment[0]); i++; }
						if (enchantment[1]) { printf("2.一鼓作气x%d  ", enchantment[1]); i++; }
						if (enchantment[2]) { printf("3.刺客之刃x%d  ", enchantment[2]); i++; }
						if (enchantment[3]) { printf("4.狙击手的矜持x%d  ", enchantment[3]); i++; }
						if (i == 0)
						{
							printf("这里空无一物\n");
							printf("\n当前附魔--");//当前附魔提示
							if (enchantment_mod == 0)printf("无\n");
							else if (enchantment_mod == 1)printf("#愈战愈勇:%d%%\n",enchatment_judge_0);
							else if (enchantment_mod == 2)printf("#一鼓作气:%d%%\n",enchatment_judge_1);
							else if (enchantment_mod == 3)printf("#刺客之刃:%d\n",weapon_special_judge_0);
							else if (enchantment_mod == 4)printf("#狙击手的矜持:%d\n",weapon_special_judge_1);
							display(1, 20);
							getch();
							goto menue3;
						}
						printf("\n\n\n当前附魔--");//当前附魔提示
						if (enchantment_mod == 0)printf("无\n");
						else if (enchantment_mod == 1)printf("#愈战愈勇:%d%%\n",enchatment_judge_0);
						else if (enchantment_mod == 2)printf("#一鼓作气:%d%%\n",enchatment_judge_1);
						else if (enchantment_mod == 3)printf("#刺客之刃:%d\n",weapon_special_judge_0);
						else if (enchantment_mod == 4)printf("#狙击手的矜持:%d\n",weapon_special_judge_1);
						printf("\nZ.返回\n");
						display(1, 20);
						do{
							back = 0;
							in = getch();
							switch (in)
							{
							case '1':		//选项--3.4.1.愈战愈勇
								if (enchantment[in - 49])
								{
									display(0, 50);
									display(1, 20);
									printf("愈战愈勇\n\n攻击造成70%%的伤害，每回合增加10%%\n\n*上限为150%%  可被其他附魔覆盖\n\n\nX.使用 Z.返回\n");
									display(1, 20);
									do {
										back = 0;
										in = getch();
										if (in == 'x' || in == 'X')		//X.使用
										{
											enchantment[0]--;
											enchantment_mod = 1;
											enchatment_judge_0 = 70;
											display(0, 50);
											display(1, 20);
											printf("不要停下啊\n");
											display(1, 20);
											getch();
										}
										else if (in == 'z' || in == 'Z') goto menue3_4;	//Z.返回
										else back = 1;
									} while (back);
								}
								else back = 1;
								break;
							case '2':		//选项--3.4.2.一鼓作气
								if (enchantment[in - 49])
								{
									display(0, 50);
									display(1, 20);
									printf("一鼓作气\n\n攻击造成160%%的伤害，每回合减少10%%\n\n*下限为80%%  可被其他附魔覆盖\n\n\nX.使用 Z.返回\n");
									display(1, 20);
									do {
										back = 0;
										in = getch();
										if (in == 'x' || in == 'X')		//X.使用
										{
											enchantment[1]--;
											enchantment_mod = 2;
											enchatment_judge_1 = 160;
											display(0, 50);
											display(1, 20);
											printf("“再而衰，三而竭”\n");
											display(1, 20);
											getch();
										}
										else if (in == 'z' || in == 'Z') goto menue3_4;	//Z.返回
										else back = 1;
									} while (back);
								}
								else back = 1;
								break;
							case '3':		//选项--3.4.3.刺客之刃
								if (enchantment[in - 49])
								{
									display(0, 50);
									display(1, 20);
									printf("刺客之刃\n\n距离小于%d时力量提升50%%\n\n\nX.使用 Z.返回\n", weapon_special_judge_0);
									display(1, 20);
									do {
										back = 0;
										in = getch();
										if (in == 'x' || in == 'X')		//X.使用
										{
											enchantment[2]--;
											enchantment_mod = 3;
											display(0, 50);
											display(1, 20);
											printf("和袖剑更配哦\n");
											display(1, 20);
											getch();
										}
										else if (in == 'z' || in == 'Z') goto menue3_4;	//Z.返回
										else back = 1;
									} while (back);
								}
								else back = 1;
								break;
							case '4':		//选项--3.4.4.狙击手的矜持
								if (enchantment[in - 49])
								{
									display(0, 50);
									display(1, 20);
									printf("狙击手的矜持\n\n距离大于%d时力量提升50%%\n\n\nX.使用 Z.返回\n",weapon_special_judge_1);
									display(1, 20);
									do {
										back = 0;
										in = getch();
										if (in == 'x' || in == 'X')		//X.使用
										{
											enchantment[3]--;
											enchantment_mod = 4;
											display(0, 50);
											display(1, 20);
											printf("和狙击枪更配哦\n");
											display(1, 20);
											getch();
										}
										else if (in == 'z' || in == 'Z') goto menue3_4;	//Z.返回
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
			case '4':	//选项--4.装备
			menue4:
				display(0, 50);
				display(1, 20);
				printf("1.近战 2.远程 3.法杖\n\nZ.返回\n");
				display(1, 20);
				do {
					int i = 0;
					back = 0;
					in = getch();
					switch (in)
					{
					case '1':	//选项--4.1.近战
					menue4_1:
						i = 0;
						display(0, 50);
						display(1, 20);
						printf("近战武器\n\n");
						if (weapon_short[0]) { printf("1.长矛  "); i++; }
						if (weapon_short[1]) { printf("2.祖传的袖剑  "); i++; }
						if (weapon_short[2]) { printf("3.淬毒匕首  "); i++; }
						if (weapon_short[3]) { printf("4.饮血剑  "); i++; }
						if (i == 0)
						{
							printf("这里空无一物\n");
							display(1, 20);
							getch();
							goto menue4;
						}
						printf("\n\n\n*当前装备:");//当前装备提示
						if (weapon_short_mod == 0)printf("无\n");
						else if (weapon_short_mod == 1)printf("长矛\n");
						else if (weapon_short_mod == 2)printf("祖传的袖剑\n");
						else if (weapon_short_mod == 3)printf("淬毒匕首\n");
						else if (weapon_short_mod == 4)printf("饮血剑\n");
						printf("\nZ.返回\n");
						display(1, 20);
						do {
							back = 0;
							in = getch();
							switch (in)
							{
							case '1':		//选项--4.1.1.长矛
								if (weapon_short[in - 49])
								{
									display(0, 50);
									display(1, 20);
									printf("长矛\n\n近战攻击力+100 近战攻击距离+50\n\n*穿刺:25%%概率造成生命值15%%的额外伤害\n\n\nX.装备 Z.返回\n");
									display(1, 20);
									do {
										back = 0;
										in = getch();
										if (in == 'x' || in == 'X')		//X.使用
										{
											weapon_short_mod = 1;
											buff_short_damage = 100;
											buff_short_range = 50;
											buff_short_critical = 0;
											display(0, 50);
											display(1, 20);
											printf("*你装备了长矛\n");
											display(1, 20);
											getch();
											goto menue0;
										}
										else if (in == 'z' || in == 'Z') goto menue4_1;	//Z.返回
										else back = 1;
									} while (back);
								}
								else back = 1;
								break;
							case '2':		//选项--4.1.2.祖传的袖剑
								if (weapon_short[in - 49])
								{
									display(0, 50);
									display(1, 20);
									printf("祖传的袖剑\n\n近战攻击力+200 近战暴击率+20%% 近战攻击距离-30\n\n*背刺:距离小于%d时造成三倍伤害\n\n\n“当我们赶到水边时便只剩下了这个”\n\n\nX.装备 Z.返回\n", weapon_special_judge_0);
									display(1, 20);
									do {
										back = 0;
										in = getch();
										if (in == 'x' || in == 'X')		//X.使用
										{
											weapon_short_mod = 2;
											buff_short_damage = 200;
											buff_short_critical = 20;
											buff_short_range = -30;
											display(0, 50);
											display(1, 20);
											printf("*你装备了祖传的袖剑\n");
											display(1, 20);
											getch();
											goto menue0;
										}
										else if (in == 'z' || in == 'Z') goto menue4_1;	//Z.返回
										else back = 1;
									} while (back);
								}
								else back = 1;
								break;
							case '3':		//选项--4.1.3.淬毒匕首
								if (weapon_short[in - 49])
								{
									display(0, 50);
									display(1, 20);
									printf("淬毒匕首\n\n近战攻击力+300 近战攻击距离+10\n\n*剧毒:攻击后3回合里每回合造成160点伤害\n\n\nX.装备 Z.返回\n");
									display(1, 20);
									do {
										back = 0;
										in = getch();
										if (in == 'x' || in == 'X')		//X.使用
										{
											weapon_short_mod = 3;
											buff_short_damage = 300;
											buff_short_range = 10;
											buff_short_critical = 0;
											if (rand() % 100 + 1 <= 5)
											{
												display(0, 50);
												display(1, 20);
												printf("这把刀可是涂了毒的(舔)\n");
												display(1, 20);
												getch();
												display(0, 50);
												display(1, 20);
												printf("你输了!\n\n\n=v=:叫你乱舔，遭报应了吧\n");
												display(1, 20);
												getch();
												return 0;
											}
											display(0, 50);
											display(1, 20);
											printf("*装备了淬毒匕首\n");
											display(1, 20);
											getch();
											goto menue0;
										}
										else if (in == 'z' || in == 'Z') goto menue4_1;	//Z.返回
										else back = 1;
									} while (back);
								}
								else back = 1;
								break;
							case '4':		//选项--4.1.4.饮血剑
								if (weapon_short[in - 49])
								{
									display(0, 50);
									display(1, 20);
									printf("饮血剑\n\n近战攻击力+350 近战攻击距离+30 近战暴击率-20%%\n\n*吸血:恢复伤害10%%的生命值\n\n\nX.装备 Z.返回\n");
									display(1, 20);
									do {
										back = 0;
										in = getch();
										if (in == 'x' || in == 'X')		//X.使用
										{
											weapon_short_mod = 4;
											buff_short_damage = 350;
											buff_short_range = 30;
											buff_short_critical = -20;
											display(0, 50);
											display(1, 20);
											printf("*你装备了饮血剑\n");
											display(1, 20);
											getch();
											goto menue0;
										}
										else if (in == 'z' || in == 'Z') goto menue4_1;	//Z.返回
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
					case '2':	//选项--4.2.远程
					menue4_2:
						i = 0;
						display(0, 50);
						display(1, 20);
						printf("远程武器\n\n");
						if (weapon_long[0]) { printf("1.连弩  "); i++; }
						if (weapon_long[1]) { printf("2.狙击枪  "); i++; }
						if (i == 0)
						{
							printf("这里空无一物\n");
							display(1, 20);
							getch();
							goto menue4;
						}
						printf("\n\n\n*当前装备:");//当前装备提示
						if (weapon_long_mod == 0)printf("无\n");
						else if (weapon_long_mod == 1)printf("连弩\n");
						else if (weapon_long_mod == 2)printf("狙击枪\n");
						printf("\nZ.返回\n");
						display(1, 20);
						do {
							back = 0;
							in = getch();
							switch (in)
							{
							case '1':		//选项--4.2.1.连弩
								if (weapon_long[in - 49])
								{
									display(0, 50);
									display(1, 20);
									printf("连弩\n\n远程攻击伤害+150 远程攻击距离+100 远程暴击率+10\n\n*双重打击:攻击变为两段，造成60%%和70%%的伤害\n\n\nX.装备 Z.返回\n");
									display(1, 20);
									do {
										back = 0;
										in = getch();
										if (in == 'x' || in == 'X')		//X.使用
										{
											weapon_long_mod = 1;
											buff_long_damage = 150;
											buff_long_range = 100;
											buff_long_critical = 10;
											display(0, 50);
											display(1, 20);
											printf("*你装备了连弩\n");
											display(1, 20);
											getch();
											goto menue0;
										}
										else if (in == 'z' || in == 'Z') goto menue4_2;	//Z.返回
										else back = 1;
									} while (back);
								}
								else back = 1;
								break;
							case '2':		//选项--4.2.2.狙击枪
								if (weapon_long[in - 49])
								{
									display(0, 50);
									display(1, 20);
									printf("狙击枪\n\n远程攻击力+300 远程攻击距离+200 暴击率-20%%\n\n*精准打击:距离大于%d时远程攻击造成200%%伤害\n\n\nX.装备 Z.返回\n", weapon_special_judge_1);
									display(1, 20);
									do {
										back = 0;
										in = getch();
										if (in == 'x' || in == 'X')		//X.使用
										{
											weapon_long_mod = 2;
											buff_long_damage = 300;
											buff_long_range = 200;
											buff_long_critical = -20;
											display(0, 50);
											display(1, 20);
											printf("*你装备了狙击枪 -＄4750\n");
											display(1, 20);
											getch();
											goto menue0;
										}
										else if (in == 'z' || in == 'Z') goto menue4_2;	//Z.返回
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
					case '3':	//选项--4.3.法杖
					menue4_3:
						i = 0;
						display(0, 50);
						display(1, 20);
						printf("法杖\n\n");
						if (weapon_magic[0]) { printf("1.洞察之杖  "); i++; }
						if (weapon_magic[1]) { printf("2.支援法杖  "); i++; }
						if (weapon_magic[2]) { printf("3.守护者之杖  "); i++; }
						if (i == 0)
						{
							printf("这里空无一物\n");
							display(1, 20);
							getch();
							goto menue4;
						}
						printf("\n\n\n*当前装备:");//当前装备提示
						if (weapon_magic_mod == 0)printf("无\n");
						else if (weapon_magic_mod == 1)printf("洞察之杖\n");
						else if (weapon_magic_mod == 2)printf("支援法杖\n");
						else if (weapon_magic_mod == 3)printf("守护者之杖\n");
						printf("\nZ.返回\n");
						display(1, 20);
						do {
							back = 0;
							in = getch();
							switch (in)
							{
							case '1':		//选项--4.3.1.洞察之杖
								if (weapon_magic[in - 49])
								{
									display(0, 50);
									display(1, 20);
									printf("洞察之杖\n\n魔法+45%%\n\n*洞察:使用“查看”时不消耗体力\n\n\nX.装备 Z.返回\n");
									display(1, 20);
									do {
										back = 0;
										in = getch();
										if (in == 'x' || in == 'X')		//X.使用
										{
											weapon_magic_mod = 1;
											buff_magic = 45;
											display(0, 50);
											display(1, 20);
											printf("*你装备了洞察之杖\n");
											display(1, 20);
											getch();
											goto menue0;
										}
										else if (in == 'z' || in == 'Z') goto menue4_3;	//Z.返回
										else back = 1;
									} while (back);
								}
								else back = 1;
								break;
							case '2':		//选项--4.3.2.支援法杖
								if (weapon_magic[in - 49])
								{
									display(0, 50);
									display(1, 20);
									printf("支援法杖\n\n魔法+30%%\n\n*后卫:回合结束后无视距离发射一个奥术导弹造成%.lf点伤害\n\n\nX.装备 Z.返回\n", 100.0 * (p_magic + buff_magic) / 100);
									display(1, 20);
									do {
										back = 0;
										in = getch();
										if (in == 'x' || in == 'X')		//X.使用
										{
											weapon_magic_mod = 2;
											buff_magic = 40;
											display(0, 50);
											display(1, 20);
											printf("*你装备了支援法杖\n");
											display(1, 20);
											getch();
											goto menue0;
										}
										else if (in == 'z' || in == 'Z') goto menue4_3;	//Z.返回
										else back = 1;
									} while (back);
								}
								else back = 1;
								break;
							case '3':		//选项--4.3.3.守护者之杖
								if (weapon_magic[in - 49])
								{
									display(0, 50);
									display(1, 20);
									printf("守护者之杖\n\n魔法+20%%\n\n*屹立:回合结束后生命值+%.lf 体力值+%.lf\n\n*救主灵刃:生命值少于70时恢复到200(仅一次)\n\n\nX.装备 Z.返回\n",25.0*(p_magic+buff_magic)/100,6.0*(p_magic+buff_magic)/100);
									display(1, 20);
									do {
										back = 0;
										in = getch();
										if (in == 'x' || in == 'X')		//X.使用
										{
											weapon_magic_mod = 3;
											buff_magic = 20;
											display(0, 50);
											display(1, 20);
											printf("*你装备了守护者之杖\n");
											display(1, 20);
											getch();
											goto menue0;
										}
										else if (in == 'z' || in == 'Z') goto menue4_3;	//Z.返回
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
		} while (back);		//玩家操作结束
		display(0, 50);
		display(1, 20);
		printf("回合结束\n");
		display(1, 20);
		getch();

		if (p_hp > 0 && b_hp > 0)	//结算效果
		{
			display(0, 50);
			display(1, 20);
			p_VIT += 10;
			printf("体力+10\n");	//自动回复体力
			if (timer[4]) { timer[4]--; printf("赐福:恢复%.lf点生命值\n", \
				0.1 * (p_magic + buff_magic)); p_hp += p_hp * 0.1 * (p_magic + buff_magic)/100;}				//法术:赐福
			if (timer[5]) {timer[5]--; printf("毒雾:造成%.lf点伤害\n", \
				b_hp*0.05 * (p_magic + buff_magic)/100); b_hp -= b_hp * 0.05 * (p_magic + buff_magic) / 100;}		//法术:毒雾
			if (timer[6]) { timer[6]--; printf("*剧毒:造成160点伤害\n"); b_hp -= 160; }							//武器:淬毒匕首
			if (weapon_magic_mod == 2) { printf("*后卫:造成%.lf点伤害\n", \
				100.0 * (p_magic + buff_magic) / 100); b_hp -= 100.0 * (p_magic + buff_magic) / 100; }			//支援法杖:后卫
			if (weapon_magic_mod == 3) { printf("*屹立:生命值+%.lf  体力+%.lf\n", \
				25.0 * (p_magic + buff_magic) / 100, 6.0 * (p_magic + buff_magic) / 100); p_hp += 25.0 * (p_magic + buff_magic) / 100, p_VIT += 6.0 * (p_magic + buff_magic) / 100; }	//守护者之杖:屹立
			if (weapon_magic_mod == 3 && p_hp < 70 && k) { p_hp = 200; k = 0; printf("*触发救主灵刃,生命值恢复至200\n"); }	//守护者之杖:救主灵刃
			display(1, 20);
			getch();
		}
		if (p_hp > p_hp_max)p_hp = p_hp_max;//修正玩家血量溢出
		if (b_hp > b_hp_max)b_hp = b_hp_max;//修正BOSS血量溢出
		if (p_dodge > 70)p_dodge = 70;		//修正玩家闪避溢出
		if (p_hp > 0 && b_hp > 0)	//BOSS回合
		{
			display(0, 50);
			display(1, 20);
			printf("=v=的回合\n");
			display(1, 20);
			getch();
			display(0, 50);
			display(1, 20);
			if (timer[0])	//道具:昏睡红茶
			{
				timer[0]--;
				printf("=v=睡着了\n");
			}
			else	//BOSS行动
			{
				if (boss_special && p_hp * 1.5 >= b_hp)	//特殊技能:背水一战
				{
					boss_special = 0;
					printf("*=v=发动了特殊技能:背水一战\n\n\n");
					printf("生命值%+d  攻击力%+.lf  移动速度%+.lf  闪避率+%d%% 攻击距离%+d\n", p_hp * 5 - b_hp, b_strength * 1.5 - b_strength, 60 - b_speed, 30, b_attack_range * 1.5 - b_attack_range);
					b_hp = 5 * p_hp;
					b_strength = 1.5 * b_strength;
					b_speed = 60;
					b_dodge += 30;
					b_attack_range = b_attack_range * 1.5;
				}
				else if (b_hp <= 1.5 * p_hp || b_hp >=3 * p_hp)	//进攻
				{
					if (range <= b_attack_range)	//距离足够--攻击
					{
						printf("=v=敲了你一下\n\n");
						if (rand() % 100 + 1 <= p_dodge)
							printf("*你躲开了\n");
						else
						{
							if (rand() % 100 + 1 <= b_critical)	//暴击
							{
								printf("触发了暴击:");
								damage = 2 * b_strength;
							}
							else damage = b_strength;	//未暴击
							if (timer[3])	//道具:虚弱药水
							{
								damage *= 0.7;
								timer[3]--;
							}
							p_hp -= damage;	//结算普攻伤害
							printf("造成了%d点伤害\n", damage);
						}
					}
					else if (range >= b_attack_range)	//距离不足--追击
					{
						range -= b_speed;
						if (range <= 0)range = 0;
						printf("=v=发起了冲刺,距离-%d \n\n*当前距离:%d\n", b_speed, range);
						b_hp += 50;
						printf("*=v=生命值+50\n");
					}
				}
				else if (b_hp > 2 * p_hp && b_hp < 3 * p_hp)	//撤退
				{
					printf("“逃げるんだよ”\n=v=逃跑了，距离+%d\n\n",b_speed);
					range += b_speed;
					printf("*当前距离:%d\n*=v=生命值+150\n",range);
					b_hp += 150;
				}
				b_strength++;	//boss攻击力增长
			}
			if (b_hp > b_hp_max)b_hp = b_hp_max;//修正BOSS血量溢出
			if (b_dodge > 70)b_dodge = 70;		//修正BOSS闪避溢出
			display(1, 20);
			getch();
		}//BOSS回合结束
	}//游戏结束
	//显示结果
	display(0, 50);
	display(1, 20);
	if (b_hp <= 0 && p_hp > 0)	//BOSS倒下  玩家存活
	{
		if (p_magic + buff_magic > 200)	//大魔法师:阿瓦达索命
		{
			printf("=v=在倒下前放出了*阿瓦达索命\n\n对你造成了生命值105%%的伤害\n\n*生命值-%.lf\n", p_hp * 1.05);
			p_hp -= p_hp * 1.05;
			display(1, 20);
			getch();
			display(0, 50);
			display(1, 20);
			if (p_hp > b_hp)printf("你还是取得了胜利\n\n");
			else if (p_hp < b_hp)printf("=v=得逞了\n\n");
			else printf("最终你们打成了平手\n\n");
			printf("*你的生命值:%d\n*=v=的生命值:%d\n", p_hp, b_hp);
		}
		else
		{
			printf("=v=倒下了...\n");
			display(1, 20);
			display(0, 50);
			display(1, 20);
			printf("不要停下来啊!\n");
		}
	}
	else if (b_hp > 0 && p_hp <= 0)	//BOSS存活	玩家倒下
	{
		printf("弱耶 拜托你很弱耶\n\n你知道现在谁是老大了喔\n");
	}
	else if (b_hp <= 0 && p_hp <= 0)	//BOSS和玩家都倒下
	{
		printf("呵，没想到最后竟是这样的结局\n\n*你与=v=都倒下了\n");
	}
	else printf("应该不会有这种情况吧...?\n");
	display(1, 20);
	getch();


	return 0;
}


void initialization(int* a, int n, int k)//初始化数组（数组, 大小，目标值）
{
	for (int i = 0; i < n; a[i++] = k);
}
void display(int type,int n)//显示操作（操作类型，次数） 0：换行 1：横线(结尾换行)—— 2:空格(结尾无换行)
{
	switch (type)
	{
	case 0:		//0.换行
		if (n == 50)	//定向优化
		{
			printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\
				\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
			break;
		}

		for (int i = 0; i < n; i++)
			printf("\n");
		break;
	case 1:		//1.横线
		
		if (n == 20)	//定向优化
		{
			printf("\n————————————————————————————————————————\n\n");
			break;
		}

		printf("\n");
		for (int i = 0; i < n; i++)
			printf("——");
		printf("\n\n");
		break;
	case 2:		//2.空格
		for (int i = 0; i < n; i++)
			printf(" ");
		break;
	default:
		break;
	}
}
