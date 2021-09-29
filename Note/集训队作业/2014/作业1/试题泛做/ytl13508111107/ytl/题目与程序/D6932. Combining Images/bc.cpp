#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=5010;
char A[MAXN],B[MAXN];
int ys[MAXN];
char ans[MAXN];
int lenA,lenB;
char col;
char rs[MAXN];
bool flag=1;
int rk[MAXN];
void init()
{
 for(int i='0';i<='9';i++)
  ys[i]=i-'0';
 for(int i='A';i<='F';i++)
  ys[i]=i-'A'+10;
}
int findA(int p,int k)
{
 int t;
 B[p]=A[p];
 B[p+1]=col;
 if(k==0)
  return p-1;
 if(A[p]=='1')
  return findA(p+2,k-1);
 if(A[p]=='0')
  t=findA(p+1,4);
 return findA(t+1,k-1);
}
int findB(int p,int k)
{
 int t;
 A[p]=B[p];
 A[p+1]=col;
 if(k==0)
  return p-1;
 if(B[p]=='1')
  return findB(p+2,k-1);
 if(B[p]=='0')
  t=findB(p+1,4);
 return findB(t+1,k-1);
}
void solve()
{
 int p1=0,p2=0;
 char tt[MAXN];
 while(p1<lenA||p2<lenB)
 {
  if(A[p1]==B[p2]&&A[p1]=='0')
  {p1++;p2++;continue;}
  if(A[p1]==B[p2]&&A[p1]=='1')
  {p1+=2;p2+=2;continue;}
  if(A[p1]=='0'&&B[p2]=='1')
  {
   col=B[p2+1];
   strcpy(tt,&B[p2+2]);
   B[p2]='0';
   int t=findA(p1+1,4);
   strcpy(&B[t+1],tt);
   lenB=strlen(B);
   p2=t+1;
   p1=t+1;
   continue;
  }
  if(B[p2]=='0'&&A[p1]=='1')
  {
   col=A[p1+1];
   strcpy(tt,&A[p1+2]);
   A[p1]='0';
   int t=findB(p2+1,4);
   strcpy(&A[t+1],tt);
   lenA=strlen(A);
   p2=t+1;
   p1=t+1;
   continue;
  }
 }
 //printf("%s\n%s\n",A,B);
 lenA=strlen(A);
 lenB=strlen(B);
 for(int i=0;i<lenA;i++)
 {
  if(A[i]==B[i]&&A[i]=='1')
   ans[i]='1';
  else
   ans[i]='0';
 }
 //printf("%s",ans);
}
int finds(int p,int k)
{
 int t;
 if(k==0)
  return p-1;
 if(ans[p]=='1')
 {
  if(col==-1)
   col=ans[p+1];
  else
   if(col!=ans[p+1])
    flag=0;
  return finds(p+2,k-1);
 }
 if(ans[p]=='0')
  t=finds(p+1,4);
 return finds(t+1,k-1);
}
void out(int a)
{
 if(a<10)
  printf("%d",a);
 if(a==10)
  printf("A");
 if(a==11)
  printf("B");
 if(a==12)
  printf("C");
 if(a==13)
  printf("D");
 if(a==14)
  printf("E");
 if(a==15)
  printf("F");
 
}
void code()
{
 int len=strlen(ans);
 int p=0;
 int cnt=0;
 while(p<len)
 {
  if(ans[p]=='1')
  {
   rs[cnt++]=ans[p];
   rs[cnt++]=ans[p+1];
   p+=2;
   continue;
  }
  flag=1;
  col=-1;
  int t=finds(p+1,4);
  if(flag)
  {
   rs[cnt++]='1';
   rs[cnt++]=col;
   p=t+1;
   continue;
  } 
  else
  {
   rs[cnt++]=ans[p];
   p++;
   continue;
  }
 }
 //printf("\n%s",rs);
 reverse(rs,rs+cnt);
 rs[cnt++]='1';
 while(cnt%4!=0)
  rs[cnt++]='0';
 reverse(rs,rs+cnt);
 
 //printf("\n%s",rs);
 for(int i=0;i*4<cnt;i++)
 {
  for(int j=0;j<4;j++)
   rk[i]=rk[i]+((rs[i*4+j]-'0')*(1<<(3-j)));
 }
 for(int i=0;i*4<cnt;i++)
  out(rk[i]);
}
int main()
{ 
		freopen("image.in","r",stdin);
	freopen("bc.out","w",stdout);
  
 int s1[MAXN],s2[MAXN];
 char tt[MAXN];
 init();
 scanf("%s",tt);
 int len1=strlen(tt);
 for(int i=0;i<len1;i++)
  s1[i]=ys[tt[i]];
 scanf("%s",tt);
 int len2=strlen(tt);
 for(int i=0;i<len2;i++)
  s2[i]=ys[tt[i]];
 for(int i=0;i<len1;i++)
 {
  for(int j=0;j<4;j++)
  {
   if((1<<(3-j))<=s1[i])
   {A[i*4+j]='1';s1[i]-=(1<<(3-j));}
   else
    A[i*4+j]='0'; 
  }
 }
 for(int i=0;i<len2;i++)
 {
  for(int j=0;j<4;j++)
  {
   if((1<<(3-j))<=s2[i])
   {B[i*4+j]='1';s2[i]-=(1<<(3-j));}
   else
    B[i*4+j]='0'; 
  }
 }
 lenA=strlen(A);
 lenB=strlen(B);
 for(int i=0;i<lenA;i++)
  if(A[i]=='1')
  {
   strcpy(tt,&A[i+1]);
   strcpy(A,tt);
   lenA=strlen(A);
   break;
  }
 
 for(int i=0;i<lenB;i++)
  if(B[i]=='1')
  {
   strcpy(tt,&B[i+1]);
   strcpy(B,tt);
   lenB=strlen(B);
   break;
  } 
 //printf("%s\n%s\n",A,B);
 solve();
 code();
 return 0;
}
