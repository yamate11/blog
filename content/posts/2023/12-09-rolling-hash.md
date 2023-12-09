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

ローリングハッシュライブラリの使い方についての自分用のメモです

## ローリングハッシュ

## 使用法

#### オブジェクトの生成

通常は，次のようにする．

```cpp
RollingHash rh;
```

これは，string を対象としたものになり，mod は $2^{61} - 1$ である．
base は，1000 以上 $2^{60}$ 未満の範囲でランダムに選択される．

base を指定する場合には，次のようにする．

```cpp
RollingHash rh(base);
```

次のコードは，base をランダム選択にするが，
選択範囲が min_base 以上 $2^{60}$ 未満になる．

```cpp
RollingHash rh(0, min_base);
```

#### ハッシュテーブルの生成

ハッシュを計算する前に，ハッシュテーブルを生成する必要がある．
文字列 s に対するハッシュテーブルは，次のように生成できる:

```cpp
string s = "Hello, world.";
vector<u64> hs = rh.hashes(s);
```

hs には，`vector<u64>` 型で，サイズ `s.size() + 1` のベクトルが設定される．
(u64 は unsigned long long のこと)．
hs の i 番目の要素 hs[i] は，sの先頭から i 文字の部分文字列
s.substr(0, i) のハッシュ値である．
特に，s のハッシュ値は hs.back() である．

#### ハッシュ値の計算

s の部分文字列のハッシュ値は，get メソッドで取得できる．
位置 start から始まる長さ len の部分文字列を取得するコードは，次の通り．

```cpp
u64 h = rh.get(hs, start, len);
```

keywords: rolling hash
