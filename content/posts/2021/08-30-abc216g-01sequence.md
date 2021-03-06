---
author: "yamate11"
title: "01Sequence - ABC216 G"
date: "2021-08-30T10:09:03+09:00"
# date_init: "2021-08-30"
tags: ["牛ゲー", "貪欲"]
# categories: ["topic"]
categories: ["solution"]
summary: "公式解説とは違う (より効率の悪い) 方法で解きました．"

---

AtCoder Beginner Contest 216 (ABC216) G - 01Sequence の解法です．
[公式解説](https://atcoder.jp/contests/abc216/editorial/2474)によると
「[牛ゲー](../08-30-ushi-game)」で解けるとのことですが，別の (より効率が悪い) 
方法で解きました．

## 問題へのリンク

https://atcoder.jp/contests/abc216/tasks/abc216_g

## 問題概要

$N$ と $(L_i, R_i, X_i)$ ($i = 1, \ldots , M$) が与えられる．
長さ$N$の0と1からなる数列 $(A_i \mid i \in [1, N])$ で，
条件 $ | \\{ i \in [L_i, R_i] \mid A_i = 1 \\}| \geq X_i  $
を満たすもののうち，
1の数が最小のものを一つ作れ．

制約: $ N, M \leq 2 \times 10^5 $


## 解法

0の数の条件に書き換える．$Y_i := R_i - L_i + 1 - X_i$ として，
条件 $ | \\{ i \in [L_i, R_i] \mid A_i = 0 \\}| \leq Y_i  $ のもとで，
全体の0の数を最大にする．

$S_j := \\{ i \in [1, M] \mid L_i \leq j \leq R_i \\}$　と書く．

$A_0, A_1, \ldots$ の順に $A_i$ の値を，貪欲に 0 を
置くように決めていくことができる．理由は以下の通り．
今，$A$ が条件を満たすとする．$i \in S_j$ に対し，

$ t(i, j) := | \\{ k \in [L_i, j) \mid A_k = 0 \\} |$

と書く．ある $j\in [1, N]$ について，$A_j = 1$ であり，しかも
すべての $i \in S_j$ について $t(i, j) < Y_i$
であったとする．この次に$A$の値が0となる添字を $k$ とする，
すなわち，$A_{k} = 0$ で，すべての $l \in [j, k)$ に対して $A_l = 1$
とする．このとき，$A_j$ と $A_{k}$ の 0/1 を入れ替えた列も，条件を満たす．
そのような $k$ が存在しないときは，単に $A_j$ の値を 0 にした列が
条件を満たす．

したがって，次の構成を行えば良い: 
$A_0, \ldots, A_{j-1}$ まで決めたとして，$A_j$ を定める．

* すべての $i \in S_j$ について，$t(i, j) < Y_i$ のとき，$A_j = 0$
* そうでないとき，$A_j = 1$

イベントソートを用いて，次のようにすれば良いように考えられる．

* 初期時点 $j = -1$ では，すべての $i$ に対し，その残り容量は $\infty$ である．
* 時点$j$ において，
  * $j = L_i$ となる $i$ の残り容量を $Y_i$ に設定する．
  * $j = R_i$ となる $i$ の残り容量を $\infty$ に設定する．
  * 残り容量が 0 である $i$ がある場合，
    * $A_i := 1$ と定める．
  * 残り容量が 0 である $i$ がない場合，
    * $A_i := 0$ と定める．
    * 全部の $i$ の残り容量を 1 減らす．

しかし，全部の残り容量を愚直に減らしていては間に合わない．
代わりに，
「自分の区間が終わるまでに，0の累積個数 $n$ がいくつ以下でなければならない」
という量 $Z_i$ を持つことにする．

* 初期時点 $j = -1$ 
  * すべての $i$ に対し，$ Z_i := \infty $
  * $n := 0$
* 時点$j$ において，
  * $j = L_i$ となる $i$ に対し，$ Z_i := n + Y_i $
  * $j = R_i$ となる $i$ に対し，$ Z_i := \infty $
  * $Z_i$ たちの最小値が $n$ である場合:
    * $A_i := 1$ 
  * $Z_i$ たちの最小値が $n$ より大きい場合:
    * $A_i := 0$ 
    * $n := n + 1$

これは，$Z_i$ を優先度キューで管理することで実装できる．


## ACコード

https://atcoder.jp/contests/abc216/submissions/25452502
