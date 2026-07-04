#include <bits/stdc++.h>
using namespace std;

const int MX = 1e5 + 3;
vector<int> adj[MX];
int mark[MX], sz[MX];

int ask(int u) {
  /* query type I
     u: node number
     return the hidden color for node u
  */
  cout << "? 1 " << u << '\n'; cout.flush();
  int x; cin >> x;
  return x; 
}

void flip(vector<int> v) {
  /* query type II
     v: vector of node number
     for every node u in V/{deepest node from root}, flip the color of every node in the path from root to u.
  */
  cout << "? 2 " << v.size() << " ";
  for (auto u : v) cout << u << " ";
  cout << '\n'; cout.flush();
  int x; cin >> x; assert(x == 1);
}

int fill_sz(int u, int prt=0) {
  sz[u] = 1;
  for (auto v : adj[u])
    if (v != prt && !mark[v]) 
      sz[u] += fill_sz(v, u);
  return sz[u];
}

int centroid(int u, int n, int prt=0) {
  for (auto v : adj[u])
    if (v != prt && !mark[v] && 2*sz[v] > n) return centroid(v, n, u);
  return u;
}

int find_par(int u) {
  assert(!mark[u]);
  vector<int> q;
  for (auto v : adj[u]) if (!mark[v]) q.push_back(v);
  q.push_back(u);
  
  int l = 0, r = q.size()-1;
  while (l < r) {
    int mid = (l+r)>>1;

    if (mid == 0) {
      int color = ask(q[0]);
      flip({q[0], q[1]});
      return ask(q[0]) == color ? q[1] : q[0];
    }

    vector<int> v;
    for (int i = 0; i <= mid; ++i) v.push_back(q[i]);
    int color = ask(u);
    flip(v);
    if ((ask(u) + color) % 2 == v.size() % 2) r = mid;
    else l = mid+1;  
  }
  return q[l];
}

void solve() {
  int n; cin >> n;
  for (int i = 1; i < n; ++i) {
    int u, v; cin >> u >> v;
    adj[u].emplace_back(v);
    adj[v].emplace_back(u);
  }
  
  int root = 1, c = 0;
  do {
    int m = fill_sz(root);
    c = centroid(root, m);
    int p = find_par(c);
    mark[c] = 1; root = p;
  } while (c != root);

  cout << "! " << root << '\n';
  cout.flush();
}

signed main() {
  // ios_base::sync_with_stdio(0); cin.tie(NULL);
  solve();
}