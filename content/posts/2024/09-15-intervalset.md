---
author: "yamate11"
title: "intervalSet ライブラリ"
date: "2024-09-15T14:58:24+09:00"
# date_init: "2024-09-15"
tags: []
categories: ["topic"]
summary: "階段関数を表現するライブラリ intervalSet の説明です．"
---

階段関数 (区分的に定数である関数) を表現するライブラリ intervalSet の説明です．
名前が良くないが，今更帰るのも面倒なので．
いわゆる，区間を pair の set (または map) で管理する，という方法の拡張になっています．

## コード

コードは[こちら](https://github.com/yamate11/compprog-clib/blob/master/intervalSet.cc)

## 対象

階段関数 は，整数の区間 $[\text{lo}, \text{hi})$ で定義された関数 $f$ で，区分的に定数となっているものです．
有限の離散的な集合上で定義された関数だから区分的に定数もへったくれもない，という話もありますが，
もちろん気持ちの問題です．

$\text{lo} = a_0, a_1, \dots, a_n = \text{hi}$ なる列が取れて，区間 $[a_i, a_{i + 1}]$ では，
$f$ の値が定数 $v_i$ となっているものとします．

区間の集合 $J$ は，その特性関数 ($f(x) = 1 \iff \exists I \in J. x \in I$) を考えることで，
このライブラリで扱うことができます．

## 概要

このライブラリでは，上のような階段関数を，map $m$ で表現します．
$m[a_0] = v_0$, $m[a_1] = v_1$, ..., $m[a_{n - 1}] = v_{n - 1}$, $m[a_n] = \bot$ となっています．
ここで，$m[a_i] \not= m[a_{i + 1}]$ であることが保障されます．

### 使用例

```cpp
ll lo = -1e18, hi = 1e18;
itv_set<ll>(lo, hi, 0) f;  // f は，[lo, hi) で値 0 を取る関数
f.put(10, 90);             // f(10) の値を 90 に変更する．
f.put(20, 30, 100);        // f(20) から f(29) までの値を 100 に変更する．
f.put(30, 40, 200);        // f(30) から f(39) までの値を 200 に変更する．
ll x = f.get_val(25);      // f(25) の値である 100 を x に代入する．
ll y = f.get_val(5);       // f(5)  の値である 0 を y に代入する．
auto [l, r, v] = f.get(35);  // f(35) と同じ値が連続している区間は [30, 40) なので，
                             // l = 30, r = 40, v = 200 となる．
f.put(29, 200);
auto [l1, r1, v1] = f.get(35);  // 今度は，l1 = 29 になる．
auto it = f.get_iter(35); // iterator (ちょっと変だが...)
assert(l1 == it.left() and r1 == it.right() and v1 == it.val());
--it;
assert(it.val() == 100);
for (auto& [l, r, v] : f) { ... }  // iterator によるループ
```

## 機能

### 構築子

```cpp
template<typename T>
itv_set<T>(ll lo = LLONG_MIN, ll hi = LLONG_MAX, const T& t = T());
```

区間はデフォルトでは [LLONG_MIN, LLONG_MAX)．格納する値の型はテンプレートパラメタで指定する．
第3引数は関数の値の初期値．

### 値の設定

```cpp
put(ll x, const T& t);         // x の値を t にする．
put(ll l, ll r, const T& t);   // [l, r) の値を t にする．
```

### 値の取得

```cpp
auto it = get_iter(x);      // x が含まれる区間の iterator を取得する．
auto [l, r, v] = get(x);    // x が含まれる区間 [l, r) と値 v を取得する．
const T& v = get_val(x);    // x の値を取得する．
```

### iterator

iterator it は，通常のように，++ (前置，後置)，-- (前置，後置)，をサポートする．

演算子 * は，区間の両端と関数の値を返す．
```cpp
auto [l, r, v] = *it;
```

次のメンバ関数が使える．it->left() 等ではなく，it.left() 等であることに注意．

```cpp
ll u = it.left();   // 区間の左端
ll r = it.right();  // 区間の右端 (区間に含まれない)
const T& t = it.val();   // 関数の値
auto it1 = it.prev();   // 一つ前の区間
auto it2 = it.next();   // 一つ後の区間 
```

itv_set は，通常通り，begin() と end() を提供する．
begin() は普通通りだが，$[a_{n - 1}, a_n)$ の区間の次が end() になることに注意．
つまり，実装で，ダミーを格納しているところは現れない．
次のようなループが書ける:

```cpp
for (auto it = f.begin(); it != f.end(); ++it) {
  auto& [l, r, v] = *it;   // もしくは， it.left() などを使っても良い．
  ...  
}
```

### 和

T に加法と乗法が定義されている場合に，和を求めることができる．

```cpp
sum(ll l0, ll r0);   // \sum { f(x) | x \in [l0, r0) }
```

### 点ごとの演算

op を T 上の2項演算，f1, f2 を itv_set<T> のオブジェクトとするとき，
各点 x ごとに f1(x) op f2(x) を行った結果の itv_set<T> オブジェクトを
返す関数 itv_apply がある．
f1 と f2 の定義域は一致していなければならない．

```cpp
auto f1 = itv_set<ll>(0, 10);
auto f2 = itv_set<ll>(0, 10);
f1.put(0, 7, 20);
f2.put(3, 10, 40);
auto g = itv_apply(plus<ll>(), f1, f2);  // g は [0, 3) で 20, [3, 7) で 60, [7, 10) で 40
```

### デバッグ

itv_set の impl メンバが，実装本体の map<ll, T> を保持している．これを表示させると良い．


keywords: interval 区間 