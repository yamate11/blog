---
author: "yamate11"
title: "Cubic? - AtCoder Beginner Contest 238 G"
date: "2022-02-13T11:48:45+09:00"
# date_init: "2022-02-13"
tags: []
# categories: ["topic"]
categories: ["solution"]
summary: "ABC238G Cubic? の解法です．公式解説と同じです．"
---

AtCoder Beginner Contest 238 - ABC 238 G - Cubic? の解法です．
[公式解説](https://atcoder.jp/contests/abc238/editorial/3358) 
と本質的に同じです．

## 問題概要

長さ$N$の数列$A$が与えられる．$Q$個の質問に答えよ

* $i$番目の質問: $L_i$, $R_i$ が与えられる．$A_{L_i} \times \cdots \times A_{R_i}$ は立方数か?

制約: $N, Q \leq 2\times 10^5$, $A_i \leq 10^6$

[問題へのリンク](https://atcoder.jp/contests/abc238/tasks/abc238_g)

## 経緯

コンテストでは，時間内には解けませんでした．
終了後に，Mo のアルゴリズムが適用できると気づいて，解けました．
公式解説を読んでみたら，ハッシュで解けると書いてありました．
Twitter で，Zobrist Hash というものがあると
[指摘されて](https://twitter.com/tatyam_prime/status/1489958194374115332)
いて，調べました．

## 解法

全部の $A_i$ を素因数分解しておく
(40msくらいでできる．[別記事](../02-06-prime-factor-perf/) 参照)．
これらの素因数分解に現れる素数全体の集合を $P$ とし，
$S := \\{ (p, i) \mid p \in P \textrm{, } i \in \\{1, 2\\} \\}$
とする．
$S$ の Zobrist Hash $h$ を考える．
Zobrist Hash については，[別記事](../02-13-zobrist-hash/) 参照．

正の整数 $a$ を素因数分解して，
冪の部分をすべて3で割ったあまりで置き換えて得られる素冪のうち，
$1$ を除いた集合を$f(a)$ と書くことにする．
たとえば，$f(7^5\times 13^{6} \times 17^{40}) := \\{7^2, 17^1\\}$．

$B_i := f(A_1 \times A_2 \times \cdots \times A_i)$ とする．
$2\times3\times5\times7\times11\times13\times17>2\times10^5$
であるから，
$|(B_{i + 1} \setminus B_{i}) \cup (B_i \setminus B_{i + 1})|$ 
はたかだか $6$ である．そこで，$B_i$ たちをすべて決定することができる．

$C_i := h(B_i)$ として，$i$ 番目の質問には，
$C_{L_i-1} == C_{R_i}$ であるかどうかを答える．
WAとなる確率はたかだか $QT / V$ (ここで，$T$ はテストケースの数，
$V$ はハッシュ関数の値域のサイズ) であるから，$V = 2^{63}$ に
とっておけば十分小さい．

## 実装

[提出コード](https://atcoder.jp/contests/abc238/submissions/29252208)


