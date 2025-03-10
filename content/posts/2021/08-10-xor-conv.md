---
author: "yamate11"
title: "xor畳み込み"
date: "2021-08-23T12:40:00+09:00"
date_init: "2021-08-12"
tags: ["xor", "畳み込み", "アダマール変換"]
categories: ["topic"]
draft: false
summary: "高速アダマール変換によって，xor畳み込みをする方法についての記事 (自分用のメモ) です．"
description: "高速アダマール変換によって，xor畳み込みをする方法についての記事 (自分用のメモ) です．"
---


## xor畳み込み

長さ $2^K$ の数列 $X$, $Y$ があるとき，
これらのxor畳み込みを，以下を満たす長さ $2^K$ の列 $Z$ として定める．
ただし，$x \oplus y$ は $x$ と $y$ の xor とする．

* $ Z_k = \sum \\{ X_i Y_j \mid i \oplus j = k \\} $

以下では，$Z = X * Y$ と書く．

## アダマール変換

長さ $2^K$ の数列に作用するアダマール (Hadamard) 変換は，以下の行列 $H_K$ で定義される
1次変換である．

$$
H_0 = 1
$$

$$
H_{k + 1} = \begin{bmatrix}
H_k & H_k \\\\
H_k & -H_k
\end{bmatrix}
$$

本来は，正規化のために定数倍するが，
ここでは，結果を整数にするためにそうしていない．

$ H_k H_k = 2^k I $ が成り立つので，$(H_k)^{-1} = 2^{-k} H_k$ である．

## 畳み込みとアダマール変換

以下が成り立つことが，計算することで容易に分かる．

$$ (H_K X) (H_K Y) = H_K (X * Y) $$

ただし，左辺は，成分ごとの積．したがって，xor 畳み込みは，下のように計算できる．

$$ X * Y = 2^{-K} H_K ((H_K X) (H_K Y)) $$

アダマール変換は，定義に従って $O(n \log n)$ で計算できる．($n = 2^K$)

メモリを賢く使って計算している例が 
[kazuma8128\'s blog](https://kazuma8128.hatenablog.com/entry/2018/05/31/144519)
に載っている．

## これを使える問題

[ABC212 H Nim Counting](https://atcoder.jp/contests/abc212/tasks/abc212_h)

