---
author: "yamate11"
title: "C++言語・STLメモ"
date: "2021-09-20T07:14:12+09:00"
# date_init: "2021-09-20"
tags: []
categories: ["topic"]
# categories: ["solution"]
description: "C++言語や，C++ Standard Template Library の書き方で，忘れやすいものをメモしておくページです．"
summary: "C++言語や，C++ Standard Template Library の書き方で，忘れやすいものをメモしておくページです．"
showtoc: true
tocopen: true
---

## stream の書式関連

参照: https://www.cs.fsu.edu/~myers/c++/notes/formatting.html

* stringstream は，str() メンバ関数で文字列になる．

```cpp
    stringstream ss;
    ss << 100; assert(ss.str() == "100");
```

* 16進表記は hex．10進表記(にもどす)は dec．大文字/小文字は [no]uppercase．

```cpp
    stringstream ss;
    ss << hex << 253 << uppercase << 254 << nouppercase << 255;
    ss << dec << 100;
    assert(ss.str() == "fdFEff100");
```

* 小数点以下の桁数は setprecision で制御

```cpp
    stringstream ss;
    double x = 1.0 / 3.0;
    ss << x << " " << setprecision(20) << x;
    assert(ss.str() == "0.333333 0.33333333333333331483");
```

* 0詰めは setfill, 表示幅は，setw で制御

```cpp
    stringstream ss, ss1;
    ss << setw(4) << 10 << "," << setw(4) << (int)1e8;
    assert(ss.str()  == "  10,100000000");
    ss1 << setfill('0') << setw(4) << 10 << "," << setw(4) << (int)1e8;
    assert(ss1.str() == "0010,100000000");
```

* ほとんどの manipulator は sticky (効果が持続) だが，
  setw は例外．

```cpp
    stringstream ss1, ss2;
    ss1 << hex << 100 << " " << 200;
    assert(ss1.str() == "64 c8");
    ss2 << setw(4) << 5 << 6;
    assert(ss2.str() == "   56");
```

## 例外

* 型宣言: `struct Exc : exception {};`
* 投げる: `throw Exc();`
* 受ける: `try { ... } catch(const Exc& e) { ... }`

使用例

```cpp
  struct Exc : exception {};
  auto all_non_zero = [&](string s) -> bool {
    auto dfs = [&](auto f, size_t i) -> void {
      if (i == s.size()) return;
      if (s[i] == '0') throw Exc();
      f(f, i + 1);
    };
    try {
      dfs(dfs, 0);
      return true;
    }catch (const Exc& e) {
      return false;
    }
  };
  assert(all_non_zero("11111"));
  assert(! all_non_zero("11101101"));
```

## ビット処理

* 1の数を数える -- `__builtin_popcountll`

```cpp
  assert(__builtin_popcountll(0xF) == 4);
  assert(__builtin_popcountll(0x100030007000F000) == 10);
```

* 右端の0の数 -- `__builtin_ctzll`
  * Count Trailing Zero であろう．
  * __builtin_ctzll(x) は，x の LSB の添字に等しい．
  * 引数は0ではいけない．
  

```cpp
  assert(__builtin_ctzll(0x1) == 0);
  assert(__builtin_ctzll(0x8) == 3);
  assert(__builtin_ctzll(1LL<<63) == 63);
```

* 左端の0の数 -- `__builtin_clzll`
  * Count Leading Zero であろう．
  * __builtin_clzll(x) は，63 - (x の MSB の添字) に等しい
  * 引数は0ではいけない．

```cpp
  assert(__builtin_clzll(0x1) == 63);
  assert(__builtin_clzll(1LL<<62) == 1);
```

## vector での 重複の削除

Unix の， `sort | uniq` に相当する操作


```cpp
  vector<int> vec({10, 2, 5, 7, 5, 2, 5});
  sort(vec.begin(), vec.end());
  vec.erase(unique(vec.begin(), vec.end()), vec.end());
  assert(vec == vector<int>({2, 5, 7, 10}));
```

## イタレータ

iterator は，「要素を指す」と考えるより「要素と要素の間を指す」
と考えた方が話が分かりやすい．

```cpp
  vector<int> vec({2, 4, 5, 5, 5, 6, 10, 12});
  auto it1 = lower_bound(vec.begin(), vec.end(), 5);
  auto it2 = upper_bound(vec.begin(), vec.end(), 5);
  auto it3 = lower_bound(vec.begin(), vec.end(), 11);
  auto it4 = upper_bound(vec.begin(), vec.end(), 11);
```

<img src="./fig01.jpg" width="65%">

## 逆方向イタレータ

`reverse_iterator<decltype(it)>(it)` で，
it の指している「要素間の位置」は変わらずに，方向だけが反転する．
上図で，5以下の要素を並べるコード:

```cpp
    stringstream ss;
    vector<int> vec({2, 4, 5, 5, 5, 6, 10, 12});
    auto itN = upper_bound(vec.begin(), vec.end(), 5);
    for (auto itR = reverse_iterator<decltype(itN)>(itN);
         itR != vec.rend(); itR++) {
      ss << *itR;
    }
    assert(ss.str() == "55542");
```

set や map などに対しても，同様のことができる．

```cpp
    stringstream ss;
    multiset<int> is({2, 4, 5, 5, 5, 6, 10, 12});
    auto itN = is.upper_bound(5);
    for (auto itR = reverse_iterator<decltype(itN)>(itN);
         itR != is.rend(); itR++) {
      ss << *itR;
    }
    cout << ss.str() << endl;
    assert(ss.str() == "55542");
```

## set や priority queue の比較関数

集合 (set) のテンプレートの第2引数が比較クラスになる．
イタレータが降順に動いていってほしい場合，次のように書けば良い．

```cpp
set<T, greater<T>> ss;
```

一般の比較関数 fn を書きたいときには，次のようにする．

```cpp
set<T, decltype(fn)>> ss(fn);
```

優先度付きキューを普通に次のように書くと降順になる:

```cpp
priority_queue<T> pque;
```

昇順にしたいときには，次のように書く:

```cpp
priority_queue<T, vector<T>, greater<T>> pque;
```

一般の比較関数 fn を書きたいときには，次のようにする．
指定した比較関数の「大きい」順に取り出される．
つまり，fn(x, y) が真の時には，yがxより先に取り出される．

```cpp
priority_queue<T, vector<T>, decltype(fn)> pque(fn);
```

例:

```cpp
  using Pair = pair<int, int>;
  auto comp = [&](Pair x, Pair y) -> bool { 
    if (x.first != y.first) return x.first  < y.first;
    else                    return x.second > y.second;
  };
  priority_queue<Pair, vector<Pair>, decltype(comp)> pque(comp);

  pque.emplace(2, 1); pque.emplace(3, 5), pque.emplace(3, 9);
  Pair p;
  p = pque.top(); pque.pop(); assert(p == Pair(3, 5));
  p = pque.top(); pque.pop(); assert(p == Pair(3, 9));
  p = pque.top(); pque.pop(); assert(p == Pair(2, 1));
```

