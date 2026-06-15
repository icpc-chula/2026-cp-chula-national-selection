#include <iostream>
#include <vector>

struct fenwick_tree {
  int n;
  std::vector<long long> t;

  fenwick_tree(int _n):
    n(_n), t(n + 1, 0ll) {}

  void update(int idx, long long v) {
    for(; idx<=n; idx+=idx&-idx) {
      t[idx] += v;
    }
  }

  long long query(int idx) {
    long long res = 0ll;
    for(; idx>0; idx-=idx&-idx) {
      res += t[idx];
    }
    return res;
  }

  long long query(int l, int r) {
    if(l > r) {
      return 0ll;
    }
    return query(r) - query(l-1);
  }
};

inline long long sum_range(int l, int r, std::vector<long long> &pref) {
  return pref[r + 1] - pref[l];
}

int main(int argc, char *argv[]) {
  std::cin.tie(nullptr)->std::ios_base::sync_with_stdio(false);
  
  int n, k;
  std::cin >> n >> k;
  std::vector<int> a(n);
  for(auto &x: a) {
    std::cin >> x;
  }

  std::vector<long long> l_inv(n, 0ll), r_inv(n, 0ll);
  long long all_inversion = 0ll;

  fenwick_tree l_fw(n);
  for(int i=0; i<n; ++i) {
    l_inv[i] = l_fw.query(a[i] + 1, n);
    all_inversion += l_inv[i];
    l_fw.update(a[i], 1);
  }

  fenwick_tree r_fw(n);
  for(int i=n-1; i>=0; --i) {
    r_inv[i] = r_fw.query(a[i] - 1);
    r_fw.update(a[i], 1);
  }

  std::vector<long long> pref_inv(n + 1, 0);
  for(int i=0; i<n; ++i) {
    pref_inv[i + 1] = pref_inv[i] + l_inv[i] + r_inv[i];
  }

  fenwick_tree window(n);
  long long window_inv = 0ll;
  for(int i=0; i<k; ++i) {
    window_inv += window.query(a[i + 1], n);
    window.update(a[i], 1);
  }

  long long max_cost = sum_range(0, k - 1, pref_inv) - window_inv;
  int ways = 1;
  for(int l=1; l<=n-k; ++l) {
    window_inv -= window.query(a[l - 1] - 1);
    window.update(a[l - 1], -1);
    
    window_inv += window.query(a[l + k - 1] + 1, n);
    window.update(a[l + k - 1], 1);

    long long current_cost = sum_range(l, l + k - 1, pref_inv) - window_inv;

    if(current_cost > max_cost) {
      max_cost = current_cost;
      ways = 1;
    }
    else if(current_cost == max_cost) {
      ways++;
    }
  }

  std::cout << all_inversion - max_cost << " " << ways << "\n";
  return 0;
}