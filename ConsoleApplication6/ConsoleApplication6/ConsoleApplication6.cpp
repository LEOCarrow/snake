#include "stdafx.h"

char print_array[X_MAX][Y_MAX];
static char direction,temp;
static bool if_get_fruit = FALSE;
using namespace std;

struct NODE
{
	int x,y;
	NODE* pre;
	NODE* next;
};
										//双向链表结构
NODE* list_delete(NODE *last);
NODE* insert(const char direction, NODE *first);
void list_check(NODE *first);							//检验碰撞
void print_frame();
NODE* settings();

int _tmain(int argc, _TCHAR* argv[])
{
	int Nowtime, Pretime,index;
	NODE *pHead,*pEnd;
	pHead = settings();
	pEnd = pHead;
	int Me_result = MessageBox(NULL,
			TEXT("press OK to start\npress cancel to exit"),
			TEXT("game"), MB_ICONINFORMATION | MB_YESNO);
	switch (Me_result)
	{
		case IDYES: break;
		case IDNO:goto exit;
	}
	while (pEnd != NULL)
	{
		pEnd->next;
	}
	print_frame();
	while (1)
	{
		if (_kbhit())
		{
			temp = _getch();
			if (temp == 'w' || temp == 's' || temp == 'a' || temp == 'd')
				direction = temp;
		}
		pEnd = list_delete(pEnd);
		pHead = insert(direction,pHead);
		list_check(pHead);
		print_frame();
		Pretime = clock();
		for (index = 0;; index++)
		{
			if (_kbhit())
			{
				temp = _getch();
				if (temp == 'w' || temp == 's' || temp == 'a' || temp == 'd')
					direction = temp;
			}
			Nowtime = clock();
			if ((Nowtime - Pretime) >= TIME_DELAY)
				break;
		}
	}
exit:
	free(pHead);	 free(pEnd);
	system("pause");
	return 0;
}


void list_check(NODE *first)
{
	NODE *current = first;
	while (current != NULL) {
		
	}
}

NODE *list_delete(NODE* last)
{
	NODE *temp;
	print_array[last->x][last->y] = ' ';
	temp = last->pre;
	temp->next = NULL;
	return temp;
	free(last);
}

NODE *insert(const char direction, NODE *first)
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


NODE* settings()
{
	int i, j, z,TEMPx,TEMPy;
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
	struct NODE* pNew;
	struct NODE* pHead = NULL;
	struct NODE* pEnd;
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
	//the second op
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
