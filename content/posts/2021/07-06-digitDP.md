---
author: "yamate11"
title: "桁DPのコーディング"
date: "2021-07-06"
tags: []
categories: ["topic"]
draft: false
---

桁DPのコーディングに関する記事です．
N 以下の整数である条件を満たすものを数えます．

## 参照

以下の[optさんの記事](https://opt-cp.com/digit-dp-implementation/)
をもとにして，少し追加しています:

<div class="iframely-embed"><div class="iframely-responsive" style="height: 140px; padding-bottom: 0;"><a href="https://opt-cp.com/digit-dp-implementation/" data-iframely-url="//cdn.iframe.ly/DwWoXJH"></a></div></div><script async src="//cdn.iframe.ly/embed.js" charset="utf-8"></script>

## コーディングの方針


* 配るDP
* 上位桁を 0-padding した状態で考える
    * 有効な桁が始まっているかどうかが必要なこともあるが，その場合にはそれを表すフラグを導入する．
    * 0以上N以下を数えることになるので，必要なら最後に調整．
* 代入は1回
    * その桁に表れうる数 (0..9 とか 0..1 とか) をループで回し，「この数を付け加えた時の格納先」を考える
    * 格納先の添字を表す変数を，格納元で初期化して適宜変更する．

```cpp
// N は各桁数値のベクトルで表現．ds[0] が最上位桁．
// もちろん，問題文の都合で string でも良い．
// 本来は ds[0] を一の位にして，
// ループを ds.size() - 1 から 0 まで回した方が自然かもしれない
vector<ll>& ds;

// DP表は，最初の次元を上限に等しいかどうかのフラグにする．
//     0 ... 上限値． 1 ... 上限値より小さいと確定
auto tbl_init = vector(2, vector(??, vector(??, 0LL)));
auto tbl = tbl_init;

tbl[0][??][??] = 1   // 00..0 という列が持つ性質のところを1にする．
for (ll i = 0; i < (ll)ds.size(); i++) {
  auto prev = move(tbl);
  tbl = tbl_init;
  for (ll f = 0; f < 2; f++) {         // 上限フラグ
    for (ll p = 0; p < ??; p++) {      // 添字
      for (ll q = 0; q < ??; q++) {    // 添字
        if (prev[f][p][q] == 0) continue; // 性能的に結構重要
        for (ll x = 0; x <= 9; x++)  { // この桁で考える数
          ll f0 = f, p0 = p, q0 = q; // 代入先の添字
          if (f == 0)  {
            // ds の値には，ここでしかアクセスしない．
            if (x > ds[i]) continue;
            if (x < ds[i]) f0 = 1;
          }
          // 「性質p,qを満たす列の末尾にxを付け加えると性質がp0,q0になる」
          // ような p0, q0 を定める．ここでは f は使わないはず．
          p0 = ....;
          q0 = ....;
          // 最後に一回だけ表の更新
          tbl[f0][p0][q0] += prev[f][p][q];
        }}}}}
```

## 問題集

<div style="left: 0; width: 100%; height: 190px; position: relative;"><iframe src="https://hatenablog-parts.com/embed?url=https%3A%2F%2Fblog.hamayanhamayan.com%2Fentry%2F2017%2F04%2F23%2F212728" style="top: 0; left: 0; width: 100%; height: 100%; position: absolute; border: 0;" allowfullscreen scrolling="no"></iframe></div>

<div style="left: 0; width: 100%; height: 190px; position: relative;"><iframe src="https://hatenablog-parts.com/embed?url=https%3A%2F%2Fyang33-kassa.hatenablog.com%2Fentry%2F2017%2F11%2F04%2F014135" style="top: 0; left: 0; width: 100%; height: 100%; position: absolute; border: 0;" allowfullscreen scrolling="no"></iframe></div>

