---
author: "yamate11"
title: "Cabbage Master - Atcoder Beginner Contest 215 H"
date: "2021-08-23T16:35:21+09:00"
# date_init: "2021-08-23"
tags: []
categories: ["solution"]
description: "Atcoder Beginner Contest 215 (ABC215) H Cabbage Master に関する記事です．公式解説そのままですけれど，予備知識を一応書きました．"

---


## 問題へのリンク

https://atcoder.jp/contests/abc215/tasks/abc215_h

## 経緯

コンテスト中は，そもそもHには到達もしませんでした．
コンテスト後に考えましたが，歯が立ちませんでした．

* Hall の定理は，見たことはあったけど，覚えていなかった
* 高速ゼータ変換や高速メビウス変換のライブラリは持っていたのですが，
  どう使うか知らなかった．
  
というわけなので，解けるはずがありませんでした．

## 問題概要

正の整数$N$, $M$; 各 $i\in [1, N]$ と 各 $j \in [1, M]$ に対して
正の整数 $A_i$, $B_j$, および $C_{ij} \in \\{0, 1\\}$ が与えられる．
ただし，任意の $j$ に対して $i$ が存在して
$C_{ij} = 1$ である．

$i\in [1, N]$ に対して $|D_i| = A_i$ となる互いに素な集合 $D_i$ を固定し，
$D = \bigcup \\{ D_i \mid i \in [1, N] \\}$ と書く．
$D$ の部分集合 $E$ と $i \in [1, N]$ に対して，$E_i := E \cap D_i$ とする．
$E$ に関する次の条件を考える．

* $E$ の $M$ 個の分割 $(F_1, \ldots, F_M)$ で，以下を満たすものは存在しない
    * $F_j \cap E_i \neq \emptyset \implies C_{ij} = 1$
    * 各 $i \in [1,N]$ に対して，
      $ \bigcup \\{ F_j \cap E_i \mid j \in [1,M] \\} \geq B_j $

条件を満たす $E$ のうち，$X = |D - E|$ の最小値を求めよ．
また，最小値を与える $E$ の個数を，mod 998244353 で求めよ．

制約: $N \leq 20$; $M \leq 10^4$; $A_i, B_j \leq 10^5$

## 予備知識

### Hall の定理

$A$, $B$ を有限集合，$G \subseteq A \times B$ とするとき，
以下の2条件は同値である．

* 単射 $f: A \to B$ で，$(a, f(a)) \in G$ であるものが存在する．
* 任意の $X \subseteq A$ に対して，$ |X| \leq |f\[X]|$．

ただし，$f[X] := \\{ b \in B \mid \exists a \in A. f(a) = b \\}$．

証明は，たとえば[高校数学の美しい物語](https://manabitimes.jp/math/904)
に載っています．

### ゼータ変換，メビウス変換

$A$ を有限集合とする．$A$の冪集合を
$ \mathcal{P}(A) $ と書く．

$ f : \mathcal{P}(A) \to M $ に対して，
$ \zeta_{U}(f) : \mathcal{P}(A) \to M $ と
$ \zeta_{L}(f) : \mathcal{P}(A) \to M $ を，
次で定義する．

* $ \zeta_{U}(f)(X) = \sum \\{ f(Y) \mid X \subseteq Y \\} $
* $ \zeta_{L}(f)(X) = \sum \\{ f(Y) \mid Y \subseteq X \\} $

作り方を考えると，$\zeta_{U}$, $\zeta_{L}$ には，逆変換が存在する．
これらを，$\mu_{U}$, $\mu_L$ と書く．

### 高速ゼータ変換，高速メビウス変換

以下のアルゴリズムによって，
$(f(X) \mid X \subseteq A)$ が与えられた時に
$\alpha = \zeta_U, \zeta_L, \mu_U, \mu_L$ に対し，
$(\alpha(f)(X) \mid X \subseteq A)$ を，$O(|A| \log|A|)$ で
計算できる．

* 配列 $P := [(X, f(X)) \mid X \subseteq A]$
* 各 $x \in A$ に対して以下によって $P$ を更新する．
    * 各 $X \subseteq A \setminus \\{x\\}$ に対して
         $Y := X \cup \\{x\\}$ とおいて，
         $(P\[X], P\[Y])
           := (P\[X] + u P\[Y], v P\[X] + P\[Y])$

ただし，$u$, $v$ は，以下の値を使う

* $\zeta_U$ ... $(u, v) = (1, 0)$
* $\zeta_L$ ... $(u, v) = (0, 1)$
* $\mu_U$ ... $(u, v) = (-1, 0)$
* $\mu_L$ ... $(u, v) = (0, -1)$


妥当性の説明は，「高速ゼータ変換」で検索すると，いろいろなところに出ています．

## 解法

[公式解説](https://atcoder.jp/contests/abc215/editorial/2505) そのままです．

次のように定める．

* $T_j := \\{ i \in [1, N] \mid C_{ij} = 1 \\}\qquad
  (j \in [1, M])$
* $f(S) := \sum \\{ A_i \mid i \in S \\} \qquad S \subseteq [1, N]$
* $g(S) := \sum \\{ B_j \mid T_j ⊆ S \\}\qquad S \subseteq [1, N]$

$f$ は，愚直に $O(N 2^N)$ で計算できる．
$g$ は，$\zeta_L$ を使って $O(NM + N 2^N)$ で計算できる．

Hall の定理を使うために，$j \in [1, M]$ に対して
$|H_j| = B_j$ なる互いに素な集合を用意して，
$H := \bigcup \\{H_j \mid j \in [1, M]\\}$ とする．
$G := \\{(d, h) \in E \times H \mid d \in E_i, h \in H_j,
          C_{i,j} = 1 \\}$
Hall の定理から，$E$ が上記の条件を満たすための必要十分条件は

* $f(E, S) < g(S)$ となる $S \subseteq [1, N]$ が存在する

ことである．ただし，

* $f(E, S) := \sum \\{ | E_i | \mid i \in S \\} \qquad S \subseteq [1, N]$

である．したがって，$f(S) > 0$ である 全部の $S \subseteq [1, N]$ に対する
$ f(S) - g(S) + 1 $ の最小値が，求める $X$ の値となる．
(ただし，0以下の時にはそもそも$A$が分割できないので，$X=0$)．

後半は，$X= 0$ なら個数は 1 なので，$X> 0$ とする．

* $F := \\{ S \subseteq [1, N] \mid f(S) - g(S) + 1 = X \\}$

とする．$S \subseteq [1, N]$ に対し，

*  $h(S)$ := $D$ から $X$ 個の要素を選ぶ方法のうち，選ばれた要素の添字の
             集合がちょうど $S$ となるものの数

とする．求める答は

*   $\sum \\{ h(S) \mid \exists S' \in F.\\; S \subseteq S' \\}$

である．$S \subseteq [1, N]$ が $\exists S' \in F.\\; S \subseteq S'$
を満たすかどうかは，
$F$ の特性関数を $\zeta_U$ で変換することで分かる．
また，$p := \zeta_L(h)$ とおくと，

* $p[S] = \bigcup \\{ D_i \mid i \in S \\}$ から X 個の要素を選ぶ方法の数
        = $\binom{f(S)}{X}$

である．したがって，$h$ は，$\mu_L(p)$ で求めることができる．

## ACコード

https://atcoder.jp/contests/abc215/submissions/25289505


