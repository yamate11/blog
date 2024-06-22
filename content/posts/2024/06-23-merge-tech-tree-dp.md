---
author: "yamate11"
title: "木DP + マージテク"
date: "2024-06-23T01:14:51+09:00"
# date_init: "2024-06-23"
tags: []
categories: ["topic"]
# categories: ["solution"]
summary: "木DP と マージテクを使って解くときのコードスニペット"
---

## 概要

木のノードのペアに関する計算を，全体で $O(N)$ で行いたい問題で，
木DP で，各ノードで，子ノードが作成した map から map を計算するというパターンがある．
最終的に map のサイズが $O(N)$ になる場合，何も考えないと全体で計算量が $O(N^2)$ になってしまうところ，
マージテクを使って $O(N \log N)$ ですまそう，という解法のコードスニペットを記述する．

## 前提

[木ライブラリ](../../2024/03-13-tree-lib/)

## コードスニペット

```cpp
  ll N; cin >> N;
  Tree tr(N);           // 木ライブラリ
  REP(i, 0, N - 1) { ll u, v; cin >> u >> v; u--; v--;  tr.add_edge(u, v); }
    
  // 木DP で，各ノードは (unordered) map を返す．ここにマージテクを適用する．
  using dfs_t = map<ll, some_type>;  
  auto dfs = [&](auto rF, ll nd) -> dfs_t {
    dfs_t ret;   // 返却する map
    // 現在のノードに対する値を ret に設定する．葉なら，このまま返すことになる．
    ret[key_for_nd] = value_for_nd;
    ll sz = 1;  // マージテク用に管理する部分木サイズ．
    for (ll cld : tr.children(nd)) {   // 各子供 cld に対し，
      bool swapped = sz < tr.stsize(cld);   // swapped が false  なら ret をそのまま使う．
                                            // true なら，子供が返したものと ret を入れ替える
      auto res_cld = rF(rF, cld);  // 子供を再帰呼出
      if (swapped) swap(ret, res_cld);   // swapped に応じて入替をする・しない
      for (auto& [key, val] : res_cld) {
        auto it = ret.find(key);   
        if (it == ret.end()) {  // 子供にだけエントリがあったので，移す
          ret[key] = move(val);
        }else {  // 両方にエントリがあったのでマージをする
          it->second = ....; // it->second と val から計算をする．
                             // ここで，swapped を参照する必要があるかも知れない．
        }
        // 返却する ret の他に global 変数で値を変更するようなことも必要かもしれない
      }
      sz += tr.stsize(cld);   // 部分木サイズのアップデートを忘れないように
    }
    return ret;
  };
  dfs(dfs, 0);
```

## 適用例

[ABC359G Sum of Tree Distance](https://atcoder.jp/contests/abc359/tasks/abc359_g)

```cpp
  ll N; cin >> N;
  Tree tr(N);
  REP(i, 0, N - 1) {
    ll u, v; cin >> u >> v; u--; v--;
    tr.add_edge(u, v);
  }
  // @InpVec(N, A, dec=1) [C5a2ovTV]
  auto A = vector(N, ll());
  for (int i = 0; i < N; i++) { ll v; cin >> v; v -= 1; A[i] = v; }
  // @End [C5a2ovTV]
    
  ll ans = 0;
  using s_t = pll;
  using a_t = unordered_map<ll, s_t>;
  auto dfs = [&](auto rF, ll nd) -> a_t {
    a_t ret;
    ret[A[nd]] = s_t(tr.depth(nd), 1);
    ll sz = 1;
    for (ll cld : tr.children(nd)) {
      bool swapped = sz < tr.stsize(cld);

      auto res_cld = rF(rF, cld);
      if (swapped) swap(ret, res_cld);
      for (auto& [g, info] : res_cld) {
        auto it = ret.find(g);
        if (it != ret.end()) {
          auto [sum_dp1, num1] = it->second;
          auto [sum_dp2, num2] = info;
          ll sum_len1 = sum_dp1 - num1 * tr.depth(nd);
          ll sum_len2 = sum_dp2 - num2 * tr.depth(nd);
          ll new_val = sum_len1 * num2 + num1 * sum_len2;
          ans += new_val;
          it->second = pll(sum_dp1 + sum_dp2, num1 + num2);
        }else {
          ret[g] = info;
        }
      }
      sz += tr.stsize(cld);
    }
    return ret;
  };
  dfs(dfs, 0);
  cout << ans << endl;
```

[提出コード](https://atcoder.jp/contests/abc359/submissions/54857281)
