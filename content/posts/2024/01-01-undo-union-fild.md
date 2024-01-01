---
author: "yamate11"
title: "Undo付きUnionFind"
date: "2024-01-01T11:48:37+09:00"
# date_init: "2024-01-01"
tags: []
categories: ["topic"]
# categories: ["solution"]
summary: "Undo付きUnionFindライブラリです．"
---

## 要約

Undo付き UnionFind です．
Offline Dynamic Connectivity で使うために作りました．

## 使用法

```cpp
UndoUnionFind uf(N); // ノードは 0 から N-1 まで
uf.merge(i, j);      // i と j を同じグループに
uf.undo();           // 直近の merge() を取り消し
ld = uf.leader(i);   // i が属するグループの代表元
sz = uf.gsize(i);    // i が属するグループの要素数
```


## ソース

[ソース](https://github.com/yamate11/compprog/blob/main/clib/UndoUnionFind.cc)

