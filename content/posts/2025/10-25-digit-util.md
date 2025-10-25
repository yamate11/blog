---
author: "yamate11"
title: "整数の桁"
date: "2025-10-25T16:28:31+09:00"
# date_init: "2025-10-25"
tags: []
categories: ["topic"]
# categories: ["solution"]
# summary: "要約を書いておく．ここには問題タイトル等は不要" 
---

整数の桁を扱うライブラリです．ソースは[こちら](https://github.com/yamate11/compprog-clib/blob/master/digit.cc)．

### 使用法

```cpp
  digit_util du;      // base == 10
  digit_util du1(3);  // base == 3
  digit_util du2(16); // base == 16
  
  du.pow(3)          // 1000
  du.pow(18)         // 1000000000000000000
  du.pow_size()      // 19, meaning du.pow(i) is valid for i from 0 to 18
  du.width(5678)     // 4, meaning 5678 has 4 digits
  du.width(0)        // Error.   width(n) is defined only for n > 0.
  du.nd_min(3)       // 100, the least number whose width is 3.
  su.nd_max(4)       // 9999, the maximum number whose width is 4.
  du.floor(1234)     // 1000, the largest power of 10 that does not exceed 1234
  du.ceil(1234)      // 10000, the smallest power of 10 that does not fall below 1234
  du.d_at(1234, 0)   // 4,  du.d_at(1234, 1) == 3,  du.d_at(1234, 2) == 2, du.d_at(1234, 3) == 1
  du.v_at(1234, 0)   // 4,  du.v_at(1234, 1) == 30, du.d_at(1234, 2) == 200, du.d_at(1234, 3) == 1000
  du.to_vector(1234) // vector<ll>{1, 2, 3, 4}
  du.to_string(1234) // "1234"
  du.from_vector(vector<ll>{1, 2, 3, 4}) // 1234
  du.from_string("1234")                 // 1234
```

### 使用準備

digit_util 構造体のオブジェクトを作成する．ここでは `du` とする．
作成時に base を指定する．十進法なら 10，16進法なら 16 という具合．
base が 10 のときには省略できる．以下，base は $b$ と記述する．

```cpp
  digit_util du;      // base == 10
  digit_util du1(3);  // base == 3
  digit_util du2(16); // base == 16
```

### 累乗

$b$ の $k$ 乗は，`pow(k)` で得られる．

```cpp
  du.pow(3)          // 1000
  du.pow(18)         // 1000000000000000000
```

実装上，`pow` の値はベクトルに格納されているが，その長さは `pow_size()` で取得できる．
つまり，`du.pow(k)` は，`0 <= k < du.pow_size()` なる k に対して有効である．

```cpp
  du.pow_size()      // 19, meaning du.pow(i) is valid for i from 0 to 18
```

### 桁数

正の整数 $x$ の桁数は，`width(x)` で取得できる．
たとえば，5678 は 4 桁の数だから，`du.width(5678)` の値は 4 である．

正の数以外を与えるとエラーになる．

```cpp
  du.width(5678)     // 4, meaning 5678 has 4 digits
  du.width(0)        // Error.   width(n) is defined only for n > 0.
```

### 桁の範囲

$n$ 桁の整数の最小値と最大値は `nd_min(n)` と `nd_max(n)` で取得できる．

```cpp
  du.nd_min(3)       // 100, the least number whose width is 3.
  su.nd_max(4)       // 9999, the maximum number whose width is 4.
```

正の整数 $x$ に対し，$b^k$ の形の数で
$x$ 以下の 最大のものと
$x$ 以上の 最小のものは，
`floor(x)` と `ceil(x)` で取得できる．
$b = 2$ のときは，`std::bit_floor` や `std::bit_ceil` と同等である．

```cpp
  du.floor(1234)     // 1000, the largest power of 10 that does not exceed 1234
  du.ceil(1234)      // 10000, the smallest power of 10 that does not fall below 1234
```

### 指定桁の数

正の整数 $x$ の $k$ 桁めの数は，`d_at(x, k)` で取得できる．ここで，$k$ は右から順に 0, 1, 2, ... と数える．
つまり，$k$ を指定すると 「$b^k$ の位」の数が取得できる．
一方で，`v_at(x, k)` は，$k$ 桁めの数が表す値である．
つまり，`du.v_at(x, k) == du.d_at(x, k) * du.pow(k)` の関係にある．

```cpp
  du.d_at(1234, 0) == 4;
  du.d_at(1234, 1) == 3;
  du.d_at(1234, 2) == 2;
  du.d_at(1234, 3) == 1;
  du.v_at(1234, 0) ==    4;
  du.v_at(1234, 1) ==   30;
  du.d_at(1234, 2) ==  200;
  du.d_at(1234, 3) == 1000;
```

### ベクトルや文字列との変換

正の整数 $x$ と，桁ごとのベクトル $v$ との変換は，`to_vector(x)`, `from_vector(v)` で，
正の整数 $x$ と，文字列 $s$ との変換は，`to_string(x)`, `from_string(s)` で実現できる．


```cpp
  du.to_vector(1234) // vector<ll>{1, 2, 3, 4}
  du.to_string(1234) // "1234"
  du.from_vector(vector<ll>{1, 2, 3, 4}) // 1234
  du.from_string("1234")                 // 1234
```



keywords: digit util
