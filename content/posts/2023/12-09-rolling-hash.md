---
author: "yamate11"
title: "ローリングハッシュライブラリ"
date: "2023-12-09T16:28:56+09:00"
# date_init: "2023-12-09"
tags: []
categories: ["topic"]
# categories: ["solution"]
summary: "ローリングハッシュライブラリの使い方についての自分用のメモです"
---

競技プログラミング用ローリングハッシュライブラリ (自作) についてのメモです．

## コード

[コードへのリンク](https://github.com/yamate11/compprog-clib/blob/master/rollingHash.cc)

## ローリングハッシュ

ローリングハッシュは，文字列のハッシュ値の計算法．
文字列 $s$ について$O(|s|)$ で前計算をしておくと，
$s$ とその部分文字列すべてについて，ハッシュ値が $O(1)$ で取得できる．

ローリングハッシュには，2つのパラメタ base と mod がある．
文字列を base 進の数値とみなして，その mod を法とした値をハッシュ値とする．
たとえば，base = 200, mod = 10007 の場合，文字列 "abc" のハッシュ値は，
$(97 * 200^2 + 98 * 200 + 99) \bmod 10007 = 6976$ である．
(文字 'a' の ASCII コードは 97 であった)

このライブラリでは，上の計算例が示すように，
末尾文字が1の位で，先頭文字が base の s.size() - 1 乗の位としている．

安全な運用のためには，以下を守る必要がある:

* mod は，大きな素数とする．(固定しても問題無い)
* base は，ランダムに取る．
* 可能な場合，base は，1文字のハッシュ値より大きく取る．
  たとえば，上の例のように，1文字のハッシュ値を ASCII コードにとるならば，
  base は 128 以上に取る．

このライブラリでは，
[keymoon 氏の記事](https://qiita.com/keymoon/items/11fac5627672a6d6a9f6)
にしたがって，mod = $2^{61} - 1$ にとっている．
この数は素数であり，`rh_prime` という定数で参照できる．
この mod を使うと，積が高速に計算できる．
__ただし，mod の値は大きいので，オーバーフローに注意__．
後述の 「mod $2^{61} - 1$ 演算」を参照．

## 使用法

以下，u64 は unsigned long long のこととする．

ハッシュ値の計算は，次の段取りによる:

* まず，RollingHash オブジェクト `rh` を作成する．
* 文字列 `s` と，その部分列のハッシュ値が欲しい場合
  * 前計算．`hs = rh.hashes(s);`
  * ハッシュ値は，次のようにとれる．
    * `s` のハッシュ値: `rh.get(hs)`．
    * `s` の位置 `i` から始まる長さ `len` の部分文字列のハッシュ値: `rh.get(hs, i, len)`．
* 文字列 `s` のハッシュ値のみがほしい場合
  * `rh.hashvalue(s)`
    
#### RollingHash オブジェクトの生成

通常は，次のようにする．

```cpp
RollingHash rh;
```

これは，string を対象としたものになり，mod は $2^{61} - 1$ である．
base は，1000 以上 $2^{59}$ 未満の範囲でランダムに選択される．

base を指定する場合には，次のようにする．

```cpp
RollingHash rh(base);
```

次のコードは，base をランダム選択にするが，
選択範囲が min_base 以上 $2^{59}$ 未満になる．

```cpp
RollingHash rh(0, min_base);
```

#### ハッシュ値の前計算

指定した文字列，およびその部分文字列に対するハッシュ値を計算するための前計算を行う，

```cpp
string s = "Hello, world.";
vector<u64> hs = rh.hashes(s);
```

返り値 hs の長さは ssize(s) + 1 で，第 i 要素は，s.substr(0, i) に対するハッシュ値である．

引数は string または `const char*`．

#### ハッシュ値の計算

s およびその部分文字列のハッシュ値は，get メソッドで取得できる．
前計算の結果も与える必要がある．

```cpp
auto hs = rh.hashes(s);
u64 h0 = rh.get(hs);               // s 自身のハッシュ値． hs[ssize(s)] に等しい．
u64 h1 = rh.get(hs, start, len);   // s.substr(start, len) のハッシュ値
u64 h2 = rh.get(hs, start);        // s.substr(start) のハッシュ値
```

部分文字列に興味が無いときには，`hashvalue()` を使えば，前計算無しでハッシュ値を取得できる:

```cpp
u64 h0 = rh.hashvalue(s);
```

なお，空文字列のハッシュ値は 0 である．

#### 連結文字列のハッシュ値

文字列 s1 のハッシュ値が h1 で，文字列 s2 のハッシュ値が h2 のとき，
s1 と s2 を連結した文字列 s1 + s2 のハッシュ値 h は，次のように計算できる:

```cpp
u64 h = rh.hash_concat(h1, h2, ssize(s2));
```

s2 の長さが必要であることに注意．

#### base 値の取得

`rh.base_power(1)` で，base 値が取得できる．一般に，`rh.base_power(k)` は，$\text{base}^k$ を返す．

#### 一般のベクトルに対するハッシュ

文字列に限らず，ベクトル `vector<T>` に対してもハッシュを計算できる
(正確にはベクトルでなくても，`operator []` が定義されていれば良い)．
この場合，`T` の各要素に対するハッシュ値が計算できる必要があるので，
それを実行する関数 conv を渡して RollingHashGen オブジェクトを作成する:
`conv(t)` の値は 0 以上 $2^{61} - 1$ 未満でなければならない．

```cpp
auto rh = make_rolling_hash_gen<T>(0, min_base, conv);
```

T の要素に対するハッシュ値が，
T から u64 へのキャストで良い場合には，次のように定義することもできる．

```cpp
RollingHashGen<T, nullptr_t> rh(0, min_base);        
```

なお，上で述べた，文字列を対象とした RollingHash 型は，
`RollingHashGen<char, nullptr_t>` の別名として定義されている．

#### mod $2^{61} - 1$ 演算

0 以上 $2^{61} - 1$ 未満の u64 型の a, b に対し，
$a + b \mod (2^{61} - 1)$，
$a - b \mod (2^{61} - 1)$，
$a \times b \mod (2^{61} - 1)$ の値を計算することができる．
ハッシュ値をセグメント木で計算する場合など，
自前で計算が必要になったときには，これらの関数が有効であろう．

```cpp
RollingHash rh;
u64 a, b;
rh_add(a, b);  // a + b   mod (2^61 - 1)
rh_subt(a, b); // a - b   mod (2^61 - 1)
rh_mul(a, b);  // a * b   mod (2^61 - 1)
rh_prime - a;  // -a      mod (2^61 - 1)
```

### メモ -- 設計・実装上の注意点

この方法だと，rh.get(hs, ss) というふうに，常に rh と hs の両方を意識しなくてはならないのが嫌な感じである．
そこで，HashValues とかいうオブジェクトを作って，hvs = rh.hashes(s) は HashValues オブジェクトを返すようにして，
HashValues オブジェクトに rh を格納してしまい，hvs.get(ss) というふうにすると，気持ちよいように思われる．
しかし，これだと，HashValues の default constructor がうまく作れないので，vector<HashValues> が初期化できず，
複数の文字列の部分列のハッシュ値が欲しいときに困る．



## keywords

keywords: rolling hash
