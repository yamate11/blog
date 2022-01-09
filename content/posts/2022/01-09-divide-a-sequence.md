---
author: "yamate11"
title: "Divide A Sequence - AtCoder Beginner Contest 234 G"
date: "2022-01-09T18:19:30+09:00"
# date_init: "2022-01-09"
tags: []
# categories: ["topic"]
categories: ["solution"]
summary: "方針にも実装にも時間がかかりました．"
---

AtCoder Beginner Contest 234 - ABC 234 G - Divide A Sequence の解法です．
[公式解説](https://atcoder.jp/contests/abc234/editorial/3227) 
と本質的に同じだと思います．

コンテストでは，時間が50分くらいあったのですが，解けませんでした．
だいたい下に書く解法には到達するまで30分以上かかって，
実装が終わったときには，コンテスト終了後2時間くらいたっていました．

## 問題概要

[問題へのリンク](https://atcoder.jp/contests/abc234/tasks/abc234_g)

長さ $N$ の数列 $A$ が与えられる．
$A$ を空でない連続した部分列 $B_1, B_2, \ldots, B_k$ 
に切り分ける各方法について，
$\prod_{i=1}^{k}(\max(B_i) - \min(B_i))$ 
を求め，その総和を$\mod 998244353$ で求めよ．

制約: $1 \leq N \leq 3 \times 10^5; \\; 1 \leq A_i \leq 10^9$

## 解法

全部 0-indexed で考える．$A_i$ の代わりに $A[i]$ と書く．
また，
Python 風に，$A[x:y]$ で，
列 $A_x, A_{x + 1}, \ldots, A_{y - 1}$ を表すことにする．

$f(n)$ を，$A[0:n]$ に対する問題の答とする．
$f(N)$ を求めることが目標である．

次のように定義する:

* $q(x, y) := \max(A[x:y])$
* $r(x, y) := \min(A[x:y])$
* $p(x, y) := q(x, y) - r(x, y)$

積和の最後の要素ごとにまとめることによって，次が成り立つ．

* $f(n) = \sum_{i = 0}^{n-1} f(i)p(i, n)$

ただし，$f(0) = 1$ とする．
これで答を求めることができるが，$\Theta(N^2)$ である．
そこで，$f(n)$ の計算結果を利用して $f(n + 1)$ を計算することを考える．
次のように置く:

* $g(n) := f(n + 1) - f(n)$

$g(0) = -1$ である．$n \geq 1$ の場合は，
$p(n, n+1) = A[n] - A[n] = 0$ に注意すると，次が成り立つ:

* $g(n) = \sum_{i = 0}^{n - 1} f(i)(p(i, n + 1) - p(i, n))$

次のように置く:

* $g_1(n) := \sum_{i = 0}^{n - 1} f(i)(q(i, n + 1) - q(i, n))$
* $g_2(n) := \sum_{i = 0}^{n - 1} f(i)(r(i, n + 1) - r(i, n))$

以下，$g_1$ を求める．
$g_2$ も同様に求められ，$g(n) = g_1(n) - g_2(n)$ 
だから，答が得られる．

$k(n)$ と $t(n, j)$ ($j \in [0, k(n)]$) を定義する:

* $t(n, 0) := n - 1$
* $A[i] > \max(A[i + 1 : n])$ が成り立つ $i \in [0, n - 1)$ を列挙して，
  大きい順に $t(n, 1), t(n, 2), \ldots, t(n, k(n) - 1)$ とする．
* $t(n, k(n)) = -1$

ただし，$n = 0$ については，$k(0) := 0$, $t(0, 0) := -1$ である．

つまり，$i \in (t(n, j + 1), t(n, j)]$ ならば，
  $\max(A[i:n]) = A[t(n, j)]$ となる．

この列を用いて，$g_1(n)$ は次のようにかける．

* $g_1(n) = \sum_{j = 0}^{k(n)} \max(0, A[n] - A[t(n, j)]) \sum_{i = t(n, j + 1) + 1}^{t(n, j)} f(i)$

そこで，いつものように累積和を

* $h(0) = 0$
* $h(n + 1) = h(n) + f(n)$

と定義すれば，

* $g_1(n) = \sum_{j = 0}^{k(n)} \max(0, A[n] - A[t(n, j)]) ( h(t(n, j) + 1) - h(t(n, j + 1) + 1))$

となる．
$t(n, *)$ は，stack で実装すれば良い．
$t(n + 1, *)$ を計算するときには，$t(n, *)$ をアップデートすることになる．
$A[t(n, j)]$ は，$j$ に関して単調増加であることに注意する．
全体の計算量は $O(N)$ である．

## コード

[提出コード全体へのリンク](https://atcoder.jp/contests/abc234/submissions/28435497)

主要部分:

```cpp
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ll N; cin >> N;
  vector<ll> A(N);
  REP(i, N) cin >> A[i];
  vector<Fp> f = {1, 0}; f.resize(N + 1);
  vector<Fp> h = {0, 1, 1}; h.resize(N + 2);
  vector<pair<ll, ll>> stack_max = {{-1, -1}, {0, A[0]}};
  vector<pair<ll, ll>> stack_min = {{-1, -1}, {0, A[0]}};
  REP2(n, 1, N) {
    auto compute = [&](auto& stack, auto cmp) -> Fp {
      Fp g = 0;
      auto [i, v] = stack.back();
      while (not (i < 0 or A[n] == v or cmp(A[n], v))) {
        stack.pop_back();
        auto [ii, vv] = stack.back();
        g += (A[n] - v) * (h[i + 1] - h[ii + 1]);
        i = ii;
        v = vv;
      }
      stack.emplace_back(n, A[n]);
      return g;
    };
    Fp g1 = compute(stack_max, less<ll>());
    Fp g2 = compute(stack_min, greater<ll>());
    f[n + 1] = f[n] + (g1 - g2);
    h[n + 2] = h[n + 1] + f[n + 1];
  }
  cout << f[N] << endl;

  return 0;
}
```
