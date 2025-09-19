---
author: "yamate11"
title: "方程式 ax \equiv b mod M の解"
date: "2025-09-19T10:08:49+09:00"
# date_init: "2025-09-19"
tags: []
categories: ["topic"]
# categories: ["solution"]
# summary: "要約を書いておく．ここには問題タイトル等は不要" 
---

## 概要

方程式 $ax \equiv b \pmod M$ の解は，次のように求められる．
$g := (a, M)$ として，

* $g \mid b$ でないとき: 解無し
* $g \mid b$ であるとき:
  $a = a'g$， $b = b'g$， $M = M'g$ として，eGCD で，$a's + M't = 1$， $0 \leq s < M'$ となる $s, t$ を求める．
  $b's \equiv x_0 \pmod{M'}$，$0 \leq x_0 <  M'$ となる $x_0$ をとると，
  解は，$x_0, x_0 + M', x_0 + 2M', \dots, x_0 + (g-1)M'$ の $g$ 個である．

## 証明

解があるとすると，$ax = b + kM$ と書けるから，$b = ax - kM$ は，$g$ の倍数．

後半．$x = x_0 + iM'$ とする．$a's + M't = 1$ から $a'b's + M'b't = b'$ なので，
$ax = ax_0 + iaM' = a'gb's + ia'gM' = g(b' - M'b't) + ia'gM' = b - Mb't + ia'M \equiv b \pmod M$


## 関連問題

[ABC423G](https://atcoder.jp/contests/abc423/tasks/abc423_g)
