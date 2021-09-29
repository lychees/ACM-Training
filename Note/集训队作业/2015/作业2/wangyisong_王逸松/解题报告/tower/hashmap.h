// last-update: 15-01-11
// by wys

#ifndef HASHMAP_H
#define HASHMAP_H

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

template <class T1,class T2,int SIZE = 7000000,u32 MOD = 10000019u>
struct hashmap begin
	
	struct data begin
		T1 key;
		T2 val;
		data *next;
	end;
	
	data pool[SIZE],*_tot;
	data *first[MOD];
	
	inline hashmap()
	begin
		_tot=pool;
	end;
	
	inline long size()
	begin
		return (long)(_tot-pool);
	end;
	
	inline T2 & operator [](T1 x)
	begin
		u32 h=x.getHash(MOD);
		data *now=first[h];
		while now do begin
			if now->key==x then break;
			now=now->next;
		end;
		if !now then begin
			now=++_tot;
			now->key=x;
			now->next=first[h];
			first[h]=now;
		end;
		return now->val;
	end;
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
