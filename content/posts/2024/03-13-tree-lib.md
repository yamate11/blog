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

#### メンバ

```cpp
int numNodes;   ... ノードの数
int root;       ... 根
vector<nbr_t> _nbr ... 後述
```




## 2. 実装

* N - 1 本目の辺が追加されたとき (N = 1 なら，コンストラクタで) 親子のアクセスに必要な設定を行っている．
  change_root() が呼ばれたときには，ご破算になる．
* stsize, depth, euler_* は，始めて該当する関数が呼ばれるときに、必要なデータを作成する．
* いくつかの箇所で，非再帰で DFS を行っている．
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
