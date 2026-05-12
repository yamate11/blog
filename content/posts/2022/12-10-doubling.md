---
author: "yamate11"
title: "ダブリングライブラリ"
date: "2024-09-08T12:50:00+09:00"
date_init: "2022-12-10"
tags: ["ダブリング"]
categories: ["topic"]
# categories: ["solution"]
# summary: "要約を書いておく．ここには問題タイトル等は不要" 
---

ダブリングを行うライブラリを書きました．ソースは[こちら](https://github.com/yamate11/compprog-clib/blob/master/doubling.cc)．

## 1. できること

### 1.1 基本用法

$f : [0, N) \to [0, N)$ が与えられた時，
$r \in [0, R]$ と $i \in [0, N)$ に対して
$f^{r}(i)$ を
計算する．

### 1.2 追加用法

上の $f$ とともに，モノイド $(M, \oplus)$ と $m: [0, N) \to M$ も与えられて，
$r, i$ に対して
$\bigoplus_{k = 0}^{r - 1} m(f^{k}(i))$ も計算する．

典型例:
* $i \mapsto f(i)$ を1回実行するごとに $m(i)$ だけのコストがかかるとき，
  $f^r(i)$ の実行に要するコストを求める．
* $[0..N-1]$ が円環状に並んでいる．$f^r(i)$ の実行で何周するか求める．
  * この場合には，$m(i) := \textrm{ if } r(i) < i \textrm{ then } 1 \textrm{ else } 0$ とすればよい．
* tree の先祖-子孫パス上の辺の重みの最大値を求める

### 1.3 二分探索

$P$ を $M$上の単調な述語として，$i$ に対して
$P(\bigoplus_{k = 0}^{r - 1} m(f^{k}(i)))$ が成り立つ最大/最小の $r$ を求める．


### 1.4 計算量

* 前計算 $O(N \log R)$
* 各回の値の計算 $O(\log R)$
* 二分探索 $O(\log R)$

## 2. 使用法

`Doubling` オブジェクト `dobj` を作って使う．


### 2.1 基本用法だけの時


#### オブジェクトの作成

関数 make_doubling を用いて，オブジェクトを作成する．

```cpp
vector<int> vecF(N); ...  // vecF[i] が関数 f(i) の値になるようにする． vector<ll> でも可．
auto dobj = make_doubling(R, vecF);
```

R は，$f^r$ を計算する $r$ の最大値以上に取る．等しくとも良い．

オブジェクトを作成すると，内部テーブルの `dobj.f_tbl[k][i]` に，$f^{2^k}(i)$ の値が格納される．

#### 値の取得

メンバ関数 f_val を用いて，値が取得できる．

```cpp
  int x = dobj.f_val(r, i);  // f^r(i) の値
```

### 2.2 追加用法も行う時

#### オブジェクトの作成

関数 make_doubling に，マッピング $m$，モノイド単位元，モノイド演算も与える．

```cpp
vector<int> vecF(N); ...  // 同上
vector<T>   vecM(N); ...  // vecM[i] がマッピング m(i) の値になるようにする．
T unit = ...;             // モノイド単位元
auto prod = [](const T& a, const T& b) -> T { ... };  // モノイド演算
auto dobj = make_doubling(R, vecF, vecM, unit, prod);
```

よく使うケースとしては，`make_doubling(R, vecF, vecM, 0LL, plus<ll>())` など．

内部テーブルの `dobj.t_tbl[k][i]` に，$\bigoplus_{j = 0}^{2^k - 1} m(f^{j}(i))$ の値が格納される．

#### 値の取得

メンバ関数 val_pair で，$f^r(i)$ と $\bigoplus_{k = 0}^{r - 1} m(f^{k}(i))$ の値のペアが取得できる．
片方のみで良いときには，f_val, t_val も使える．

```cpp
  auto [idx, val] = dobj.val_pair(r, i);
  int idx2 = dobj.f_val(r, i);      // idx == idx2
  T val2 = dobj.t_val(r, i);        // val == val2
```

### 2.3. 二分探索

メンバ関数 binsearh_lo と binsearch_hi がある．
$P$ を $M$ 上の述語とする．
$P'(r, i) := P(\bigoplus_{k = 0}^{r - 1} m(f^{k}(i)))$ として，これが $r$ について単調であるとする．

* binsearch_lo:  述語 $P'$ が，r が小さい時に成り立つ場合，成り立つ最大の r を求める．
* binsearch_hi:  述語 $P'$ が，r が大きい時に成り立つ場合，成り立つ最大の r を求める．

```cpp
  auto check0 = [&](T t) -> bool { /* P0(t) が成り立つとき true を返す */ };        
  ...
  ll r0 = binsearch_lo(check0, i);  // P0'(r, i) が成り立つ最大の r
  ll r1 = binsearch_hi(check1, i);  // P1'(r, i) が成り立つ最小の r
```

述語を成り立たせる $r$ が存在しないときには，binsearch_lo は -1 を，binsearch_hi は R + 1 を返す．

どちらのメンバ関数も，省略可能な引数 lo (既定値 0) と hi (既定値は -1 だが，これは R を意味する) を持っていて，
指定するとその範囲で探索が行われる．単調性もその範囲で保証すれば良い．


keywords: doubling


