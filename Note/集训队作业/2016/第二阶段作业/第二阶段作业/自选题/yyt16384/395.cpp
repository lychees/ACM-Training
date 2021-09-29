#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <string>
#include <utility>
#include <vector>

#ifdef _WIN32
#define LLFORMAT "I64"
#else
#define LLFORMAT "ll"
#endif

const int MAXN = 205;
const int MAXL = 25;
const int RANDLEN = 4;
const int INF = 0x3f3f3f3f;

struct Data
{
	int type;
	int pos;
	int id;

	Data() {}
	Data(int type_, int pos_, int id_) : type(type_), pos(pos_), id(id_) {}
};

namespace flow
{

const int MAXN = 405;
const int MAXM = 160005;

struct Edge
{
	int y, w, v;
	int next;
};

int n, s, t;
Edge e[MAXM];
int eh[MAXN];
int en;
int dist[MAXN];
int pre[MAXN];

void clear()
{
	memset(eh, -1, sizeof(eh));
	en = 0;
	n = 2;
	s = 0;
	t = 1;
}

void addedge_one(int x, int y, int w, int v)
{
	e[en].y = y;
	e[en].w = w;
	e[en].v = v;
	e[en].next = eh[x];
	eh[x] = en++;
}

void addedge_raw(int x, int y, int w, int v)
{
	addedge_one(x, y, w, v);
	addedge_one(y, x, 0, -v);
}

void addedge(int x, int y, int minw, int maxw, int v)
{
	if (maxw > minw)
		addedge_raw(x + 2, y + 2, maxw - minw, v * 2);
	if (minw)
	{
		addedge_raw(s, y + 2, minw, v);
		addedge_raw(x + 2, t, minw, v);
	}
}

int mindist()
{
	static int que[MAXN];
	static bool inque[MAXN];
	int qb = 0, qe = 1;
	memset(dist, INF, sizeof(dist));
	dist[s] = 0;
	memset(inque, 0, sizeof(inque));
	que[0] = s;
	inque[s] = true;
	pre[s] = -1;

	while (qb != qe)
	{
		int x = que[qb];
		qb = (qb + 1) % MAXN;
		inque[x] = false;
		for (int i = eh[x]; i != -1; i = e[i].next)
			if (e[i].w && dist[x] + e[i].v < dist[e[i].y])
			{
				dist[e[i].y] = dist[x] + e[i].v;
				pre[e[i].y] = i;
				if (!inque[e[i].y])
				{
					inque[e[i].y] = true;
					que[qe] = e[i].y;
					qe = (qe + 1) % MAXN;
				}
			}
	}

	return dist[t];
}

int work()
{
	int x;
	int d = INF;
	x = t;
	while (x != s)
	{
		if (e[pre[x]].w < d)
			d = e[pre[x]].w;
		x = e[pre[x] ^ 1].y;
	}
	x = t;
	while (x != s)
	{
		e[pre[x]].w -= d;
		e[pre[x] ^ 1].w += d;
		x = e[pre[x] ^ 1].y;
	}
	return d;
}

std::pair<int, int> maxflow()
{
	int flow = 0;
	int cost = 0;
	n += 2;
	int tmpdist;
	while ((tmpdist = mindist()) < INF)
	{
		int tmp = work();
		flow += tmp;
		cost += tmpdist * tmp;
	}
	return std::make_pair(flow, cost / 2);
}

}

int N, m;
int qr[MAXN];
int qrpos[MAXN];
int namen;
std::vector<std::string> names;
std::map<std::string, int> nameid;
std::vector<Data> _occ[MAXN];
int occn[MAXN];
Data *occ[MAXN];
int ans;
std::vector<std::string> ansprint[MAXN];

int getid(const char *s)
{
	std::map<std::string, int>::const_iterator it;
	if ((it = nameid.find(s)) != nameid.end())
		return it->second;
	else
	{
		_occ[namen].push_back(Data(1, 0, -1));
		names.push_back(s);
		return nameid[s] = namen++;
	}
}

void input()
{
	scanf("%d", &N);
	for (int i = 0; i < N; ++i)
	{
		char type;
		scanf(" %c", &type);
		if (type == '+')
		{
			char s[MAXL];
			scanf("%s", s);
			int id = getid(s);
			_occ[id].push_back(Data(0, m, i));
		}
		else if (type == '-')
		{
			char s[MAXL];
			scanf("%s", s);
			int id = getid(s);
			_occ[id].push_back(Data(1, m, i));
		}
		else
		{
			scanf("%d", &qr[m]);
			qrpos[m] = i;
			++m;
		}
	}
	for (int i = 0; i < namen; ++i)
		_occ[i].push_back(Data(0, m, -1));
	++m;

	for (int i = 0; i < namen; ++i)
	{
		occn[i] = _occ[i].size();
		occ[i] = &*_occ[i].begin();
	}
}

void insert_at(int newp, int x, int minw, int maxw)
{
	flow::addedge(newp, x, minw, maxw, 1);
}

void erase_at(int newp, int x, int minw, int maxw)
{
	flow::addedge(x, newp, minw, maxw, 1);
}

void insert_between(int newp, int l, int r, int minw, int maxw)
{
	for (int i = l; i <= r; ++i)
		flow::addedge(newp, i, minw, maxw, 1);
}

void erase_between(int newp, int l, int r, int minw, int maxw, bool zerov = false)
{
	for (int i = l; i <= r; ++i)
		flow::addedge(i, newp, minw, maxw, !(zerov && i == r));
}

void init()
{
	flow::clear();
	for (int i = 0; i < m - 1; ++i)
		flow::addedge(i, i + 1, qr[i], qr[i], 0);
	flow::n = m;

	for (int i = 0; i < namen; ++i)
	{
		for (int j = 0; j < occn[i] - 1; ++j)
		{
			if (occ[i][j].type == 0 && occ[i][j + 1].type == 0)
			{
				insert_at(flow::n, occ[i][j].pos, 1, 1);
				erase_between(flow::n, occ[i][j].pos, occ[i][j + 1].pos, 0, 1, (j == occn[i] - 2));
				++flow::n;
			}
			else if (occ[i][j].type == 1 && occ[i][j + 1].type == 1)
			{
				erase_at(flow::n, occ[i][j + 1].pos, 1, 1);
				insert_between(flow::n, occ[i][j].pos, occ[i][j + 1].pos, 0, 1);
				++flow::n;
			}
			else if (occ[i][j].type == 0 && occ[i][j + 1].type == 1)
			{
				insert_at(flow::n, occ[i][j].pos, 1, 1);
				erase_between(flow::n, occ[i][j].pos, occ[i][j + 1].pos, 0, 1);
				erase_at(flow::n + 1, occ[i][j + 1].pos, 1, 1);
				insert_between(flow::n + 1, occ[i][j].pos, occ[i][j + 1].pos, 0, 1);
				flow::addedge(flow::n + 1, flow::n, 0, 1, 0);
				flow::n += 2;
			}
		}
	}

	for (int i = 0; i < m - 1; ++i)
	{
		insert_at(flow::n, i, 0, INF);
		erase_between(flow::n, i + 1, m - 1, 0, INF, true);
		++flow::n;
	}
}

std::string gen_random_string()
{
	std::string s;
	for (int i = 0; i < RANDLEN; ++i)
		s += 'a' + rand() % 26;
	return s;
}

std::string gen_random_name()
{
	std::string s;
	do
	{
		s = gen_random_string();
	}while (nameid.find(s) != nameid.end());
	nameid[s] = -1;
	return s;
}

int getanspos(int qid, const Data &rdata)
{
	if (qid - 2 == rdata.pos)
		return rdata.id;
	else
		return qrpos[qid - 2];
}

void solve()
{
	ans = flow::maxflow().second + m - 1;
	printf("%d\n", ans);

	int nowp = m + 2;

	for (int i = 0; i < namen; ++i)
	{
		for (int j = 0; j < occn[i] - 1; ++j)
		{
			if (occ[i][j].type == 0 && occ[i][j + 1].type == 0)
			{
				int pt = nowp;
				ansprint[occ[i][j].id].push_back("+ " + names[i]);
				for (int k = flow::eh[pt]; k != -1; k = flow::e[k].next)
					if (flow::e[k].v == -2 && flow::e[k].w == 1)
					{
						int anspos = getanspos(flow::e[k].y, occ[i][j + 1]);
						ansprint[anspos].push_back("- " + names[i]);
					}
				++nowp;
			}
			else if (occ[i][j].type == 1 && occ[i][j + 1].type == 1)
			{
				int pt = nowp;
				for (int k = flow::eh[pt]; k != -1; k = flow::e[k].next)
					if (flow::e[k].v == 2 && flow::e[k].w == 0)
					{
						int anspos = getanspos(flow::e[k].y, occ[i][j + 1]);
						ansprint[anspos].push_back("+ " + names[i]);
					}
				ansprint[occ[i][j + 1].id].push_back("- " + names[i]);
				++nowp;
			}
			else if (occ[i][j].type == 0 && occ[i][j + 1].type == 1)
			{
				int pt1 = nowp, pt2 = nowp + 1;
				ansprint[occ[i][j].id].push_back("+ " + names[i]);
				int anspos1 = -1, anspos2 = -1;
				for (int k = flow::eh[pt1]; k != -1; k = flow::e[k].next)
					if (flow::e[k].v == -2 && flow::e[k].w == 1)
					{
						anspos1 = getanspos(flow::e[k].y, occ[i][j + 1]);
						break;
					}
				for (int k = flow::eh[pt2]; k != -1; k = flow::e[k].next)
					if (flow::e[k].v == 2 && flow::e[k].w == 0)
					{
						anspos2 = getanspos(flow::e[k].y, occ[i][j + 1]);
						break;
					}
				if (anspos1 != -1)
				{
					if (anspos1 <= anspos2)
					{
						ansprint[anspos1].push_back("- " + names[i]);
						ansprint[anspos2].push_back("+ " + names[i]);
					}
					else
					{
						std::string name = gen_random_name();
						ansprint[anspos2].push_back("+ " + name);
						ansprint[anspos1].push_back("- " + name);
					}
				}
				ansprint[occ[i][j + 1].id].push_back("- " + names[i]);
				nowp += 2;
			}
		}
	}

	for (int i = 0; i < m - 1; ++i)
	{
		int pt = nowp;
		for (int k = flow::eh[pt]; k != -1; k = flow::e[k].next)
			if ((flow::e[k].v == -2 || flow::e[k].v == 0) && flow::e[k].w)
			{
				int anspos;
				if (flow::e[k].v == 0)
					anspos = -1;
				else
					anspos = qrpos[flow::e[k].y - 2];
				for (int p = 0; p < flow::e[k].w; ++p)
				{
					std::string name = gen_random_name();
					ansprint[qrpos[i]].push_back("+ " + name);
					if (anspos != -1)
						ansprint[anspos].push_back("- " + name);
				}
			}
		++nowp;
	}

	for (int i = 0; i < m - 1; ++i)
	{
		char str[15];
		sprintf(str, "= %d", qr[i]);
		ansprint[qrpos[i]].push_back(str);
	}

	for (int i = 0; i < N; ++i)
		for (int j = 0; j < (int)ansprint[i].size(); ++j)
			printf("%s\n", ansprint[i][j].c_str());
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("395.in", "r", stdin);
	freopen("395.out", "w", stdout);
#endif

	input();
	init();
	solve();

#ifndef ONLINE_JUDGE
	fclose(stdin); fclose(stdout);
#endif
	return 0;
}
