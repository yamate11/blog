---
author: "yamate11"
title: "AtCoder Regular Contest 056 D - サケノミ"
date: "2021-01-06"
tags: []
categories: ["solution"]
draft: false
---
AtCoder Regular Contest (ARC) 056 D - サケノミ についての記事です．

## 問題へのリンク

<div class="iframely-embed"><div class="iframely-responsive" style="height: 140px; padding-bottom: 0;"><a href="https://atcoder.jp/contests/arc056/tasks/arc056_d" data-iframely-url="//cdn.iframe.ly/O2puFJ0"></a></div></div><script async src="//cdn.iframe.ly/embed.js" charset="utf-8"></script>

## 状況

解けないだけではなく，答を見てもなかなかわからなかったので，整理するために書いています．下記を参考にしています．

* [公式解説](https://img.atcoder.jp/data/arc/056/editorial.pdf)
* [kmjpさんのブログ](https://kmjp.hatenablog.jp/entry/2016/06/26/0930)

## 解法

時刻 $2j+1$ にドリンクを飲むような飲み方全部に関する，時刻 $2j+1$ 時点での美味しさの総和の最大値を $x(j)$ とする． 時刻 $2i$ に全部のグラスが空だったとき，半開区間 $(2i, 2j]$ に属する時刻に注がれるドリンクの美味しさの総和を $y(i, j)$ とすると， $x(j) = \max \\{ x(i) + y(i, j) \mid i < j \\} $ である．ここで，$z(i, j) = x(i) + y(i, j)$ と書くことにする．時刻 $j$ に注がれるドリンク全体の集合を $P$ とし，$ p \in P $ に対して時刻 $2j$ の一回前にドリンク $p$ が注がれる時刻を $l_p$ とする (時刻 j が初回なら，$l_p = 0$ とする)．すると，次が成り立つ．

* $x(j) = z(j,j) = \max \\{ z(i,j) \mid i < j \\}$
* $z(i,j) - z(i, j-1) = \sum \\{ w_p \mid p \in P,\; i \in [l_p, j) \\}$

したがって，ベクトル $ v_j = ( z(i,j) \mid i < j ) $ を $j$ に関して遅延伝搬セグメント木 (区間和，区間最大値) で更新していくことができ，$O(M \log M)$ (ここに $M = \sum \\{ M_i \mid i \leq N \\}$ )で計算できる．答は最終時刻 $T$ に対する $x(T) = z(T, T)$ である．

## その他

似たような問題を見たことがあるような気がして探してみると，EDPC の [W. Intervals](https://atcoder.jp/contests/dp/tasks/dp_w) とほぼ同じでした．こちらの方が古いですが．何度やっても解けません．

