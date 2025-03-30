---
author: "yamate11"
title: "積の和典型"
date: "2025-03-30T21:06:08+09:00"
# date_init: "2025-03-30"
tags: []
# categories: ["topic"]
# categories: ["solution"]
# summary: "要約を書いておく．ここには問題タイトル等は不要" 
---

[ABC399-F Range Power Sum](https://atcoder.jp/contests/abc399/tasks/abc399_f) が，
積の和典型だとのことなので，関連記事へのリンクなど．

### リンク

* [積の和典型 - ei1333の日記](https://ei1333.hateblo.jp/entry/2021/07/30/144201)

## ABC399-F

### 問題概要

[問題へのリンク](https://atcoder.jp/contests/abc399/tasks/abc399_f)

$A = (A_1, \dots, A_N)$ が与えられる．次を mod 998244353 で求めよ:

$$
\sum_{1 \leq l \leq r \leq N}\left( \sum_{l \leq i \leq r} A_i \right)^K
$$

制約: $N \leq 2\times 10^5$, $K \leq 10$．

### 解法

(累積和で2項展開しても解けるが，それは置いといて...) 以下，
[公式解説](https://atcoder.jp/contests/abc399/editorial/12565) より．

次のように言い換えられる．

* ボールが $A_i$ 個入った箱が一列に並んでいる．
* 箱の間に，2個の仕切りを入れる．
* 2つの仕切りの間にあるボールに，$1, 2, \ldots, K$ と書かれたラベルを1枚ずつ貼る

仕切りの入れ方とラベルの貼り方をセットで考えて，この方法の数が，求める答になる．
DP で求める．

dp[i][j][k] = (箱 i まで見て，仕切りを j 個入れていて，ラベルを k 枚貼るような方法の数)

