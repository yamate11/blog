#include <bits/stdc++.h>
#include <cassert>
typedef long long int ll;
using namespace std;

// For performance measurement.
// Returns seconds from the epoch in double
double get_time_sec() {
  using namespace std::chrono;
  return static_cast<double>(duration_cast<nanoseconds>(steady_clock::now().time_since_epoch()).count())/1000000000;
}

template<typename E>
struct CSR {
  int size;
  vector<int> start;
  vector<E> es;
  vector<pair<int, E>> tmp;
  CSR(int size_) : size(size_), start(size + 1) {}
  void add(int i, const E& e) { tmp.emplace_back(i, E(e)); }
  void add(int i, E&& e) { tmp.emplace_back(i, e); }
  void build() {
    vector<int> num(size);
    int tot = 0;
    for (auto& [i, e] : tmp) {
      num[i]++;
      tot++;
    }
    es.resize(tot);
    for (int i = 0; i < size; i++) start[i+1] = start[i] + num[i];
    for (auto& [i, e] : tmp) {
      es[start[i + 1] - num[i]] = move(e);
      num[i]--;
    }
  }
};

double r1, r2, r3, r4;

void func_vv(ll N, const auto& edges, auto& ans) {
  r1 = get_time_sec();
  vector<vector<int>> nbr(N);
  for (const auto& [u, v] : edges) {
    nbr[u].push_back(v);
    nbr[v].push_back(u);
  }
  r2 = get_time_sec();
  auto dfs = [&](auto rF, int node, int parent) -> int {
    int cnt = 1;
    for (int child : nbr[node]) {
      if (child == parent) continue;
      cnt += rF(rF, child, node);
    }
    ans[node] = cnt;
    return cnt;
  };
  dfs(dfs, 0, -1);
}

void func_csr(ll N, const auto& edges, auto& ans) {
  r3 = get_time_sec();
  CSR<int> csr(N);
  for (const auto& [u, v] : edges) {
    csr.add(u, v);
    csr.add(v, u);
  }
  csr.build();
  r4 = get_time_sec();
  auto dfs = [&](auto rF, int node, int parent) -> int {
    int cnt = 1;
    for (int i = csr.start[node]; i < csr.start[node + 1]; i++) {
      int child = csr.es[i];
      if (child == parent) continue;
      cnt += rF(rF, child, node);
    }
    ans[node] = cnt;
    return cnt;
  };
  dfs(dfs, 0, -1);
}

int main(/* int argc, char *argv[] */) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout << setprecision(20);

  double t1 = get_time_sec();
  ll N; cin >> N;
  vector<pair<int, int>> edges;
  for (ll i = 0; i < N-1; i++) {
    ll u, v; cin >> u >> v;
    edges.emplace_back(u, v);
  }
  vector<int> ans1(N);
  vector<int> ans2(N);

  double t2 = get_time_sec();
  func_vv(N, edges, ans1);
  double t3 = get_time_sec();
  func_csr(N, edges, ans2);
  double t4 = get_time_sec();

  assert(ans1 == ans2);

  cout << "read input  " << t2 - t1 << endl;
  cout << "vv  " << t3 - t2 << endl;
  cout << "   conv " << r2 - r1 << endl;
  cout << "csr  " << t4 - t3 << endl;
  cout << "   conv " << r4 - r3 << endl;

  return 0;
}

