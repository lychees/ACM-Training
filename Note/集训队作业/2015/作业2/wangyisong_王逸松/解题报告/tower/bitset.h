// last update: 15-01-14
// by wys

#ifndef BITSET_H
#define BITSET_H

#define if if (
#define then )
#define do )
#define for for (
#define while while (
#define switch switch (
#define begin {
#define end }

#define u32 unsigned int
#define u64 unsigned long long

#ifndef BITSET_SIZE
#define BITSET_SIZE 170
#endif

#define BITSET_ARRAY_SIZE (BITSET_SIZE/32+1)

inline int popcount(u32 x)
begin
	x -= (x >> 1) & 0x55555555;
	x = (x & 0x33333333) + ((x >> 2) & 0x33333333);
	x = (x + (x >> 4)) & 0x0f0f0f0f;
	return (x * 0x01010101)>>24;
end;

struct bitset begin
	u32 a[BITSET_ARRAY_SIZE];
	
	inline void clear0()
	begin
		int i;
		for i=0;i<BITSET_ARRAY_SIZE;i++ do a[i]=0;
	end;
	
	inline void clear1()
	begin
		int i;
		for i=0;i<BITSET_ARRAY_SIZE;i++ do a[i]=0xffffffffu;
	end;
	
	inline void set0(int x)
	begin
		a[x>>5]&=~(1u<<(x&31));
	end;
	
	inline void set1(int x)
	begin
		a[x>>5]|=1u<<(x&31);
	end;
	
	inline void flip(int x)
	begin
		a[x>>5]^=1u<<(x&31);
	end;
	
	inline int popcount() const
	begin
		int i;
		int ret=0;
		for i=0;i<BITSET_ARRAY_SIZE;i++ do ret+=::popcount(a[i]);
		return ret;
	end;
	
	inline bool is1(int x) const
	begin
		return a[x>>5]&(1u<<(x&31));
	end;
	
	inline u32 getHash(u32 MOD) const
	begin
		u32 ret=a[0];
		int i;
		for i=1;i<BITSET_ARRAY_SIZE;i++ do begin
			ret=((1ull<<32)*ret+a[i])%MOD;
		end;
		return ret;
	end;
	
	static const char tb[32];
	
	inline static const char LOG(u32 x)
	begin
		return tb[((x)*263572066)>>27];
	end;
	
	inline static const u32 lowbit(u32 x)
	begin
		return x&-x;
	end;
	
	inline int findnext(int x) const  // find first 1 after x
	begin
		int pos=x>>5;
		u32 tmp=a[pos]&~((1u<<(x&31))*2u-1);
		if tmp then return (pos<<5)+LOG(lowbit(tmp));
		int i;
		for i=pos+1;i<BITSET_ARRAY_SIZE;i++ do begin
			tmp=a[i];
			if tmp then return (i<<5)+LOG(lowbit(tmp));
		end;
		return 0x3f3f3f3f;
	end;
	
	inline int findnext0(int x) const  // find first 0 after x
	begin
		int pos=x>>5;
		u32 tmp=(~a[pos])&~((1u<<(x&31))*2u-1);
		if tmp then return (pos<<5)+LOG(lowbit(tmp));
		int i;
		for i=pos+1;i<BITSET_ARRAY_SIZE;i++ do begin
			tmp=~a[i];
			if tmp then return (i<<5)+LOG(lowbit(tmp));
		end;
		return 0x3f3f3f3f;
	end;
end;

const char bitset::tb[32]={
	31,0,27,1,28,18,23,2,
	29,21,19,12,24,9,14,3,
	30,26,17,22,20,11,8,13,
	25,16,10,7,15,6,5,4
};

inline bool operator < (const bitset &a,const bitset &b)
begin
	const u32 *A=a.a,*B=b.a;
	int i;
	for i=0;i<BITSET_ARRAY_SIZE;i++ do begin
		if A[i]!=B[i] then return A[i]<B[i];
	end;
	return false;
end;

inline bool operator == (const bitset &a,const bitset &b)
begin
	const u32 *A=a.a,*B=b.a;
	int i;
	for i=0;i<BITSET_ARRAY_SIZE;i++ do begin
		if A[i]!=B[i] then return 0;
	end;
	return 1;
end;

inline bitset AND(const bitset &a,const bitset &b)
begin
	const u32 *A=a.a,*B=b.a;
	bitset ret;
	int i;
	for i=0;i<BITSET_ARRAY_SIZE;i++ do begin
		ret.a[i]=A[i]&B[i];
	end;
	return ret;
end;

inline bitset AND_NOT(const bitset &a,const bitset &b)
begin
	const u32 *A=a.a,*B=b.a;
	bitset ret;
	int i;
	for i=0;i<BITSET_ARRAY_SIZE;i++ do begin
		ret.a[i]=A[i]&~B[i];
	end;
	return ret;
end;

inline bitset OR(const bitset &a,const bitset &b)
begin
	const u32 *A=a.a,*B=b.a;
	bitset ret;
	int i;
	for i=0;i<BITSET_ARRAY_SIZE;i++ do begin
		ret.a[i]=A[i]|B[i];
	end;
	return ret;
end;

#undef if
#undef then
#undef do
#undef for
#undef while
#undef switch
#undef begin
#undef end

#endif
