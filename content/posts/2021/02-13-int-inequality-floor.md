---
author: "yamate11"
title: "整数・実数の大小比較とfloor, ceil"
date: "2023-03-23T18:36:00+09:00"
date_init: "2021-02-13"
tags: []
categories: ["topic"]
draft: false
---
## 経緯

よく考えればもちろん作れるのだけれど，すぐ間違うのでメモをしておきます．

## 公式

$d \in \mathbb{Z}$，$t \in \mathbb{R}$ とする．

* $d \leq t \iff d \leq \lfloor t \rfloor$
* $d < t \iff d < \lceil t \rceil$
* $t \leq d \iff \lceil t \rceil \leq d$
* $t < d \iff \lfloor t \rfloor < d$

## 考え方

\begin{eqnarray*}
d\leq t 
    &\iff& t \in \\{ t \mid d \leq t \\} \\\\
    &\iff& t \in \bigcup \\{ [e, e+1) \mid e = d, d+1, \ldots \\} \\\\
    &\iff& \bigvee \\{ t \in [e, e+1) \mid e = d, d+1, \ldots \\} \\\\
    &\iff& \bigvee \\{ \lfloor t \rfloor = e \mid e = d, d+1, \ldots \\} \\\\
    &\iff& d \leq \lfloor t \rfloor \hspace{20em}
\end{eqnarray*}

同様に，

\begin{eqnarray*}
d<t &\iff& t \in \\{ t \mid d < t \\} \\\\
    &\iff& \bigvee \\{ t \in (e-1, e] \mid e = d+1, d+2, \ldots \\} \\\\
    &\iff& \bigvee \\{ \lceil t \rceil = e \mid e = d+1, d+2, \ldots \\} \\\\
    &\iff& d < \lceil t \rceil \hspace{20em}
\end{eqnarray*}

\begin{eqnarray*}
t \leq d
    &\iff& \bigvee \\{ t \in (e-1, e] \mid e = d, d - 1, \ldots \\} \\\\
    &\iff& \bigvee \\{ \lceil t \rceil = e \mid e = d, d - 1, \ldots \\} \\\\
    &\iff& \lceil t \rceil \leq d \hspace{20em}
\end{eqnarray*}

\begin{eqnarray*}
t < d
    &\iff& \bigvee \\{ t \in [e, e+1) \mid e = d - 1, d - 2, \ldots \\} \\\\
    &\iff& \bigvee \\{ \lfloor t \rfloor = e \mid e = d - 1, d - 2, \ldots \\} \\\\
    &\iff& \lfloor t \rfloor < d \hspace{20em}
\end{eqnarray*}

## 追記

(追記: 2023/03/23)

これを使う場面として良くあるのが，正の整数 $a$, $b$, $c$ について
$ab \leq c$ などであるかどうかを判定したいが，
$ab$ が long long に収まらないかもしれない，
というとき．
$ab \leq c \iff a \leq c/b \iff a \leq \lfloor c/b \rfloor$
などとして，判定すれば良い．

なお，この目的のためには，GCC の拡張
__builtin_smulll_overflow も使える (Signed - MULtiplication - Long Long)．
形式は，

```cpp
bool __builtin_smulll_overflow(long long a, long long b, long long* res)
```

で，`a * b` が long long でオーバーフローする時は true が返る．
オーバーフローしない時には false が返り，`*res` に積が設定される．
たとえば上記の判定は:

```cpp
if (long long ab; not __builtin_smulll_overflow(a, b, &ab) and ab <= c) {
  ...
}
```

などと実現できる．





