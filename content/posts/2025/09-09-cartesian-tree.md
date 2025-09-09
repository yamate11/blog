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
    CartesianTree cp(vec);
    // CartesianTree cp(vec, less<ll>()); ... same
    // CartesianTree cp(vec, [](ll a, ll b) { return a < b; }); ... same
    assert(cp.root == 2);     // vec[2] is the least element
    assert(cp.left[2] == 0);  // least in vec[0:2] is vec[0]
    assert(cp.left[0] == -1); // "no such element" is expressed by -1
    assert(cp.right[2] == 5);
    assert(cp.left[5] == 3 or cp.left[5] == 4);  // either of tied element can be chosen
```

## 定義


Cartesian
