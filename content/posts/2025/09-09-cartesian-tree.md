---
author: "yamate11"
title: "Cartesian Tree"
date: "2025-09-09T14:49:47+09:00"
# date_init: "2025-09-09"
tags: []
categories: ["topic"]
# categories: ["solution"]
summary: "Cartesian Tree のライブラリ"
---

Cartesian Tree のライブラリを書いた．

## 使用法

```cpp
    vector<ll> vec{80, 90, 20, 50, 50, 40}
    CartesianTree ct(vec);
    // CartesianTree ct(vec, less<ll>()); ... same
    // CartesianTree ct(vec, [](ll a, ll b) { return a < b; }); ... same
    assert(ct.root == 2);     // vec[2] is the least element
    assert(ct.left[2] == 0);  // least in vec[0:2] is vec[0]
    assert(ct.left[0] == -1); // "no such element" is expressed by -1
    assert(ct.right[2] == 5);
    assert(ct.left[5] == 3 or ct.left[5] == 4);  // either of tied element can be chosen
```

## 定義

要素がすべて異なる列 $A = (a_1, \ldots, a_n)$ に対して，$A$ の Cartesian Tree $T$ は，
次のように構成される二分木である．

* $T$ のノードは，$1, 2, \dots, n$ である．
* 区間 $[a, b]$ に対する 部分木 $T'$ を，次のように定義する．
  * 空区間 に対する $T'$ は，空である．
  * $[a, b]$ における $A$ の最小値を $a_r$ とするとき，$T'$ の根は $a_r$ である．
  * $[a, r - 1]$ に対する木の根を $p$, $[r + 1, b]$ に対する木の根を $q$ とするとき，
    $r$ の左の子は $p$ であり, $r$ の右の子は $q$ である．
* 区間 $[1, n]$ に対する $T'$ を $T$ とする．
  
要素がかならずしもすべて異ならない列に対しても，値が等しい要素に適当に序列を付けて，
Cartesian Tree を考えることとする．

## コンストラクタ

普通は，ベクトルなどをコンストラクタの引数にする．

```cpp
vector<ll> vec{80, 90, 20, 50, 50, 40};        
CartesianTree ct0(vec);
```

引数のないコンストラクタもある．
その場合には，メンバ build() にベクトルなどを与える．
ベクトルなどの型をあらかじめテンプレート引数で与えておく必要がある．

```cpp
CartesianTree<vector<int>> cp;
cp.build(vector<int>{4, 1, 5});
```

「小さい」の定義は，コンストラクタで与えることができる．

```cpp
vector<ll> vec{80, 90, 20, 50, 50, 40};        
CartesianTree ct1(vec, greater<ll>());
CartesianTree ct2(vec, [](ll a, ll b) { return a > b; });
```

## メンバ

### 根

根は，メンバ root でアクセスする．

```cpp
cout << ct0.root << endl;  // 2
```

### 子

左の子と右の子は，vector 型のメンバ left と right に格納されている．

```cpp
cout << ct0.left[2]  << endl; // 0
cout << ct0.right[2] << endl; // 5
```

* 子供が無いときには，left や right には $-1$ が格納される．
* 最小値が2箇所以上にあるときには，どれかひとつが適当に選ばれる．

### 親

親は格納していないので，必要なら利用者が作る．

## 例

スタックを使って最小値を処理していくようなコードは，Cartesian Tree で書けることが多いのではないかと思う．

#### ABC189 C - Mandarin Orange

よくある「ヒストグラムにおさまる最大の四角形」を求める問題

```cpp
  // vector A に問題を読み込む．
  CartesianTree ct(A);
  ll ans = 0;
  auto f = [&](auto rF, ll lo, ll hi, ll x) -> void {
    if (x < 0) return;
    updMax(ans, (hi - lo) * A[x]);
    rF(rF, lo,    x,  ct.left[x]);
    rF(rF, x + 1, hi, ct.right[x]);
  };
  f(f, 0, N, ct.root);
  cout << ans << endl;
```

#### 



keywords: stack histogram