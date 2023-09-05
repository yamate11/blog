---
author: "yamate11"
title: "二重連結"
date: "2023-09-05T18:13:58+09:00"
# date_init: "2023-09-05"
tags: []
categories: ["topic"]
# categories: ["solution"]
summary: "無向グラフの二重連結に関して，辺二重連結，橋，点二重連結，関節点，block-cut tree などに関するまとめです"
---

## 概要

無向グラフの二重連結に関して，二重辺連結，橋，二重点連結，関節点，block-cut tree などに関するライブラリを書いたので，そのメモです．

## 概念

以下，グラフは単純とは限らない，無向グラフとします．

グラフのある辺を削除すると，
連結成分の数が増えるとき，その辺を **橋** (bridge) と呼ぶ．

橋の無いグラフは，**二重辺連結** (two-edge connected) であるという．

グラフの点集合の部分集合が，二重辺連結部分グラフを導き，
そのようなものの中で極大であるとき，これを二重辺連結成分と呼ぶ．

グラフのある点 (とその点が端点である辺) を削除すると，
連結成分の数が増えるとき，
その点を **関節点** (articulation point) と呼ぶ．

関節点の無いグラフは，**二重点連結** (biconnected) であるという．

グラフの点集合の部分集合が，二重点連結部分グラフを導き，
そのようなものの中で極大であるとき，これを二重点連結成分と呼ぶ．

## 命題たち

以下のことがなりたつ (と思うのですが，まだちゃんと証明できていない
ものもあります)

* 二重点連結グラフは，二重辺連結である．
* 二重辺連結成分を集めてくると，グラフ点集合の分割になる．
* 二重辺連結成分$A$, $B$ に，$(A, B) \in R \iff \exists a \in A \exists b \in B (a,b)$は橋．という関係を入れると，森になる．
* 2つの二重点連結成分の共通部分は，空集合であるか，関節点1点からなる．

二重点連結成分の全体 $C$ と，関節点全部からなる集合 $A$ の和集合
$A \cup C$ に，
$\\{ (a, c) \mid a \in A, c \in C, a \in c \\}$ で関係を入れると，
これは森になります．元のグラフが連結ならば，木です．
これを，Block-Cut tree (forest?) と言うそうです．
(block は二重点連結成分を指し，cut は関節点を指す)

## ライブラリ

以下のような仕様のものを作りました．
一応，自己ループや多重辺があっても，また，連結で無くても動作するはずです．

```cpp
struct bridge {  // 二重辺連結に関する機能
  bridge(int size);  // constructor
  void add_edge(int u, int v);  // もとのグラフの辺の定義
  bool is_bridge(int u, int v); // 橋かどうか判定
  int num_tecc();               // 連結成分の数
  const vector<int>& tecc(int ccid);  // 各連結成分の頂点をあつめたvector
  int node_tecc_idx(int u);     // もとのグラフの点 u が属する連結成分の ID
  vector<pair<int, int>> tecc_edges();  // 上述の森の辺 (ペアの要素は，連結成分ID)
};

struct articulation {  // 二重点連結に関する機能
  articulation(int size);  // constructor
  void add_edge(int u, int v);  // もとのグラフの辺の定義
  bool is_articulation(int u);  // 関節点かどうか判定
  int bcc_size();               // 連結成分の数  (上と整合していないなあ...)
  const vector<int>& bcc(int idx);  // 各連結成分の頂点をあつめたvector
  enum kind { BLOCK, CUT };     // block-cut forest でどちらを表しているかを示す enum
  struct bctree {  // block-cut forest (名前が整合的でない...)
    int size();    // forest の頂点の数
    vector<pair<int, int>> edges();  // forest の辺
    pair<kind, int> what(int node);  // forest の頂点が，もとのグラフでは何か?
                  // {BLOCK, x} なら ID x である連結成分， {CUT, u} なら関節点 u
    int node(kind w, int i);  // what の逆．forest における頂点番号を返す．
  };
  bctree* make_bctree();   // Block Cut Forest を作る．戻り値はポインタであることに注意．
};
```

典型的な使用法は次のような感じです:

二重辺連結について:

```cpp
  int N; cin >> N;

  bridge bu(N);
  for (int i = 0; i < N; i++) {
    int u, v; cin >> u >> v; u--; v--;
    bu.add_edge(u, v);
  }
  int u = ..., v = ...;
  bu.is_bridge(u, v);  // (u, v) は橋か?
  for (int x = 0; x < bu.num_tecc(); x++) {
    for (int u : bu.tecc(x)) {
      ... u ... ;  // x 番目の二重辺連結成分 bu.tecc(x) の要素に順にアクセス
    }
  }
  int x = bu.node_tecc_idx[u];  // 頂点 u は x 番目の連結成分に属する
  for (auto [x, y] : bu.tecc_edges()) {
    // (x, y) が，上述の森の辺をなしている．
  }
```

なお，元のグラフが連結でない場合には，`bu.tecc_edges()` の関係は
木にはならずに森になります．`bu.llk.roots` は，
(型は `vector<int>` )，もとのグラフの連結成分から1点ずつとった集合に
なっています．

二重点連結について:

```cpp
  int N; cin >> N;
  articulation au(N);
  for (int i = 0; i < N; i++) {
    int u, v; cin >> u >> v; u--; v--;
    au.add_edge(u, v);
  }
  int u = ...;
  au.is_articulation(u);  // u は関節点か?
  for (int x = 0; x < au.bcc_size(); x++) {
    for (int u : au.bcc(x)) {
      ... u ...;  // x 番目の二重点連結成分 au.bcc(x) の要素に順にアクセス
    }
  }

  // Block-Cut tree に，別のライブラリである Tree を使う場合
  // この下は，元のグラフが連結であるという前提のコードになっている...
  //    (ライブラリ自体は，そうでなくても動作はする．bctree() という名前になっているが....)
  auto bctree = au.make_bctree();
  ll sz = bctree->size();  // Block-Cut tree の頂点数
  Tree bct(0, sz);
  for (auto [a, b] : bctree->edges()) bct.add_edge(a, b);
     // bctree->edges() が，Block Cut tree としての辺の関係
  for (int a = 0; a < sz; a++) {
    auto [w, i] = bctree->what(a);  // aは BLOCK? それとも CUT?
    if (w == articulation::BLOCK) {
      // この連結成分は，au.bcc(i) である．
    }else if (w == articulation::CUT) {
      // この関節点は，(もとのグラフの頂点番号で) i である．
    }else assert(0);
    // what の逆変換が bctree->node() である．
  }
  

```


実装は，lowlink を使っています．DFS 木の行きがけ順を表す
`vector<int> _ord` と，back edge を高々1回たどって到達できる点の
`_ord` の値の最小値である `vector<int> _low` を最初に計算し，これらを用いて
橋や関節点の判定をしています．

一応，ソースは[こちら](https://gist.github.com/yamate11/f2b1cdfa626fbf3308e0e0abbc76a226)にあります．



## 参考サイト

けむさんの [二重連結性と lowlink の話](https://kntychance.hatenablog.jp/entry/2022/09/16/161858) がたいへん参考になりました．お礼申し上げます．
