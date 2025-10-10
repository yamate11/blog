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

### 1.3 計算量

* 前計算 $O(N \log R)$
* 各回の値の計算 $O(\log R)$

## 2. 使用法

### 2.1 基本用法だけの時

* `DoublingFRel` オブジェクト `dobj` を作る．
  ```cpp
    Doubling dobj(R, N, vecF);
  ```
  * 関数 $f$ の値を，`vector<ll>` などの型を持つ `vecF` に用意しておく．長さは $N$．
* 値 $f^r(i)$ は，`dobj.val(r, i)` で取得できる．
  ```cpp
    cout << dobj.val(r, i) << endl;
  ```
  * 有効な範囲は，$0 \leq r \leq R$，$0 \leq i < N$．
  * なお，$r = 2^k$ に対する $f^r(i)$ が，内部テーブル `dobj.tbl[k][i]` に格納されている．


### 2.2 追加用法も行う時

* モノイド演算が，型 `T` の 加法 (`operator +`) であるときは，
  `make_doubling_with_monoid<T>` を使って，`dobj` を作る．
  ```cpp
    auto dobj = make_doubling_with_monoid<T>(R, N, vecF, vecM);
  ```
  * `R`, `N`, `vecF` は，上と同じ．
  * 関数 $m$ の値を，`vector<T>` などの型を持つ `vecM` に格納しておく．長さは $N$．
  * `<T>` は省略できない．

* モノイド演算が `T` の加法でないときには，`make_doubling_with_monoid_unit_add` を使って `dobj` を作る．
  ```cpp
    auto dobj = make_doubling_with_monoid_unit_add(R, N, vecF, vecM, unit, add);
  ```
  * 単位元 `unit` は `T` 型．`T` はこの引数から推論される．
  * 加法 `add` は `T` を 2 つ引数にとって呼べて `T` を返すもの．

* これらの場合，`dobj.val(r, i)` は，`pair<int, T>` で $(f^r(i), \bigoplus_{k = 0}^{r - 1} m(f^{k}(i)))$
  を返す．
  ```cpp
    auto [j, c] = dobj.val(r, i);
    cout << "f^r(i) is " << j << " and total cost is " << c << endl;
  ```
  * 内部テーブル `dobj.tbl` の型も `vector<vector<pair<int, T>>>` になる．

## 3. 実装上の注意

* 以前は，内部テーブルを f 用の `vector<vector<int>>` と モノイド用の `vector<vector<T>>` の2つを
  持っていた．性能バグだった．


keywords: doubling


