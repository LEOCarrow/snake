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

class list
{
	NODE* head;
	NODE* tail;
public:
	list(){ head = NULL; tail = NULL; }			//头指针与尾指针初始化
	void list_insert(char direction);			//添加
	void list_delete();							//删除
};

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

	print_frame();
	exit:
	system("pause");
	return 0;
}


void list_check()
{

}


void list::list_delete()
{

}


void list::list_insert(char direction)
{

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