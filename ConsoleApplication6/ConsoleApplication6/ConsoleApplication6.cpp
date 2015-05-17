#include "stdafx.h"

static char print_array[Y_MAX][X_MAX];
static unsigned int score = 0;
static char direction = 'd';
using namespace std;

struct Coordinate			//点坐标
{
	int x,y;
};
struct NODE				//双向链表结构
{
	Coordinate coord;
	NODE* pre;
	NODE* next;
};

void list_delete(NODE *pHead);
struct NODE* list_insert(NODE *first);
short hitCheck(const NODE *first, struct Coordinate fruit);	//检验碰撞
void print_frame();
void delay();
void kb_check();
struct NODE* settings();
struct Coordinate gen_fruit(NODE *first);

int main()
{
	struct Coordinate fruit = {0, 0};
	struct NODE *pHead = NULL;
	short hit_re = 3;
	int answer = '\0';
	printf("The Gluttonous Snake Game\n");
	printf("\nPress enter to start\nPress anykey to EXIT\n");
	if ((answer = getchar()) == '\n') {
		system("cls");
	} else {
		return 0;
	}
	if (!(pHead = settings())) {
		printf("Initialization Faild\n");
		exit(-1);
	}

	fflush(stdin);
	//first start
	print_frame();
	//loop
	while (1)
	{
		pHead = list_insert(pHead);
		list_delete(pHead);
		hit_re = hitCheck(pHead, fruit);
		switch (hit_re)
		{
			case 3:
				break;
			case 2:
				++score;
				printf("\a");
				if (!(pHead = list_insert(pHead))) {
					printf("Memory F\n");
					exit(-1);
				}
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
		while (current != NULL) {
			current = current->next;
			free(pHead);
			pHead = current;

		}
		pHead = NULL;
		current = NULL;
		system("pause");
	return 0;
}

// 撞墙返回0，撞自己返回1，撞果子返回2，啥都没撞返回3
short hitCheck(const NODE *first,struct Coordinate fruit)
{
	int head_x = (first->coord).x, head_y = (first->coord).y;
	int body_x = 0, body_y = 0;

	// 吃到果子
	if (head_x == fruit.x && head_y == fruit.y)
		return 2;

	// 撞自己
	NODE *current = first->next;
	while (current != NULL) {
		if (head_x == (current->coord).x && head_y == (current->coord).y)
			return 1;
		current = current->next;

	}
	if ((first->coord).x == 0 || (first->coord).x == X_MAX || (first->coord).y == 0 || (first->coord).y == Y_MAX)
		return 1;
	// 啥都没撞
	return 3;
}

void list_delete(NODE* pHead)
{
	NODE* TEMP,*_TEMP;
	_TEMP = pHead->pre;
	TEMP = _TEMP->pre;
	print_array[(_TEMP->coord).y][(_TEMP->coord).x] = ' ';
	TEMP->next = pHead;
	pHead->pre = TEMP;
	free(_TEMP);
}

struct NODE *list_insert(NODE *first)
{
	struct NODE *end;
	struct NODE *newfirst = (NODE *)malloc(sizeof(NODE));
	if (!newfirst) {
		printf("Memory calloc F\n");
		return NULL;
	}
	end = first->pre;
	newfirst = first->pre;
	newfirst->next = first;
	newfirst->next = end;
	end->pre = newfirst;
	(newfirst->coord).x = (first->coord).x;				(newfirst->coord).y = (first->coord).y;
	switch (direction) {
	case 'w':
		(newfirst->coord).y = ((first->coord).y) + 1;
		(newfirst->coord).x = (first->coord).x;
		print_array[(newfirst->coord).y][(newfirst->coord).x] = 'O';
		break;
	case 'a':
		(newfirst->coord).y = (first->coord).y;
		(newfirst->coord).x = (first->coord.x) - 1;
		print_array[(newfirst->coord).y][(newfirst->coord).x] = 'O';
		break;
	case 's':
		(newfirst->coord).y = (first->coord.y) - 1;
		(newfirst->coord).x = (first->coord).x;
		print_array[(newfirst->coord).y][(newfirst->coord).x] = 'O';
		break;
	case 'd':
		(newfirst->coord).y = (first->coord).y;
		(newfirst->coord).x = ((first->coord).x) + 1;
		print_array[(newfirst->coord).y][(newfirst->coord).x] = 'O';
		break;
	}
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
	print_array[TEMPy][TEMPx--] = 'O';
	print_array[TEMPy][TEMPx] = 'O';
	TEMPx = int(X_MAX / 2);
	TEMPy = int(Y_MAX / 2);


	NODE *p, *h, *l;
	h = (NODE*)malloc(sizeof(NODE));
	h->pre = NULL;			//当空的双向链表就像上图那样前驱和后驱都会指向自己；
	h->next = NULL;
	p = h;
	for (size_t i = 0; i < 3; i++)
	{
		l = (NODE *)malloc(sizeof(NODE));
		((l->coord).x) = TEMPx;	((l->coord).y) = TEMPy;		//赋值
		p->next = l;
		l->pre = p;
		l->next = h;      //注意，l->next链接的是头节点，　
		h->pre = l;		//而头结点的前驱是l。 这样便构成了一个循环的双向链表
		p = l;
		TEMPy--;
	}
	return (h);			//返回链表

}

struct Coordinate gen_fruit(NODE *first)
{
	struct Coordinate fruit;
	re_fruit:
		// 在1到X/Y_MAX之间取数
		srand(time(NULL));
		fruit.x = 1 + rand() % (X_MAX - 1);
		srand(time(NULL));
		fruit.y = 1 + rand() % (Y_MAX - 1);

		// 检查是否在蛇身上
		NODE *current = first->next;
		while (current != NULL) {
			if (fruit.x == (current->coord).x && fruit.y == (current->coord).y)
				goto re_fruit;
			current = current->next;
		}
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
