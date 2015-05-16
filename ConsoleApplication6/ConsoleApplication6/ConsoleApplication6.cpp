#include "stdafx.h"

char print_array[X_MAX][Y_MAX];
static char direction,temp;
using namespace std;

struct NODE				//双向链表结构
{
	Coordinate coord;
	NODE* pre;
	NODE* next;
};

struct Coordinate
{
	int x,y;
};

struct NODE* list_delete(NODE *last);
struct NODE* list_insert(const char direction, NODE *first);
short hitCheck(const NODE *first, int fruit_x, int fruit_y);	//检验碰撞
void print_frame();
struct NODE* settings();
struct Coordinate gen_fruit(NODE *first);

int main()
{
	int Nowtime, Pretime,index;
	struct Coordinate fruit = {0, 0};
	struct NODE *pHead = NULL, *pEnd = NULL;
	if (!(pHead = settings())) {
		printf("Initialization Faild\n");
		exit(-1);
	}
	pEnd = pHead;
	//pointers
	printf("The Gluttonous Snake Game\n");
	printf("\nPress enter to start\nPress anykey to EXIT\n");
	char answer = getchar();
	if (answer == '\n') {
		printf("Ready Go!\n");
	} else {
		goto EXIT;
	}

	while (pEnd != NULL)
	{
		pEnd->next;
	}
	print_frame();
	while (1)
	{
		system("cls");
		if (_kbhit())
		{
			temp = _getch();
			if (temp == 'w' || temp == 's' ||
					temp == 'a' || temp == 'd')
				direction = temp;
		}
		pEnd = list_delete(pEnd);
		pHead = list_insert(direction,pHead);
		hitCheck(pHead, fruit.x, fruit.y);
		print_frame();
		Pretime = clock();
		for (;;)
		{
			if (_kbhit())
			{
				temp = _getch();
				if (temp == 'w' || temp == 's' ||temp == 'a' || temp == 'd')
					direction = temp;
			}
			Nowtime = clock();
			if (difftime(Nowtime,Pretime) >= TIME_DELAY)
				break;
		}
	}
EXIT:
		free(pHead);	 free(pEnd);
		system("pause");
	return 0;
}

// 撞墙返回0，撞自己返回1，撞果子返回2，啥都没撞返回3
short hitCheck(const NODE *first,int fruit_x, int fruit_y)
{
	int head_x = first->x, head_y = first->y;
	int body_x = 0, body_y = 0;

	// 吃到果子
	if (head_x == fruit_x && head_y == fruit_y) {
		return 2;
	}

	// 撞墙
	if (head_y == 0 || head_y == Y_MAX ||
				head_x == 0 || head_x == X_MAX) {
		return 0;
	}

	// 撞自己
	NODE *current = first->next;
	while (current != NULL) {
		if (head_x == current->x && head_y == current->y)
			return 1;
		current = current->next;

	}

	// 啥都没撞
	return 3;
}

struct NODE *list_delete(NODE* last)
{
	NODE *temp;
	print_array[last->x][last->y] = ' ';
	temp = last->pre;
	temp->next = NULL;
	return temp;
	free(last);
}

struct NODE *list_insert(const char direction, NODE *first)
{
	NODE *newfirst = (NODE *)malloc(sizeof(NODE));
	if (!newfirst) {
		printf("Memory calloc F\n");
		return NULL;
	}
	newfirst->next = first;
	newfirst->pre = NULL;
	first->pre = newfirst;

	switch (direction) {
	case 'w':
		newfirst->y = first->y + 1;
		newfirst->x = first->x;
		print_array[newfirst->x][newfirst->y = '█'];
		break;
	case 'a':
		newfirst->y = first->y;
		newfirst->x = first->x - 1;
		print_array[newfirst->x][newfirst->y] = '█';
		break;
	case 's':
		newfirst->y = first->y - 1;
		newfirst->x = first->x;
		print_array[newfirst->x][newfirst->y] = '█';
		break;
	case 'd':
		newfirst->y = first->y;
		newfirst->x = first->x + 1;
		print_array[newfirst->x][newfirst->y] = '█';
		break;
	default:
		return NULL;
	}
	return newfirst;
}


void print_frame()
{
	int i, index;
	for (i = 0; i < 15; i++)
	{
		for (index = 0; index < 15; index++)
			printf("%c", print_array[i][index]);
		printf("\n");
	}
}


struct NODE* settings()
{
	int i, j, z, TEMPx, TEMPy;
	TEMPx = int(0.5*X_MAX);
	TEMPy = int(0.5*Y_MAX);
	for (i = 0; i < 15; i++)
	{
		for (j = 0; j < 15; j++)
		{
			if (i == 0 || i == 14)
			{
				for (j = 0; j < 15; j++)
				{
					print_array[i][j] = '.';
				}
			}
			else
			{
				print_array[i][0] = '.';
				for (z = 1; z < 14; z++)
				{
					print_array[i][z] = ' ';
				}
				print_array[i][14] = '.';
			}
		}
	}
	print_array[TEMPx][TEMPy] = '@'; TEMPy--;
	print_array[TEMPx][TEMPy] = '█'; TEMPy--;
	print_array[TEMPx][TEMPy] = '█';

	//初始链表创建
	struct NODE* pNew = NULL;
	struct NODE* pHead = NULL;
	struct NODE* pEnd = NULL;
	//the first op
	pEnd = pNew = (struct NODE*)malloc(sizeof(struct NODE));
	if (!pNew) {
		printf("Memory calloc F\n");
		return NULL;
	}
	(pNew->x) = 7; (pNew->y) = 7;
	pNew->next = pHead;
	pEnd = pNew;
	pHead = pNew;
	pEnd->pre = NULL;
	//the second op
	pNew = (struct NODE*)malloc(sizeof(struct NODE));
	if (!pNew) {
		printf("Memory calloc F\n");
		return NULL;
	}

	pNew->pre = pEnd;
	(pNew->x) = 7; (pNew->y) = 6;
	pNew->pre = NULL;
	pNew->next = NULL;
	pEnd->next = pNew;
	pHead = pNew;
	//the third op
	pNew = (struct NODE*)malloc(sizeof(struct NODE));
	if (!pNew) {
		printf("Memory calloc F\n");
		return NULL;
	}

	pNew->pre = pEnd;
	(pNew->x) = 7; (pNew->y) = 5;
	pNew->next = NULL;
	pEnd->next = pNew;
	pHead = pNew;
	free(pNew);
	return pHead;
}

// 生成水果
Coordinate gen_fruit(NODE *first) {
	Coordinate fruit;
re_fruit:
	while (1) {
		// 在1到X/Y_MAX之间取数
		srand(time(NULL));
		fruit.x = 1 + rand() % (X_MAX - 1);
		srand(time(NULL));
		fruit.y = 1 + rand() % (Y_MAX - 1);

		// 检查是否在蛇身上
		NODE *current = first->next;
		while (current != NULL) {
			if (fruit.x == current->x && fruit.y == current->y)
				goto re_fruit;
			if (fruit.x == current->x &&fruit.y == current->y)
				break;
			current == current->next;
		}
	return fruit;
}
