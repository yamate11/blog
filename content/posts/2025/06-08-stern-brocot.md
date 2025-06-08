---
author: "yamate11"
title: "Stern Brocot Tree (連分数)"
date: "2025-06-08T23:26:34+09:00"
# date_init: "2025-06-08"
tags: []
categories: ["topic"]
# categories: ["solution"]
# summary: "要約を書いておく．ここには問題タイトル等は不要" 
---

## 概要

Stern Brocot Tree を扱うライブラリを書いた．

## Stern Brocot Tree

連分数

$$
a_0 + \cfrac{1}{a_1 + \cfrac{1}{\ddots a_{n - 1} + \cfrac{1}{a_n}}}
$$

を，$[a_0, a_1, \dots, a_n]$ と書く．各 $a_i$ は，非負整数．

$x + 1 = x + \cfrac{1}{1}$ だから，$[a_0, a_1, \dots, a_n]$ と $[a_0, a_1, \dots, a_n - 1, 1]$ は同じ数を表す．
これを除くと表現は一意になる．そこで，$[a_0, a_1, \dots, a_n]$ の表現では，$a_n \neq 1$ と約束する．
例外として，$1$ は，$[1]$ で表現する．

連分数 $\alpha = [a_0, a_1, \dots, a_n]$ に対して，
$u(\alpha) = [a_0, a_1, \dots, a_n + 1]$ と，
$v(\alpha) = [a_0, a_1, \dots, a_n - 1, 2]$
を考える．これは，連分数最後のパートが

$$\cfrac{1}{a_n} = \cfrac{1}{ (a_n - 1) + \cfrac{1}{1} }$$

になっている ($a_n > 1$ に注意) ところ，片方は $a_n - 1$ を 1 増やして，もう片方は右端分母の $1$ を 1増やしたもの
と考えられる．したがって
$ [a_n - 1, 2] < [a_n] < [a_n + 1] $
であるので，$n$ が偶数のときには，

$$ v(\alpha) < \alpha < u(\alpha) $$

となり，$n$ が偶数のときには

$$ u(\alpha) < \alpha < v(\alpha) $$

となる．$1 = [1]$ を root として，$\alpha$ の子供として $u(\alpha)$ と $v(\alpha)$ をとる無限完全二分木を，
Stern Brocot Tree と呼ぶ．

* すべての正の有理数 $\alpha$ は，Stern Brocot Tree に，ただ一度だけ現れる．
* $\alpha$ を頂点とする部分木に現れる有理数の全体 $I(\alpha)$ は開区間をなす．
  * $I(1) = (0, \infty)$
  * $u(\alpha)$, $v(\alpha)$ のうち，小さい方を $\text{lo}(\alpha)$, 大きい方を $\text{hi}(\alpha)$ と書くと，
    $I(\alpha) = (\beta, \gamma)$ のとき，$I(\text{lo}(\alpha)) = (\beta, \alpha)$，
    $I(\text{hi}(\alpha)) = (\alpha, \gamma)$．
* 連分数 $[a_0, a_1, \dots, a_n]$ のノードの深さは，$\sum_i a_i - 1$．
* 既約分数 $a/b$ の親ノードが既約分数 $c/d$ であれば，$b > d$．(整数 $m$ は，$m/1$ と書くと解する)

<img src="fig01.jpg">

## ライブラリ

SternBrocotNode という構造体を作った．オブジェクトは，Stern Brocot Tree のノードを表す．

### 使用例

```cpp
SternBrocotNode n1(3, 5);           // 3/5
SternBrocotNode n2{{0, 1, 1, 2}};   // [0, 1, 1, 2]
SternBrocotNode n3;                 // 1
assert(n1 == n2);     // 等価判定
assert(n1 < n3);      // 大小比較
n3.set(5, 2);         // 設定
...
```

### インタフェース

#### メンバ

```cpp
vector<ll> coeff;
```
係数ベクトル．$[a_0, a_1, \ldots, a_n]$ を保持する．

#### コンストラクタと値の設定

```cpp
  SternBrocotNode()       // 1が設定される．
  SternBrocotNode(const vector<ll> coeff_)   // 引数の係数行列が設定される
  SternBrocotNode(ll a, ll b)      // a/b が設定される．
  SternBrocotNode& set(const vector<ll> coeff_)   // オブジェクトの値が変更される
  SternBrocotNode& set(ll a, ll b)        // オブジェクトの値が変更される
```

#### 比較

等価の比較 (`==`, `!=`) と，大小の比較 (`<`, `>`, `<=`, `>=`) ができる．

1 かどうかは， メンバ関数 `is_root()` で判定できる．

#### 既約分数としての値

```cpp
  pair<ll, ll> numden() const
```

分子，分母のペアが返る．変な名前の関数だが，numerator と denominator がこの順でペアにされている．
使用例:

```cpp
  SternBrocotNode n1 = ...;
  auto [p, q] = n1.numden();
  cout << "The value is " << p << " / " << q << "\n";
```

#### 深さ

```cpp
  ll depth() const  // ルート(1) の深さは 0．
```

#### 親子関係

```cpp
  SternBrocotNode parent() const 
  SternBrocotNode big_step_parent() const 
  SternBrocotNode child_lo() const
  SternBrocotNode child_hi() const
```

`parent()` は，普通の木としての親ノード．
`big_step_parent()` は，「折れ曲がらない」間，親をたどって行き着いた先．
正確には，自分の先祖のうち，$[a_0, a_1, \dots, a_n]$ の表記による長さが自分より短くなるもののうち，
もっとも深い位置にあるもの．ただし，自分の長さが$1$のときには，$[1]$ とする．
ルート ($[1]$) に対しては，`parent()` と `big_step_parent()` は実行できない (エラーになる)．

`child_lo()`，`child_hi()` は，上の説明にある $\text{lo}(\alpha)$, $\text{hi}(\alpha)$ を返す．

「root に到達するまで parent() をとり続ける」みたいなことを，
`SternBrocotNode{{(ll)1e18}}` に対してうっかり行ったりすると，すぐ TLE する．
big_step_parent をうまく使えないか考える．

#### 深さ k の先祖

```cpp
  SternBrocotNode ancestor(ll k) const 
```

深さ k の位置にある先祖を返す．自分の深さが k なら自分を返す．
自分の深さが k より小さいときにはエラーになる．

#### LCA

```cpp
  SternBrocotNode lca(const SternBrocotNode& o) const
  static SternBrocotNode lca(const SternBrocotNode& n1, const SternBrocotNode& n2)
```

LCAを返す．

#### 部分木区間

```cpp
  pair<optional<SternBrocotNode>, optional<SternBrocotNode>> range() const
```

上の説明にある $I(\alpha) = (x, y)$ であるとき，x, y のペアを返す．
区間が $(0, \cdot)$ や $(\cdot, \infty)$ になるときには，SternBrocotNode オブジェクトでは
表現できないので，戻り値は `optional<StrenBrocotNode>` のペアにしてあり，これらのケースでは `nullopt` が返る．

使用例:

```cpp
  SternBrocotNode n1 = ...;
  const auto& [p, q] = n1.range();
  /* p や q を後で変更したいのであれば:
      auto tmp = n1.range();
      auto& [p, q] = tmp;
  */
  string p0, q0;
  if (p) {   // p が nullopt でない
    auto [a, b] = p->numden();    // *p が SternBrocotNode オブジェクトになる
    p0 = to_string(a) + " / " + to_string(b);
  }else {    // p は nullopt
    p0 = "zero";
  }
  if (q) {
    auto [a, b] = q->numden();
    q0 = to_string(a) + " / " + to_string(b);
  }else {
    q0 = "infty";
  }
```

### 実装

いくつか試した後，結局，係数ベクトルだけを持つことにした．

もっとチューンすれば速くなるところはある．たとえば，depth を持つとか，
$[a0, ..., an + (x/y)]$ を $(px + qy) / (rx + sy)$ と表す $(p, q, r, s)$ を持つようにすれば，
毎度係数行列を全部なめて denom, numer を計算しなくてもすむようになりそう．でも，コードが面倒．

