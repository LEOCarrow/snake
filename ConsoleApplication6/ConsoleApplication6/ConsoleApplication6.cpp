// ConsoleApplication8.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

static char print_array[Y_MAX][X_MAX];
static unsigned int score = 0;
static char direction = 'd';
int snake_count = 3;
bool if_get_fruit = 0;
using namespace std;

struct Coordinate			//点坐标
{
	int x, y;
};
struct NODE				//双向链表结构
{
	Coordinate coord;
	NODE* pre;
	NODE* next;
};

NODE* list_delete(NODE *pHead);
struct NODE* list_insert(NODE *first, bool if_get_fruit);
short hitCheck(const NODE *first, struct Coordinate fruit);	//检验碰撞
void print_frame();
void delay();
void kb_check();
struct NODE* settings();
struct Coordinate gen_fruit(NODE *first);

int main()
{
	struct Coordinate fruit = { 0, 0 };
	struct NODE *pHead = NULL;
	short hit_re = 3;
	int answer = '\0';
	printf("The Gluttonous Snake Game\n");
	printf("\nPress enter to start\nPress anykey to EXIT\n");
	if ((answer = getchar()) == '\n') {
		system("cls");
	}
	else {
		return 0;
	}
	if (!(pHead = settings())) {
		printf("Initialization Faild\n");
		exit(-1);
	}

	fflush(stdin);
	//first start
	fruit = gen_fruit(pHead);
	print_frame();
	//loop
	while (1)
	{
		pHead = list_insert(pHead, 0);
		pHead = list_delete(pHead);
		hit_re = hitCheck(pHead, fruit);
		switch (hit_re)
		{
		case 3:
			break;
		case 2:
			++score;
			printf("\a");
			if_get_fruit = 1;
			if (!(pHead = list_insert(pHead, if_get_fruit))) {
				printf("Memory F\n");
				exit(-1);
			}
			++snake_count;
			fruit = gen_fruit(pHead);
			break;
		case 1:
			goto EXIT;
		}
		system("cls");
		print_frame();
		fflush(stdin);
		delay();
	}
EXIT:
	struct NODE *current = pHead;
	struct NODE *previous = NULL;
	for (size_t i = 0; i < snake_count; i++) {
		previous = current;
		current = current->next;
		free(previous);
		previous = NULL;
	}
	pHead = NULL;
	current = NULL;
	system("pause");
	return 0;
}

// 撞墙返回0，撞自己返回1，撞果子返回2，啥都没撞返回3
short hitCheck(const NODE *first, struct Coordinate fruit)
{
	int head_x = (first->coord).x;
	int head_y = (first->coord).y;

	// 吃到果子
	if (head_x == fruit.x && head_y == fruit.y)
		return 2;

	// 撞墙
	if (head_x == 0 || head_x == X_MAX - 1)
		return 1;
	if (head_y == 0 || head_y == Y_MAX - 1)
		return 1;

	// 撞自己
	NODE *current = first->next;
	for (int i = 0; i<(snake_count - 1); i++) {
		if (head_x == (current->coord).x && head_y == (current->coord).y)
			return 1;
		current = current->next;

	}
	if ((first->coord).x == 0 || (first->coord).x == X_MAX - 1 || (first->coord).y == 0 || (first->coord).y == Y_MAX - 1)
		return 1;
	// 啥都没撞
	return 3;
}

NODE* list_delete(NODE* pHead)
{
	NODE* TEMP, *_TEMP;
	TEMP = pHead->pre;
	_TEMP = TEMP->pre;
	print_array[(TEMP->coord).y][(TEMP->coord).x] = ' ';
	printf("%c", print_array[TEMP->coord.y][TEMP->coord.x]);
	_TEMP->next = pHead;
	pHead->pre = _TEMP;
	free(TEMP);
	return pHead;
}

struct NODE *list_insert(NODE *first, bool if_get_fruit)
{
	struct NODE *end = NULL;
	struct NODE *newfirst = (NODE *)malloc(sizeof(NODE));
	if (!newfirst) {
		printf("Memory calloc F\n");
		return NULL;
	}
	end = first->pre;
	first->pre = newfirst;
	newfirst->pre = end;
	newfirst->next = first;
	end->next = newfirst;
	switch (direction) {
	case 'w':
		(newfirst->coord).y = ((first->coord).y) - 1;
		(newfirst->coord).x = (first->coord).x;
		print_array[(newfirst->coord).y][(newfirst->coord).x] = '@';
		break;
	case 'a':
		(newfirst->coord).y = (first->coord).y;
		(newfirst->coord).x = (first->coord.x) - 1;
		print_array[(newfirst->coord).y][(newfirst->coord).x] = '@';
		break;
	case 's':
		(newfirst->coord).y = (first->coord.y) + 1;
		(newfirst->coord).x = (first->coord).x;
		print_array[(newfirst->coord).y][(newfirst->coord).x] = '@';
		break;
	case 'd':
		(newfirst->coord).y = (first->coord).y;
		(newfirst->coord).x = ((first->coord).x) + 1;
		print_array[(newfirst->coord).y][(newfirst->coord).x] = '@';
		break;
	}
	if_get_fruit = 0;
	return newfirst;
}

void print_frame()
{
	int i, index;
	for (i = 0; i < Y_MAX; i++)
	{
		for (index = 0; index < X_MAX; index++)
			printf("%c", print_array[i][index]);
		printf("\n");
	}
}

struct NODE* settings()
{
	int TEMPx, TEMPy;
	TEMPx = int(X_MAX / 2);
	TEMPy = int(Y_MAX / 2);

	// 初始化墙和蛇
	for (size_t i = 0; i < X_MAX; i++)		// 最上面一排
		print_array[0][i] = '-';
	for (size_t i = 0; i < X_MAX; i++)		// 最下面一排
		print_array[Y_MAX - 1][i] = '-';
	for (size_t i = 1; i < (Y_MAX - 1); i++) {	// 最左边和最右边一排
		print_array[i][0] = '|';
		print_array[i][X_MAX - 1] = '|';
	}
	for (size_t i = 1; i < (Y_MAX - 1); i++) {	// 其余部分
		for (size_t j = 1; j < (X_MAX - 1); j++) {
			print_array[i][j] = ' ';
		}
	}

	//初始链表创建
	print_array[TEMPy][TEMPx--] = '@';
	print_array[TEMPy][TEMPx--] = '@';
	print_array[TEMPy][TEMPx] = '@';
	TEMPx = int(X_MAX / 2);
	TEMPy = int(Y_MAX / 2);


	NODE *p, *h, *l;
	h = (NODE*)malloc(sizeof(NODE));
	h->coord.y = TEMPy;
	h->coord.x = TEMPx--;
	h->pre = NULL;			//空的双向链表前驱和后驱都会指向自己；
	h->next = NULL;
	p = h;
	for (size_t i = 0; i < 2; i++)
	{
		l = (NODE *)malloc(sizeof(NODE));
		((l->coord).x) = TEMPx--;	((l->coord).y) = TEMPy;		//赋值
		p->next = l;
		l->pre = p;
		l->next = h;      //注意，l->next链接的是头节点，　
		h->pre = l;		//而头结点的前驱是l。 这样便构成了一个循环的双向链表
		p = l;
	}
	return (h);			//返回链表

}

struct Coordinate gen_fruit(NODE *first)
{
	struct Coordinate fruit;
re_fruit:
	// 在1到X/Y_MAX之间取数
	srand(time(NULL));
	fruit.x = 1 + rand() % (X_MAX - 2);
	srand(time(NULL) % rand());
	fruit.y = 1 + rand() % (Y_MAX - 2);

	// 检查是否在蛇身上
	NODE *current = first->next;
	for (int i = 0; i < snake_count; i++) {
		if (fruit.x == (current->coord).x && fruit.y == (current->coord).y)
			goto re_fruit;
		current = current->next;
	}
	print_array[fruit.y][fruit.x] = '*';
	return fruit;
}

inline void kb_check()
{
	char temp;
	if (_kbhit())
	{
		temp = _getch();
		switch (temp)
		{
		case 'w':
			if (direction != 's')
				direction = 'w';
			break;
		case 's':
			if (direction != 'w')
				direction = 's';
			break;
		case 'a':
			if (direction != 'd')
				direction = 'a';
			break;
		case 'd':
			if (direction != 'a')
				direction = 'd';
			break;
		}
	}
}

void delay()
{
	time_t start_time, cur_time; // 变量声明
	time(&start_time);
	do {
		kb_check();
		time(&cur_time);
	} while ((cur_time - start_time) < TIME_DELAY);
}