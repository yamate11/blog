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

定義から明らか．

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
\sum_{i = 0}^{r}\binom{n}{i}\binom{m}{r - i} = \binom{n + m}{r}
$$

$|A| = n$, $|B| = m$ であるとき，$A$ と $B$ の排他和から $r$ 個取るのは，$A$ から $i$ 個取って $B$ から $r - i$ 個取ることになる．


5.
$$
\sum_{i = 0}^{r}\binom{n}{i}\binom{m}{r + i} = \binom{n + m}{n + r}
$$

上と類似．左辺は $\sum_{i = 0}^{r}\binom{n}{n - i}\binom{m}{i + r}$ と書き直せる．
$A$ と $B$ の排他和から $n + r$ 個取るときには，少なくとも $B$ から $r$ 個は取るので，$B$ から $i + r$ 個，$A$ から $n - i$ 個取ることになる．

6.

$$
\sum_{r = 0}^{n} r \binom{n}{r} = n 2^{n - 1}
$$

(左辺) $= \sum_{r = 1}^{n} r \binom{n}{r} = n \sum_{r = 1}^{n} \binom{n - 1}{r - 1} = n 2^{n - 1} =$ (右辺)

