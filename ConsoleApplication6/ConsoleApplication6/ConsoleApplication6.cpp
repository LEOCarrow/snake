// ConsoleApplication6.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

char print_array[X_MAX][Y_MAX];
char direction;
bool if_get_fruit=0;
using namespace std;

struct NODE
{
	int x,y;
	NODE* pre;
	NODE* next;
};												//双向链表结构
void list_delete();
struct NODE *insert(const char direction, NODE *first);
void list_check();							//检验碰撞
//边框
void print_frame();
//初始化
void settings();

int _tmain(int argc, _TCHAR* argv[])
{
	settings();
	int Me_result = MessageBox(NULL, TEXT("press OK to start\npress cancel to exit"),
		TEXT("game"), MB_ICONINFORMATION | MB_YESNO);
	switch (Me_result)
	{
	case IDYES: break;
	case IDNO:goto exit;
	}
	while (1)
	{
		print_frame();
	}
	exit:
	system("pause");
	return 0;
}


void list_check()
{

}


NODE *list_delete(NODE *previous,NODE *last)
{
	free(last);
	last = NULL;
	previous->next = NULL;
	return previous;
}

NODE *list_insert(const char direction, NODE *first)
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
	case 'a':
		newfirst->y = first->y;
		newfirst->x = first->x - 1;
	case 's':
		newfirst->y = first->y - 1;
		newfirst->x = first->x;
	case 'd':
		newfirst->y = first->y;
		newfirst->x = first->x + 1;
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
		cout << endl;
	}
}


void settings()
{
	int i, j, z,TEMPx,TEMPy;
	TEMPx = 0.5*X_MAX;
	TEMPy = 0.5*Y_MAX;
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
}
