---
author: "yamate11"
title: "LIS - 最長増加部分列"
date: "2024-09-01T13:13:07+09:00"
# date_init: "2024-09-01"
tags: []
categories: ["topic"]
# categories: ["solution"]
summary: "復元方法も含めた最長増加部分列に関するまとめ"
---

## 1. 最長増加部分列問題

最長増加部分列問題 (LIS = Longest Increasing Subsequence) は，与えられた数列
$A = (a_0, a_1, \dots, a_n)$
の部分列であって，
単調増加であるもののうち最長のもの，ないし，その長さを求める問題．

## 2. 長さだけで良い場合

列 $B = (b_1, b_2, \dots, b_m)$ を次のように構築する．

### 2.1. 狭義単調列の場合

* 最初は，$B = ()$.
* $i = 1, 2, ..., n$ の順に，次を実行．
  * $a_i \leq b_k$ となる最小の $k$ を二分探索で求める．(C++ なら，`lower_bound` が使える)
    * このような $k$ が存在しない場合には，$a_i$ を $B$ に加える．($B$ の長さが 1 増える．)
    * 存在する場合には，$b_k$ を $a_i$ で置き換える．
      ($a_i = b_k$ なら何もしないことになる)
* 作成された $B$ の長さが，求める長さになる．

途中の段階 ($a_i$ を処理したとき) の $b_k$ は，「$(a_1, \dots, a_i)$ の長さ $k$ の増加列の末項の最小値」
になっている．

### 2.2. 広義単調列の場合

上とほぼ同じだが，条件「$a_i \leq b_k$」を「$a_i < b_k$」 に差し替える．
C++ なら，`upper_bound` になる．

## 3. 列を 1 つ求めたい場合

値を $B$ にいれて管理するだけではなく，その値に対応する添字も $J$ にいれて管理する．
さらに，各 $i = 1, 2, \dots, n$ に対して，
「$a_i$ を含む LIS における $a_i$ の一つ前の項の，もとの数列での添字」
を，$c_i$ として保存する．具体的な手順は以下の通り．

* 最初は，$B = ()$，$J = ()$.
* $i = 1, 2, ..., n$ の順に，次を実行する．
  * この時点で，$B = (b_1, \dots, b_m)$，$J = (j_1, \dots, j_m)$ であるとする．
  * $a_i \leq b_k$ となる  (広義単調列なら，$a_i < b_k$ となる) 最小の $k$ を二分探索で求める．
    * このような $k$ が存在しない場合には，$k := m + 1$ として，
      * $B$ には，$a_i$ を加える．
      * $J$ には，$i$ を加える．
    * 存在する場合には，
      * $b_k$ を $a_i$ で置き換える．
      * $j_k$ を $i$ で置き換える．
  * $c_i$ については，
    * $k > 1$ の場合には，$c_i := j_{k - 1}$ とする．
    * $k = 1$ の場合には，$c_i := 0$ とする．
* 最終的に $B = (b_1, \dots, b_m)$，$J = (j_1, \dots, j_m)$ が得られたとする．
  1 つの LIS が，次の手順で求められる．
  * 求める LIS の末項は，$b_m$ すなわち $a_{j_m}$ である．
  * $a_{j}$ が LIS の項である時，$c_j > 0$ なら，その一つ前の項は $a_{c_j}$ である．$c_j = 0$ ならそれが初項である．

## 4. 適用可能な問題

* [ABC 369 F Gather Coins](https://atcoder.jp/contests/abc369/tasks/abc369_f)

