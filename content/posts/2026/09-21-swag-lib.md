---
author: "yamate11"
title: "SWAG"
date: "2026-09-21T16:29:16+09:00"
# date_init: "2026-09-21"
tags: ["swag"]
categories: ["topic"]
# categories: ["solution"]
# summary: "SWAG のライブラリ"
---

SWAG のライブラリを書きました．[ソースはこちら](https://github.com/yamate11/compprog-clib/blob/master/swag.cc)

## 使用法

```cpp
    auto sw1 = make_swag(plus<ll>(), 0LL);
    auto sw = make_swag(multiplies<MyMatrix>(), MyMatrix{{1,0},{0,1}});
              // operator and its unit element.
              // operator should be associative.
    sw.push(obj1);   // push obj1 into the queue
    sw.pop();        // pop the front element
    T v = sw.get_val(); // calculate the aggregated value e1 `op` e2 `op` ... `op` en
                        //     where e1 is the front and en is the back
    T a = sw.front();   // the front element
    T b = sw.back();    // the back element
    auto vec = sw.vec_view();  // list the elements for debugging
```

## メモ

* SWAG = Sliding Window AGgregation
* 結合法則を満たす (実装の都合上単位元も持つ) 演算
* 機能: 
  * queue に push
  * queue から pop
  * queue の要素全体に演算を適用 (fold)．入れた順に左から
* 計算量: push, pop, 演算適用とも，ならし $O(1)$．
* 4本のスタック (要素と値，後ろ半分と前半分) で実現．