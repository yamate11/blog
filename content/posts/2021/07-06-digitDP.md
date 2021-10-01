---
author: "yamate11"
title: "桁DPのコーディング"
date_init: "2021-07-06"
date: "2021-10-01"
tags: []
categories: ["topic"]
draft: false
summary: "桁DPのコーディングに関する記事です．N 以下の整数で，ある条件を満たすものを数えます．opt さんの記事をもとにしています．"
---

桁DPのコーディングに関する記事です．
N 以下の整数で，ある条件を満たすものを数えます．

## 参照

以下の[optさんの記事](https://opt-cp.com/digit-dp-implementation/)
をもとにして，少し追加しています:

<div class="iframely-embed"><div class="iframely-responsive" style="height: 140px; padding-bottom: 0;"><a href="https://opt-cp.com/digit-dp-implementation/" data-iframely-url="//cdn.iframe.ly/DwWoXJH"></a></div></div><script async src="//cdn.iframe.ly/embed.js" charset="utf-8"></script>

## コーディングの方針

* 配るDP
* 表の更新を書く行は，ソース上で1箇所にする．
    * その桁に表れうる数 (0..9 とか 0..1 とか) をループで回し，
      「この数を付け加えた時の格納先」を考える
    * 格納先の添字を表す変数を，格納元で初期化して適宜変更する．
* 上位桁を 0-padding した状態で考える．
    * 0以上N以下の数を数えることになる．
    * 次のような場合は，すべてがゼロであることを表すフラグを使って対応する．
      * 「左端の桁」の概念が出てくる
      * 0以上ではなく，1以上を数える

```cpp
#define REP(i, x) for (ll i = 0; i < (x); i++)

// N は各桁数値のベクトルで表現．ds[0] が最上位桁．
// 問題文の都合で string にしても良い．
vector<ll>& ds;

// DP表 tbl[eq][az][p1][p2]...
//   eq: 上限値に等しいかどうかを表すフラグ
//   az: 全部の桁がゼロ (all zero) かどうかを表すフラグ
//           p1やp2の計算に使わなければ省略して良い
//           「最上位桁」を特別に扱う場合などに必要
//   p1,p2... : 考えるべき性質 (問題に応じて変わる)
vector tbl_init(2, vector(2, vector(??, vector(??, 0LL))));
auto tbl = tbl_init;

tbl[1][1][??][??] = 1   // 初期状態は，eq=1, az=1
for (auto d : ds) {
  auto prev = move(tbl);
  tbl = tbl_init;
  REP(eq,2) REP(az,2) REP(p1,??) REP(p2,??) {
    if (prev[eq][az][p1][p2] == 0) continue; // 性能的に重要かもしれない
    REP(x,10) { // この桁で考える数
      // eq, az, p1, p2 の新しい値 new_eq, new_az, new_p1, new_p2 を計算する
      // たとえば new_p1 は，「直前の桁までで 性質 P1 の値が p1 であったとき，
      // 次の桁として x を追加すると，P1 の値が new_p1 になる」もの．
      if (eq && x > d) continue;
      ll new_eq = eq && x == d;
      ll new_az = az && x == 0;  // p1 などの計算に必要なら使う．
      ll new_p1 = ....;
      ll new_p2 = ....;
      // 最後にテーブルを更新する
      tbl[new_eq][new_az][new_p1][new_p2] += prev[eq][az][p1][p2]; 
    }}}
```

## 問題集

<div style="left: 0; width: 100%; height: 190px; position: relative;"><iframe src="https://hatenablog-parts.com/embed?url=https%3A%2F%2Fblog.hamayanhamayan.com%2Fentry%2F2017%2F04%2F23%2F212728" style="top: 0; left: 0; width: 100%; height: 100%; position: absolute; border: 0;" allowfullscreen scrolling="no"></iframe></div>

<div style="left: 0; width: 100%; height: 190px; position: relative;"><iframe src="https://hatenablog-parts.com/embed?url=https%3A%2F%2Fyang33-kassa.hatenablog.com%2Fentry%2F2017%2F11%2F04%2F014135" style="top: 0; left: 0; width: 100%; height: 100%; position: absolute; border: 0;" allowfullscreen scrolling="no"></iframe></div>

