---
author: "yamate11"
title: "集合・多重集合のハッシュ"
date: "2024-08-26T00:00:00+09:00"
date_init: "2022-02-13T11:32:14+09:00"
tags: ["ハッシュ"]
categories: ["topic"]
# categories: ["solution"]
summary: "集合のハッシュに関する記事です"
---

集合と多重集合のハッシュに関する記事です．

## 1. 集合のハッシュ

Zobrist Hashing と呼ばれるハッシュ方式がある．以下の記載は
[Wikipedia](https://en.wikipedia.org/wiki/Zobrist_hashing)
に依る．

### 1.1 Zobrist Hashing とは

以下では，ビットごとの XOR を $\oplus$ と書く．

Zobrist hashing は，固定された有限集合 $S$ の部分集合 に対するハッシュ方式である．
$R$ を2冪の大きな数 (たとえば $2^{63}$) として，
あらかじめ各 $x \in S$ に対して区間$[0, R)$ から一様乱数により $r(x)$ を選んでおく．
$X \subseteq S$ のハッシュ値 を，$h(X) := \bigoplus \\{ r(x) \mid x \in X\\}$
で定める．

### 1.2 性質

* $h(Y) = h(X) \oplus h(X \setminus Y) \oplus h(Y \setminus X)$．
  * したがって，$h(X)$ がわかっていれば，
    $h(X \cup \\{x\\})$ や，$h(X \setminus \\{x\\})$ を $O(1)$ で計算できる．
* 衝突確率．$X, Y \subseteq S$, $X \neq Y$
  のとき，$h(X) = h(Y)$ となる確率は，$1/R$ である．
  実際，$\\{d_1, d_2, \ldots, d_k\\} := (X \setminus Y) \cup (Y \setminus X)$ とすると，
  衝突する条件は，$r(d_1) = \bigoplus \\{ r(d_j) \mid j = 2, \ldots, k \\}$ である．

### 1.3 使用例

[ABC238 G - Cubic?](../02-13-abc238-g-cubic/)


## 2. 多重集合のハッシュ

XOR の代わりに加法 (mod M) を用いることで，多重集合のハッシュが作成できる．
以下の記載は，[ABC367の noshi91 さんによるユーザ解説](https://atcoder.jp/contests/abc367/editorial/10713) による．

### 2.1 定義

固定された有限集合 $S$ の部分多重集合に対するハッシュ方式を定義する．
$P$ を大きな素数，たとえば $P = 2^{61} - 1$ として，
あらかじめ各 $x \in S$ に対して，区間 $[0, P)$ から一様乱数により $r(x)$ を選んでおく．
$X \subseteq S$ のハッシュ値を，$h(X) := \sum \\{ r(x) \mid x \in X \\} \bmod P$ で定める．

### 2.2 性質

* $h(Y) \equiv h(X) + h(Y \setminus X) - h(X \setminus Y) \pmod P$．
  * したがって，$h(X)$ がわかっていれば，
    $h(X \cup \\{x\\})$ や，$h(X \setminus \\{x\\})$ を $O(1)$ で計算できる．
* 衝突確率．$X, Y$ が $S$ の部分多重集合で, $X \neq Y$
  のとき，$h(X) = h(Y)$ となる確率は，$1/P$ である．
  * (証明) $X \neq Y$, $h(X) = h(Y)$ とする．
    $X$ と $Y$ に現れる回数が異なる要素 $x$ をとり，前者の回数から後者の回数を引いた差を $c$ とする．
    $X'$, $Y'$ を，$X$, $Y$ の $x$ 以外の要素からなる多重集合とすれば，
    $0 = h(X) - h(Y) \equiv c r(x) + h(X') - h(Y')$ であるから，$ r(x) \equiv (h(Y') - h(X')) / c $ を得る．
    $r(x)$ がこの関係を満たす確率は $1/P$ である．    

### 2.3 使用例

[ABC367 F - Rearrange Query](https://atcoder.jp/contests/abc367/tasks/abc367_f)

### 2.4 注意事項

上記 [ユーザ解説](https://atcoder.jp/contests/abc367/editorial/10713) によれば，
$P = 2^{64}$ でも (上の証明の $c$ で割る部分は適用できないが) 問題無く小さな衝突確率になるとのことである．