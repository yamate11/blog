---
author: "yamate11"
title: "Offline Dynamic Connectivity"
date: "2024-01-01T12:09:02+09:00"
# date_init: "2024-01-01"
tags: []
categories: ["topic"]
# categories: ["solution"]
summary: "オフライン動的連結ライブラリです"
---

## 要約

Offline dynamic connectivity のライブラリです．

次のクエリを処理します．

* type 1 : ノード x と y を無向辺でつなぐ
* type 2 : ノード x と y の間の無向辺を削除する
* type 3 : この時点での接続関係に関する UnionFind 構造にアクセスできるので，
  それを用いてなんらかの判定を行う．たとえば，ノード x と y
  が同一連結成分に属するかどうか，などが判定できる．

「offline」なので，クエリ全体を最初に全部読めることが必要です．

計算量: クエリの数を $Q$，type 3 クエリの1回あたりの計算量を $A$ として，
$O(QA\log Q)$ です．UnionFind 構造は Undo 付きのものが使われるので，
`leader()` の計算量は $\log Q$ であることに注意します．
たとえば type 3 クエリが「ノード x と y が同一連結成分に属するか?」なら，
全体の計算量は，$O(Q\log^2 Q)$ です．

## 使用法

次の順で処理を行う．

1. OffDynConn オブジェクトを作成する．
2. 接続/接続解除に関する情報 (時刻と辺の両端のノード) を設定する．
3. 判定を実行する．

### オブジェクトの作成

コンストラクタには，グラフのノード数 size と，時刻の上限 tilm を与える．

```cpp
OffDynConn odc(size, tlim);
```

tlim は，クエリ数としても良いが，
判定の数 (type3 のクエリの数) 分だけあれば十分である．
このライブラリは，同時刻に対して
type1, type2 の処理が複数個与えられた場合には，
それらを与えられた順に実行して，最後にその時刻に対する type3 の処理を行う．
したがって，type3 の処理を $0, 1, ..., \textrm{tlim} - 1$
と番号付けしておいて，$i - 1$ 番と $i$ 番の間に行うべき
type 1, type 2 の処理を，時刻 $i$ に行うようにすれば，正しく動作する．
tlim の大きさは，それなりに性能に影響があるようだ．

### 接続 / 接続解除

```cpp
odc.set_edge(t, x, y, true);   // 時刻 t に x と y を結ぶ
odc.set_edge(t, x, y, false);  // 時刻 t に x と y の接続を切る
```

### 内部構造構築

```cpp
odc.build();
```

`build()` が呼ばれると，UnionFind 構造が構築される．
後述の `run()` が呼ばれると自動的に実行されるので，
明示的に呼ばなくても良い．(呼んでも良い)

### 判定の実行

```cpp
odc.run(f);
```

type 3 の処理を行う関数 f を指定する．
関数 f は，時刻を表す 1 つの引数 t をとり，何も返さない．例:

```cpp
auto f = [&](int t) -> void { ... };
```

run 関数では，t = 0, 1, ..., tlim - 1 に対して，
この順で f(t) が呼び出される．

OffDynConn 構造体は UnionFInd 構造体への参照をメンバ uuf に持っているので，
関数 f の中で，i の連結成分の代表元は `odc.uuf.leader(i)`
によって取得できる．


## アルゴリズム

各タイプのクエリが実行される「時刻」に関して，
セグメント木のようなデータ構造を用意する．
type 1, 2 のクエリから，
各辺 $e$ に対してその辺が接続されている時間が決まるので，それを
$\bigcup \\{[a_i, b_i) \mid i \in I\\}$ として，各
$[a_i, b_i)$ を表すセグメント木のノードの集合に $e$ を登録しておく．

最後に，このセグメント木に対して DFS を実行する．
ノードに入るときに，そこに登録されている辺に対して，
Unionfind 構造で merge を行い，
ノードから出るときに undo を行う．
葉の位置では，type3 に対する判定処理を行う．

## コード

Yet to be written [コード]()

このコードは
[Undo付きUnionFind](https://yamate11.github.io/blog/posts/2024/01-01-undo-union-fild/)
に依存しています．

