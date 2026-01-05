---
author: "yamate11"
title: "桁DPのコーディング"
date_init: "2021-07-06"
date: "2026-01-05"
tags: []
categories: ["topic"]
draft: false
summary: "桁DPのコーディングに関する記事です．N 以下の整数で，ある条件を満たすものを数えます．opt さんの記事をもとにしています．"
---

桁DPのコーディングに関する記事です．
N 以下の整数で，ある条件を満たすものを数えます．

## 参照

2021年頃に，opt さんのページをベースに書いたのですが，リンクが切れてしまいました．

[shino16さんの記事](https://shino16.github.io/blog/post/algo/%E3%82%AA%E3%83%BC%E3%83%88%E3%83%9E%E3%83%88%E3%83%B3/) を最近 (といっても，記事が書かれたのは5年以上前) になって読んで，
この方法は，DFA を使っていると考えるとわかりやすいのだ，と思いました．

## 考え方

「これこれを満たす数で $x$ 以下のものを数えよ」という問題だとする．$x$ の桁数を $N$ とする．

* 長さ $N$ の数字列で，十進数と見たときに $x$ 以下のものを受理する DFA $D_1$ を考える．
  * 本当にそう考えるとうまくいかないが，$i$ 番目の入力文字が，$x$ の左から $i$ 桁めの数字とセットになってやってくる，
    と思えば，「小さいと決まった」「大きいと決まった」「まだわからない」の3状態の DFA を考えれば良い．
* 長さ $N$ の数字列で，十進数と見たときに (くどいな) 「これこれを満たす」ものを受理する DFA $D_2$ を考える．
  * 単純な例: 「5の倍数」であれば，mod 5 を表す 0,1,2,3,4 の5状態の DFA を考えれば良い．
* $D_1 \times D_2$ に受理される数字列を数える．数え方は次の通り．
  * dp[i][s] := (長さ $i$ の数字列で，走らせるとDFAの状態 $s$ で止まるものの数)
  * $\sum \\{ \text{dp}[N][s] \mid s \text{は受理状態} \\}$ が答．
  * 配るDPで実装．各状態 $s$ と各文字 $d$ について，`dp[i + 1][trans(s, d)] += dp[i][s]`．


## 注意事項

* 「$y$ 以上 $x$ 以下のものを」だったら，$x$ 以下のものの数から $y-1$ 以下のものの数を引けば良い．
* $s$ は tuple $(u, v)$ なので，実装時には `dp[i][u][v]` のようにすれば良い．
  $D_2$ の状態もまた tuple になることも多い．`dp[i][u][v1][v2][v3]` のようになるので，次のような
  コードになる:
  ```cpp
    int new_u  = trans1(u, d);
    int new_v1 = trans2(v1, v2, v3, d);
    int new_v2 = trnas3(v1, v2, v3, d);
    int new_v3 = trans4(v1, v2, v3, d);
    dp[i + 1][new_u][new_v1][new_v2][new_v3] += dp[i][u][v1][v2][v3];
  ```
* 「$x$以下」を受理する DFA $D_1$ は3状態なのだが，「大きいと決まった」状態に遷移すると，
  その後はずっとそこにとどまって受理されない．そこで，この状態は実装しなくても良いので，上記 u は，
  0 と 1 のみをとるようにする．よく eq と書かれるので，ここでもそうする．1 は $x$ と等しい，
  つまり「まだわからない」ことにして，0 は「小さいと決まった」にする．つまり，初期値は eq = 1．
  更新 (上の trans1) は次の通り:
  ```cpp
    int new_eq = eq and d == x[i];
  ```
* 「数を数える」ではないタスクを要求されることもある．「DFA の状態 $s$ に達する数字列全体が表す量を保持する」
  ことができれば，同様に扱える．たとえば「$x$以下のすべての整数を十進表記するとき $1$ は何回現れるか?」であれば，
  「$\text{dp}[i][s] = (a, b) \iff s$ に達する数が $a$ 個でそこに現れる1の数が $b$ 個」と定義すれば良い．
* 数を長さ$N$固定の数字列とみるので，小さい数は 0-padding して考えることになる．
  「最上位桁」のような概念を扱う際には，「そこまで全部0」(true/false) のような状態を考えると良い．
  名前を az (all zero) として，初期値は az = 1．更新は，
  ```cpp
    int new_az = az and d == 0;
  ```

## コーディング

```cpp
#define REP(i, a, b) for (ll i = (a); i < (b); i++)

string x; cin >> x;   // x は文字列で読むことにする．

// dp[i] を tbl で，dp[i - 1] を prev で表す
vector tbl_init(2, vector(2, vector(??, vector(??, 0LL))));   // eq, az, v1, v2,...
auto tbl = tbl_init;

tbl[1][1][??][??] = 1   // 初期状態は，eq=1, az=1
for (char ct : x) {
  int t = ct - '0';
  auto prev = move(tbl);
  tbl = tbl_init;
  REP(eq,0,2) REP(az,0,2) REP(v1,0,??) REP(v2,0,??) {
    if (prev[eq][az][v1][v2] == 0) continue;
    REP(d,0,10) { // DFA が d を読んだときの遷移
      if (eq and d > t) continue;  // 「大きいと決まった」
      int new_eq = eq and d == t;
      int new_az = az and d == 0;
      int new_v1 = ....;
      int new_v2 = ....;
      tbl[new_eq][new_az][new_v1][new_v2] += prev[eq][az][v1][v2];  }}}
```

## 問題集

<div style="left: 0; width: 100%; height: 190px; position: relative;"><iframe src="https://hatenablog-parts.com/embed?url=https%3A%2F%2Fblog.hamayanhamayan.com%2Fentry%2F2017%2F04%2F23%2F212728" style="top: 0; left: 0; width: 100%; height: 100%; position: absolute; border: 0;" allowfullscreen scrolling="no"></iframe></div>

<div style="left: 0; width: 100%; height: 190px; position: relative;"><iframe src="https://hatenablog-parts.com/embed?url=https%3A%2F%2Fyang33-kassa.hatenablog.com%2Fentry%2F2017%2F11%2F04%2F014135" style="top: 0; left: 0; width: 100%; height: 100%; position: absolute; border: 0;" allowfullscreen scrolling="no"></iframe></div>

