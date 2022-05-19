---
author: "yamate11"
title: "Mo's algorithm メモ"
date: "2022-05-19T09:30:00+09:00"
date_init: "2022-03-06"
tags: ["Mo"]
categories: ["topic"]
# categories: ["solution"]
summary: "Mo's algorithm のコンテスト用メモです"
---

Mo's algorithm を使う問題はそんなに頻繁に出てくるわけではないので，
書こうとして，あれ，なんだっけ，となりがちです．
ライブラリにするほどではないと思うので，
コンテストの時に貼れるようにメモをしておきます．

## 適用できる問題

* $Q$個のクエリ $\text{query}(l, r)$ を処理せよという形．
  ($0 \leq l \leq r \leq N$)
* $\text{query}(l - 1, r)$
  $\text{query}(l + 1, r)$
  $\text{query}(l, r - 1)$
  $\text{query}(l, r + 1)$ は，
  $\text{query}(l, r)$ から $O(1)$ で計算できる．
* クエリは先読み可能である．
* 計算量は $O(N\sqrt{Q})$ で，定数倍は結構大きいので，
  $Q$ や $N$ の大きさは，$10^5$ とか 
  せいぜい $10^6$ とかいったところ
  
## アルゴリズム

* $[0, N]$ を $\sqrt{Q}$ 個のブロックに (だいたい) 等分割する
* 次の順序でクエリをソートする: $(l, r)$ と $(l', r')$ との比較で:
  * $l$ と $l'$ が入るブロックが違う時には，左のブロックに入っている方が先
  * 同じブロックに入る時には，$r$ と $r'$ で小さい方が先
* この順序でクエリを処理する．前回の値から $l$ と $r$ を1つずつ増減させて
  今回の値を求める．
  
## 計算量

ブロックの個数を $K$，ブロックのサイズを $B$ とする．
$l$ の増減による計算はたいてい $B$ 以下で，ブロックをまたぐときも $2B$
以下だから，全体で $O(BQ)$回．
$r$ の増減による計算はあるブロックを処理している間の合計で $N$ 以下だから，
全体で $O(KN)回$．ここでだいたい $K = \sqrt{Q}$, $B = N / K$ だから，
両者合わせて $O(BQ + KN)$ = $O(N\sqrt{Q})$ である．

## コード例

$\text{query}(l, r)$ が，
「$\bigoplus\\{ a_i \mid i \in [l, r) \\}$ を求めよ」という問題だと
した場合，次のようなコードで計算できる．

```cpp
    // ブロックサイズ
    ll B = max(1LL, llround(1.3 * N / sqrt(Q)));  // 1.3 は適当に調整...

    // クエリの先読み
    using tup_t = tuple<int, int, int, int>; // ブロックID, r, l, クエリID
    vector<tup_t> qs;
    for (int query_id = 0; query_id < Q; query_id++) {
      int l, r; cin >> l >> r; l--;       // 添字0開始，半開区間
      int block_id = l / B;
      qs.emplace_back(block_id, r, l, query_id);
    }

    // 重要: ソートを忘れない!
    sort(qs.begin(), qs.end(),
         // 比較関数は無くても良いが，あった方が速い．「補足」参照
         [](const tup_t& t1, const tup_t& t2) -> bool {
           auto [block_id1, r1, _a, _b] = t1;
           auto [block_id2, r2, _c, _d] = t2;
           if (block_id1 != block_id2) return block_id1 < block_id2;
           if ((block_id1 & 1) == 0) return r1 < r2;
           else                      return r1 > r2;
         });

    // メイン
    vector<T> ans(Q);
    state_t state = state_t();  // 現在のクエリの状態を初期化
    int cl = 0, cr = 0;         // 現在の l, r の値
    for (auto [_not_used, r, l, query_id] : qs) {
      while (l < cl) {      // 左側が拡張
        cl--;
        state.add(A[cl]);
      }
      while (cr < r) {      // 右側が拡張
        state.add(A[cr]);
        cr++;
      }
      while (cl < l) {      // 左側が縮小
        state.subtract(A[cl]);
        cl++;
      }
      while (r < cr) {      // 右側が縮小
        cr--;
        state.subtract(A[cr]);
      }
      ans[query_id] = state.value();
    }

    for (T a : ans) cout << a << "\n";   // 答の出力
```

## 補足1

Codeforces の[記事](https://codeforces.com/blog/entry/61203)に，
Hilbert curve を使うと性能があがるという報告があります．
追試をしてみましたが，あまり速くなりませんでした．
左右端の拡張と縮小の回数を減らそうという趣旨とみましたが，
もとの Mo's algorithm のブロックサイズを適切に設定することによって，
ほぼ同等の回数にすることができます．
Hilbert curve order を計算する時間が馬鹿にならないので，
トータルの性能としては，改善されないようです．

## 補足2

姑息な定数倍高速化ですが，
クエリをソートする際に，
$r$ の側は左→右と右→左を交互に行うのが得策のようです．
データにもよるでしょうが，
実験してみたところ，拡張・縮小回数を30%ほど削減できました
(実行時間も20%ほど減りました)．
