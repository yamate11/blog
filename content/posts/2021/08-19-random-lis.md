---
author: "yamate11"
title: "Random LIS - Atcoder Regular Contest 104 E"
date: "2021-08-19"
tags: ["ordered bell number", "DP", "LIS", "期待値"]
categories: ["solution"]
draft: false
---

Atcoder Regular Contest 104 (ARC 104) E Random LIS に関する記事です．

## 問題文へのリンク

https://atcoder.jp/contests/arc104/tasks/arc104_e

## 経緯

過去問埋めで解いてみようとしましたが，全然分かりませんでした．
[公式解説](https://atcoder.jp/contests/arc104/editorial/159) を読んでもやっぱりわからず，
[けんちょんさんの解説](https://drken1215.hatenablog.com/entry/2020/10/06/101900) 
でなんとか理解できました．

## 解法

例えば，N = 4 として，数列 `10 7 10 15` と数列 `5 1 5 2000` は，
数値の差こそあれ，大小関係は同一である．これらを `1 0 1 2` というパターンとして
1つのグループとしてまとめることにする．以下を実行する．

* 全パターンを列挙する．
* 各パターンについて，
    * LISの長さを求める．
    * そのパターンに属する数列の数を数える．
    
グループがいくつあるかは，
[Ordered Bell number](https://en.wikipedia.org/wiki/Ordered_Bell_number)
として知られているということである．N = 6 の場合には，4683個．
丁寧に列挙することもできるであろうが，$6^6 = 46656$ であるから，0 から N-1 までの
数の N 個の並びから，不適なものを弾いても十分速い．
各グループに属する数列では，LIS の長さは同じであり，N <= 6 だからこれを求めるのは容易である．
各グループに属する数列の数を求めるのが主要なタスクとなる．

$\\{0, 1\\} \cup \\{A_i + 1\mid i = 1, \ldots, N\\}$ を昇順にソートして 
$p_0, p_1, .., p_M$ とし，$P_i$ を整数の半開区間 $[p_i, p_{i+1})$ とする．

パターンを1つとる．パターン中に現れる数が $0, 1, \ldots, D-1$ だとする．
各 $d \in [0, D)$ について，これが現れる位置を
$q_1, \ldots, q_k$ としたとき，$\min(A_{q_1}, \ldots, A_{q_k})$ を $B_d$ とする．
たとえば，パターン `2 2 2 0 1 1` については，$B_0 = A_3$,
$B_1 = \min(A_4, A_5)$, $B_2 = \min(A_0, A_1, A_2)$ である．
すると，パターンに属する数列の数は，数列 $( x_d | d \in [0, D) )$ であって
$x_d \in [1, B_d + 1)$ を満たすものの数に等しいので，これを数えることにする．

動的計画法による．
「長さ i の列 $( x_d | d \in [0, i) )$ で
$x_d \in [1, B_d + 1)$ を満たし，$ x_{i-1} \in P_j $ であるもの」の集合を $S_{i,j}$
とし，`dp[i][j]` を，$S_{i,j}$ の要素の数とする．
普通に dp[i][j] → dp[i+1][j'] の遷移を書こうとすると，j = j' の時に
うまくいかない．そこで，次のことに注目する: 
長さ i の列 $(x_d \mid d \in [0, i) )$ について，次の2つは同値である．

* $( x_d \mid d \in [0, i) ) \in S_{i,j}$ 
* $k < i$, $u < j$ が存在して，以下が成り立つ．
    * $(x_d \mid d \in [0, k) ) \in S_{k, u}$
    * 各 $e \in [k, i)$ に対して，$B_e + 1 \geq p_{j+1}$
    * $i - k \leq p_{j+1} - p_j$

そこで，以下のように遷移を定義することができる:

```
  dp[i][j] ← dp[k][u] * binom(p[j+1] - p[j], i - k)
    where
      * i > k  and
      * j > u  and
      * i - k <= p[j+1] - p[j]  and
      * forall e in [k, i).  B[e] + 1 >= p[j+1]
```

## ACコード

https://atcoder.jp/contests/arc104/submissions/25160111




