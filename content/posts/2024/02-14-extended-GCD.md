---
author: "yamate11"
title: "拡張ユークリッドアルゴリズム"
date: "2024-02-14T13:52:00+09:00"
# date_init: "2024-02-14"
tags: ["gcd"]
categories: ["topic"]
# categories: ["solution"]
# summary: "要約を書いておく．ここには問題タイトル等は不要" 
---

## 拡張ユークリッドアルゴリズムのメモ

(といっても，Wikipedia を参照するだけ)

### 参照先

[Wikipediaの記事](https://en.wikipedia.org/wiki/Extended_Euclidean_algorithm)

### ポイント

* 与えられた $a$, $b$ に対して，$g := \text{gcd}(a, b)$ と $sa + tb = g$ となる $s$，$t$ を求める．
  * $a$, $b$ は正，負，0 いずれも可．
  * ただし，$\text{gcd}(a, 0) = \text{gcd}(0, a) = a$
  * $|s| \leq \max(|a|, |b|)$，$|t| \leq \max(|a|, |b|)$ が成り立つ．
    $|a|$ や $|b|$ が 64 ビットで表せていれば，このアルゴリズムで得られる $|a|$，$|b|$ もそうなる．
    ($|sa|$ や $|tb|$ ははみ出すかもしれない)

### アルゴリズム概要

* `1 * a + 0 * b = a` と，`0 * a + 1 * b = b` から始める．
* $s_i a + t_i b = z_i$ と $s_{i + 1} a + t_{i + 1} b = z_{i + 1}$  まで得られたとする．
  *  右辺の割算 $z_i = p z_{i + 1} + q$ をする．
  *  ($i$ の式) $ - p \times (i + 1$ の式) を作って，
  $(s_i - p \\, s_{i + 1}) a + (t_i - p \\, t_{i + 1}) b = q$ を得る．
* 右辺が $g := \text{gcd}(a, b)$ になるまで繰り返す．
* なお，もう一回まわすと $s_{k + 1} a + t_{k + 1} b = 0$ になり，$|s_{k + 1}| = |a|/g$，$|t_{k + 1}| = |b|/g$ が成り立つ．

### コード

[util.cc](https://github.com/yamate11/compprog/blob/main/clib/util.cc) の，関数 eGCD()

