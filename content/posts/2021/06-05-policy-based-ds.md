---
author: "yamate11"
title: "policy-based data structure の tree"
date: "2021-06-05"
tags: []
categories: ["topic"]
draft: false
---
gcc (g++) の policy-based data structure の中にある tree (の競技プログラミングでの利用) に関する記事です．

## リンク

* [Policy-based Data Structure](https://gcc.gnu.org/onlinedocs/libstdc++/ext/pb_ds/) (GCC online docs)
* [Codeforces admant\'s blog](https://codeforces.com/blog/entry/11080)

## まとめ

以下の操作ができる set や map 

* x を指定して，x より小さい要素がいくつあるか数える
* n を指定して，n 番目に小さい要素へのイテレータを取得する

## 先頭部分

```cpp
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
```

## 型の定義

#### 例: pair<int, int> の集合

```cpp
using pair_t = pair<int, int>;
using ordered_set = tree<
  pair_t,
  null_type,
  less<pair_t>,
  rb_tree_tag,
  tree_order_statistics_node_update
  >;
```

#### 例: string から int へのマップ

```cpp
using ordered_map = tree<
  string,
  int,
  less<string>,
  rb_tree_tag,
  tree_order_statistics_node_update
>;
```

## 機能の呼び出し

```cpp
  ordered_set os;
  os.insert(pair_t(0,0));
  os.insert(pair_t(1,0));
  os.insert(pair_t(1,1));
  os.insert(pair_t(2,0));
  os.insert(pair_t(2,1));

// order_of_key: 指定した値よりも小さい要素の数
  assert(os.order_of_key(pair_t(-1,0)) == 0);
  assert(os.order_of_key(pair_t(0,0)) == 0);
  assert(os.order_of_key(pair_t(0,1)) == 1);
  assert(os.order_of_key(pair_t(1,0)) == 1);
  assert(os.order_of_key(pair_t(1,1)) == 2);
  assert(os.order_of_key(pair_t(100,0)) == 5);

// find_by_order: 指定した位置の要素へのイテレータ
  assert(*os.find_by_order(0) == pair_t(0,0));
  assert(*os.find_by_order(2) == pair_t(1,1));
  assert(*os.find_by_order(4) == pair_t(2,1));
  assert(os.find_by_order(5) == os.end());
```

## 注意

* 必ずしも速くないらしい．Fenwick tree なり segment tree の倍くらい遅いというレポートがある
* multiset や multimap に相当する機能はない ([リンク](https://gcc.gnu.org/onlinedocs/libstdc++/manual/policy_data_structures_design.html#concepts.associative_semantics.multi))
