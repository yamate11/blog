---
author: "yamate11"
title: "二項係数に関する公式"
date: "2024-06-21T18:42:07+09:00"
# date_init: "2024-06-21"
tags: []
categories: ["topic"]
# categories: ["solution"]
# summary: "要約を書いておく．ここには問題タイトル等は不要" 
---

1. 

$$
\binom{n}{r} = \binom{n - 1}{r - 1} + \binom{n - 1}{r}
$$

言わずもがな．パスカルの三角形

2. 

$$
\binom{n}{r} = \frac{n}{r} \binom{n - 1}{r - 1}
$$

定理から明らか．

3.

$$
\sum_{i = r}^{n} \binom{i}{r} = \binom{n + 1}{r + 1}
$$

Hockey-stick identity. 次のように1を繰り返し適用．
$\binom{n + 1}{r + 1} = \binom{n}{r} + \binom{n}{r + 1}
 = \binom{n}{r} + \binom{n - 1}{r} + \binom{n - 1}{r + 1}
 = \binom{n}{r} + \binom{n - 1}{r} + \binom{n - 2}{r} + \binom{n - 2}{r + 1}
 = \dots$

4.

$$
\binom{n + m}{r} = \sum_{i = 0}^{r}\binom{n}{i}\binom{m}{r - i}
$$

$n + m$ から $r$ 取る組合せは，$n$ から $i$ 取って，$m$ から $r - i$ とる組合せで $i$ を動かしたもの．

5.

$$
\sum_{r = 0}^{n} r \binom{n}{r} = n 2^{n - 1}
$$

左辺は，$\sum_{r = 1}^{n} r \binom{n}{r} = n \sum_{r = 1}^{n} \binom{n - 1}{r - 1} = n 2^{n - 1}$
と計算できる．