---
author: "yamate11"
title: "全方位木ライブラリ"
date: "2024-02-14T00:00:00+09:00"
date_init: "2022-08-17T16:39:04+09:00"
# date_init: "2022-08-17"
tags: ["全方位木"]
categories: ["topic"]
# categories: ["solution"]
summary: "全方位木ライブラリ使用法のメモ"
---

## 実装

[tree.cc](https://github.com/yamate11/compprog/blob/main/clib/tree.cc) の関数 `reroot()`

## このライブラリで解ける問題

木の各ノード $x$ に対して，子供から再帰的に値を計算する状況を考える．

* 子供の値をまとめる演算は，可換モノイド $\mathcal{M} = (M, \oplus, e)$ の演算であるとする．
* 子供 $c$ から渡された値 $v_c \in A$ を適宜変換して，$w_c = f(v_c, c, x) \in M$ とした上で，
  モノイド演算を施して 値 $ w = \bigoplus_c w_c  \in M$ を得て，さらにそれを適宜変換した
  $g(w, x)$ がこのノードの値 $v_x \in A$ になる，という設定とする:
  $$ v_x = g\left(\bigoplus_c f(v_c, c, x), x\right) $$

$g$ は単に $w$ を返すことも多い．

ここで問題となるのは，$x$ での値 $v_x$ を計算するには，$x$ を木全体の根と考える必要があるということだ．
愚直に行うと $\Omega(|T|^2)$ かかってしまう．そこで，次のように計算を進める:

* まず，一つのノード $0$ を根として，DFS で，$v_0$ を計算する．この際，各ノード $x$ とその子 $d$ に対して，
  次の2つを保存しておく．
  * $l_{x, d} := \bigoplus\\{f(v_c, c, x) \mid c$ は，$x$ の子のうち，$d$ よりも左にあるもの $\\}$ 
  * $r_{x, d} := \bigoplus\\{f(v_c, c, x) \mid c$ は，$x$ の子のうち，$d$ よりも右にあるもの $\\}$ 
* 次に，$0$ から DFS で降りていきながら各 $v_x$ を計算する．
  DFSがノード $x$ に来たとき，$x$ の子の $d$ について $v_d$ を計算する．
  * $d$ を根と思ったときに，$x$ は $d$ の子になるわけだが，こう思ったときの $x$ の値は，
  $g(l_{x, d} \oplus r_{x, d}, x)$ である．これを，$d$ に渡す．
  * 渡された $d$ は，その値と，残り全部の子の値から，$v_d$ を計算することができる．

## 使用法

関数 `reroot` が用意されている．

```cpp
template <typename M, typename A>
vector<A> reroot(Tree& tree, const M& unit, auto add, auto mod1, auto mod2)
```

* template parameter の `M` はモノイド，`A` は計算する値
* 以下の引数を与えて呼び出すと，各ノードにおける値 $v_x$ を，ベクトルに格納して返す．
  * `tree` は，このファイルで定義されている木を表す構造体 `Tree` (以下では $T$ と書く) のオブジェクト
  * `unit` は，モノイド演算の単位元
  * `add` は，モノイド演算 $\oplus: M \times M \to M$
  * `mod1` は，上の関数 $f: A \times T \times T \to M$
  * `mod2` は，上の関数 $g: M \times T \to A$

なお，$M = A$ で $g(m, x) = m$ のときには，次を使っても良い．

```cpp
template <typename M>
vector<M> reroot(Tree& tree, const M& unit, auto add, auto mod1)
```

## 例題 [ABC222F - Expensive Expense](https://atcoder.jp/contests/abc222/tasks/abc222_f)

* TBW
* これはシンプル


## 例題 [ABC160F - Distributing Integers](https://atcoder.jp/contests/abc160/tasks/abc160_f)

> 木が与えられる．各頂点 $k$ につき，次の問題を解け
> * 頂点 $k$ に 1 を書き，残りの頂点には，既に書き込まれた頂点に
>   隣接する頂点に 2, 3, ... の数を書く．
>   このように書ける方法の数を$\mod 10^9 + 7$ で求めよ．

全方位木を使うには，

* 頂点を1つ固定した問題が，木DPで解けて，
* その木DPの際に，各ノードの処理がモノイド演算でできること

が必要．ということで，まず，$k$ を固定した問題を 木DPで解く方法を考える．

* 1 は根に書くと決まっている．
* 根の子供が，たとえば $c_1, c_2, c_3$ の3つだとして，それぞれを頂点とする部分木のサイズを
  $m_1, m_2, m_3$ とする．
* 2 ～ N を，この3つに割り振る方法を決める．すると，各部分木 $c$ で，割り振られた数を書く問題に
  なるが，それは，1 ～ $m_c$ を書く問題の答と一致する．

具体的には，上の場合，求める数を $h$ とすると，

$$h(k) = \binom{m_1 + m_2 + m_3}{m_1}h(c_1)\binom{m_2 + m_3}{m_2}h(c_2)\binom{m_3}{m_3}h(c_3)
  = (m_1 + m_2 + m_3)!\frac{h(c_1)}{m_1!}\frac{h(c_2)}{m_2!}\frac{h(c_3)}{m_3!}$$

となる．$k$ 以外の一般のノード $n$ も同じように考えて，

$$h(n) = \left(\sum m_c\right)!\prod\frac{h(c)}{m_c!}$$

ということであるから，次のように考えれば良い:

* 各ノードの値 $v_x \in A ( = F_p \times Z) $ は，$(h(x), m_x)$ とする．$m_x$ は，$x$ をトップとする部分木のサイズ
  * $m_x$ は，最初に読んだときの tree 構造体の stsize を使ってはいけない．「部分木」というのは，
    reroot しながら，現在の根に対して定義されるものだから．
* モノイドは，$F_p \times Z$．たまたま型は $A$ と同じだが，意味が違って，左は $h(c) / m_c!$ を表す．
  右は $A$ と同じで $m_c$．  
  演算は，左成分は積，右成分は和をとる．
* 関数 $f : A \times T \times T \to M$ は，$f((w, m), n, c) := (w / m!, m)$
* 関数 $g : M \times T \to A$ は，$g((w, m), n) := (m! w, m + 1)$．自分のノードが部分木サイズに加わるので，
  ここで $m$ から $m + 1$ に変わる．



## 例題 [EDPC V Subtree](https://atcoder.jp/contests/dp/tasks/dp_v)

> 木と正整数 $M$ が与えられる．
> 全頂点を白黒に塗り分けるに塗り分け，任意の2つの異なる黒頂点a,bに関して，
> a から b へのパスが全部黒で塗られているようにする．
> 各頂点$v$について，上を満たして $v$ が黒く塗られる塗り方の数を
> $\mod M$ で求めよ．

<img src="fig01.jpg" width="80%">

ここでは，白く塗られる塗り方の数も問われているものだと仮定して，
解を考える．

3つの条件を考える．
* B(n): n は黒く塗られ，n の子孫は条件を満たす．
* W(n): n は白く塗られ，n の子孫は条件を満たす．
* A(n): n および n の子孫はすべて白く塗られている．

ノードの集合Xについて，次のように定める．
* P(X): 全ての $c \in X$ について B(c) または A(c)
* Q(X): 全ての $c \in X$ について B(c) または W(c) であり，
  たかだか1つを除いて A(c) である．

これらは，n が塗れるかどうかの条件に関係する．
具体的には，C(n) を，n の子供の集合として，次が成り立つ．

* n が黒く塗れるための条件は，P(C(n))．
* n が白く塗れるための条件は，Q(C(n))．

$P(X)$, 
$Q(X)$, 
$P(\\{c\\})$, 
$Q(\\{c\\})$
を満たす塗り方の数を
$\alpha_1, \beta_1, \alpha_2, \beta_2$ とするとき，
$P(X \cup \\{c\\})$, 
$Q(X \cup \\{c\\})$,
を満たす塗り方の数は
$(\alpha_1\alpha_2, \beta_1 + \beta_2 - 1)$ である．
そこで，

* $(\alpha_1, \beta_1) \oplus (\alpha_2, \beta_2)
 := (\alpha_1\alpha_2, \beta_1 + \beta_2 - 1)$

で，モノイド演算を定義する．単位元は $(1, 1)$ である．

また，$c$ を黒，白で塗る方法の数を
$\alpha$, $\beta$ とするとき，
$P(\\{c\\})$, $Q(\\{c\\})$ を満たす塗り方の数は，
$\alpha + 1$, $\alpha + \beta$ である．そこで，

* $g((\alpha, \beta), n, c)) = (\alpha + 1, \alpha + \beta)$

で，$g$ を定義する．

