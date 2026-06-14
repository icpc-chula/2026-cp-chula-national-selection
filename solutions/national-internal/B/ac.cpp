#include <iostream>
#include <string>
#include <vector>

const int MxN = 100010;

int n, m;
int parent[MxN * 2], components;

int find_root(int u) {
  if(u == parent[u]) {
    return u;
  }
  return parent[u] = find_root(parent[u]);
}

void unite(int u, int v) {
  int ru = find_root(u), rv = find_root(v);
  if(ru == rv) {
    return ;
  }
  components--;
  parent[rv] = ru;
}

inline int upper(int i, int j) {
  return 2 * (i * m + j);
}

inline int lower(int i, int j) {
  return 2 * (i * m + j) + 1;
}

int main(int argc, char *argv[]) {
  std::cin.tie(nullptr)->std::ios_base::sync_with_stdio(false);
  std::cin >> n >> m;
  std::vector<std::string> a(n);
  for(int i=0; i<n; ++i) {
    std::cin >> a[i];
  }

  for(int i=0; i<2*n*m; ++i) {
    parent[i] = i;
  }
  components = 2 * n * m;
  
  for(int i=0; i<n; ++i) {
    for(int j=0; j<m; ++j) {
      if(i + 1 < n) {
        unite(lower(i, j), upper(i + 1, j));
      }
      if(j + 1 < m) {
        int rt = (a[i][j] == '\\') ? upper(i, j) : lower(i, j);
        int lt = (a[i][j + 1] == '\\') ? lower(i, j + 1) : upper(i, j + 1);
        unite(rt, lt);
      }
    }
  }
  
  std::cout << components << "\n";
}