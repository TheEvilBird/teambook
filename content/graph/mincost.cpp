/**
 * Author: Alex Ponkratov
 * Date: 2024-04
 * Description: Similar to the Edmonds-Karp.
 * Time: O(VE + FE \log(V))
 */

struct MinCost {
  struct Edge {
    int from, to;
    ll flow, cap, price;
    int rev_id;

    Edge() {}
    Edge(int from, int to, ll flow, ll cap, ll price, int revId) 
          : from(from), to(to), flow(flow), cap(cap), price(price), rev_id(revId) {}
  };

  int n;
  vector<vector<int>> g;
  int ptr = 0;
  vector<Edge> edges;
  vector<int> dist, add_flow;
  vector<pair<int, int>> par;
  int s, t;

  MinCost(int n) : n(n), g(n), dist(n), add_flow(n), par(n) {}

  void add_edge(int from, int to, ll cap, ll price) {
    edges.emplace_back(from, to, 0, cap, price, ptr ^ 1);
    g[from].emplace_back(ptr);
    ++ptr;

    edges.emplace_back(to, from, 0, 0, -price, ptr ^ 1);
    g[to].emplace_back(ptr);
    ++ptr;
  }

  void FB() {
    dist.assign(n, INF);
    add_flow.assign(n, 0);
    par.assign(n, {-1, -1});
    dist[s] = 0;
    add_flow[0] = INF;
    queue<int> q;
    q.push(s);
    vector<int> used(n, 0);
    used[s] = 1;
    while (!q.empty()) {
      int v = q.front();
      q.pop();
      used[v] = 0;
      for (int i = 0; i < sz(g[v]); ++i) {
        auto &e = edges[g[v][i]];
        if (e.flow < e.cap && dist[e.to] > dist[v] + e.price) {
          dist[e.to] = dist[v] + e.price;
          add_flow[e.to] = min(add_flow[v], (int) (e.cap - e.flow));
          par[e.to] = {v, i};
          if (!used[e.to]) {
            q.push(e.to);
            used[e.to] = 1;
          }
        }
      }
    }
  }

  void push_flow(ll flow, ll &ans) {
    int cur = t;
    while (cur != s) {
      int prev = par[cur].first, id = par[cur].second;
      auto &e = edges[g[prev][id]];
      e.flow += flow;
      edges[e.rev_id].flow -= flow;
      ans += e.price * flow;
      cur = prev;
    }
  }

  ll min_cost_max_flow(int _s, int _t) {
    s = _s;
    t = _t;
    ll ans = 0;
    while (true) {
      FB();
      ll flow = add_flow[t];
      if (flow == 0) {
        break;
      }
      push_flow(flow, ans);
    }
    return ans;
  }
};