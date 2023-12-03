---
author: "yamate11"
title: "セグメント木ライブラリ"
date: "2023-12-03T12:21:00+09:00"
# date_init: "2023-12-03"
tags: ['セグメント木']
categories: ["topic"]
# categories: ["solution"]
# summary: "要約を書いておく．ここには問題タイトル等は不要" 
---

自作セグメント木ライブラリの使い方についての自分用のメモです．

AtCoder Library にセグメント木はありますが，
それができる前から使っていたものなので...

## 使用法

値の型を `DAT`, 更新演算の型を `OP` とする．

### 基本のセグメント木

#### 作成

```cpp
  auto st = make_seg_tree(unit_dat, add, init_vec);
```

* unit_dat は，加法単位元
* add には，加法の演算を行う関数を指定する．
  関数ポインタ，クロージャ，関数オブジェクトが使える．
* init_vec は初期ベクトル

初期ベクトル設定は，分けても良い:

```cpp
  auto st = make_seg_tree(unit_dat, add);
  st.set_data(init_vec);
```

#### 値の設定

```
  st.update(i, x);
```

$i$ 番目の値として $x$ を設定する．
1点しか設定できないので，2引数であることに注意．


#### 値の取得

```
  DAT x = st.query(il, ir);
  DAT x = st[i];   // これは，st.query(i, i + 1) と同じ
```

$il$ 以上 $ir$ 未満の値に add を適用した結果を返す．

### 遅延セグメント木

#### 関数

3つの関数を指定する．

* add は加法． $\verb!DAT! \times \verb!DAT! \to \verb!DAT!$
* comp は更新演算の合成． $\verb!OP! \times \verb!OP! \to \verb!OP!$．
  comp(f, g) は，$f \circ g$ を表す．
* apply は更新演算の適用．$\verb!OP! \times \verb!DAT! \to \verb!DAT!$．

当然，apply と add の順序交換ができる必要がある．具体的には:

* $\text{apply}(f, \text{add}(x, y))
    = \text{add}(\text{apply}(f, x), \text{apply}(f, y))$

#### 作成

```cpp
  auto st = make_seg_tree_lazy(unit_dat, unit_op, add, comp, apply, init_vec);
```

分けても良い:

```cpp
  auto st = make_seg_tree_lazy(unit_dat, unit_op, add, comp, apply);
  st.set_data(init_vec);
```

#### 値の設定

```cpp
  st.update(il, ir, x);
```

#### 値の取得

```cpp
  DAT x = st.query(il, ir);
  DAT x = st[i];   // st.query(i, i + 1) と同じ．
```

## 設定例

#### 1点更新，区間和取得

```cpp
  auto st = make_seg_tree(0LL, plus<ll>());
```

#### 1点更新，区間最小値取得

```cpp
  auto st = make_seg_tree(LLONG_MAX, [](ll x, ll y) { return min(x, y); });
```

std::min は，オーバーロードがあるので，そのまま名前で渡すわけにはいかない．

#### 区間加算，区間最小値取得

```cpp
  auto mymin = [](ll x, ll y) -> ll { return min(x, y); };
  auto st = make_seg_tree_lazy(LLONG_MAX, 0LL, mymin, plus<ll>(), plus<ll>());
```

* apply と add は自然に順序交換ができる．
* オーバーフローしうる場合には， LLONG_MAX ではなく `(ll)(1e18)` などを用いる必要があるかもしれない．

#### 区間代入，区間最小値取得

代入する値は `optional<ll>` で表す．
nullptr が「何もしない」ことをあらわし，単位元となる．

```cpp
  using OP = optional<ll>;
  auto mymin = [](ll x, ll y) -> ll { return min(x, y); };
  auto comp = [](OP f, OP g) -> OP { return f ? f : g; };
  auto appl = [](OP f, ll x) -> ll { return f ? *f : x; };
  auto st = make_seg_tree_lazy(LLONG_MAX, OP(), mymin, comp, appl);
```

#### 区間代入，区間和取得

何も考えないと，add と apply の順序交換ができない．
そこで，
DAT として，long long の対をとり，
左に和を保持し，右には区間の長さを保持する．
右側は最初に設定したあとは変更されない．
加法演算としては，$\text{add}((v_1, l_1), (v_2, l_2)) = (v_1 + v_2, l_1 + l_2)$ を
用いる．
更新演算適用は，長さ $l$ の区間に一斉に $f$ を代入することになるので，
結果は $fl$ となる．ただし，$f$ が nullptr の時は，なにもしない．

```cpp
  using DAT = pair<ll, ll>;
  using OP = optional<ll>;
  auto add = [](DAT x, DAT y) -> DAT { return DAT(x.first + y.first, x.second + y.second); };
  auto comp = [](OP f, OP g) -> OP { return f ? f : g; };
  auto appl = [](OP f, DAT x) -> DAT { return f ? DAT(*f * x.second, x.second) : x; };
  auto dat_init = vector<DAT>();
  REP(i, 0, init_vec.size()) dat_init.emplace_back(init_vec[i], 1);
  auto st = make_seg_tree_lazy(DAT(), OP(), add, comp, appl, dat_init);
```


## 二分探索

チェック関数は次のように書く:

```cpp
  auto check = [&](DAT x) -> bool { ...; };
```

探索用に4つのメソッドが用意されている:

* 範囲が広いほど check が成立しやすいときに使うメソッド:
  * `st.binsearch_r_from(check, x)`
    * `check(st.query(x, y))` が成り立つ最小の y を返す．
    * そのような y が無いときには，init_vec.size() + 1 を返す．
  * `st.binsearch_l_from(check, y)`
    * `check(st.query(x, y))` が成り立つ最大の x を返す．
    * そのような x が無いときには，-1 を返す．
* 範囲が狭いほど check が成立しやすいときに使うメソッド:
  * `st.binsearch_r_until(check, x)`
    * `check(st.query(x, y))` が成り立つ最大の y を返す．
    * そのような y が無いときには，x - 1 を返す．
  * `st.binsearch_l_until(check, y)`
    * `check(st.query(x, y))` が成り立つ最小の x を返す．
    * そのような x が無いときには，y + 1 を返す．

## セグメント木の vector

引数無しのコンストラクタが用意してあるので，
正の長さを持つベクトルを宣言することもできる．
その時に型を指定する必要があるが，
`make_seg_tree` や `make_seg_tree_lazy` を使って一つインスタンスを
作った上で `decltype` を利用するのが現実的だと思う:

```cpp
  using sg1_t = decltype(make_seg_tree_lazy(0, 0, plus<int>(), plus<int>(), plus<int>()));
  vector<sg1_t> sg1(10);

  auto sg4 = make_seg_tree(LLONG_MIN, [](ll x, ll y) -> ll { return max(x, y); });
  using sg4_t = decltype(sg4);
  vector<sg4_t> vec4(2, sg4);
```

ベクトルの要素は同じ型を持たなければならないので，
異なる加法関数などを用いる場合には，クロージャではうまくいかず，
関数ポインタを用いる必要があるかもしれない．

## コードへのリンク

[GitHub へのリンク](https://github.com/yamate11/compprog/blob/main/clib/segTree.cc)


keywords: segtree segment tree
