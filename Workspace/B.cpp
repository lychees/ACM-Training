struct SAM
{
    SAM *son[4],*pre;
    int len;
    int ok;

    void init()
    {
        clr(son,0);
        pre=0;
        ok=0;
    }
};


SAM sam[N],*head,*last;
int cnt;


void initSam()
{
    head=last=&sam[0];
    head->init();
    cnt=1;
}


int get(char x)
{
    if(x=='A') return 0;
    if(x=='T') return 1;
    if(x=='G') return 2;
    return 3;
}

void insert(int x)
{
    SAM *p=&sam[cnt++],*u=last;

    p->init();

    p->len=last->len+1;
    last=p;
    for(;u&&!u->son[x];u=u->pre) u->son[x]=p;
    if(!u) p->pre=head;
    else if(u->son[x]->len==u->len+1) p->pre=u->son[x];
    else
    {
        SAM *r=&sam[cnt++],*q=u->son[x];
        *r=*q; r->len=u->len+1;
        p->pre=q->pre=r;
        for(;u&&u->son[x]==q;u=u->pre) u->son[x]=r;
    }
}


char s[N*2];
int cur;

int start[N],len[N];

vector<pair<int,int> > V[N];

int ans[N];


map<int,int> mp;


int n,m;

int main()
{
//  FFF;

    while(scanf("%d%d",&n,&m)!=-1)
    {
        cur=0;
        int i;
        for(i=1;i<=n;i++)
        {
            scanf("%s",s+cur);
            start[i]=cur;
            len[i]=strlen(s+cur);
            cur+=len[i]+3;
        }
        for(i=1;i<=m;i++)
        {
            int u,v;
            scanf("%d%d",&u,&v);
            V[u].pb(MP(v,i));
        }


        for(i=1;i<=n;i++) if(SZ(V[i])>0)
        {
            int j;
            initSam();
            for(j=start[i];s[j];j++)  insert(get(s[j]));
            SAM *p=last;
            while(p!=NULL) p->ok=1,p=p->pre;


            mp.clear();
            for(j=0;j<SZ(V[i]);j++)
            {
                int k=V[i][j].first;
                int id=V[i][j].second;
                if(mp.count(k))
                {
                    ans[id]=mp[k];
                    continue;
                }
                SAM *p=head;
                int t,tmp=0,cur=0;
                for(t=start[k];s[t];t++)
                {
                    int x=get(s[t]);
                    if(p->son[x])
                    {
                        cur++;
                        p=p->son[x];
                        if(p->ok) tmp=max(tmp,cur);
                    }
                    else break;
                }
                mp[k]=tmp;
                ans[id]=tmp;
            }
            V[i].clear();
        }
        for(i=1;i<=m;i++) printf("%d\n",ans[i]);
    }
}
