#include "stdafx.h"

char print_array[Y_MAX][X_MAX];
static char direction,temp;
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

struct NODE* list_delete(NODE *last);
struct NODE* list_insert(const char direction, NODE *first);
short hitCheck(const NODE *first, struct Coordinate fruit);	//检验碰撞
void print_frame();
struct NODE* settings();
struct Coordinate gen_fruit(const NODE *first);

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

	printf("The Gluttonous Snake Game\n");
	printf("\nPress enter to start\nPress anykey to EXIT\n");
	char answer = getchar();
	if (answer == '\n') {
		printf("Ready Go!\n");
	} else {
		return 0;
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
		hitCheck(pHead, fruit);
		print_frame();
		Pretime = clock();
		for (;;)
		{
			if (_kbhit())
			{
				temp = _getch();
				if (temp == 'w' || temp == 's' ||
						temp == 'a' || temp == 'd')
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
short hitCheck(const NODE *first,struct Coordinate fruit)
{
	int head_x = first->coord.x, head_y = first->coord.y;
	int body_x = 0, body_y = 0;

	// 吃到果子
	if (head_x == fruit.x && head_y == fruit.y)
		return 2;

	// 撞墙
	if (head_y == 0 || head_y == Y_MAX ||
				head_x == 0 || head_x == X_MAX)
		return 0;

	// 撞自己
	NODE *current = first->next;
	while (current != NULL) {
		if (head_x == current->coord.x && head_y == current->coord.y)
			return 1;
		current = current->next;

	}

	// 啥都没撞
	return 3;
}

struct NODE *list_delete(NODE* last)
{
	struct NODE *temp;
	print_array[last->coord.y][last->coord.x] = ' ';
	temp = last->pre;
	temp->next = NULL;
	free(last);
	return temp;
}

struct NODE *list_insert(const char direction, NODE *first)
{
	struct NODE *newfirst = (NODE *)malloc(sizeof(NODE));
	if (!newfirst) {
		printf("Memory calloc F\n");
		return NULL;
	}
	newfirst->next = first;
	newfirst->pre = NULL;
	first->pre = newfirst;

	switch (direction) {
	case 'w':
		newfirst->coord.y = (first->coord.y) + 1;
		newfirst->coord.x = first->coord.x;
		print_array[newfirst->coord.y][newfirst->coord.x] = '█';
		break;
	case 'a':
		newfirst->coord.y = first->coord.y;
		newfirst->coord.x = (first->coord.x) - 1;
		print_array[newfirst->coord.y][newfirst->coord.x] = '█';
		break;
	case 's':
		newfirst->coord.y = (first->coord.y) - 1;
		newfirst->coord.x = first->coord.x;
		print_array[newfirst->coord.y][newfirst->coord.x] = '█';
		break;
	case 'd':
		newfirst->coord.y = first->coord.y;
		newfirst->coord.x = (first->coord.x) + 1;
		print_array[newfirst->coord.y][newfirst->coord.x] = '█';
		break;
	default:
		return NULL;
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
	int i, j, z, TEMPx, TEMPy;
	TEMPx = int(0.5*X_MAX);
	TEMPy = int(0.5*Y_MAX);

	// 初始化墙和虫
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
	struct NODE* pNew = NULL;
	struct NODE* pHead = NULL;
	struct NODE* pEnd = NULL;
	//the first op
	pEnd = pNew = (struct NODE*)malloc(sizeof(struct NODE));
	if (!pNew) {
		printf("Memory calloc F\n");
		return NULL;
	}
	(pNew->coord.x) = TEMPx; (pNew->coord.y) = TEMPy;
	print_array[TEMPy][TEMPx] = '@'; TEMPy--;
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
	(pNew->coord.x) = TEMPx; (pNew->coord.y) = TEMPy;
	print_array[TEMPy][TEMPx] = '█'; TEMPy--;
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
	(pNew->coord.x) = TEMPx; (pNew->coord.y) = TEMPy;
	print_array[TEMPy][TEMPx] = '█';
	pNew->next = NULL;
	pEnd->next = pNew;
	pHead = pNew;
	free(pNew);
	return pHead;
}

// 生成水果
struct Coordinate gen_fruit(const NODE *first) {
	struct Coordinate fruit;
	while (TRUE) {
		// 在1到X/Y_MAX之间取数
		srand(time(NULL));
		fruit.x = 1 + rand() % (X_MAX - 1);
		srand(time(NULL));
		fruit.y = 1 + rand() % (Y_MAX - 1);

		// 检查是否在蛇身上
		NODE *current = first->next;
		while (current != NULL) {
			if (fruit.x == current->x &&
					fruit.y == current->y)
				break;
			current == current->next;
		}
	}
	return fruit;
}
