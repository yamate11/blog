---
author: "yamate11"
title: "木ライブラリ"
date: "2026-05-23"
date_init: "2024-03-13"
tags: ["木"]
categories: ["topic"]
# categories: ["solution"]
# summary: "要約を書いておく．ここには問題タイトル等は不要" 
---

自分用の木のライブラリのメモです．ソースは[こちら](https://github.com/yamate11/compprog-clib/blob/master/tree.cc)．

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
ll add_edge(ll x, ll y);
```

### データメンバ (public相当のもの)

```cpp
ll numNodes;   ... ノードの数
ll root;       ... 根
```

他に，`vector<vector<pe_t>> _nbr` があり，隣接ノード情報を格納している．
型 `pe_t` は，隣接ノード番号と辺の番号を持つ．
配列 `_nbr[nd]` に，`nd` の隣接ノード情報が格納されているわけだが，
`nd != root` のときには，`_nbr[nd].back()` に親が格納されている．
また，HL 分解を行うと，`_nbr[nd][0]` に，heavy child/edge が格納されるようになる．

### メンバ関数

#### 親子関係

```cpp
ll num_children(ll nd)
ll parent(ll nd)
ll child(ll nd, ll idx)
auto children(ll nd)
auto neighbor(ll nd)
pe_t parent_pe(ll nd)
pe_t child_pe(ll nd, ll idx)
auto children_pe(ll nd)
auto neighbor_pe(ll nd)
```

* `tr.num_children(nd)` は，ノード nd の子供の数を返す．
* `tr.parent(nd) は，nd の親のノードを返す．root の parent は -1．
* `tr.child(nd, idx)` は，ノード nd の idx 番目の子供を帰す．idx は，0 以上 tr.num_children(nd) 以下．
* `tr.children(nd)` は，nd の子供の集まりへの view を返す．したがって，次のような使い方ができる:
  * `for (ll c : tr.children(nd) { ... }`
* `tr.children(nd)` は，nd の子供と親の集まりへの view を返す．
* 構造体 `pe_t` は，ll 型のメンバ `peer` と `edge` を持つ．
  * `peer` ... ノード
  * `edge` ... 辺の番号
* `tr.parent_pe(nd)` は，nd の親と，nd からその親への辺の番号を返す．
* `tr.child_pe(nd, idx)` は，nd の idx 番目の子供と，nd からその子供への辺の番号を返す．
* `tr.parent_pe(nd).peer == tr.parent(nd)` などが成り立つ．
* `tr.children_pe(nd)` は，nd の子供に対する pe_t 構造体を渡る view を返す．
  次のように使える:
  * `for (auto [cld_nd, cld_edge] : tr.children_pe(nd)) { ... }`
  * `for (const pe_t& pe : tr.children_pe(nd)) { ... pe.peer ... pe.edge ... }`
* `tr.neighbor_pe(nd)` は，nd の子供と親に対する pe_t 構造体を渡る view を返す．

#### 辺とノードの対応

```cpp
ll edge_idx(ll x, ll y)
pair<ll, ll> nodes_of_edge(ll e, ll mode = 0)
```

* `tr.edge_idx(x, y)` は，ノード x と y を結ぶ辺の番号を返す．
そのような辺が存在しないときには -1 を返す．`tr.edge_idx(x, y)` と `tr.edge_idx(y, x)` の値は等しい．
実装は，「x の親が y」か「y の親が x」になっているかどうかを調べている．
* `tr.nodes_of_edge(e, mode)` は，番号が e である辺の両端のノードのペアを返す．
    * mode == 0 (デフォルト) のとき: 第 1 要素が親，第 2 要素が子
    * mode == 1 のとき: 第 1 要素が子，第 2 要素が親
    * mode == -1 のとき: 第 1 要素は第 2 要素より小さい．

  向き (0/1) を dir に入れておけば，`auto [src, dest] = tr.nodes_of_edge(e, dir)` のように使える．


#### 深さ，部分木のサイズ

```cpp
ll depth(ll nd)
ll stsize(ll nd)
```

* `tr.depth(nd)` は，nd の深さを返す．rootの深さは 0 である．
* `tr.stsize(nd)` は，nd を頂点とする部分木のノード数を返す．nd が root のときには，`tr.numNodes` と同じ値になる．

#### オイラーツアー

```cpp
ll euler_in(ll nd)
ll euler_out(ll nd)
tuple<ll, ll, ll> euler_elem(ll idx)
  // 以下の関数で，euler_elem(idx) の3要素それぞれが取得できる
  ll euler_elem_edge(ll idx)
  ll euler_elem_from(ll idx)
  ll euler_elem_to(ll idx) 
```

* オイラーツアーは，辺を DFS の順に辿ったものである．
  * ただし，最初 (0番目) と最後  ($2 \times \text{numNodes} - 1$ 番目) は，
    仮想的な点と root を結ぶ仮想的な辺を，それぞれ root に向かって，root から 辿るものとする．
  * 仮想的な辺を含めると辺の数は numNodes となる．仮想的な辺の番号は，numNodes - 1 とする．
    各辺が2回ずつ辿られるので，辿られる回数は ($2 \times \text{numNodes}$) である．
* `[e, x, y] = tr.euler_elem(k)` とすると，k 番目にたどられる辺は x と y を結ぶ番号 e のものであり，
  x から y の方向に辿られる．
  e, x, y それぞれは，`tr.euler_elem_edge(k)`, `tr.euler_elem_from(k)`, `tr.euler_elem_to(k)` で
  取得できる．
* ノード `nd` とその親 `p` を結ぶ辺は，`tr.euler_in(nd)` 番目に，p から nd 方向に辿られ，
  `tr.euler_out(nd)` 番目に，nd から p 方向に辿られる．

#### HL分解

`heavy_head()` や `hl_path()` を呼ぶと HL 分解が行われる．
具体的には，配列 `_nbr[nd]` の順序が入れ替わって，`_nbr[hd][0]` に heavy edge が来るようになる．
したがって，オイラーツアーと併用するときには，HL分解を先に実施しなければならない．
逆順になってしまったときにはエラーが報告される．

Tree の3番目のコンストラクタ引数が `use_hl_decomp` という bool 型のものになっている．
これに true を与えると，親子の決定などの直後に HL 分解が行われるので安全．
もしくは，`add_edge()` が終わったところで `tr._set_heavy()` を呼んでも良い．

```cpp
ll heavy_head(ll nd)
```

heavy edge のみを通って到達できるもっとも低い先祖を返す．
nd = root のときや，nd の親との辺が light edge のときには，nd 自身を返す．

```cpp
vector<pair<ll, ll>> hl_path(ll x, ll y)
```

x から y へのパスを構成するオイラーツアーの添字区間列を返す．より正確には以下の通り

* x = y のときには，空ベクトルが返される．
* そうでないとき．x と y の LCA を a とする．
  * `vector<pair<ll, ll>> vx` を次のように構成する:
    * x = a のときには，空ベクトル
    * そうでないときには，a から x へのパス上の各辺 (下向き) を，オイラーツアー添字の半開区間 $[s_i, e_i)$ に分割し，これらを全部集めたものを vx とする．(各半開区間は，light edge の後ろに 0 個以上の heavy edge が続く．ただし，先頭の半開区間だけは，light edge がないかもしれない．半開区間の数は $\log(\textrm{numNodes})$ 以下．
  * `vector<pair<ll, ll>> vy` も同様に構成する．
  * vx と vy を連結したものを返す．(vx と vy のうち，小さい添字を格納しているものを先にする)

典型的な使用法は以下のようになる (のではないかと思う):

```cpp
  Tree tr(N, 0, true);  // 第3引数を true にしておくと安全
  ...
  // オイラーツアーに合わせてサイズ 2*N のセグメント木を作る
  vector<T> data_init(2 * N, ....);
  st = make_seg_tree_lazy( ...., data_init);
  ...
  REP(_q, 0, Q) { // クエリ処理
    ...
    else if (...) {  // パス u-v に関する更新
      ll u, v; cin >> u >> v; u--; v--;   
      for (auto [l, r] : tr.hl_path(u, v)) {
        st.update(l, r, ...);  // 区間 [l, r) を更新
      }
    ...
    else if (...) {  // ノード nd に関する問合せ
      ll nd; cin >> nd; nd--;
      // ノード nd に関して，その親との間の辺を見れば良いのだったら
      ll e_idx = tr.euler_in(nd);
      ... st.at(e_idx) ...
  }
```



#### LCA

```cpp
ll lca(ll x, ll y)
```

ノード x と y の Lowest Common Ancestor を返す．

実装: x と y から親をたどって，ただし，heavy edge ではheavy headまで跳んで，みつけている．

#### 深さ d の位置の先祖

```cpp
ll ancestor_at_depth(ll x, ll dp)
```

深さ d の位置の先祖を返す．lca と同じように heavy head を使っている．

#### 2ノード間のパス

```cpp
vector<ll> nnpath(ll x, ll y)
```

ノード x から y への経路を返す．`path = tr.nnpath(x, y)` とすると，
`path` は `vector<ll>` 型で，`path[0]` は x に等しく，`path.back() は y に等しく，
`path[i]` と `path[i + 1]` の間には辺がある．

#### 直径

```cpp
tuple<ll, ll, ll, ll, ll> diameter()
```

`[diam, nd0, nd1, ct0, ct1] = tr.diameter()` とすると，
* diam は，直径．すなわち，もっとも長いパスに含まれる辺の数．すなわち，
  もっとも長いパスに含まれるノードの数から 1 を引いたもの
* nd0 と nd1 は，距離が直径に等しいような2ノード．
* ct0 と ct1 は，nd0 と nd1 を結ぶ経路の中央のノード．
  直径が偶数の時，ct0 と ct1 は等しい．
  直径が奇数の時，ct0 が nd0 寄り，ct1 が nd1 寄り．

#### 重心

重心とは，その頂点を根にしたときに，すべての隣接頂点の部分木サイズが全頂点数の半分以下である頂点のこと．
木には重心が 1点または2点存在する．

```cpp
pair<ll, ll> centroids()
```

`[a, b] = tr.centroids()` とすると，
* 重心が1点の時には，a に重心ノード番号が，b には -1 が設定される．
* 重心が2点の時には，a, b に重心ノード番号が設定される．


#### 根の変更

```cpp
void change_root(ll newRoot)
```

根を newRoot に変更する．

### 全方位木 (rerooting)

[別記事](http://localhost:5080/blog/posts/2022/08-17-rerooting/) 参照



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

## 3. ノードが 0..N-1 でないとき

座標圧縮を使うのが便利．次のような感じ:

```cpp
  vector<pll> es; // {(20, 42319), (42319, 35), (20, 6612)} のように辺が入っているとする．
  CoordCompr cc;
  for (auto [u, v] : es) { cc.add(u); cc.add(v); }
  Tree tr(cc.size());  // 必要なら tr(cc.size(), cc.c(root)); など．
  for (auto [u, v] : es) { tr.add_edge(cc.c(u), cc.c(v)); }
  // たとえば，nd の子供をプリントするなら:
  for (ll cld : tr.children(cc.c(nd))) cout << cc.d(cld) << "\n";

```


## 4. 非再帰 DFS

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
