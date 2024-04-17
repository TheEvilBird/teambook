/**
 * Author: Alex Ponkratov
 * Date: 2024-04
 * Description: Dinic's algorithm
 * Time: O(V^{2}E)
 */

struct Dinic {
  struct Edge {
    int from, to;
    ll flow, cap;
    int rev_id;

    Edge() {}
    Edge(int from, int to, ll flow, ll cap, int rev_id) 
          : from(from), to(to), flow(flow), cap(cap), rev_id(rev_id) {}
  };

  int n;
  vector<vector<int>> g;
  int ptr = 0;
  vector<Edge> edges;
  vector<int> head, dist;
  int s, t;

  Dinic(int n) : n(n), g(n), head(n, 0), dist(n) {}

  void add_edge(int from, int to, ll cap) {
    edges.emplace_back(from, to, 0, cap, ptr ^ 1);
    g[from].emplace_back(ptr);
    ++ptr;
    edges.emplace_back(to, from, 0, 0, ptr ^ 1);
    g[to].emplace_back(ptr);
    ++ptr;
  }

  ll dfs(int v, ll cur_flow, ll min_flow) {
    if (v == t) {
        return cur_flow;
    }
    for (; head[v] < sz(g[v]); ++head[v]) {
        auto &e = edges[g[v][head[v]]];
        if (dist[v] + 1 == dist[e.to] && e.cap - e.flow >= min_flow) {
            ll new_flow = dfs(e.to, min(cur_flow, e.cap - e.flow), min_flow);
            if (new_flow > 0) {
                e.flow += new_flow;
                edges[e.rev_id].flow -= new_flow;
                return new_flow;
            }
        }
    }
    return 0;
  }

  bool bfs(ll min_flow = 1) {
    dist.assign(n, INF);
    dist[s] = 0;
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (auto id: g[v]) {
            auto e = edges[id];
            if (dist[e.to] == INF && e.cap - e.flow >= min_flow) {
                dist[e.to] = dist[v] + 1;
                q.push(e.to);
            }
        }
    }
    return dist[t] != INF;
  }

  ll maxflow(int _s, int _t) {
    s = _s;
    t = _t;
    ll flow = 0;
    for (int k = 30; k >= 0; --k) {
        ll min_flow = (1LL << k);
        while (bfs(min_flow)) {
            head.assign(n, 0);
            ll f = dfs(s, INF, min_flow);
            while (f) {
                flow += f;
                f = dfs(s, INF, min_flow);
            }
        }
    }
    return flow;
  }
};