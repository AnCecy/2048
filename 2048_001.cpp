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

void BeginToPlay(int chessb[4][4])		//��������ʼ�����������
{
	int i, j;
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			chessb[i][j] = 0;
		}
	}

	srand((int)time(0));		//��ʼ���������
	NewChess(chessb);
	NewChess(chessb);
	
	ShowTB(chessb, 0);
}

void NewChess(int chessb[4][4])		//�������������������
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
	for(i=1;i<5;i++)		//����һ�����̣������ֵĸ�����0��䣬�հ׵ĸ������±����
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
	while(i<=j)		//�������飬�����ֵķŵ�ǰ��׼�������ѡ��
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
			i++;		//�˴�ֻҪi��0��λ�ã������������򲻻���ƣ�˵��ѭ��������i��ֵ���ǵ�ǰ�������±�ĸ���
	}
	
	int x, y;
	int pick = rand()%i;		//���ѡ��һ�����������±꣬��Ϊx����Ϊy
	x = fakeb[pick]/10 - 1;
	y = fakeb[pick]%10 - 1;
	
	pick = rand()%2 + 1;		//�������2����4����������
	chessb[x][y] = pick*2;
}

int GameoverFlag(int chessb[4][4])
{
	return 1;
}

int GoingUp(int chessb[4][4])		//�����ƶ�����
{
	int i, j, m, n, zeroflag, moveflag = 0, score = 0;
	for(j=0;j<4;j++)
	{
		zeroflag = chessb[0][j] + chessb[1][j] + chessb[2][j] + chessb[3][j];		//�жϸ����Ƿ����Ԫ�أ�������Ϊ0

		if(zeroflag)
		{
			m = 0;
			n = 3;		//ָ��ͷβ��ָ��
			while(m<=n)		//���������Ӿۼ���һ��
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

			for(i=0;i<3;i++)		//��һ�ϲ�
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

int GoingDown(int chessb[4][4])		//�����ƶ�����
{
	int i, j, m, n, zeroflag, moveflag = 0, score = 0;
	for(j=0;j<4;j++)
	{
		zeroflag = chessb[0][j] + chessb[1][j] + chessb[2][j] + chessb[3][j];		//�жϸ����Ƿ����Ԫ�أ�������Ϊ0

		if(zeroflag)
		{
			m = 3;
			n = 0;		//ָ��ͷβ��ָ��
			while(m>=n)		//���������Ӿۼ���һ��
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

			for(i=3;i>0;i--)		//��һ�ϲ�
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