---
author: "yamate11"
title: "Dilworthの定理, Konigの定理"
date: "2024-05-202T15:31:00+09:00"
# date_init: "2022-02-02"
tags: ["Dilworth", "Konig"]
categories: ["topic"]
# categories: ["solution"]
summary: "ABC237 Ex Hakata を解くのに必要だった Dilworth の定理他に関する記事です．"
---

## 趣旨

[AtCoder Beginner Contest 237 (ABC237) Ex Hakata](https://atcoder.jp/contests/abc237/tasks/abc237_h) の
[公式解説](https://atcoder.jp/contests/abc237/editorial/3321) に，
Dilworth の定理を使って解ける，と書いてあるのですが，
それを読んだだけでは (当然?) わからなかったので，
(自分が) わかるように書こうという趣旨です．

結局，この問題を解くには，次の事実が必要であると思います
(言葉は下の方で定義しています)．

#### 命題1

> 順序集合 $(S, <)$ の反鎖のサイズの最大値は，$|S| - m$ である．
> ここで $m$ は，$S$を左右に置いて，$s < t$ の時に
> 左の$s$と右の$t$ を辺で結んだ二部グラフ
> における最大マッチングのサイズである．

Dilworth の定理だけではなく，K&ouml;nig の定理も知っていると良い感じです．

以下の記述 (定理の証明) は，Wikipedia の
<a href="https://en.wikipedia.org/wiki/Dilworth%27s_theorem">Dilworth's theorem</a> と
<a href="https://en.wikipedia.org/wiki/K%C5%91nig%27s_theorem_(graph_theory)">Konig's theorem</a>
に依っています．

## 定義・記法

以下，順序とは，半順序のこと．
順序集合 $\mathcal{S} = (S, <)$ において，$C \subseteq S$ が鎖であるとは，
$C$の任意の2要素が比較可能であること．
$A \subseteq S$ が反鎖であるとは，
$A$の任意の2要素が比較不能であること．
$D \subseteq 2^S$が鎖分割であるとは，$D$が$S$の分割であり
(つまり，$C, C' \in D, C \neq C' \implies C\cap C' = \emptyset$
で，$\bigcup D = S$)，$D$の要素がすべて鎖であること．


2部グラフ $(L, R, E)$ 
($L$と$R$が頂点の集合，$E\subseteq L\times R$ が辺の集合) において，
$e = (l, r) \in E$ に対して，$l$, $r$ をそれぞれ $e_L$, $e_R$ と書く．
$M \subseteq E$ がマッチングであるとは，以下が成り立つこと:

* $e, e' \in M, e \neq e' \implies e_L \neq e'_L, e_R \neq e'_R$

$C \subseteq L \cup R$ が頂点被覆であるとは，
任意の$e\in E$ に対して $e_L \in C$ または $e_R \in C$ となること．

## 自明な事実

#### 補題

> 順序集合において，
> $A$ が反鎖，$D$ が鎖分割ならば，$|A| \leq |D|$．

#### 証明

$D$ の要素である鎖には，$A$ の要素はたかだか1つしか入れない．(終)

#### 補題

> 2部グラフにおいて，
> $M$ がマッチング，$C$ が頂点被覆ならば，$|M| \leq |C|$．

#### 証明

$e \in M$ に対し，$e_L \in C$ または $e_R \in C$ の成り立つ方を
対応させる写像 $M \to C$ は単射である． (終)

## 定理たち

#### Dilworth の定理

> 順序集合において，
> $|A| = |D|$ となる反鎖$A$と鎖分割$D$が存在する．
> 上の補題と合わせて，このサイズが反鎖の最大サイズ，鎖分割の最小サイズである．

#### K&ouml;nig の定理

> 2部グラフにおいて，
> $|M| = |C|$ となるマッチング$M$と頂点被覆$C$が存在する．
> 上の補題と合わせて，このサイズが，マッチングの最大サイズ，頂点被覆の最小サイズである．

## 相互証明

Dilworth の定理と K&ouml;nig の定理の片方を仮定すると，
他方を証明することができる．

#### K&ouml;nig → Dilworth

順序集合 $(S, <)$ が与えられたとする．
左右に$S$を置いて，右が大きい組合せを辺でつないだ二部グラフ，つまり，
$(S\times \\{0\\}, S\times\\{1\\}, \\{((s, 0), (t, 1)) \mid s < t\\})$
を考える．
最大マッチング$M$と最小頂点被覆$C$を取る．K&ouml;nig の定理より，
$m = |M| = |C|$ として良い．

$A$ を，$C$ に現れない頂点の集合とする．つまり，
$A = \\{ s \in S \mid (s, 0) \not\in C, (s, 1) \not\in C\\}$．
すると，$A$は反鎖であり，$|S| - |C| \leq |A|$ である．

$S$ に，$M$ によって導かれる有向グラフ
$(S, \\{(s, t) \mid ((s, 0), (t, 1)) \in M\\})$ を考える．
$M$がマッチングなので，このグラフの頂点の入次数，出次数はたかだか1である．
また，$(S, <)$ は順序集合だから，グラフにループは存在しない．
したがって，入次数0の頂点から始めて，辺をたどれるだけたどって得られる
集合の全体を $D$ とすると，$D$ は，$S$ の鎖分割になり，$|D| = |S| - |M|$
である．

以上まとめて，$|D| = |S| - m \leq |A| \leq |D|$ となるから，
$|A| = |D| = |S| - m$ が得られた．(終)

#### Dilworth → K&ouml;nig

(この部分は，ABC237Ex には直接必要ではない)

2部グラフ $(L, R, E)$ が与えられたとする．$S = L \cup R$ として，
順序集合 $(S, E)$ を考える．
最大反鎖$A$と最小鎖分割$D$をとる．
Dilworth の定理より，$|A| = |D|$ である．
$D$ の要素は，単元集合であるか，辺を構成する2点であるかのいずれかである．
前者の集合を $D_1$, 後者の集合を $D_2$ とする．

$D$は鎖分割であるから，$M = D_2$はマッチングとなる．
$C = S \setminus A$ とすると，$A$は反鎖であるから，$C$は頂点被覆である．
$|M| = |C|$ となることを見るために，次を示す:

* $\bigcup D_1 \subseteq A$ 
* $e\in D_2$ に対し，$e_L \in A$ と $e_R \in A$ のうちちょうど一方が成り立つ

$p = |\bigcup D_1 \setminus A|$ とする．
$D_2$ の要素 $e$ については，$e$ は 鎖なので，
$e_L \in A$ と $e_R \in A$ の両方は成り立たないが，両方とも成り立たない
ものの数を $q$ とする．すると，
$|D| = |A| \leq (|D_1| - p) + (|D_2| - q) = |D| - (p + q) \leq |D|$
であるから，$p = q = 0$ でなければならない．

したがって，$|A| = |D_1| + |D_2|$ であり，$|S| = |D_1| + 2 |D_2|$ 
とあわせて，$|C| = |S| - |A| = |D_2| = |M|$ が得られた．(終)

## K&ouml;nig の定理の証明 (flow版)

2部グラフを $(L, R, E)$ とする．最大マッチング $M$ をとり，$|M| = m$ とする．
サイズ $m$ の頂点被覆を作ればよい．

2点 $s, t$ を追加して，次のような，辺に容量のある有向グラフ$(G, Q)$ を考える:

* $G = L \cup R \cup \\{s, t\\}$
* $(x, y) \in Q$ が成り立つのは次のいずれか
  * $x = s,\\; y \in L$．このとき，辺の容量は $1$．
  * $x \in R,\\; y = t$．このとき，辺の容量は $1$．
  * $x \in L,\\; y \in R,\\; (x, y) \in E$．このとき，辺の容量は $\infty$．  

最大マッチングのサイズが $m$ なので，この有向グラフの $s$ から $t$ への最大流は $m$ である．
これに対応する最小カット $K = (S, T)$ をとる．ただし，$s \in S$，$t \in T$ とする．
$U = T \cap L,\\;V = S \cap R,\\;Z = \\{(x, y) \in Q \mid x \in S,\\; y \in T\\}$ とする．
$(x, y) \in Z$ をとると，$(x, y) \in Q$ であるから，上の 3 つの条件のいずれかがなりたつのだが，
$K$ の容量は有限であるから，一番下の条件は該当しない．つまり，$x = s,\\; y \in U$ であるか
$x \in V,\\;y = t$ かのいずれかである．
$K$ の容量が $m$ であるので，$ | U \cup V | = m$ であることになる．

あとは，$U \cup V$ が頂点被覆になることを言えば良い．
そうでないとして，$x \in L \setminus U,\\; y \in R \setminus V,\\; (x, y) \in E$ なる
$(x, y)$ が存在したとすると，$x \in S$，$t \in T$ ということであるから，
カット容量が $\infty$ になってしまい，矛盾する．
(終)




## K&ouml;nig の定理の証明 (flow でない版)

二部グラフ$(L, R, E)$ の最大マッチング$M$をとる．
$M_L := \\{ e_L \mid e \in M \\}$，
$M_R := \\{ e_R \mid e \in M \\}$，
$m := |M|$ とする．以下のように定義する．

* $L_0 := L \setminus M_L$
* $F_i := \\{ e \in E \setminus M \mid e_L \in L_0 \\}$
* $R_i := \\{ e_R \mid e \in F_i \\}$
* $G_i := \\{ e \in M \mid e_R \in R_i \\}$
* $L_{i + 1} := \\{ e_L \mid e \in G_i \\}$
* $C := (L \setminus \bigcup_i L_i) \cup \bigcup_i R_i$

##### 主張1: C は頂点被覆である．

$e \in E$ を取り，$e_L \not\in C$ を
仮定し，$e_R \in C$ を言えば良い．仮定より $e_L \in L_i$
となる $i$ がとれる．

* $e \in E \setminus M$ のときには，$e_R \in R_i \subseteq C$ である．
* $e \in M$ のときには，定義より $i \neq 0$ である．したがって，
  $e' \in G_{i-1}$ なる $e'$ がとれて，$e_L = e'_L$ である．
  $e, e' \in M$ で $M$ はマッチングであるから，
  $e = e'$ となり，$e_R = e'_R \in R_{i-1} \subseteq C$
  である．

##### 主張2: $C \subseteq M_L \cup M_R$

$s \in C \cap L$ については，
$C \cap L = L \setminus \bigcup_i L_i \subseteq L \setminus L_i = M_L$
から従う．
$s \in C\cap R = \bigcup_i R_i$ について．$s \not\in M_R$ であると仮定する．
$s \in R_i$ とすると，$l_0, r_0, l_1, \ldots, r_i = s$ なる$S$の
列が取れて，$(l_j, r_j) \in E \setminus M$, $(l_{j + 1}, r_j) \in M$ となる．
ここで，$M' \subseteq E$ を，
$M' = M \setminus \\{(l_{j + 1}, r_j) \mid j = 0, \ldots i-1\\}
\cup \\{(l_j, r_j) \mid j = 0, \ldots, i\\}$ で定義すると，
$M'$ はマッチングとなり，$|M'| = |M| + 1$ であるから，$M$ が最大マッチング
であることに反する．したがって，$s \in M_R$ でなければならない．

##### 主張3: $e \in M$ ならば，$e_L \not\in C$ または $e_R \not\in C$

$e\in M$ かつ $e_R \in C$ とする．$e_R \in R_i$ となる $i$ がとれる．
すると，$e \in G_i$ であり，したがって，$e_L \in L_{i+1}$ である．
ゆえに，$e_L \not\in C$.

主張2,3より，$C \to M$ への単射が構成できるので，$|C| \leq |M|$．
従って補題より $|C| = |M|$ である．主張1と合わせて定理が証明された．(終)


## 命題1の証明

K&ouml;nig の定理 (いま証明した) を前提とすれば，
上記 K&ouml;nig → Dilworth の証明から明らか．(終)




















