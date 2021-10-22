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

自然数の集合 $N$ を，XORを加算とする，
体 $\textrm{F}_2 = \\{0,1\\}$ 上のベクトル空間と見たときに，
$x_1, .., x_n \in Z$ が張る部分空間の基底の求め方に関する記事です．
熨斗袋さんのツイートで紹介されていた方法です:

<blockquote class="twitter-tweet"><p lang="ja" dir="ltr">xor の掃き出しすごい簡単に出来るんですね<br><br>vector&lt;int&gt; basis;<br>for(int e : a){<br> for(int b : basis)<br> chmin(e, e ^ b);<br> if(e)<br> basis.push_back(e);<br>}<br><br>これで数列 a の基底が basis に入る</p>&mdash; 熨斗袋 (@noshi91) <a href="https://twitter.com/noshi91/status/1200702280128856064?ref_src=twsrc%5Etfw">November 30, 2019</a></blockquote> <script async src="https://platform.twitter.com/widgets.js" charset="utf-8"></script>


### 記法など

自然数の集合 $\\{0, 1, \ldots...\\}$ を $N$ と書く．
以下では，$N$ を，
XOR を加算とする，体 $\textrm{F}_2 = \\{0, 1\\}$ 上の
ベクトル空間と見る．
$X \subseteq N$ が張る空間を $S(X)$ と書く．

$x \in N \setminus \\{0\\}$ の最上位ビットを $\textrm{MSB}(x)$ と書く．
たとえば，
$\textrm{MSB}(1) = 0$, $\textrm{MSB}(5) = 2$．
$2^{\textrm{MSB}(x)}$ を $r(x)$ と書く．


### 命題

> $x_1, \ldots, x_n \in N$ に対し，
> $y_1, \ldots, y_n \in N$ を
> 次で定義する: 
> 
> * $z_{i, 1} := x_i$
> * $z_{i,j} := \min(z_{i,{j-1}}, \text{XOR}(z_{i,{j-1}}, y_j))$
> &nbsp;($j = 2, \ldots, i$)
> * $y_i := z_{i,i}$
> 
> $W := \\{i \in [1, n] \mid y_i \neq 0\\}$ とするとき，
> $\\{y_i \mid i \in W\\}$ および $\\{x_i \mid i \in W\\}$ は，
> $S(\\{x_1, \ldots, x_n\\})$ の基底である．
> 
> また，前者に関しては，$a \in N$ のこの基底による表現 
> $ a = \textrm{XOR}\\{y_i \mid i \in U\\}$
> を，次のように計算することができる: 
> 
> * $a_1 := a$
> * $a_{j + 1} := \min(a_j, \textrm{XOR}(a_j, y_j))$ &nbsp; 
>   ($j = 1, \ldots, i - 1$)
> * $U := \\{ j \in W \mid a_{j + 1} = \textrm{XOR}(a_j, y_j)\\}$

### 証明

$i \in W$ に対して，
$M_i := \\{ \textrm{MSB}(y_j) \mid j \in [1, i) \cap W \\}$
とする．以下が帰納法で証明できる:

* $m \in M_i$ ならば，$\textrm{AND}(2^{\textrm{MSB}(m)}, y_i) = 0$．

従って，$\\{y_i \mid i \in W\\}$ は線形独立である．
また，$\\{y_i \mid i \in [1, j) \cap W\\}$ が，
$\\{x_1, x_2, \ldots, x_j\\}$ を生成することも帰納法で証明できる．

従って，
$\\{y_i \mid i \in W\\}$ は， $S(\\{x_1, \ldots, x_n\\})$ の基底である．

$y_i$ は，$\\{x_j \mid j in [1, i] \cap W\\}$ の線形結合で書けるので，
$\\{x_i \mid i \in W \\}$ は，$S(\\{x_1, \ldots, x_n\\})$ を生成する．
$x_i$ たちが線形独立でないと仮定すると，
$x_i = \textrm{XOR}(\\{x_j \mid j \in J\\})$ となる $i \in W$ と
$J \subseteq [1, i) \cap W$ がとれる．しかし，すると
$\textrm{XOR}(\\{x_j \mid j \in J\\}) = 
\textrm{XOR}(\\{y_j \mid j \in J'\\})$ となる $J' \subseteq [1, i) \cap W$
がとれる．$y_i$ の構成を考えると，$j \in J'$ のとき，
$z_{i,j} = x_i + \textrm{XOR}(\\{y_j \mid j \in J'\\})$, 
そうでないとき $z_{i,j} = z_{i, j-1}$ となり，したがって，$y_i = 0$ となり，
矛盾する．(終)

