/* **********************************************
Author      : wuyiqi
Created Time: 2013-8-22 13:17:48
File Name   : 1004.cpp
*********************************************** */

#include <cstdio>
#include <algorithm>
using std::max;
#define L x->c[0]
#define R x->c[1]
#define KT  root->c[1]->c[0]
#pragma comment(linker, "/STACK:1024000000,1024000000")
const int maxn = 1000010;
struct node {    
    struct node *c[2] , *fa;    
    int id;    
    int sz;     
    int val;       
    int mx;
    int sum;
    bool d() {    
        return fa->c[0] == this;    
    }    
    void setc(int d,node *s) {    
        c[d] = s;    
        s->fa = this;    
    }    
    void up() {    
        sz = c[0]->sz + c[1]->sz + 1;     
        sum = c[0]->sum + c[1]->sum + val;
        if(c[0]->val == -1000000) {
            mx = val;
            mx = max(mx,val+c[1]->mx);
            return ;
        }
        mx = c[0]->mx;
        mx = max(mx,c[0]->sum+val+c[1]->mx);      
        mx = max(mx,c[0]->sum+val);
     }    
    void clear(node *null) {    
        c[0] = c[1] = null;    
    }    
}NODE[maxn] , *null = &NODE[0];   
int top;
struct ST{
    node* root;
    void Rotate(node *x,int f){    
        node *y = x->fa;    
        y->setc(!f,x->c[f]);    
        x->fa = y->fa;    
        if(y->fa != null) y->fa->setc(!y->d(),x);    
        x->setc(f,y);    
        y->up();    
    }    
    void Splay(node *x,node *goal) {    
        while(x->fa!=goal) {    
            if(x->fa->fa == goal) Rotate(x,x->d());    
            else {    
                int f = x->fa->d();    
                x->d() == f ? Rotate(x->fa,f) : Rotate(x,!f);    
                Rotate(x,f);    
            }    
        }    
        x->up();    
        if(goal == null)  {    
            root = x;    
        }    
    }    
    void RTO(int k,node *goal) {    
        node *x = root;    
        while(L->sz + 1 != k) {    
            if(k < L->sz + 1) x = L;    
            else {    
                k -= L->sz + 1;    
                x = R;    
            }    
        }    
        Splay(x,goal);    
    }   
    node* new_node(node *fa,int v) {    
        node *x = &NODE[++top];    
        x->id = top;    
        x->c[0] = x->c[1] = null;    
        x->sz = 1;    
        x->val = v;    
        x->mx = v;
        x->sum = v;
        x->fa = fa;    
        return x;    
    }    

    void init() {    
        root = new_node(null,-1);
        root->c[1] = new_node(root,-1);
        root->sz = 2;
        root->c[1]->up();
        root->up();
    }    
    void Del_root() {    
        node *t = root;    
        if(t->c[1] != null) {    
            root = t->c[1];    
            RTO(1,null);    
            root->c[0] = t->c[0];    
            if(root->c[0] != null)     
                root->c[0]->fa = root;    
        } else  {    
            root = root->c[0];    
        }    
        root->fa = null;    
        if(root != null) root->up();    
    }    
    void vist(node *x) {
        if(x != null) {
            printf("now: %d left %d right %d val : %d  premx %d  sum=%d\n ",x->id,x->c[0]->id,x->c[1]->id,x->val,x->mx,x->sum);
            if(x->c[0] != null)  vist(x->c[0]);
            if(x->c[1] != null) vist(x->c[1]);
            
        }
    }
    void debug() {
        puts("************");
           vist(root);
           puts("*******************");
    }
    void insert(node* &x,node *y) {    
        if(x == null) {    
            x = y;    
            return ;    
        }    
        if(y->val <= x->val) {    
            insert(x->c[0],y);    
            x->c[0]->fa = x;    
        } else {    
            insert(x->c[1],y);    
            x->c[1]->fa = x;    
        }    
        x->up();    
    }    
    void insert(int &cur,int x) {
         RTO(cur,null);
         RTO(cur+1,root);
         node* tmp = new_node(null,x);
         root->c[1]->setc(0,tmp);
         root->c[1]->up();
         root->up();
         cur++;
    }
    void del(int &cur) {
         if(root->sz == 2 || cur == 1) return ;
         RTO(cur,null);
         Del_root();
         cur --;
    }
    int query(int cur,int k) {
        RTO(1,null);
        RTO(k+2,root);
      //  debug();
        return KT->mx;
    }
}spt; 
void prepare() {    
    null->id = 0;    
    null->c[0] = null->c[1] = null->fa = NULL;    
    null->sz = 0;    
    null->val = -1000000;
    null->sum = 0;
    null->mx = -1000000;
    top = 0;    
}   
int cur;
int main()
{
    int q,x,k;
    while(scanf("%d",&q)!=EOF) {
        cur = 1;
        char op[100];
        prepare();
        spt.init();
        while(q--) {
            scanf("%s",op);
            if(op[0] == 'I') {
                scanf("%d",&x);
                spt.insert(cur,x); 
            } else if(op[0] == 'D') {
                spt.del(cur);
            } else if(op[0] == 'L') {
                if(cur == 1) continue;
                cur --;
            } else if(op[0] == 'R') {
                if(spt.root->sz == 2) {
                    cur = 1;
                    continue;
                }
                cur++;
                if(cur >= spt.root->sz) {
                    cur = spt.root->sz - 1;
                }
            } else {
                scanf("%d",&k);
                printf("%d\n",spt.query(cur,k));
            }
        }
    }
    return 0;
}