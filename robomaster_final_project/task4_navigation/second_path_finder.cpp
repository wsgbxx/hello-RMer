#include<iostream>
using namespace std;
int h[1000][3],b[100];
int xx[4]={-1,1,0,0},yy[4]={0,0,-1,1};
bool a[100][100];
int main()
{
int t=0,w=1,x,y,k=0;
for(int i=0;i<    ;++i)
for(int j=0;j<    ;++j)
cin>>a[i][j];
h[1][1]=0,h[1][2]=0;
a[1][1]=1;
do{
t++;
for(int i=0;i<4;++i)
{
   x=h[t][1]+xx[i];
   y=h[t][2]+yy[i];
if(x>=0&&x< &&y>=0&&y< &&a[x][y]==0)
{
a[x][y]=1;
w++;
h[w][0]=t;
h[w][1]=x;
h[w][2]=y;
if(x== &&y== )break;
}
}
}while(t<w);
while(w>=1)
{
k++;
b[k]=w;
w=h[w][0];
}
for(int i=k;i>=1;--i)
cout<<"("<<h[b[i]][1]<<","<<h[b[i]][2]<<")"<<endl;
return 0;
}
