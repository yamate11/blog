---
author: "yamate11"
title: "二分探索ライブラリ"
date: "2024-02-19T17:44:50+09:00"
# date_init: "2024-02-19"
tags: []
categories: ["topic"]
# categories: ["solution"]
# summary: "二分探索ライブラリ関数の自分用のメモです"
---

自分用の [二分探索ライブラリ](https://github.com/yamate11/compprog/blob/main/clib/binsearch.cc) のメモです．

## 使用法

### 整数版

以下では，INT は，int, long long, unsigned int などを表す．

#### signature

```cpp
template <typename INT>
requires integral<INT>
INT binsearch(auto check, INT yes, INT no)
```

#### 引数

* check ... 判定関数．INT を受け取って bool を返す．
* yes ... 真になる値
* no ... 偽になる値

#### 制約

check 関数は，以下のいずれかを満たす述語 $P(x)$ を，開区間 (yes, no) において実装したものでなければならない

* ある $t$ が存在して，
  * $x \leq t$ である $x$ について，$P(x)$ は真．
  * $t < x$ である $x$ について，$P(x)$ は偽．
* ある $t$ が存在して，
  * $x \leq t$ である $x$ について，$P(x)$ は偽．
  * $t < x$ である $x$ について，$P(x)$ は真．

概念的には，$P(\text{yes})$ は真で，$P(\text{no})$ は偽でなければならない．
ただし，実際には，`check(yes)` や `check(no)` は呼ばれない．

#### 返却値

`binsearch(check, ...)` が返す値 x について，
* `check(x)` は true を返す．
* yes < no のとき，`check(x + 1)` は，false を返す．
* yes > no のとき，`check(x - 1)` は，false を返す．

#### 使用例:

```cpp
auto check = [](ll x) -> bool { return x * x <= 20000; }
ll x = binsearch(check, 100LL, 200LL); //  x <- 141
// または，binsearch<ll>(check, 100, 200);   INT の型は yes や no から推論される．
```

一応，不要なオーバーフローを起こさないよう，`(yes + no) / 2` ではなく，`no + (yes - no) / 2` と書いている．

### 浮動小数点版

以下では，DOUBLE は，float, double, long double などを表す．

#### signature

```cpp
template <typename DOUBLE>
requires floating_point<DOUBLE>
DOUBLE binsearch(auto check, DOUBLE yes, DOUBLE no, DOUBLE err);
```

#### 引数

* check ... 判定関数．DOUBLE を受け取って bool を返す．
* yes ... 真になる値
* no ... 偽になる値
* err ... 絶対誤差

#### 制約

整数版と同じ

#### 返却値

`binsearch(check, ...)` が返す値 $x$ は，制約のところで述べた $t$ との絶対誤差が err 未満であるか，
または，$t$ との絶対誤差が err 未満であるような DOUBLE で表現可能な値が無い場合には，表現可能な値で
$t$ に最も近い値である．したがって，`check(x)` が true を返す保証はない．

#### 実装

$\lceil\log_2 (| Y - N | / \text{err})\rceil + 1$ 回のループを回す．
ここで，$Y$ と $N$ は，yes と no の引数で与える値．


使用例:

```cpp
auto check = [](double x) -> bool { return x * x <= 2; }
double x = binsearch(check, 1.0, 2.0, 1e-6); // x <- 1.4142...
```
