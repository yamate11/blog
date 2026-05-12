---
author: "yamate11"
title: "包除原理"
date: "2026-05-04T18:32:25+09:00"
# date_init: "2026-05-04"
tags: ["包除原理"]
categories: ["topic"]
# categories: ["solution"]
# summary: "要約を書いておく．ここには問題タイトル等は不要" 
---

何のページになるか良く分からないが，希望としては，包除原理を使う問題を集めたい?

$x \in \mathbb{N}$ に対して $\bar{x} := \\{0, 1, \ldots, x-1\\}$ と書く．


## 定理の言明

> $U$ は集合とする．各 $i = 0, \ldots, n-1$ に対して $A_i \subseteq U$ が定められている時，
  $$ \biggl|\bigcup_{i \in \overline{n}} A_i\biggr| =
     \sum \left\\{ (-1)^{|X| + 1} \biggl|\bigcap_{i \in X} A_i\biggr| \\;\middle|\\; X \in \mathcal{P}(\bar{n}) \setminus \\{ \emptyset \\} \right\\} $$

証明は，このブログの中だと [ここ](https://yamate11.github.io/blog/posts/2022/03-22-fast-zeta/) にある．

## 使う問題

### ABC456-G Count Holidays

[問題へのリンク](https://atcoder.jp/contests/abc456/tasks/abc456_g)

次の部分問題を包除原理で解いている:

正整数 $n$ と $k$ が与えられる．
集合 $\bar{n}$ の部分集合 $X$ について，$p(X)$ を，$X$ に含まれる区間の長さの最大値とする．
つまり，$i, i + 1, \dots, i + j - 1$ がすべて $X$ の要素になるような $i$ が存在するような $j$ の最大値である．
$p(X) \leq k$ であるような $X \subseteq \bar{n}$ の個数を，mod 998244353 で求めよ．
時間計算量 $O(n/k)$．ただし，必要な階乗などは前計算してあって $O(1)$ で得られるとする．

#### 解

$p(X) \geq k + 1$ なる $X$ の個数を数えて $2^n$ から引けば良い．

$A_i$ を，$\bar{n}$ の部分集合で$i$ から長さ$k + 1$ 以上の区間が始まるものの集合とする．つまり，
$A_i := \\{ X \subseteq \bar{n} \\;\bigl|\bigr.\\; [i, i + k + 1) \subseteq X$ かつ $i - 1 \not\in X\\}$
とする．
ただし，$i = 0$ のとき，$-1 \not\in X$ は自動的に成り立つと解釈する．

$p(X) \geq k + 1$ となることは，$X \in \bigcup_{i \in \bar{n}} A_i$ となることと同値だから，
包除原理によってその右辺を計算すればよい．
$m = 1, 2, \ldots$ について，$P_m := \\{ X \subseteq \bar{n} \mid |X| = m \\}$，
$f(m) := \sum \left\\{ |\bigcap_{i \in X} A_i| \\;|\\; X \in P_m \right\\}$
とすれば，包除原理の右辺は $\sum_{m = 1}^{n} (-1)^{m + 1} f(m)$ となる．
$X \in P_m$ に対して，$Q(X) := \bigcap_{i \in X} A_i$ は，
$X$ の点同士がすべて $k + 2$ 以上離れていなければ空集合になる．
したがって，$(k + 2)(m - 1) + 1 \leq n$ が必要で，$m$ はこの範囲を動かせば良い．
空集合でない場合には，$X$ の要素から $k + 1$ 個は $Q(X)$ 
$m - 1$ 個ないし $m$ 個



keywords: inclusion exclusion principle
