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

ダブリングを行うライブラリを書きました．ソースは[こちら](https://github.com/yamate11/compprog-clib/blob/master/doubling.cc)．

## できること

### その1

$f : [0, N) \to [0, N)$ が与えられた時，
$r \in [0, R]$ と $i \in [0, N)$ に対して
$f^{r}(i)$ を
計算する．

典型的には:

* $N$ は $10^5$ くらい，$R$ は $10^{18}$ くらい，または
* $N$ も $R$ も $10^5$ くらいだが，何回も (たとえば $10^5$回くらい)
  計算する

### その2

上の $f$ の他に，モノイド $(M, \oplus)$ と $m: [0, N) \to M$ が与えられて，
$r, i$ に対して
$\bigoplus_{k = 0}^{r - 1} m(f^{k}(i))$ を計算する．

## 使用法

### その1

* `DoublingFRel` オブジェクト `d` を作る．
  * 上記 $R$，$N$，$f$ を `doubling_from_func` に与える．
    ```cpp
    ll R = 100000, N = 100000;
    auto f = [&](ll i) -> ll { return (i * i) % N; };
    auto d = doubling_from_func(R, N, f);
    ```
  * 関数 $f$ の代わりにベクトルなどのコンテナを与えたいときには，`doubling_from_container` を用いる．
    ```cpp
    ll R = 100000, N = 100000;
    vector<ll> vec(N);
    REP(i, 0, N) vec[i] = ...;
    auto d = doubling_from_container(R, N, vec);
    ```  
* 値 $f^r(i)$ は，`d.val(r, i)` で取得できる．
  ```cpp
  ll r = 12345, i = 54321;
  cout << d.val(r, i) << endl;
  ```

なお，内部テーブルには，$f^{r}(i)$ が，$i \in [0, N)$ と
$r = 1, 2, 4, 8, \ldots$ に対して
格納されている．

### その2

* `DoublingCum` オブジェクト `dc` を作る．
  * マッピング $m$ を関数で指定するときには，`doubling_cum_from_func` を用いる．
    * モノイド $M$ を，テンプレートパラメタとして指定する．
    * 第1パラメタには，「その1」で説明した `DoublingFRel` オブジェクトを指定する．
    * 第2パラメタには，マッピング $m$ を指定する．
    ```cpp
    ll R = 100000, N = 100000;
    auto f = [&](ll i) -> ll { return i * i % N; };
    auto d1 = doubling_from_func(R, N, f);

    struct M {
      ll v;
      M(ll v_ = LLONG_MIN) v(v_) {}
      M operator+(const M& o) const { return M(max(v, o.v)); }
    };
    auto m = [&](ll i) -> M { return M(i * i * i); };
    auto dc = doubling_cum_from_func(d1, m);
    ```
  * マッピング $m$ をベクトルなどのコンテナで指定したいときには，`doubling_cum_from_container` を用いる．
    ```cpp
    vector<ll> vec_m(N); ...;
    auto dc = doubling_cum_from_container(d1, vec_m);
    ```
  * モノイド演算について，単位元が `T()` でなかったり，演算が `plus<T>()` でない場合には，
    `doubling_cum_from_*` の第3, 4 パラメタで，単位元と演算を指定する．
    ```cpp
    auto m = [&](ll i) -> ll { return i * i * i; };
    auto mymax = [](ll a, ll b) { return max(a, b); };
    auto dc = doubling_cum_from_func(d1, m, LLONG_MIN, mymax);
    ```
* 値 $\bigoplus_{k = 0}^{r - 1} m(f^{k}(i))$ は，`dc.val(r, i)` で取得できる．
  ```cpp
  ll r = 12345, i = 54321;
  cout << dc.val(r, i) << endl;
  ```

なお，内部テーブルには，
$m( f^{r}(i) )$ が，$i \in [0, N)$ と
$r = 1, 2, 4, 8, \ldots$ に対して格納されている．



keywords: doubling


