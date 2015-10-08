#include <bits/stdc++.h>
using namespace std ;

typedef long long LL ;

#define clr( a , x ) memset ( a , x , sizeof a )

const int MAXN = 100005 ;

namespace Suffix_Automation {

    const int N = 26 ;

    struct Node {
        Node* nxt[N] ;
        Node* fail ;
        LL num ;
        int l ;
        int c ;

        void newnode ( int _l , int _c ) {
            clr ( nxt , NULL ) ;
            fail = NULL ;
            num = 1 ;
            l = _l ;
            c = _c ;
        }
    } ;

    Node node[MAXN << 1] ;
    Node* last ;
    Node* root ;
    Node* cur ;

    void init () {
        root = last = cur = node ;
        cur->newnode ( 0 , 0 ) ;
    }

    void create ( Node* p , Node* np , int c ) {
        Node *q = p->nxt[c] , *nq = ++ cur ;
        *nq = *q ;
        nq->l = p->l + 1 ;
        q->fail = nq ;
        if ( np != NULL ) np->fail = nq ;
        for ( ; p && p->nxt[c] == q ; p = p->fail ) p->nxt[c] = nq ;
    }

    void add ( int c ) {
        c -= 'a' ;
        Node *p = last , *np = last = ++ cur ;
        np->newnode ( p->l + 1 , c ) ;
        for ( ; p && p->nxt[c] == NULL ; p = p->fail ) p->nxt[c] = np ;
        if ( p == NULL ) np->fail = root ;
        else {
            if ( p->l + 1 == p->nxt[c]->l ) np->fail = p->nxt[c] ;
            else create ( p , np , c ) ;
        }
    }
} ;

using namespace Suffix_Automation ;

char s1[MAXN] , s2[MAXN] ;
int idx[MAXN << 1] ;
LL d[26] ;

int cmp ( const int& a , const int& b ) {
    return node[a].l > node[b].l ;
}

void solve () {
    unsigned long long ans = 1 ;
    scanf ( "%s%s" , s1 , s2 ) ;
    init () ;
    for ( int i = 0 ; s2[i] ; ++ i ) {
        add ( s2[i] ) ;
    }
    int cnt = cur - node ;
    for ( int i = 0 ; i <= cnt ; ++ i ) {
        idx[i] = i ;
    }
    sort ( idx , idx + cnt + 1 , cmp ) ;
    for ( int i = 0 ; i <= cnt ; ++ i ) {
        Node* p = idx[i] + node ;
        for ( int j = 0 ; j < N ; ++ j ) {
            if ( p->nxt[j] != NULL ) p->num += p->nxt[j]->num ;
        }
    }
    for ( int i = 0 ; i < N ; ++ i ) {
        if ( root->nxt[i] != NULL ) d[i] = root->nxt[i]->num ;
        else d[i] = 0 ;
    }

    init () ;
    for ( int i = 0 ; s1[i] ; ++ i ) {
        add ( s1[i] ) ;
    }
    cnt = cur - node ;
    for ( int i = 0 ; i < N ; ++ i ) {
        if ( root->nxt[i] == NULL ) ans += d[i] ;

        cout << d[i] << " ";
    }
    cout << endl;


    for ( int i = 1 ; i <= cnt ; ++ i ) {
        Node* p = node + i ;
        unsigned long long l = p->l - p->fail->l ;
        for ( int j = 0 ; j < N ; ++ j ) {
            if ( p->nxt[j] == NULL ) ans += l * d[j] ;
        }
        ans += l ;
    }
    printf ( "%I64u\n" , ans ) ;
}

int main () {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
#endif

    int T ;
    scanf ( "%d" , &T ) ;
    cout << T << endl;
    for ( int i = 1 ; i <= T ; ++ i ) {
        solve () ;
    }
    return 0 ;
}
