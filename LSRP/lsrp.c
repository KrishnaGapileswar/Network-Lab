#include<stdio.h>
#define infinity 9999
#define max 10
void djikstra(int g[max][max],int n,int startnode);
int main()
{
        int g[max][max],i,j,n,u;
        printf("\n enter no. of nodes");
        scanf("%d",&n);
        printf("\n enter the cost matrix");
        for(i=0;i<n;i++)
                for(j=0;j<n;j++)
                        scanf("%d",&g[i][j]);
        printf("\n enter rhe starting node");
        scanf("%d",&u);
        djikstra(g,n,u);
        return 0;
}
void djikstra(int g[max][max],int n,int startnode)
{
        int cost[max][max],distance[max],pred[max];
        int visited[max],count,mindist,nextnode,i,j;
        for(i=0;i<n;i++)
                for(j=0;j<n;j++)
                        if(g[i][j]==0)
                                cost[i][j]=infinity;
                        else
                                cost[i][j]=g[i][j];
        for(i=0;i<n;i++)
        {
                distance[i]=cost[startnode][i];
                pred[i]=startnode;
                visited[i]=0;
     }
        distance[startnode]=0;
        visited[startnode]=1;
        count=1;
        while(count<n-1)
        {
                mindist=infinity;
                for(i=0;i<n;i++)
                {
                        if(distance[i]<mindist && !visited[i])
                        {
                                mindist=distance[i];
                                nextnode=i;
                        }
                }
                visited[nextnode]=1;
                for(i=0;i<n;i++)
                {
                        if(!visited[i])
                        {
                                if(mindist+ cost[nextnode][i]<distance[i])
                                {
                                        distance[i]=mindist+cost[nextnode][i];
                                        pred[i]=nextnode;
                                }}
                        count++;
                }
                for(i=0;i<n;i++)
                        if(i!=startnode)
                        {
                                printf("\n dist of %d from %d =%d",i,startnode,distance[i]);
                                printf("\n path:\n");
   printf("%d",i);
                                j=i;
                                do{
                                        j=pred[j];
                                        printf(" <- %d",j);
                                }
                                while(j!=startnode);
                        }}}
                                   
