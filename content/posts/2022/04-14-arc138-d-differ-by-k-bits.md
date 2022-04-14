---
author: "yamate11"
title: "Differ by K bits - Atcoder Regular Contest 138 D"
date: "2022-04-14T08:22:15+09:00"
# date_init: "2022-04-14"
tags: ["XOR", "グレイコード"]
# categories: ["topic"]
categories: ["solution"]
summary: "公式解説とは少しだけ異なる解法です"
---

Atcoder Regular Contest 138
(大和証券プログラミングコンテスト 2022 Spring) - ARC 138 D -
Differ by K bits の解法です．
[公式解説](https://atcoder.jp/contests/arc138/editorial/3741)
を読んで，きれいに解けるのにびっくりしてしまいました．
ここに書くのはもっと泥臭いです．

## 問題概要

整数 $N$, $K$ が与えられる．
$0, 1, \ldots, 2^N - 1$ の順列
$P_0, P_1, \ldots, P_{2^N - 1}$ で，
隣接項が 2進表記でちょうど$K$桁だけ異なるものが存在するかどうか判定し，
存在する場合には1つ構成せよ．

制約: $1 \leq K \leq N \leq 18$

[問題へのリンク](https://atcoder.jp/contests/arc138/tasks/arc138_d)

## 解法

$N = 1$ の場合には，$K = 1$ であり，$P_i = i$ という解がある．
以下，$N \geq 2$ とする．

$K = N$ の場合は，あきらかに解はない．
また，$K$ が偶数の場合には，ビットカウントが奇数になる数が作れないので，
解はない．
$K < N$ かつ $K$ が奇数の場合には，
$n = K + 1, K + 2, \ldots, N$ の順に解を構成することができる．

まず，$n = K + 1$ とする．
[グレイコード](https://ja.wikipedia.org/wiki/%E3%82%B0%E3%83%AC%E3%82%A4%E3%82%B3%E3%83%BC%E3%83%89)を1つおきに反転すれば良い．具体的には，
$Q_i := i \oplus \textrm{sftR}(i)$
とすると，$(Q_i)_i$ は順列になり，隣接項は2進表記で1桁だけ異なる．
ただし，$\oplus$ は XOR で，sftR は右ビットシフト．
したがって，

$$
P_i :=
\begin{cases}
Q_i & \text{ $i$ が偶数の時}\\\\
\textrm{flip}(Q_i) & \text{ $i$ が奇数の時}
\end{cases}
$$

が解となる．ただし，flip は，末尾nビットのビット反転．

あとは，$n$ を1つずつ増やしていく．

* 順列の前半 ($i < 2^n$) は，1つ前の数列をそのまま用いる．
* 後半の先頭 ($i = 2^n$) は，
  前半の最後の数の $K-1$ ビットを反転させた上で，
  最上位ビットを立てる．
* 後半の残りは，前半の対応する場所と同じビットを反転する．

具体的には，$(Q_i)_i$ を $n$ に対する解であるとして，
$n + 1$ に対する解 $(P_i)_i$ は次のようになる．

$$
P_i :=
\begin{cases}
Q_i & (i < 2^n) \\\\
Q_{2^n - 1} \oplus (2^{K - 1} - 1) \oplus 2^n & (i = 2^n) \\\\
Q_{i - 1} \oplus (Q_{i - 2^n - 1} \oplus Q_{i - 2^n}) & (i > 2^n)
\end{cases}
$$


## 実装

```cpp
  ll N, K; cin >> N >> K;
  if (N == 1) { cout << "Yes\n0 1\n"; return 0; }
  if (K == N or K % 2 == 0) { cout << "No\n"; return 0; }
  vector<ll> ans(1LL << N);
  ll n = K + 1;
  ll mask = (1LL << n) - 1;
  REP(i, 1LL << n) {
    ll x = i ^ (i >> 1);
    ans[i] = i % 2 == 0 ? x : (x ^ mask);
  }
  for (; n < N; n++) {
    ll j0 = 1LL << n;
    ans[j0] = ans[j0 - 1] ^ ((1LL << (K - 1)) - 1) ^ j0;
    REP(i, j0 - 1) ans[j0 + i + 1] = ans[j0 + i] ^ ans[i] ^ ans[i + 1];
  }
  cout << "Yes\n";
  for (ll a : ans) cout << a << " ";
  cout << endl;
```

[ACコード](https://atcoder.jp/contests/arc138/submissions/30954663)



