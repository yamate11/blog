---
author: "yamate11"
title: "Cartesian Tree"
date: "2026-06-23"
date_init: "2025-09-09"
tags: []
categories: ["topic"]
# categories: ["solution"]
summary: "Cartesian Tree のライブラリ"
---

Cartesian Tree のライブラリを書いた．

## 使用法

```cpp
    vector<ll> vec{80, 90, 20, 50, 50, 40}
    auto ct = make_cartesian_tree(vec);
    assert(ct.root == 2);     // vec[2] is the least element
    assert(ct.left[2] == 0);  // least in vec[0:2] is vec[0]
    assert(ct.left[0] == -1); // "no such element" is expressed by -1
    assert(ct.right[2] == 5);
    assert(ct.left[5] == 3 or ct.left[5] == 4);  // either of the tied elements can be chosen

    auto ct2 = make_cartesian_tree(vec, greater<ll>()); // root = idx of greatest element
    auto ct3 = make_cartesian_tree(vec, comp);
                // comp is (const T&, const T&) -> bool, where T is the value type fo vec
    auto ct4 = make_cartesian_tree_comp_index(vec, comp); //
                // comp is (int i, int j) -> bool.  Convenient for specifying tie break.
```

## 定義

要素がすべて異なる列 $A = (a_1, \ldots, a_n)$ に対して，$A$ の Cartesian Tree $T$ は，
次のように構成される二分木である．

* $T$ のノードは，$1, 2, \dots, n$ である．
* 区間 $[a, b]$ に対する 部分木 $T'$ を，次のように定義する．
  * 空区間 に対する $T'$ は，空である．
  * $T'$ の根は，$[a, b]$ における $A$ の最小値を与える要素 $r$ である．
  * $[a, r - 1]$ に対する木の根を $p$, $[r + 1, b]$ に対する木の根を $q$ とするとき，
    $r$ の左の子は $p$ であり, $r$ の右の子は $q$ である．
* 区間 $[1, n]$ に対する $T'$ を $T$ とする．
  
要素がかならずしもすべて異ならない列に対しても，値が等しい要素に適当に序列を付けて，
Cartesian Tree を考えることとする．
このライブラリの実装では，右側 (番号が大きい方) の要素が小さいものとして扱っている．

小さい順でなく大きい順にしたり，タイブレークを明示したりすることもできる．下記参照．

## オブジェクトの作成

構造体名は CartesianTree であるが，通常は，作成関数 make_cartesian_tree を利用するのが便利．
普通は，ベクトルなどを引数として与える．

```cpp
vector<ll> vec{80, 90, 20, 50, 50, 40};        
auto ct0 = make_cartesian_tree(vec);
```

第2引数に比較関数を与えることができる．

```cpp
auto ct1 = make_cartesian_tree(vec, greater<ll>());
auto ct2 = make_cartesian_tree(vec, [](ll a, ll b) { return a > b; });
```

上の作成関数で指定する比較関数の引数は，ベクトルなどの value_type であるが，
添字を引数にしたい場合には，作成関数 make_cartesian_tree_comp_index を用いる．

```cpp
auto ct3 = make_cartesian_tree_comp_index(vec, [](ll i, ll j) -> {
             if (vec[i] != vec[j]) return vec[i] < vec[j];
             else return i < j;
           });
```

上の例では，値が等しいときには左側を優先して取るようにしている．

配列などを作成するときのために，引数のないコンストラクタもある．
その場合には，メンバ関数 build() でベクトルなどを与える．
以下のテンプレート引数を明示的に設定する必要があるかもしれない:

* `typename Ctn`: データとして与えるコンテナの型．`vector<ll>` など．
* `typename Comp`: 比較関数の型．デフォルトは `less<typename Ctn::value_type>`
* `bool comp_arg_index`: 比較関数の引数が `typename Ctn::value_type` であるか (`false`) 添字型 (`ll` など) であるか (`true`)．デフォルトは `false`

```cpp
vector<CartesianTree<vector<ll>, greater<ll>, false>> ct(10);
for (ll i = 0; i < 10; i++) ct[i].build(vec[i], greater<ll>());
```

## メンバ

### 根

根は，メンバ root でアクセスする．

```cpp
cout << ct0.root << endl;  // 2
```

### 子

左の子と右の子は，vector 型のメンバ left と right に格納されている．

```cpp
cout << ct0.left[2]  << endl; // 0
cout << ct0.right[2] << endl; // 5
```

* 子供が無いときには，left や right には $-1$ が格納される．

### 親

親は vector 型のメンバ parent に格納されている．

```cpp
cout << ct0.parent[0] << " " << ct0.parent[5] << endl; // 2 2
```

* `parent[root]` の値は -1 である．

## スタック処理との関係

スタックを使って 最小値/最大値 を処理していくようなコードは，Cartesian Tree を使うと簡潔になることが多いと思う．
実際，H に関する Cartesian Tree を構築するときに使用しているスタックについて，添字 i を処理したときの値が
st = (s[0], s[1], ..., s[k]) (s[k] = i) であるとする．
これは，i = s[k] から始めて，i' < i; H[i'] < H[i] となる最大の i' = s[k - 1] を順にとっていくものになっているので，
できあがった Cartesian Tree で，根に向かうパスで，右の枝を辿るときの親を並べると得られる．

## 例

#### ABC189 C - Mandarin Orange

よくある「ヒストグラムにおさまる最大の四角形」を求める問題

```cpp
  // vector A に問題を読み込む．
  CartesianTree ct(A);
  ll ans = 0;
  auto f = [&](auto rF, ll lo, ll hi, ll x) -> void {
    if (x < 0) return;
    updMax(ans, (hi - lo) * A[x]);
    rF(rF, lo,    x,  ct.left[x]);
    rF(rF, x + 1, hi, ct.right[x]);
  };
  f(f, 0, N, ct.root);
  cout << ans << endl;
```

#### 自分より大きい，もっとも近くにある要素

配列 H[0], ..., H[N - 1] の各添字 i について，l < i < r，H[l] > H[i] < H[r] であって，j = l + 1, .., i - 1, i + 1, .., r - 1 については，H[j] <= H[i] であるような l =: L[i], r =: R[i]  を求める．(無いときには -1 と N)．

Cartesian Tree を 逆順 (greater<ll>() を指定する) に作っておく．
* H に同じ値がないときには簡単．
  * L[ct.root] = -1, R[ct.root] = N．
  * L[ct.left[i]] = L[i], R[ct.left[i]] = i, L[ct.right[i]] = i, R[ct.right[i]] = R[i]．

* H に同じ値がありうる場合．L と R を別々に求める．
  * L を求めるときには，比較関数を「H が等しい時には右 (添字の大きい方) を優先」にする．
  * R を求めるときには，比較関数を「H が等しい時には左 (添字の小さい方) を優先」にする．




keywords: stack histogram
