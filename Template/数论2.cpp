#define m MOD
inline void INCll(LL&x,LL y){x += y; if (x >= m) x -= m;}
inline LL sumll(LL a, LL b){a += b; if (a >= m) a -= m; return a;}
inline void DECll(LL &a, LL b){a -= b; if (a < 0) a += m;}
inline LL dffll(LL a, LL b){a -= b; if (a < 0) a += m; return a;}
inline int pdtll(LL a, LL b){
    //x%=m,y%=m; if(a<0)a+=m;if(b<0)b+=m;
    x =(x*y-(LL)(((long double)x*y+0.5)/(long double)m)*m)%m; if (x<0) x += m;
    return x;
}
inline void MULll(LL &a, LL b){a = pdtll(a, b);}
#undef m

/*
inline LL pdt64(LL x,LL y){
    //x%=m,y%=m; if(a<0)a+=m;if(b<0)b+=m;
    x =(x*y-(LL)(((long double)x*y+0.5)/(long double)m)*m)%m; if (x<0) x += m;
    return x;
}

inline LL pdt64(LL x,LL y){
    //x%=m,y%=m; if(a<0)a+=m;if(b<0)b+=m;
    LL p=sqrt(m)+0.5,q=p*p-m,a=x/p,b=x%p,c=y/p,d=y%p,e=a*c/p*q,f=a*c%p*q;
    LL t=((a*d+b*c)%m+e)%m;x=t/p*q,y=t%p*p;
    x = (((b*d+f)%m+x)%m+y)%m; if (x<0) x += m;
    return x;
}

inline LL pdt64(LL a,LL b){
    a%=m,b%=m; if (a<0) a+=m; if (b<0) b += m;
    LL c=0; for (;b;b>>=1,Incc(a,a))
        if (b&1) Incc(c,a);
    return c;
}*/

