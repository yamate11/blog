---
author: "yamate11"
title: "木ライブラリ"
date: "2024-03-13T13:41:23+09:00"
# date_init: "2024-03-13"
tags: ["木"]
categories: ["topic"]
# categories: ["solution"]
# summary: "要約を書いておく．ここには問題タイトル等は不要" 
---

自分用の木のライブラリのメモです．

## 1. 典型的な使用法

```cpp
ll N; cin >> N;
Tree tr(N, root);     // ノード数 N, 根は root．
vector weight(N - 1, 0LL);
REP(i, 0, N - 1) {
  ll a, b, w; cin >> a >> b >> w; a--; b--;    // 0-indexed.
  ll e = tr.add_edge(u, v);
  weight[e] = w;
}
auto dfs = [&](auto rF, ll nd) -> void {
  for (ll cld = tr.children(nd)) { ... }
  for (auto [cld, e] = tr.children_pe(nd)) { ... nd ... cld ... weight[e] ... }
};
dfs(dfs, root);
```

辺に関する情報は，辺の番号を添字とするベクトルなどに確保しておくのが良い．
上の weight を参照．

#### 作成

ノード 0, 1, ..., N-1 の木で，根が root のオブジェクトをつくる．
root は省略可で，その場合は 0 が根になる．

```cpp
Tree tr(N, root);
```

次のメンバ関数を N - 1 回呼んで辺を定義する．N - 1 回呼ばれると，内部で使用する値を計算しに行く．
戻り値は，辺のID．(0, 1, 2, ... の順で返る)

```cpp
int add_edge(int x, int y);
```

### データメンバ (public相当のもの)

```cpp
int numNodes;   ... ノードの数
int root;       ... 根
```

* bool 型の static member に，use_stsize, use_depth, use_euler がある．既定値はどれも true.
  false にすると，stsize(), depth(), euler_in(), euler_out() が使えなくなる代わりに多少速いと期待される．
  あまり変わらないと思うが．  

### メンバ関数

#### parent

```cpp
int parent(int nd)
```

親のノードを返す．根の parent は -1．

#### num_children, child, children

```cpp
int num_children(int nd)
int child(int nd, int idx)
auto children(int nd)
```

* `tr.num_children(nd)` は，ノード nd の子供の数を返す．
* `tr.child(nd, idx)` は，ノード nd の idx 番目の子供を帰す．idx は，0 以上 tr.num_children(nd) 以下．
* `tr.children(nd)` は，nd の子供を渡るイタレータを返す．したがって，次のような使い方ができる:
  * `for (int c : tr.children(nd) { ... }`

#### parent_pe, child_pe, children_pe, child_edge, children_pe

```cpp
pe_t parent_pe(int nd)
pe_t child_pe(int nd, int idx)
int child_edge(int nd, int idx)
auto children_pe(int nd)
```

* 構造体 `pe_t` は，int 型のメンバ `peer` と `edge` を持つ．
  * `peer` ... ノード
  * `edge` ... 辺の番号
* `tr.parent_pe(nd)` は，nd の親と，nd からその親への辺の番号を返す．
* `tr.child_pe(nd, idx)` は，nd の idx 番目の子供と，nd からその子供への辺の番号を返す．
* `tr.parent_pe(nd).peer == tr.parent(nd)` などが成り立つ．
* `tr.child_edge(nd, idx)` は，nd から，その idx 番目の子供への辺の番号を返す．
  `tr.child_pe(nd).edge == tr.child_edge(nd)` が成り立つ．
* `tr.children_pe(nd)` は，nd の子供に対する pe_t 構造体を渡るイタレータを返す．
  次のように使える:
  * `for (auto [cld_nd, cld_edge] : tr.children_pe(nd)) { ... }`
  * `for (const pe_t& pe : tr.children_pe(nd)) { ... pe.peer ... pe.edge ... }`

#### edge_idx, nodes_of_edge

```cpp
int edge_idx(int x, int y)
pair<int, int> nodes_of_edges(int e)
```

`tr.edge_idx(x, y)` は，ノード x と y を結ぶ辺の番号を返す．
そのような辺が存在しないときには -1 を返す．`tr.edge_idx(x, y)` と `tr.edge_idx(y, x)` の値は等しい．

`tr.nodes_of_edge(e)` は，番号が e である辺の両端のノードのペアを返す．第 1 要素は第 2 要素より小さい．


#### depth, stsize

```cpp
int depth(int nd)
int stsize(int nd)
```

`tr.depth(nd)` は，nd の深さを返す．rootの深さは 0 である．
`tr.stsize(nd)` は，nd を頂点とする部分木のノード数を返す．nd が root のときには，`tr.numNodes` と同じ値になる．




## 2. 実装

* N - 1 本目の辺が追加されたとき (N = 1 なら，コンストラクタで) 親子のアクセスに必要な設定を行っている．
  change_root() が呼ばれたときには，ご破算になる．
* 親子関係 (方向) について．
  * add_edge では，各ノード nd について，辺でつながっているノードと，辺のIDを，_nbr[nd].pe に格納する．
  * 全部の辺が追加されたら，DFS で，各ノード nd について，「nd の親が格納されている _nbr[nd].pe の添字」
    を，_nbr[nd].parent_idx に格納する．
  * parent(nd) などは，parent_idx を見て値を返す．
  * child(nd, i) などは，i < parent_idx なら _nbr[nd].pe[i] を，そうでなければ _nbr[nd].pe[i + 1] を見る．
    * このために，_nbr[root].parent_idx は，大きな値 (具体的には ssize(_nbr[root].pe)) にしている．
  * 子供の走査は，nbr_iterator というイテレータを定義しておこなっている．これは，はじめから見ていって，
    添字が parent_idx に来ると，そこは飛ばすようになっている．
  * begin() と end() の送信先として，children_view という構造体を定義している．
  * nbr_iterator と children_view は，bool 型の template parameter である get_peer を持っている．
    get_peer が true のときには，子供のノード (peer) を扱う．false のときには，子供のノードと辺のペア
    (pe_t) を扱う．

## 3. 非再帰 DFS

一時，非再帰 DFS で実装していたこともあったが，測定してみるとそれほど速くなるというわけでもないようなので，
やめてしまった．以下の記述は残しておく．

再帰で次のように書く場合を考える:

```cpp
  auto dfs = [&](auto rF, int nd, T param) -> S {
    procA();
    for (int cld : tree.children(nd)) {
      procB();
      S s = rF(rF, cld, new_param);
      procC();
    }
    return procD();
  }
```

非再帰だと，だいたい次のように書くことになる:

```cpp
  vector<S> vec_s(N);    // 返り値は，配列に格納してしまうのが簡便．(スタックに入れることもできる)
  vector<tuple<int, int, T>> stack{{root, -1, param_start}};
                         // スタック．(ノード，子供の添字，パラメタ1, パラメタ2, ....)
  while (not stack.empty()) {
    auto& [nd, cidx, param] = stack.back();  // cidx の値を書き換えるので，auto& としておく
    int cld;
    if (cidx == -1) {
      // スタックに積むときには cidx == -1 としているので，このノードに初めて来たときにこうなる
      procA();
    }else {
      // cidx >= 0 なら，cidx 番目の子供を処理した直後ということになる．
      cld = tree.child(nd, cidx);    // 今処理した子供
      S s = vec_s[cld];              // 返り値が必要なら配列を参照する
      procC();
    }
    cidx++;    // 次に処理する子供の添字
    if (cidx < tree.num_children(nd)) {
      cld = tree.child(nd, cidx);    // 次に処理する子供
      procB();
      stack.emplace_back(cld, -1, new_param);
    }else {
      s[nd] = procD();               // 返り値を配列に
      stack.pop_back();
    }
  }
```
