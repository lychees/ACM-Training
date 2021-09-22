#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dominator_tree.hpp>

using namespace boost;

typedef adjacency_list<vecS, vecS, bidirectionalS> graph_t;

void gao(int v, const vector<int>& p, vector<int>& ret) {
  if (ret[v] == 0) {
    ret[v] += v + 1;
    if (p[v] != -1) {
      gao(p[v], p, ret);
      ret[v] += ret[p[v]];
    }
  }
}

int main() {
  int n, m, a, b;

  while (scanf("%d%d", &n, &m) != EOF) {
    graph_t g(n);
    for (int i = 0; i < m; ++i) {
      scanf("%d%d", &a, &b);
      --a;
      --b;
      add_edge(a, b, g);
    }

    vector<default_color_type> color(n, white_color);
    depth_first_visit(g, n - 1, dfs_visitor<null_visitor>(), color.data());

    graph_t f;
    for (auto i = edges(g); i.first != i.second; ++i.first) {
      a = source(*i.first, g);
      b = target(*i.first, g);
      if (color[a] == black_color && color[b] == black_color) {
        add_edge(a, b, f);
      }
    }

    vector<int> parent(n, -1);
    lengauer_tarjan_dominator_tree(f, n - 1, parent.data());

    vector<int> ans(n, 0);
    for (int i = 0; i < n; ++i) {
      if (i == n - 1 || parent[i] != -1) {
        gao(i, parent, ans);
      }
      printf("%d%c", ans[i], i == n - 1 ? '\n' : ' ');
    }
  }

  return 0;
}

