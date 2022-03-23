---
author: "yamate11"
title: "ゼータ変換，メビウス変換，高速ゼータ変換, 高速メビウス変換"
date: "2022-03-22T19:59:40+09:00"
# date_init: "2022-03-22"
tags: ["ゼータ変換", "高速ゼータ変換"]
categories: ["topic"]
# categories: ["solution"]
summary: "高速ゼータ変換について，自分用にまとめた記事です．"
---

(高速)ゼータ変換，(高速)メビウス変換については，
良い記事がたくさんありますので，1つ足してもしょうがないのですが，
自分用にまとめました．

## ゼータ変換，メビウス変換

$F$ を有限集合とする．その冪集合を $\mathcal{P}(F)$ と書く．

$M$ を加群として，
関数 $f: \mathcal{P}(F) \to M$ に対して，そのゼータ変換
$\zeta(f): \mathcal{P}(F) \to M$ を，
$\zeta(f)(X) = \sum_{Y \subseteq X}f(Y)$
で定義する．あるいは，
$\zeta(f)(X) = \sum_{Y \supseteq X}f(Y)$
で定義することもある．
$f$ のメビウス変換を，上の2つのゼータ変換の定義に応じて，
$\mu(f)(X) = \sum_{Y \subseteq X}(-1)^{|X - Y|}f(Y)$
あるいは
$\mu(f)(X) = \sum\_{Y \supseteq X}(-1)\^{|Y - X|}f(Y)$
で定義する．

### 定理1

> $\zeta$ と $\mu$ は互いに他の逆変換である．

## 高速ゼータ変換，高速メビウス変換

$x \in \mathbb{N}$ に対して $\bar{x} := \\{0, 1, \ldots, x-1\\}$ と書く．
簡単のため $F = \bar{n}$ とする．

次のDPを用いて，ゼータ変換を高速に計算することができる．

定義が$\zeta(f)(X) = \sum_{Y \subseteq X}f(Y)$の場合，

* $\newcommand{\dp}{\text{dp}}
   \dp[i]\[X] := \sum \\{ f(Y) \mid Y \subseteq X \text{ and }
Y \cap (\bar{n} \setminus \bar{i}) = X \cap (\bar{n} \setminus \bar{i}) \\}$

要するに，$Y \in \mathcal{P}(F)$ であって，

* $i$以上のところでは $X$ と一致していて，
* $i$ 未満のところでは$X$の部分集合になっている

ようなものに対する $f(Y)$ の和，ということである．
すると，求める値は $\zeta(f)(X) = \dp[n]\[X]$ であり，遷移は次のようになる:

* $\dp[0]\[X] = f(X)$
* $\dp[i]\[X] =
\begin{cases}
\dp[i - 1]\[X] & \text{ if } i \not\in X \\\\
\dp[i - 1]\[X] + \dp[i - 1]\[X \setminus \\{i\\}] & \text{ if } i \in X \\\\
\end{cases}
$

定義が$\zeta(f)(X) = \sum_{Y \supseteq X}f(Y)$の場合も同様．
変えるところは，定義が

* $\newcommand{\dp}{\text{dp}}
   \dp[i]\[X] := \sum \\{ f(Y) \mid Y \supseteq X \text{ and }
Y \cap (\bar{n} \setminus \bar{i}) = X \cap (\bar{n} \setminus \bar{i}) \\}$

となることと，次の遷移．

* $\dp[i]\[X] =
\begin{cases}
\dp[i - 1]\[X] & \text{ if } i \in X \\\\
\dp[i - 1]\[X] + \dp[i - 1]\[X \cup \\{i\\}] & \text{ if } i \not\in X \\\\
\end{cases}
$

メビウス変換も式の形はほぼ同じだから，同じようなDPで計算できる．

* $\dp[i]\[X] =
\begin{cases}
\dp[i - 1]\[X] & \text{ if } i \not\in X \\\\
\dp[i - 1]\[X] + \dp[i - 1]\[X \setminus \\{i\\}] & \text{ if } i \in X \\\\
\end{cases}
$



## 今後の課題

定理1の証明を書く．

たぶん，約数に関する話もまとめなくてはいけないだろうが，
今はまとめるほど理解していない．

上の，冪集合として書いている話はlatticeにできるのだろうが，
そのとき「高速」パートがどうなるかわかっていない．


