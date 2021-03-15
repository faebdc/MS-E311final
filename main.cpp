#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;
const int N = 105;
const int M = 105;
const int Questions = 7;
const bool Details = 0;

class mdp
{
	int n,m,d;	// n is the number of actions, and m is the number of states
	double p[M][N][M];	// p_{ijk} is the probability that transform from state i to state k, after action j, 
	double y[M];	// y_i is the cost-to-go value in state i
	double y0[M];	// y_0
	double c[N];	// c_i is the cost of action i
	double gamma;	// gamma is the discount factor
	bool A[M][N];	// A_{ij} denote whether action j is available on state i
	double temp[N+M];	// for intermediate result
	bool tempbool[N+M], tempboolx[N+M];
	
	
	public:
	
	void setN(int x)
	{
		n=x;
	}
	
	void setM(int x)
	{
		m=x;
	}
	
	void setD(int x)
	{
		d=x;
		setM(d*d);
	}
	
	int cz(int x,int y)
	{
		return((x-1)*d+y);
	}
	
	int cx(int x)
	{
		return((x+d-1)/d);
	}
	
	int cy(int x)
	{
		return((x-1)%d+1);
	}
	
	int abss(int x)
	{
		if(x<0)
			x=-x;
		return x;
	}
	
	bool neighbor(int x,int y)
	{
		return ( (abss(cx(x)-cx(y))+ abss(cy(x)-cy(y)) ) == 1);
	}
	
	void randomP()
	{
		int i,j,k;
		for(i=1;i<=m;i++)
		{
			for(j=1;j<=n;j++)
			{
				int tot=0;
				while(!tot)
				{
					for(k=1;k<=m;k++)
					{
						p[i][j][k]=rand();
						tot+=p[i][j][k];
					}
				}
				for(k=1;k<=m;k++)
					p[i][j][k]/=tot;
			}
		}
	}
	
	void randomPMaze()
	{
		int i,j,k;
		for(i=1;i<=m;i++)
		{
			for(j=1;j<=n;j++)
			{
				int tot=0;
				while(!tot)
				{
					for(k=1;k<=m;k++)
					{
						if(neighbor(i,k))
							p[i][j][k]=rand();
						else
							p[i][j][k]=0;
						tot+=p[i][j][k];
					}
				}
				for(k=1;k<=m;k++)
					p[i][j][k]/=tot;
			}
		}
	}
	
	
	
	void randomA()
	{
		int i,j;
		for(i=1;i<=m;i++)
		{
			int tot=0;
			while(!tot)
			{
				for(j=1;j<=n;j++)
				{
					if(rand()&1)
					{
						A[i][j]=1;
						tot++;
					}
					else
						A[i][j]=0;
				}
			}
		}
	}
	
	void randomAMaze()
	{
		int i,j;
		for(i=1;i<=m;i++)
		{
			int tot=0;
			while(!tot)
			{
				for(j=1;j<=n;j++)
				{
					if(rand()&1)
					{
						A[i][j]=1;
						tot++;
					}
					else
						A[i][j]=0;
				}
			}
		}
	}
	
	void randomC()
	{
		int i;
		for(i=1;i<=n;i++)
		{
			c[i]=rand();
			c[i]/=1e4;
		}
	}
	
	void randomGamma()
	{
		gamma=rand();
		gamma+=10000;
		gamma/=50000;
	}
	
	void setSameY0(double x)
	{
		int i;
		for(i=1;i<=m;i++)
			y0[i]=x;
	}
	
	void printP()
	{
		printf("P=\n");
		int i,j,k;
		for(i=1;i<=m;i++)
		{
			for(j=1;j<=n;j++)
			{
				for(k=1;k<=m;k++)
					printf("%.3f ",p[i][j]);
				printf("\n");
			}
			printf("\n");
		}
		printf("\n");
	}
	
	void printY()
	{
		printf("y=\n");
		int i;
		for(i=1;i<=m;i++)
		{
			printf("%.6f ",y[i]);
		}
		printf("\n");
		printf("\n");
	}
	
	void printC()
	{
		printf("c=\n");
		int i;
		for(i=1;i<=m;i++)
		{
			printf("%.3f ",c[i]);
		}
		printf("\n");
		printf("\n");
	}
	
	void printGamma()
	{
		printf("gamma=\n");
		printf("%.3f ",gamma);
		printf("\n");
		printf("\n");
	}
	
	int getm()
	{
		return m;
	}
	
	void initY(bool print)
	{
		int i;
		if(print)
			printf("y[%d]=  ",0);
		for(i=1;i<=m;i++)
		{
			y[i]=y0[i];
			if(print)
				printf("%.6f ",y[i]);
		}
		if(print)
			printf("\n");
	}
	
	void printYSimple()
	{
		int i;
		for(i=1;i<=m;i++)
		{
			printf("%.6f ",y[i]);
		}
	}
	
	void VI(int rounds, bool print)
	{
		
		int i,j,k,l;
		
		
		initY(1);
		
		printf("VI:\n");
		
		for(j=1;j<=10000;j++)
		{
			for(i=1;i<=m;i++)
			{
				double nowx=1e100;
				for(k=1;k<=n;k++)
				{
					if(!A[i][k])
						continue;
					double now=c[k];
					for(l=1;l<=m;l++)
						now+=gamma*p[i][k][l]*y[l];
					nowx=min(nowx,now);
				}
				temp[i]=nowx;
			}
			for(i=1;i<=m;i++)
			{
				y[i]=temp[i];
			}
			if(j<=rounds && (print || j==rounds) || j==10000)
			{
				printf("y[%d]=  ",j);
				printYSimple();
				printf("\n");
			}
		}
		
		printf("\n");
	}
	
	
	void RandomVI(int rounds, bool print, int sampleSize)
	{
		
		int i,j,k,l,icnt;
		
		
		initY(Details);
		
		printf("RandomVI with sample size %d:\n", sampleSize);
		
		for(j=1;j<=rounds;j++)
		{
			for(i=1;i<=m;i++)
				temp[i]=y[i];
			memset(tempbool,0,sizeof tempbool);
			tempbool[0]=1;
			for(icnt=1;icnt<=sampleSize;icnt++)
			{
				i=rand()%(m+1);
				while(tempbool[i])
					i=rand()%(m+1);
				tempbool[i]=1;
				
				double nowx=1e100;
				for(k=1;k<=n;k++)
				{
					if(!A[i][k])
						continue;
					double now=c[k];
					for(l=1;l<=m;l++)
						now+=gamma*p[i][k][l]*y[l];
					nowx=min(nowx,now);
				}
				temp[i]=nowx;
			}
			for(i=1;i<=m;i++)
			{
				y[i]=temp[i];
			}
			if(print || j==rounds)
			{
				printf("y[%d]=  ",j);
				printYSimple();
				printf("\n");
			}
		}
		
		if(Details)
			printf("\n");
	}
	
	
	void RandomVIInfluence(int rounds, bool print, int sampleSize)
	{
		
		int i,j,k,l,icnt;
		bool relate;
		
		
		initY(Details);
		
		printf("RandomVI based on influence tree with sample size %d:\n", sampleSize);
		
		
		for(i=1;i<=m;i++)
			tempbool[i]=1;
		
		for(j=1;j<=rounds;j++)
		{
			for(i=1;i<=m;i++)
				temp[i]=y[i];
			for(i=1;i<=m;i++)
				tempboolx[i]=tempbool[i];
			memset(tempbool,0,sizeof tempbool);
			tempbool[0]=1;
			for(icnt=1;icnt<=sampleSize;icnt++)
			{
				relate=0;
				i=rand()%(m+1);
				while(tempbool[i] || !relate)
				{
					i=rand()%(m+1);
					for(k=1;k<=m;k++)
					{
						if( tempboolx[k] && neighbor(i,k) )		//This is special for the maze game.
							relate=1;
					}
				}
				tempbool[i]=1;
				
				double nowx=1e100;
				for(k=1;k<=n;k++)
				{
					if(!A[i][k])
						continue;
					double now=c[k];
					for(l=1;l<=m;l++)
						now+=gamma*p[i][k][l]*y[l];
					nowx=min(nowx,now);
				}
				temp[i]=nowx;
			}
			for(i=1;i<=m;i++)
			{
				y[i]=temp[i];
			}
			if(print || j==rounds)
			{
				printf("y[%d]=  ",j);
				printYSimple();
				printf("\n");
			}
		}
		
		if(Details)
			printf("\n");
	}
	
	
	void CyclicVI(int rounds, bool print)
	{
		
		int i,j,k,l;
		
		
		initY(Details);
		
		printf("CyclicVI:\n");
		
		for(j=1;j<=rounds;j++)
		{
			for(i=1;i<=m;i++)
			{
				double nowx=1e100;
				for(k=1;k<=n;k++)
				{
					if(!A[i][k])
						continue;
					double now=c[k];
					for(l=1;l<=m;l++)
						now+=gamma*p[i][k][l]*y[l];
					nowx=min(nowx,now);
				}
				y[i]=nowx;
			}
			if(print || j==rounds)
			{
				printf("y[%d]=  ",j);
				printYSimple();
				printf("\n");
			}
		}
		
		printf("\n");
	}
	
	
	void RPCyclicVI(int rounds, bool print)
	{
		
		int i,j,k,l,icnt;
		
		
		initY(Details);
		
		printf("RPCyclicVI:\n");
		
		for(j=1;j<=rounds;j++)
		{
			for(i=1;i<=m;i++)
				temp[i]=y[i];
			memset(tempbool,0,sizeof tempbool);
			tempbool[0]=1;
			for(icnt=1;icnt<=m;icnt++)
			{
				i=rand()%(m+1);
				while(tempbool[i])
					i=rand()%(m+1);
				tempbool[i]=1;
				
				double nowx=1e100;
				for(k=1;k<=n;k++)
				{
					if(!A[i][k])
						continue;
					double now=c[k];
					for(l=1;l<=m;l++)
						now+=gamma*p[i][k][l]*y[l];
					nowx=min(nowx,now);
				}
				y[i]=nowx;
			}
			if(print || j==rounds)
			{
				printf("y[%d]=  ",j);
				printYSimple();
				printf("\n");
			}
		}
		
		printf("\n");
	}
	
	mdp()
	{
		/*****
		setN(10);
		setM(10);
		randomP();
		randomC();
		randomGamma();
		randomA();
		*****/
		
		setN(10);
		setD(3);	// d*d states, here d=3, a 3*3 maze
		randomPMaze();
		randomC();
		randomGamma();
		randomA();
	}
};

void init()
{
	//srand(time(0));
	srand(0);
	rand();
}

int main()
{
	freopen("out.txt","w",stdout);
	
	init();
	static mdp a;
	
	/**********     Problem 4     **********/
	
	{
	if(Questions&1)
	{
		printf("Question 4:\n\n");
		
		a.setSameY0(0.0);
		//a.printP();
		//a.printC();
		//a.printGamma();
		a.VI(20,Details);
		int i;
		int m=a.getm();
		for(i=1;i<=m;i++)
		{
			a.RandomVI(100,Details,i);
			a.RandomVIInfluence(100,Details,i);
		}
		
		printf("\n\n********************\n");
	}
	}
	
	/**********        end        **********/
	
	
	
	
	/**********     Problem 5     **********/
	
	{
	if(Questions&2)
	{
		printf("Question 5:\n\n");
		
		a.setSameY0(0.0);
		//a.printP();
		//a.printC();
		//a.printGamma();
		a.VI(20,Details);
		a.CyclicVI(20,Details);
		
		printf("\n\n********************\n");
	}
	}
	
	/**********        end        **********/
	
	
	
	/**********     Problem 6     **********/
	
	{
	if(Questions&4)
	{
		printf("Question 6:\n\n");
		
		a.setSameY0(0.0);
		//a.printP();
		//a.printC();
		//a.printGamma();
		a.VI(20,Details);
		a.RPCyclicVI(20,Details);
		
		printf("\n\n********************\n");
	}
	}
	
	
	/**********        end        **********/
	
	
	
	
	return 0;
}
