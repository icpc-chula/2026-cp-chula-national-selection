#include <bits/stdc++.h>
using namespace std;

const int MX = 1e5 + 3;
const int HALF = 500000004;
const int MOD = 1e9 + 7;
vector<int> adj[MX];
int ans = 0;

bool dfs(int u, int t, int prt=0) {
  if (u==t) return true;
  bool found = false;
  for (auto v : adj[u]) {
    if (v==prt) continue;
    ans = (ans + HALF) % MOD;
    if (dfs(v, t, u)) {
      found = true;
      ans = (ans + HALF) % MOD;
    }
  }
  return found;
}

signed main() {
  ios_base::sync_with_stdio(0); cin.tie(NULL);
  int n, t; cin >> n >> t;
  for (int i = 1; i < n; ++i) {
    int u, v; cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  dfs(1, t);
  cout << ans << '\n';
}