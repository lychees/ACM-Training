#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <iostream>
#include <queue>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <list>
#include <math.h>
using namespace std;
const int MAXN = 100010;
int a[MAXN];
struct Node
{
    int index;
    int v;
    Node(){}
    Node(int _index,int _v)
    {
        index = _index;
        v = _v;
    }
};
struct classcomp1
{
    bool operator()(const Node &a,const Node &b)const
    {
        if(a.v != b.v)return a.v < b.v;
        else return a.index > b.index;
    }
};
struct classcomp2
{
    bool operator()(const Node &a,const Node &b)const
    {
        if(a.v != b.v)return a.v > b.v;
        else return a.index > b.index;
    }
};
multiset<Node,classcomp1>st1;
multiset<Node,classcomp2>st2;
multiset<Node,classcomp1>::iterator it1;
multiset<Node,classcomp2>::iterator it2;
int dp[MAXN][2];
int main()
{
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
    int T;
    scanf("%d",&T);
    int n;
    while(T--)
    {
        scanf("%d",&n);
        memset(dp,0,sizeof(dp));
        st1.clear();
        st2.clear();
        int ans = 0;
        for(int i = 0;i < n;i++)
        {
            scanf("%d",&a[i]);
            Node tmp = Node(i,a[i]);
            st1.insert(tmp);
            st2.insert(tmp);
            //for(it1 = st1.begin();it1 != st1.end();it1++)
                //printf("%d  %d\n",(*it1).index,(*it1).v);
            //it = st1.find(Node(i,a[i]));
            it1 = st1.find(tmp);
            //printf("0000%d  %d\n",(*it1).index,(*it1).v);
            //it1=st1.begin();
            it1++;
            //printf("0000%d  %d\n",(*it1).index,(*it1).v);
            //it1++;
            //printf("size %d\n",st1.size());
            if(it1 != st1.end())
            {
                //printf("*%d\n",(*it1).index);
                dp[i][0] = dp[(*it1).index][0]+1;
            }
            else
            {
                dp[i][0] = 1;
                //printf("%d\n",i);

            }
            it2 = st2.find(tmp);
            it2++;
            //it2++;
            if(it2==st2.end())
            {
                dp[i][1] = 1;
                //printf("%d\n",i);
            }
            else
            {
                //printf("**%d\n",(*it2).index);
                dp[i][1] = dp[(*it2).index][1]+1;
            }
            //printf("%d %d %d\n",i,dp[i][0],dp[i][1]);
            ans = max(ans,dp[i][0]);
            ans = max(ans,dp[i][1]);
        }
        printf("%d\n",ans);
    }
    return 0;
}





