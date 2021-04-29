#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void ShowTB(int chessb[4][4], int score);
void BeginToPlay(int chessb[4][4]);
void NewChess(int chessb[4][4]);
int GameoverFlag(int chessb[4][4]);
int GoingUp(int chessb[4][4]);
int GoingDown(int chessb[4][4]);
//int GoingLeft(int chessb[4][4]);
//int GoingRight(int chessb[4][4]);

void main()
{
	int chessb[4][4];
	int score = 0;

	BeginToPlay(chessb);

	char order;
	while(GameoverFlag(chessb))
	{
		scanf("%c",&order);
		switch(order)
		{
			case 'w':	score += GoingUp(chessb);	ShowTB(chessb, score);	break;
			case 's':	score += GoingDown(chessb);	ShowTB(chessb, score);	break;
/*			case 'a': GoingLeft;
			case 'd': GoingRight;
			case 'r': ReStart;*/
		}
	}
}

void ShowTB(int chessb[4][4], int score)
{
	printf("\n\n");
	
	int i, j;
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			printf("\t%d",chessb[i][j]);
		}
		printf("\n\n");
	}

	printf("\tscore %d\n",score);
	printf("\tpress w,s,a,d to move\n\tpress r to restart\n\n");
}

void BeginToPlay(int chessb[4][4])		//函数：初始化并输出棋盘
{
	int i, j;
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			chessb[i][j] = 0;
		}
	}

	srand((int)time(0));		//起始随机数种子
	NewChess(chessb);
	NewChess(chessb);
	
	ShowTB(chessb, 0);
}

void NewChess(int chessb[4][4])		//函数：随机出现新棋子
{	
	int fakeb[16];

	int i, j;
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			fakeb[4*i+j] = chessb[i][j];
		}
	}

	int n = 0;
	for(i=1;i<5;i++)		//复制一个棋盘，有数字的格子用0填充，空白的格子用下标填充
	{
		for(j=1;j<5;j++)
		{
			if(fakeb[n])
			{
				fakeb[n] = 0;
				n++;
			}
			else
			{
				fakeb[n] = i*10 + j;
				n++;
			}
		}
	}

	int temp;
	i = 0;
	j = 15;
	while(i<=j)		//遍历数组，有数字的放到前排准备被随机选择
	{
		if(fakeb[i]==0)
		{
			if(fakeb[j]==0)
				j--;
			else
			{
				temp = fakeb[i];
				fakeb[i] = fakeb[j];
				fakeb[j] = temp;
				i++;
				j--;
			}
		}
		else
			i++;		//此处只要i在0的位置，不发生交换则不会后移，说明循环结束后i的值就是当前数组有下标的个数
	}
	
	int x, y;
	int pick = rand()%i;		//随机选择一个数，读出下标，行为x，列为y
	x = fakeb[pick]/10 - 1;
	y = fakeb[pick]%10 - 1;
	
	pick = rand()%2 + 1;		//随机生成2或者4并插入棋盘
	chessb[x][y] = pick*2;
}

int GameoverFlag(int chessb[4][4])
{
	return 1;
}

int GoingUp(int chessb[4][4])		//向上移动函数
{
	int i, j, m, n, zeroflag, moveflag = 0, score = 0;
	for(j=0;j<4;j++)
	{
		zeroflag = chessb[0][j] + chessb[1][j] + chessb[2][j] + chessb[3][j];		//判断该列是否存在元素，存在则不为0

		if(zeroflag)
		{
			m = 0;
			n = 3;		//指向头尾的指针
			while(m<=n)		//将所有棋子聚集到一边
			{
				while(chessb[n][j]==0)
				{
					n--;
				}
				if(chessb[m][j]==0)
				{
					for(i=m;i<3;i++)
						chessb[i][j] = chessb[i+1][j];
					chessb[3][j] = 0;
					n--;
					moveflag = 1;
					continue;
				}
				else
					m++;
			}

			for(i=0;i<3;i++)		//逐一合并
			{
				if(chessb[i][j]==chessb[i+1][j]&&chessb[i][j]!=0)
				{
					chessb[i][j] *= 2;
					score += chessb[i][j];
					for(m=i+1;m<3;m++)
					{
						chessb[m][j] = chessb[m+1][j];
					}
					moveflag = 1;
				}
			}
		}
	}
	
	if(moveflag)
	{
		NewChess(chessb);
	}

	return score;
}

int GoingDown(int chessb[4][4])		//向下移动函数
{
	int i, j, m, n, zeroflag, moveflag = 0, score = 0;
	for(j=0;j<4;j++)
	{
		zeroflag = chessb[0][j] + chessb[1][j] + chessb[2][j] + chessb[3][j];		//判断该列是否存在元素，存在则不为0

		if(zeroflag)
		{
			m = 3;
			n = 0;		//指向头尾的指针
			while(m>=n)		//将所有棋子聚集到一边
			{
				while(chessb[n][j]==0)
				{
					n++;
				}
				if(chessb[m][j]==0)
				{
					for(i=m;i>0;i--)
						chessb[i][j] = chessb[i-1][j];
					chessb[0][j] = 0;
					n++;
					moveflag = 1;
					continue;
				}
				else
					m--;
			}

			for(i=3;i>0;i--)		//逐一合并
			{
				if(chessb[i][j]==chessb[i-1][j]&&chessb[i][j]!=0)
				{
					chessb[i][j] *= 2;
					score += chessb[i][j];
					for(m=i-1;m>0;m--)
					{
						chessb[m][j] = chessb[m-1][j];
					}
					moveflag = 1;
				}
			}
		}
	}
	
	if(moveflag)
	{
		NewChess(chessb);
	}

	return score;
}

/*
int GoingLeft(int chessb[4][4])
{}

int GoingRight(int chessb[4][4])
{}
/*
int ReStart()
{}
*/