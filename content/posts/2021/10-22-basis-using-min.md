---
author: "yamate11"
title: "XORに関する基底"
date: "2021-10-22T14:03:51+09:00"
# date_init: "2021-10-22"
tags: []
categories: ["topic"]
# categories: ["solution"]
summary: "Z を，XORを加算とする，体 F2 = {0,1} 上のベクトル空間と見たときに，x_1, .., x_n ∈ Z が張る部分空間の基底の求め方"
---

自然数の集合 $\mathbb{N}$ を，XORを加算とする，
体 $\textrm{F}_2 = \\{0,1\\}$ 上のベクトル空間と見たときに，
$x_1, .., x_n \in \mathbb{N}$ が張る部分空間の基底の求め方に関する記事です．
熨斗袋さんのツイートで紹介されていた方法です:

<blockquote class="twitter-tweet"><p lang="ja" dir="ltr">xor の掃き出しすごい簡単に出来るんですね<br><br>vector&lt;int&gt; basis;<br>for(int e : a){<br> for(int b : basis)<br> chmin(e, e ^ b);<br> if(e)<br> basis.push_back(e);<br>}<br><br>これで数列 a の基底が basis に入る</p>&mdash; 熨斗袋 (@noshi91) <a href="https://twitter.com/noshi91/status/1200702280128856064?ref_src=twsrc%5Etfw">November 30, 2019</a></blockquote> <script async src="https://platform.twitter.com/widgets.js" charset="utf-8"></script>


### 記法など

自然数の集合 $\\{0, 1, \ldots...\\}$ を $\mathbb{N}$ と書く．
自然数のビットごとのXOR演算を $\oplus$ と書く．
$\mathbb{N}$ を，
$\oplus$ を加算とする，体 $\textrm{F}_2 = \\{0, 1\\}$ 上の
ベクトル空間と見る．
$X \subseteq \mathbb{N}$ が張る空間を $S(X)$ と書く．
自然数$a, b$ に対して，閉区間，半開区間を $[a, b]$, $[a, b)$ などと書く．

$x \in N \setminus \\{0\\}$ に対して，
$2^t \leq x < 2^{t + 1}$ を満たす $t \in \mathbb{N}$ を
$\textrm{MSB}(x)$ と書く．
たとえば，
$\textrm{MSB}(1) = 0$, $\textrm{MSB}(5) = 2$ である．


### 命題

> $x_1, \ldots, x_n \in \mathbb{N}$ に対し，
> $y_1, \ldots, y_n \in \mathbb{N}$ を
> 次で定義する: 
> 
> * $z_{i, 1} := x_i$
> * $z_{i,j + 1} := \min(z_{i,j}, \\;\\; z_{i,j} \oplus y_j)$
> &nbsp;$\quad (j = 1, \ldots, i - 1)$
> * $y_i := z_{i,i}$
> 
> $W := \\{i \in [1, n] \mid y_i \neq 0\\}$ とするとき，
> $Y := \\{y_i \mid i \in W\\}$ および
> $X := \\{x_i \mid i \in W\\}$ は，
> $S(\\{x_1, \ldots, x_n\\})$ の基底である．
> 
> また，前者に関しては，$a \in \mathbb{N}$ に対して，
> $c_1, \ldots, c_n \in \\{0, 1\\}$ を以下のように定めると，
> $ a = \bigoplus_{i = 1}^{n} c_i y_i$ が成り立つ．
> 
> * $a_1 := a$
> * $a_{j + 1} := \min(a_j,\\; a_j \oplus y_j)$ &nbsp; 
>   ($j = 1, \ldots, n$)
> * $a_{j + 1} = a_j$ のとき，$c_j = 0$，
>   $a_{j + 1} < a_j$ のとき，$c_j = 1$．

### 証明

$y_i$ は，$x_i$ および $y_1, \ldots, y_{i-1}$ の一部の和であるから，
$x_i$ は，$y_1, \ldots, y_i$ の一部の和である．すなわち，
$\\{y_1, \ldots, y_n\\}$ は，$\\{x_1, \ldots, x_n\\}$ を生成する．
したがって，$Y$ は$\\{x_1, \ldots, x_n\\}$ を生成する．

次に，$i, j \in W$, $i > j$ として，$t = \text{MSB}(y_j)$ とすると，
$y_i$ の第$t$ビットは 0 である．
なぜなら，$z_{i, j}$ の第 $t$ ビットが 0 であっても 1 であっても，
最小値を作ることから，$z_{i, j+1}$ の第 $t$ ビットは 0 になる．
この後の $k >= j + 1$なる $z_{i, k}$においては，帰納法の仮定により，
$y_{k-1}$ の第 $t$ ビットは 0 であるから，$z_{i, k}$ の第 $t$ ビットは
0のまま変化しない．

このことから，$\\{y_i \mid i \in W\\}$ は線形独立である．
これらのいくつかの線形結合が 0 であるとし，
その最も若い番号を $j$ とすると，
第 $\text{MSB}(y_j)$ ビットを比較して，$y_j$ の係数が 0 であることがわかる．
以下同様である．

従って，$Y$は， $S(\\{x_1, \ldots, x_n\\})$ の基底となる．

また，$y_i = x_i \oplus c_1 y_1 \oplus \cdots \oplus c_{i-1} y_{i-1}$
($c_j \in \\{0, 1\\}$) と書けるから，
$x_i = c_1 y_1 \oplus \cdots \oplus c_{i-1} y_{i-1} \oplus y_i$
である．つまり，$X$ は，基底 $Y$ から「基本変形」を繰り返して得られる集合
であるので，$X$も基底になる．(終)



