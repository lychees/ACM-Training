#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#define N 60
#define For(i,x,y) for (i=x;i<=y;i++)
using namespace std;
struct w {
	int x,y,z;
};
struct ww {
	int a,b,c,A,B,C,x,y,z;
};
int i,j,k,n,m,T,te;
int a[N][N][N];
inline void print() {
	int i,j,k;
	For(k,1,n) {
		For(j,1,n) {
			For(i,1,n) printf("%d ",a[i][j][k]);
			printf("\n");
		}
		printf("\n");
	}
	//printf("__________________________\n");
}
inline void get(w A,ww B,int t) {
	int b[3]={A.x,A.y,A.z};
	a[b[B.a]][b[B.b]][b[B.c]]=t;
}
inline void work1(int n,int l,int r,ww A);
inline void work2(int n,int l,int r,ww A) {
	w B={A.x,A.y,A.z};
	int i,j;
	if (n&1) {
		int vx=A.A,vz=A.C;
		For(i,1,n) {
			For(j,1,n-1) {
				get(B,A,l);
				l++;
				if (i==n&&j==n-1) break;
				
				if (j==n-1) B.x+=vx,vz*=-1;
				else B.z+=vz;
			}
		}
		B.y+=A.B;
	} else {
		int vx=A.A,vz=A.C;
		For(i,1,n-1) {
			For(j,1,n) {
				get(B,A,l);
				l++;
				if (i==n-1&&j==n) break;
				
				if (j==n) B.z+=vz,vx*=-1;
				else B.x+=vx;
			}
		}
		B.y+=A.B;
	}
	//print();
	work1(n,l,r,(ww){A.c,A.b,A.a,-A.C,A.B,-A.A,B.z,B.y,B.x});
}
inline void work1(int n,int l,int r,ww A) {
	w B={A.x,A.y,A.z};
	if (n==2) {
		get(B,A,l);
		B.z+=A.C;
		get(B,A,l+1);
		return;
	}
	int i,j;
	w C={A.x,A.y+A.B*(n-2),A.z+A.C*(n-1)};
	int vx=A.A,vy=A.B;
	For(i,1,n-1) {
		For(j,1,n-1) {
			get(B,A,l);
			get(C,A,r);
			l++,r--;
			if (i==n-1&&j==n-1) break;
			
			if (j<n-1) B.x+=vx,C.x+=vx;
			else B.y+=vy,C.y-=vy,vx*=-1;
		}
	}
	B.z+=A.C,C.z-=A.C;
	//print();
	work2(n-1,l,r,(ww){A.a,A.b,A.c,A.A*((n-1)&1?-1:1),-A.B,A.C,B.x,B.y,B.z});
}
int main() {
	scanf("%d",&n);
	if (n==1) {
		printf("1\n");
		return 0;
	}
	int A=n*(2*n-1);
	work1(n,A+1,n*n*n,(ww){0,1,2,1,1,1,1,2,1});
	{
		w B={1,1,1};
		ww C={0,1,2};
		For(i,1,n) {
			For(j,1,2*n-1) {
				get(B,C,A);
				A--;
				if (j==2*n-1) break;
				if (i&1) {
					if (j<n) B.x++;
					else B.y++;
				} else {
					if (j<n) B.y--;
					else B.x--;
				}
			}
			B.z++;
		}
	}
	print();
	//for(;;);
	return 0;
}
