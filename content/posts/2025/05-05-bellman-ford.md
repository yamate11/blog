---
author: "yamate11"
title: "Bellman-Ford, 牛ゲーライブラリ"
date: "2025-05-05T09:58:16+09:00"
# date_init: "2025-05-05"
tags: ["Bellman-Ford", "牛ゲー"]
categories: ["topic"]
# categories: ["solution"]
# summary: "要約を書いておく．ここには問題タイトル等は不要" 
---

この組合せで適切かどうか分からないが，こう作った．

[ライブラリソース](https://github.com/yamate11/compprog-clib/blob/master/bellmanford.cc)

## 解ける問題

### Bellman-Ford アルゴリズム

重み付き有向グラフで，特定の点からすべての点への距離 (パスの重みの和の最小値) を求める．
重みは負でも良い．負閉路があると距離が定義できない ($-\infty$ になる) が，このアルゴリズムはその検出ができる．
計算量は，頂点数 $N$，辺数 $M$ として，$O(NM)$．

### 牛ゲー

次の制約問題を解く．

> 変数 $x_i$ ($i = 1, \ldots, n$) に関し，次の制約の下で，$x_n - x_1$ の最大値 (または最小値) を求めよ．
> * $x_{A_j} - x_{B_j} \leq C_j$   $\quad(j = 1, \ldots, m)$

$C_j$ は負でも良い．移項すれば良いので，$x_{A_j} - x_{B_j} \geq C_j$ という制約でも良い．

この問題で，求める最大値は，「重み $C_j$ の有向辺 $(A_j, B_j)$ を持つグラフで，$1$ から $N$ への距離」になる
([参考リンク](https://qiita.com/tanabe13f/items/6c723c29a121de760790))．
次が対応する．
* 制約を満たせないことと，グラフが負閉路を持つこと
* いくらでも大きな値を取れることと，グラフで$1$から$N$に到達できないこと

最小値バージョンは，同じ制約の下で $x_1 - x_n$ の最大値を求めて符号を反転すれば良い．

## 使用法

### Bellman-Ford

辺の重みの総和は，$10^{18}$ 未満であること．

```cpp
  BellmanFord bf(3);      // 頂点数3
  bf.add_edge(0, 1,  5);  // 頂点0から1への重み5の辺
  ...
  bool b = bf.run(0);     // 頂点0を始点としてアルゴリズムの実行
  if (b) cout << "distance (0,2) is " << bf.dist[2] << endl;
  else cout << "Negative loop detected." << endl;
```

上のように実行する．
負閉路があるときには，`run()` は false を返す．
負閉路がないときには，true が返り，
距離は，オブジェクトの dist メンバ (型は `vector<ll>`) に格納されている．
到達できない点には $10^{18}$ 以上の値が設定される．

### 牛ゲー

```cpp
  UshiGame ug(3);               // 変数の数は3
  // 制約．add_constr*(from, to, lim) ... from を基準とした to の値の制約が val
  ug.add_constrLE(0, 1, 5);     // x[1] - x[0] <= 5
  ug.add_constrGE(1, 2, -4);    // x[2] - x[1] >= -4
  ...
  auto res = ug.getmax(0, 2);  // x[2] - x[0] を最大化する
  if (not res) cout << "infeasible\n";
  else if (*res >= (ll)1e18) cout << "unlimited\n";
  else cout << *res << endl;
```

* 変数の数をコンストラクタの引数にして