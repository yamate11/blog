---
author: "yamate11"
title: "Mo's algorithm メモ"
date: "2022-03-06T10:53:51+09:00"
# date_init: "2022-03-06"
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
    // ブロック数
    int K = lround(sqrt(Q));

    // クエリの先読み
    using tup_t = tuple<int, int, int, int>; // ブロックID, r, l, クエリID
    vector<tup_t> qs(Q);
    for (int query_id = 0; query_id < Q; query_id++) {
      int l, r; cin >> l >> r; l--;       // 添字0開始，半開区間
      int block_id = l / K;
      qs.emplace_back(block_id, r, l, query_id);
    }

    // 重要: ソートを忘れない!
    sort(qs.begin(), qs.end());

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
