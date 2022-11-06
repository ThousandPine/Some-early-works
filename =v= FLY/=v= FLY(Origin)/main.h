#define Default_MAP_ROWS 25         //地图显示区域 行
#define Default_MAP_COLS 40         //地图显示区域 列 {(已修复的BUG)取40列时多处出现异常崩溃}
#define Default_BUFFER_ROWS 5       //地图缓冲区域 行
#define Default_GRAPH_NUM 3         //初始障碍数量
#define Default_RATE 20             //游戏难度
#define Default_DAMAGE 1            //碰撞伤害
#define Default_PLAYER_HP 100       //玩家初始生命
#define Default_PLAYER_POS_X 20     //玩家初始位置 x
#define Default_PLAYER_POS_Y 10     //玩家初始位置 y
#define Default_PLAYER_NAME "=v="   //玩家初始名字 {在=v= Fight中被击败的=v=，被流放到了这个世界（bushi}
#define Default_Sign_Background ' ' //默认背景符号
#define Default_Sign_Player '='     //默认玩家符号
#define Default_Sign_Obstacle '*'   //默认障碍符号
#define MAIN_OPTION 2               //主菜单选项数量
#define Setting_OPTION 3            //设置菜单选项数量
#define Setting_0_OPTION 5          //场景设置菜单选项数量
#define Setting_1_OPTION 4          //玩家设置菜单选项数量
#define Graph_MAX_ROWS 100          //图像行上限
#define Graph_MAX_COLS 300          //图像列上限
#define FILE_Setting "Setting.txt"  //设置文件
#define FILE_Graph "Graph.txt"      //图像文件

//储存玩家数据
typedef struct
{
    int x, y; //玩家坐标
    int HP;   //玩家血量
} Player;
//储存图像信息
typedef struct list
{
    int rows, cols;                                     //尺寸 行、列
    char graph[Graph_MAX_ROWS + 1][Graph_MAX_COLS + 1]; //二维数组存储图形
    struct list *next;                                  //下一个图像的地址
} Graph;
//储存游戏设置
typedef struct
{
    int MAP_ROWS;    //地图显示区域 行
    int MAP_COLS;    //地图显示区域 列
    int BUFFER_ROWS; //地图缓冲区域 行
    int GRAPH_NUM;   //障碍数量
    int RATE;        //游戏刷新率
    int HP;          //玩家血量
    int damage;      //碰撞伤害
    char name[51];   //玩家名称
    char *line;      //界面分界线
    char Background; //背景符号
    char Obstacle;   //障碍符号
    Graph *head;     //图形列表头节点
    Graph *tail;     //图形列表尾节点
    // int x, y;        //玩家坐标
} GameSetting;
extern char **MAP;          //地图
extern GameSetting Setting; //游戏设置
extern Player user;

// Game
void Display_MainMenu(int pos);           //显示主菜单 1.开始游戏 2.设置游戏内容{地图尺寸, 初始生命, 难度, 等}
int Enter_Game(void);                     //开始游戏
void Display_Map(void);                   //显示地图
void Refresh_Map(void);                   //刷新地图内容(包括缓冲区)
void Set_Buffer(void);                    //生成缓冲区内容
int Insert_Graph(int x, int y, Graph *p); //插入图形 输入坐标,将图形插入到缓冲区,遇到边界则裁切
int Get_Collison(int x, int y);           //碰撞判定 输入坐标,返回碰撞情况 {-1:障碍物, 0:无碰撞, 1~N:不同类型道具}
// funtion
int getin(void);                                                              //读取输入,返回操作 {-1:退出 0:未识别, 1:上, 2:下, 3:左, 4:右 5:选中}
int read(void);                                                               //读取数字
void gets_n(char *s, int n);                                                  //读取字符串
char **Calloc_Graph(int x, int y);                                            //创建二维数组(char) 输入行列长度,返回数组头地址
void Put_String_Mid(char *s);                                                 //将字符串居中输出
void Put_Graph(Graph *p);                                                     //输出图像
int Set_Window(int rows, int cols);                                           //修改控制台窗体大小 {-1:未成功, 0:成功}
char *Set_String(char sign, int len);                                         //生成指定长度的重复字符串
void Set_Menu(int pos, char option[][50], int Option_NUM, const char *title); //生成菜单 传入:选中位置, 选项字符串, 选项数量, 标题
Graph *Add_Graph(void);                                                       //添加图形 {创建成功返回地址, 否则返回NULL}
Graph *Find_Graph(int n);                                                     //定位指定1~N序号的图像 {成功返回地址, 失败返回NULL}
int Delete_Grapg(int n);                                                      //删除指定1~N序号的图像 {0:失败, 1:成功}
void Set_Pos(short x, short y);                                               //控制控制台光标位置
// setting
int Initialize_Setting(void);        //重置设置
int Initialize_Graph(void);          //重置图像
void Trans_Graph(Graph *p);          //转换图像符号
void Enter_SettingMenu(void);        //进入设置菜单
void Display_SettingMenu(int pos);   //显示设置菜单
void Enter_0_SettingMenu(void);      //进入场景设置菜单
void Display_0_SettingMenu(int pos); //显示场景设置菜单
void Enter_1_SettingMenu(void);      //进入玩家设置菜单
void Display_1_SettingMenu(int pos); //显示玩家设置菜单
// file
int Read_SettingFile(void);   //读入文件的设置
void Write_SettingFile(void); //将设置写入文件
int Read_GraphFile(void);     //读入文件的图像
void Write_GraphFile(void);   //将图像写入文件