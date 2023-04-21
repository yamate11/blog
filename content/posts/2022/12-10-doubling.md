---
author: "yamate11"
title: "ダブリングライブラリ"
date: "2022-12-10T09:33:05+09:00"
# date_init: "2022-12-10"
tags: ["ダブリング"]
categories: ["topic"]
# categories: ["solution"]
# summary: "要約を書いておく．ここには問題タイトル等は不要" 
---

<!-- タイトルはキーワードがインデックスされないかもしれないので，
     ここに書いておく -->
<!-- AtCoder *** Contest xxx - A*C xxx F - 問題タイトル の解法です．-->

ダブリングを行うライブラリを書きました．自分用のメモです．

## できること

### その1

$f : [0, N) \to [0, N)$ が与えられた時，
$f^{r}(i)$ を，$r \in [0, R]$ と $i \in [0, N)$ に対して計算する．

典型的には:

* $N$ は $10^5$ くらい，$R$ は $10^{18}$ くらい，または
* $N$ も $R$ も $10^5$ くらいだが，何回も (たとえば $10^5$回くらい)
  計算する

### その2

上の $f$ の他に，モノイド $(M, \oplus)$ と $m: [0, N) \to M$ が与えられて，
$r, i$ に対して
$\bigoplus_{k = 0}^{r} m(f^{k}(i))$ を計算する．

## 使用例

### その1

```cpp
ll R = 100000, N = 100000;
auto f = [&](ll i) -> ll { return i * i % N; };
DoublingFRel d(R, N, f);
ll r = 12345, i = 54321;
cout << d.val(r, i) << endl;         // f^{r}(i)
```

内部テーブルには，$f^{r}(i)$ が，$i \in [0, N)$ と
$r = 1, 2, 4, 8, \ldots$ に対して
格納されている．

### その2

```cpp
struct M {
  ll v;
  M(ll v_ = LLONG_MIN) v(v_) {}
  M operator+(const M& o) const { return M(max(v, o.v)); }
};

ll R = 100000, N = 100000;
auto f = [&](ll i) -> ll { return i * i % N; };
auto m = [&](ll i) -> M { return M(i * i * i); };

DoublingFRel d1(R, N, f);
DoublingCum<M> d2(d1, m);
ll r = 12345, i = 54321;
cout << d2.val(r, i);  // \sum { m( f^{(j)}(i) ) | j = 0, 1, ..., r-1 }

```

内部テーブルには，
$m( f^{r}(i) )$ が，$i \in [0, N)$ と
$r = 1, 2, 4, 8, \ldots$ に対して格納されている．

普通の和を計算するのなら，struct M を定義する必要はない．
ただし，`DoublingCum<ll>` のように，テンプレートパラメタを明示的に
与える必要がある．


keywords: doubling


