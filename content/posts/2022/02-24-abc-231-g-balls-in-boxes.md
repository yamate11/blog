---
author: "yamate11"
title: "Balls in Boxes - Atcoder Beginner Contest 231 G"
date: "2022-02-24T10:06:13+09:00"
# date_init: "2022-02-24"
tags: ["期待値"]
# categories: ["topic"]
categories: ["solution"]
summary: "解説ACです"
---

AtCoder Beginner Contest 231 - ABC 231 G - Balls in Boxes の解法です．
公式解説と同じです．

## 問題概要

[問題へのリンク](https://atcoder.jp/contests/abc231/tasks/abc231_g)

$N$個の箱があり，箱$i$ には $A_i$ 個のボールが入っている．
「箱を1つ選んでボールを1個入れる」ことを$K$回繰り返す．
操作後の各箱のボールの数を $B_i$ として，
$\prod_{i=1}^{N}B_i$ の期待値を mod 998244353 で求めよ．

## 解法1

[公式解説1](https://atcoder.jp/contests/abc231/editorial/3051) による．

例として $N=3$ とする．

確率変数 $X_i$ を，「箱$i$が選ばれた回数」を表すものとする．
求める期待値は，
$E( (A_1 + X_1)(A_2 + X_2)(A_3 + X_3) )$．
展開すると
$A_1A_2A_3 + A_1A_2E(X_1) + A_2A_3E(X_2) + A_3A_1E(X_3)$
$    + A_1E(X_2X_3) + A_2E(X_3X_1) + A_3E(X_2X_3) + E(X_1X_2X_3)
$
だが，対称性から $E(X_1) = E(X_2)$ などが成り立つので，これは
$A_1A_2A_3 + (A_1A_2 + A_2A_3 + A_3A_1)E(X_1)$
$    + (A_1 + A_2 + A_3)E(X_1X_2) + E(X_1X_2X_3)
$
に等しい．

一般に，$A_1, \ldots, A_i$ の $j$ 次の対称式の値を $S(i,j)$ とし，
$e(i) := E(X_1X_2\cdots X_i)$ とすれば，
求める答は $\sum_{i = 1}^{N} S(N, N + 1 - i)e(i - 1)$
となる．

対称式の値の方は，
$S(i, j) = [t^{i - j}]\prod_{k = 1}^{i}(t - A_k)$ であるから，
右辺を愚直に計算して $O(N^2)$ で求められる．

$e(i)$ を求めるために，確率変数 $Y_{i,k}$ を，箱$i$ が $k$ 回目に
選ばれるとき $1$，選ばれないとき $0$ をとるものとする．
$X_i = \sum_{k = 1}^{K}Y_{i,k}$ であるから，$E(X_1\cdots X_i)$ を展開して，
$e(i) = \sum \\{ E(\prod_{j = 1}^i Y_{j,c(j)}) \mid c : \bar{i} \to \bar{K} \\}$
となる．ここに，$\bar{n} := \\{1, 2, \ldots, n\\}$．
$c : \bar{i} \to \bar{K}$ が単射でない時には，
$\prod_{j = 1}^i Y_{j,c(j)}$ の値は 0 である．
一方で $c : \bar{i} \to \bar{K}$ が単射の時には，
$Y_{1,c(1)}, \cdots, Y_{i,c(i)}$ は独立である．
したがって，
$e(i) = \sum \\{ \prod_{j = 1}^i E(Y_{j,c(j)}) 
                  \mid c : \bar{i} \to \bar{K} \text{ は単射} \\}$
$      = \sum \\{ 1 / N^i
                  \mid c : \bar{i} \to \bar{K} \text{ は単射} \\}$
$      = (1 / N^i) (K! / (K - i)!)$
と計算できる．

## 解法2

[公式解説2](https://atcoder.jp/contests/abc231/editorial/3091) による．
$\prod_{i = 1}^{N} B_i$ を，「$B_i$ 個ずつあるものから1つずつ選ぶ
場合の数と見る」というのがポイント．

すべての操作について $\prod_{i=1}^{N}B_i$ の和を求め，
$N^K$ で割れば答が求められる．

操作列 $C_1, \ldots, C_K$ をとる．
すなわち，各 $i$ に対して $1 \leq C_j \leq N$ となる列をとる．
列 $D_1, \ldots, D_N$ を，各 $i$ に対して，$1 \leq D_i \leq B_i$
となるようにとる．
<!-- $P := \\{i \mid D_i \leq A_i\\}$ とする． -->

列 $P_1, \ldots, P_N$ を次のように定める:

* $D_i \leq A_i$ のとき，$P_i := D_i$
* そうでないとき，$P_i := 0$

列 $Q_1, \ldots, Q_K$ を次のように定める: 
$i := C_j$ として，$A_i < D_i$ であって，しかも，
第$j$回目の操作で，
箱$i$が選ばれた回数がちょうど $D_i - A_i$ 回になった場合には，
$ Q_j := -i$，そうでないとき，$ Q_j := i$

$(C, D)$ に対して $(P, Q)$ を対応させる写像は単射である．
$(C, D)$ の数は，すべての操作に対する $\prod_{i=1}^{N} B_i$ の和であるから，
$(P, Q)$ の数が求める答になる．これは，次の場合の数である．

* $S \subseteq \bar{N}$ を選ぶ．
* 各 $i \in S$ について $\bar{A_i}$ から1つ選ぶ
* 各 $i \in \bar{N} \setminus S$ に対し，
  ($Q_j = -i$ とする) $j = j_i \in \bar{K}$ を，重複のないように選ぶ．
* 各 $j \in \bar{K} \setminus \\{ j_i \mid i \in \bar{N} \setminus S\\}$
  について，$\bar{N}$ から1つ選ぶ

$S$ を決めたときの後半2項目の選び方は，$m := |\bar{N} \setminus S|$ として，
$(K! / (K - m)!)N^{K - m}$ である．つまり，$m$ にしか依存しない．
前半2項目のために，次のDPを考える．
求める答は 
$\sum_{m=0}^{N}\textit{dp}[N][N-m]\cdot(K! / (K - m)!)N^{K - m}$である．

* $dp[i][j] := \sum\\{ f(S) \mid S \subseteq \bar{i}$, $|S| = j \\}$ 
  * ただし，$f(S)$ は，各 $k \in S$ について，$A_k$ から1つとる場合の数．

次のように $O(N)$ で計算できる．

* $dp[0][0] = 1$, $\qquad dp[0][j] = 0\quad$ ($j > 0)$
* $dp[i][j] = dp[i - 1][j] + A_i \times dp[i - 1][j - 1]$

式を書いてみると，解法1も解法2も同じ計算になることがわかる．
(dpの部分は，対称式の計算と同じ．)

## 実装

[ACコード](https://atcoder.jp/contests/abc231/submissions/29614471)

