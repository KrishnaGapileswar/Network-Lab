#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n,m;
	cout<<"Enter Number of Nodes : ";
	cin>>n;
	cout<<"Enter Number of Edges : ";
	cin>>m;
	int graph[n+1][n+1];
	int u,v;
	int i,j;
	int w;
	int dist[n+1][n+1];
	int visited[n+1][n+1];
	cout<<"Enter path and cost\n";
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
		{
			dist[i][j]=dist[j][i]=99999;
			graph[i][j]=graph[j][i]=0;
			visited[i][i]=0;
		}
	}
	for(i=1;i<=m;i++)
	{
		cin>>u>>v>>w;
		graph[u][v]=1;
		graph[v][u]=1;
		dist[u][v]=dist[v][u]=w;
		visited[u][v]=v;
		visited[v][u]=u;
	}
	for(i=1;i<=n;i++)
	{
		dist[i][i]=0;
	}
	int k;
	int c=0;
	while(c!=2)
	{
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
		{
			for(k=1;k<=n;k++)
			{
				if(dist[i][j]>dist[i][k]+dist[k][j])
				{
					dist[i][j]=dist[i][k]+dist[k][j];
					visited[i][j]=k;
				}
			}
		}
	}
	c++;
	}
	for(i=1;i<=n;i++)
	{
		cout<<"Node "<<i<<endl;
		for(j=1;j<=n;j++)
		{
			if(i!=j)
			{
				cout<<"Distance from "<<i<<" to "<<j<<" is "<<dist[i][j]<<" via "<<visited[i][j]<<endl;
			}
		}
	}
	return 0;
}
