---
author: "yamate11"
title: "Xor Query -- AtCoder Beginner Contest 223 H"
date: "2021-10-21T23:28:37+09:00"
# date_init: "2021-10-21"
tags: []
# categories: ["topic"]
categories: ["solution"]
summary: "AtCoder Beginner Contest 223 (ABC223) H - Xor Query の解法です．解説ACですが，基底は熨斗袋さんの方法で求めました．"
---

AtCoder Beginner Contest 223 (ABC223) H - Xor Query の解法です．解説ACですが，基底は熨斗袋さんの方法で求めました．

## 問題概要

```
正の整数 N と長さN の正の整数列 A = (A_i)_{i<=N} が与えられる．
Q個のクエリを処理せよ．クエリでは，(L, R, X) が与えられるので，
A_L, A_{L+1}, ..., A_R から1つ以上を選んでそれらの XOR を X に
できるかどうか判定する．
制約: N <= 4e5, Q <= 2e5, 1 <= A_i,X_i < 2^60, 
TL: 3sec
```

[問題へのリンク](https://atcoder.jp/contests/abc223/tasks/abc223_h)

## 解法

$A_i$ や $X_i$ を，$\textrm{F}_2$ のベクトルと見る．

$(A_{i}, A_{i-1}, \ldots, A_1)$ が張る空間の基底
$B_i = (A_{j_p} \mid p = 1, 2, .., m_i)$ を次のように選ぶ

* $B_0 = $空リスト
* $B_i'$ を，$B_{i-1}$ の先頭に $A_i$ を追加したものとするとき，
  $B_i$ は，[予備知識](../10-22-basis-using-min) に記載した方法で$B_i'$ から選んだ基底．

この場合，$B_i = (A_{j_1}, \ldots, A_{j_{m_i}})$ は，
$A_i, A_{i-1}, \ldots, A_1$ が張る空間の基底で，
$i = j_1 > j_2 > \cdots > j_{m_i}$ となっており，$j_k \geq j >  j_{k+1}$
のとき，$A_j$ は，$A_{j_1}, \ldots, A_{j_k}$ が張る空間に属する．

クエリ $(L, R, X)$ は，次のように処理できる:
$B_R = (A_{j_1}, \ldots, A_{j_m})$ とする．
$X$ が $(A_{j_1}, \ldots, A_{j_k})$ が張る空間に属するような
最小の $k$ を，[予備知識](../10-22-basis-using-min) に記載した方法で決定する．
$L \leq {j_k}$ なら「Yes」を，そうでなければ「No」を出力する．

$A_i$ などのビット数を$p$として，$B_i$ の決定は $O(p^2)$ で，
$k$ の決定は $O(p)$ でできるので，全体の計算量は
$O(p^2 N + pQ)$ である．

一般に，$x$ が $y_1, \ldots, y_m$ が張る空間に属するかどうかは，
熨斗袋さんの方法で $O(m)$ で計算できるので，
上の手続きの計算量は，
$O(p^2 (N + Q))$ である．

## ACコード

```cpp
#include <bits/stdc++.h>
#include <cassert>
typedef long long int ll;
using namespace std;
#define REP2(i, a, b) for (ll i = (a); i < (b); i++)
#define REP2R(i, a, b) for (ll i = (a); i >= (b); i--)
#define REP(i, b) REP2(i, 0, b)
#define ALL(coll) (coll).begin(), (coll).end()
#define SIZE(v) ((ll)((v).size()))

int main(/* int argc, char *argv[] */) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout << setprecision(20);

  auto func1 = [&](ll x, const auto& v) -> pair<ll, ll> {
    REP(j, SIZE(v)) if ((x = min(x, x ^ v[j].second)) == 0) return {j, 0};
    return {-1, x};
  };

  ll N, Q; cin >> N >> Q;
  vector<ll> A(N); REP(i, N) cin >> A[i];
  using sta = pair<ll, ll>;
  vector<vector<sta>> B(N);

  REP(i, N) {
    B[i].emplace_back(i, A[i]);
    if (i == 0) continue;
    ll sz = SIZE(B[i - 1]);
    ll j0 = [&]() -> ll {
      REP(j, sz) {
        auto [p, y] = B[i - 1][j];
        auto [k, x] = func1(y, B[i]);
        if (k < 0)  B[i].emplace_back(p, x);
        else        return j + 1;
      }
      return sz;
    }();
    REP2(j, j0, sz) B[i].push_back(B[i - 1][j]);
  }

  REP(i, Q) {
    ll l, r, x; cin >> l >> r >> x; l--; r--;
    auto [j, dummy] = func1(x, B[r]);
    cout << (j >= 0 && l <= B[r][j].first ? "Yes\n" : "No\n");
  }
  return 0;
}
```

