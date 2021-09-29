#include <stdio.h>
#include <string.h>
#define MAXL 10005
#define INF 0x7f7f7f7f
int n;
void perm(char *s,char *t,int *pm)
{
	int r=0;
	int h[MAXL]={0};
	int i,j,pos;
	for (i=0;i<=n;i++)
		if (!h[i])
		{
			pos=i;
			do
			{
				pm[pos]=r;
				h[pos]=1;
				for (j=0;j<=n;j++)
					if (t[j]==s[pos])
					{
						pos=j;break;
					}
			}while (pos!=i);
			r++;
		}
}
int ok(char *s,char *t,int nx,int sw,int *pm)
{
	return s[sw]==t[nx]||pm[nx]!=pm[sw];
}
int getlen(int x,int y)
{
	return y>x?y-x:y-x+n+1;
}
void addstr(char *s,int x,char *res)
{
	while (s[x]!='#')
	{
		res[strlen(res)+1]='\0';
		res[strlen(res)]=s[x];
		x=(x+1)%(n+1);
	}
}
void getans(char *s1,char *s2,char *ans)
{
	char s[MAXL];
	char t[MAXL];
	int pm[MAXL];
	char now[MAXL];
	char tmp[MAXL];
	int i,j;
	int nx,sw,co,ct;
	char tmpc;
	strcpy(s,s1);
	strcpy(t,s2);
	t[strlen(t)+1]='\0';
	t[strlen(t)]='#';
	strcpy(ans,"");
	for (i=0;i<=n;i++)
	{
		strcpy(now,s);
		strcpy(tmp,s);
		tmp[strlen(tmp)+1]='\0';
		tmp[strlen(tmp)]='#';
		nx=n;
		while (strcmp(tmp,t))
		{
			co=INF;
			perm(tmp,t,pm);
			for (j=0;j<=n;j++)
				if (nx!=j&&tmp[j]!=t[j]&&ok(tmp,t,nx,j,pm))
				{
					if ((ct=getlen(nx,j))<co)
					{
						co=ct;
						sw=j;
					}
				}
			tmpc=tmp[sw];tmp[sw]=tmp[nx];tmp[nx]=tmpc;
			addstr(tmp,nx,now);
			nx=sw;
		}
		if (strcmp(ans,"")==0||strlen(ans)>strlen(now))
			strcpy(ans,now);
		tmpc=t[n];
		for (j=n;j>=1;j--) t[j]=t[j-1];
		t[0]=tmpc;
	}
}
int main()
{
	char s1[MAXL];
	char s2[MAXL];
	char ans1[MAXL];
	char ans2[MAXL];
	scanf("%d%s%s",&n,s1,s2);
	getans(s1,s2,ans1);
	getans(s2,s1,ans2);
	if (strlen(ans1)<strlen(ans2)) printf("%s\n",ans1);
	else printf("%s\n",ans2);
	return 0;
}
