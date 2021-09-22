#include <cstdio>
#include <algorithm>

using namespace std;

//#include <boost/graph/adjacency_list.hpp>
//#include <boost/graph/max_cardinality_matching.hpp>

using namespace boost;

using graph_t = adjacency_list<vecS, vecS, undirectedS>;
using vertex_t = graph_traits<graph_t>::vertex_descriptor;
using mate_map_t = vector_property_map<vertex_t>;
using vertex_index_map_t = property_map<graph_t, vertex_index_t>::type;

int gao(int n, const graph_t& g) {
  mate_map_t mate(n);
  checked_edmonds_maximum_cardinality_matching(g, mate);
  return matching_size(g, mate);
}

int main() {
  int n, m, a, b, c;
  graph_t g;
  vector<int> ans;
  vector<pair<int, int> > e;

  while (scanf("%d%d", &n, &m) != EOF) {
    e.clear();
    g.clear();
    for (int i = 0; i < m; ++i) {
      scanf("%d%d", &a, &b);
      --a;
      --b;
      e.push_back({a, b});
      add_edge(a, b, g);
    }
    c = gao(n, g);

    ans.clear();
    for (int i = 0; i < m; ++i) {
      tie(a, b) = e[i];
      g.clear();
      for (int j = 0; j < m; ++j) {
        if (e[j].first != a && e[j].first != b &&
            e[j].second != a && e[j].second != b) {
          add_edge(e[j].first, e[j].second, g);
        }
      }
      if (gao(n, g) < c - 1) {
        ans.push_back(i);
      }
    }

    fprintf(stderr, "n=%d m=%d c=%d ans=%d\n", n, m, c, (int)ans.size());
    printf("%u\n", ans.size());
    for (int i = 0; i < (int)ans.size(); ++i) {
      if (i > 0) {
        putchar(' ');
      }
      printf("%d", ans[i] + 1);
    }
    puts("");
  }

  return 0;
}

