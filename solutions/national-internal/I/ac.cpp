#include <cstring>
#include <iostream>
#include <queue>
#include <numeric>
#include <utility>
#include <vector>

const int MxN = 100010;
const long long INF = 1e18;

struct state_t {
  int v;
  long long w;

  state_t(int _v, long long _w): 
    v(_v), w(_w) {}

  bool operator < (const state_t &o) const {
    return w > o.w;
  }
};

std::vector<std::pair<int, long long>> adj[MxN];
long long dist[MxN];

int main(int argc, char *argv[]) {
  std::cin.tie(nullptr)->std::ios_base::sync_with_stdio(false);
  int n, m;
  long long w0;
  std::cin >> n >> m >> w0;
  for(int i=1, u, v; i<=m; ++i) {
    long long w;
    std::cin >> u >> v >> w;
    adj[u].emplace_back(v, w);
    adj[v].emplace_back(u, w);
  }
  
  std::priority_queue<state_t> pq;
  memset(dist, 0x3f, sizeof(dist));
  pq.emplace(1, dist[1] = w0);
  while(!pq.empty()) {
    state_t cur = pq.top();
    pq.pop();
    if(cur.v == n) {
      break;
    }
    for(auto x: adj[cur.v]) {
      long long nxt = cur.w; 
      while(std::gcd(nxt, x.second) != 1) {
        nxt++;
      }
      nxt += x.second;
      if(dist[x.first] > nxt) {
        pq.emplace(x.first, dist[x.first] = nxt);
      }
    }
  }
  if(dist[n] >= INF) {
    std::cout << "-1\n";
  }
  else {
    std::cout << dist[n] - w0 << "\n";
  }
  return 0;
}