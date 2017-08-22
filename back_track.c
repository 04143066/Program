#include <stdio.h>
#include <malloc.h>
#define NUM 4

typedef struct n
{
	int n;		                                 	//集装箱数量
	int w[NUM];                              		//集装箱重量
	int x[NUM];                                    		//集装箱操作
	int v[NUM];                          			//集装箱价值
	int c;                                          	//背包承受量
	int cw;                                          	//背包当前重量 
	int bestvalue;                                   	//当前最优价值 
	int value;                                       	//当前价值 
}node;

void backtrack(int t,node no);
void output(node no);
int bound(int i,node no);
node init();

int main()
{
	node no;
	no = init();
	backtrack(0, no);
	return 0;
}

node init()
{
	int i;
	node no;
	no.n = NUM;		                                    //集装箱数量
	int w[NUM] = {7,3,4,5};                         
	int x[NUM] = {0};      
	int v[NUM] = {42,12,40,25}; 
	for(i=0; i<NUM; i++)
	{
		no.w[i] = w[i];
		no.x[i] = x[i];
		no.v[i] = v[i];
	}
	no.cw = 0;                                          //背包当前重量 
	no.c = 10;                                          //背包承受量 
	no.bestvalue = 0;                                   //当前最优价值 
	no.value = 0;                                       //当前价值 
	return no;
}

void backtrack(int t,node no)
{
	if(t >= no.n)
	{
		output(no);
	}
	else
	{
		if(no.cw + no.w[t] <=no.c)
		{
			no.x[t] = 1;
			no.cw += no.w[t];
			no.value += no.v[t];
			backtrack(t+1,no);
			no.cw -= no.w[t];
			no.value -=no.v[t];
		}
		if(bound(t+1,no) > no.bestvalue)
		{
			no.x[t] = 0;
			backtrack(t+1,no);
		}
		backtrack(t+1,no);
	}
}

int bound(int i,node no)
{
	int max = 0;
	int left = no.c-no.cw;
	while(i <= no.n && no.w[i] <=left)
	{
		left -= no.w[i];
		max += no.v[i];
		i++;
	}
	if( i<=no.n )
	{
		max += no.v[i] + (left/no.w[i]);
	}
	return max;
}

void output(node no) 
{
	static int count = 0;
	int i;
	if(no.value > no.bestvalue)
	{
		no.bestvalue = no.value;
	}
	printf("No.%2d  ",++count);
	for(i=0; i<no.n; i++)
	{
		printf("   %d  ",no.x[i]);
	}
	printf("    最优解: %d  ",no.bestvalue);
	printf("\n");
}
