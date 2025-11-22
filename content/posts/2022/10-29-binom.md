---
author: "yamate11"
title: "二項係数に関する公式"
date: "2025-11-22"
date_init: "2022-10-29"
tags: []
categories: ["topic"]
summary: "二項係数に関する公式です．"
---


\begin{eqnarray}
& \sum_{r=0}^{n}\binom{n}{r}a^r b^{n-r} = (a + b)^n
\\\\
& \sum_{r=0}^{n}\binom{n}{r} = 2^n
\\\\
& r\binom{n}{r} = n\binom{n-1}{r-1}
\\\\
& \binom{n}{r} + \binom{n}{r + 1} = \binom{n+1}{r + 1}
\\\\
& \sum_{i=r}^{n}\binom{i}{r} = \binom{n+1}{r+1}
\\\\
& \sum_{i=0}^{c}\binom{a}{i}\binom{b}{c-i} = \binom{a+b}{c}
\\\\
& \sum_{i=0}^{\infty}\binom{a}{i}\binom{b}{i} = \binom{a+b}{a}
\\\\
& \sum_{i=0}^{\infty}\binom{a}{i + c}\binom{b}{i} = \binom{a+b}{a - c}
\\\\
\end{eqnarray}

### 注

* (1) 二項定理
* (2) 上で $a = b = 1$
* (3) 定義に従って展開
* (4) パスカルの三角形の作り方
* (5) Hockey Stick Identity
* (6) a + b から c をとるとき，a から i とったとすれば，残りは b からとっている．
* (7) (6) で c := b とする．
  もしくは，a + b から a 個をマークし，a の方からはマークしていないものを，b の方からはマークしているものを選ぶ．
* (8) (7)から始めて(4)を繰返し使う．もしくは，a + b から a - c 個をマークして，(7)と同様にする．