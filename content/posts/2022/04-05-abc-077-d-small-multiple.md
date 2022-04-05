---
author: "yamate11"
title: "Small Multiple - Atcoder Beginner Contest 077 D"
date: "2022-04-05T09:58:31+09:00"
# date_init: "2022-04-05"
tags: ["0-1BFS"]
# categories: ["topic"]
categories: ["solution"]
summary: "公式解説の行間を埋めました．"
---

Atcoder Beginner Contest 077 - ABC 077 D - Small Multiple の解法です．
[公式解説](https://img.atcoder.jp/arc084/editorial.pdf) の通りですが，
少し丁寧に書きました．


# 問題概要

2以上の整数 $K$ が与えられる．
$K$ の倍数である正の整数について，
十進表記の各桁の和としてありうる最小の値を求めよ．

制約: $K \leq 10^5$

[問題へのリンク](https://atcoder.jp/contests/abc077/tasks/arc084_b)

# 解法

整数 $t$ の十進表記を $t = \sum_{i=0}^{m} d_i 10^i$ としたとき，
各桁の和を $f(t) = \sum_{i=0}^{m} d_i$ で表す．次が成り立つのは明らか．

* $f(t + 1) \leq f(t) + 1$
* $d_0 \not= 9$ のとき，$f(t + 1) = f(t) + 1$
* $f(10t) = f(t)$

#### 補題1

> 非負整数列 $a_0, a_1, \ldots$ が次を満たすとする:
>
> * $a_0 = 0$
> * 各 $i$ について，
>   $a_{i + 1} = a_i + 1$ または $a_{i + 1} = 10 a_i$
> 
> 非負整数列 $b_0, b_1, \ldots$ を，次で定義する:
> * $b_0 = 0$
> * $a_{i + 1} = a_i + 1$ のとき，$b_{i + 1} = b_i + 1$
> * $a_{i + 1} = 10 a_i$ のとき，$b_{i + 1} = b_i$
> 
> このとき，$f(a_i) \leq b_i$ である．

#### 証明

簡単な帰納法．(終)

#### 補題2

> 正の整数 $t$ に対し，整数列 $a_0, a_1, ..., a_m$ で，次を満たすものが取れる:
>
> * $m > 0$
> * $a_0 = 0$
> * 各 $i$ について，
>   $a_{i + 1} = a_i + 1$ または $a_{i + 1} = 10 a_i$
> * $a_m = t$
> * 補題1で定義する列 $b_0, b_1, \ldots, b_m$ について，$f(a_m) = b_m$

#### 証明

$t = 10s$ のときには，$s$ に対する列の後ろに $t$ を追加すれば良い．
$t = 10s + k\quad(1 \leq k \leq 9)$ のときには，$t - 1$ に対する
列の後ろに $t$ を追加すれば良い．(終)

ノードが $0, 1, \ldots, K-1$ からなる重み付き有向グラフを考える:
$\newcommand{\foo}{\\;(\textrm{mod}~K)}$

* $x$ から $x + 1 \foo$  に，重み 1 の辺がある．
* $x$ から $10x \foo$ に，重み 0 の辺がある．

補題1の条件を満たす整数列 $a_0, a_1, \ldots, a_m$ と
$b_0, b_1, \ldots, b_m$ に対して，
$a_0\foo, a_1\foo, \ldots, a_m\foo$ は，このグラフのパスになり，
その重みは $b_m$ である．
したがって，補題1, 2 より，ノード 0 から ノード 0 に至る長さ 2 以上の
パスのうち最も短いものの重みが求める答となる．

0-1 BFS により，計算量 $O(K)$ で求められる．

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

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout << setprecision(20);

  ll K; cin >> K;
  using sta = pair<ll, ll>;
  deque<sta> deq;
  const ll big = 1e10;
  vector<ll> dist(K, big);
  dist[1] = 1;
  deq.emplace_back(1, 1);
  while (not deq.empty()) {
    auto [d, n] = deq.front(); deq.pop_front();
    if (dist[n] < d) continue;
    if (n == 0) {
      cout << d << endl;
      return 0;
    }
    ll y = (n + 1) % K;
    if (d + 1 < dist[y]) {
      dist[y] = d + 1;
      deq.emplace_back(d + 1, y);
    }
    y = (10 * n) % K;
    if (d < dist[y]) {
      dist[y] = d;
      deq.emplace_front(d, y);
    }
  }

  return 0;
}
```

