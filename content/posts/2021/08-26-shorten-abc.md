---
author: "yamate11"
title: "Shorten ABC - AtCoder Regular Contest 110 E"
date: "2021-08-26T06:08:51+09:00"
# date_init: "2021-08-26"
tags: ["DP", "文字置き換え", "数え上げ", "判定問題"]
categories: ["solution"]
description: "鹿島建設プログラミングコンテスト2020 (AtCoder Regular Contest 110 - ARC110) の E - Shorten ABC の解法です．"
---

## 経緯

解説AC です．公式解説も皆さんの解説もたくさん参考にしています．

## 問題概要

A, B, C からなる，長さ N の文字列がある．
隣り合った異なる文字を，どちらとも違う文字で置き換える操作ができる．
操作を0回以上行ってできる文字列の数を mod $10^9 + 7$ で求めよ．

制約: $N \leq 10^6$

* [問題へのリンク](https://atcoder.jp/contests/arc110/tasks/arc110_e)

## 解法

Python 流に，文字列 s と t の連結を s+t で，
文字列sの位置p(含む)から位置q(含まない)の部分文字列をs[p:q]で表す．
文字列長1の文字列と文字を同一視する．

与えられた文字列が1種類の文字からなるときは，答は 1 である．
以下，そうでないとする．

A,B,Cからなる文字列 s に対する e(s) を定義する．

* e("A") = 1
* e("B") = 2
* e("C") = 3
* e(s + c) = e(s) XOR e(c)    (len(c) = 1)

次が成り立つ．

* 文字列 s を文字 c に変換できるための必要十分条件は，以下の
  両方が成り立つことである．
  * e(s) = e(c)
  * len(s) = 1 であるか，または，s が2種類以上の文字を含む．
  
帰納法で簡単に証明できる．次も成り立つ．

* 長さ a の文字列 s が2種類以上の文字を含むとする．
  s を長さ b の文字列 t に変換できる必要十分条件は，
  $0 = p_0 < p_1 < ... < p_{b} = a$ なる列がとれて，
  $e(s[p_i:p_{i+1}]) = e(t[i])$ が成り立つことである．
  
必要性は明らかなので，十分性を示す．
$s[p_i:p_{i+1}]$ が1種類の文字 X しか含まない場合が問題となる．
$p_{i+1} - p_i$ は奇数で，t[i] = X である．
このブロックより右か左に X 以外の文字が現れるところがある．
どちらでも同じなので，右に現れるとしよう．
$s[p_j:p_{j+1}]$ に X 以外の文字が現れ，$i < k < j$ なる
$s[p_k:p_{k+1}] $ には，X しか現れないとする．
この場合，$p_{k+1} - p_k$ は奇数で，t[k] = X である．
そこで，切り方を変えて，$s[p_i], \ldots, s[p_i + (j - i - 1)]$ の各
1文字を t[i], ..., t[j-1] に対応させ，
$s[p_i + (j-i-1):p_{j+1}]$ を
t[j] に対応させる．t[j] に対応させる文字列は，元の対応文字列に
偶数個の X を追加したものであるから，XOR の値は変わらない．
したがって，t に変換することが可能である．(終)

s を与えられた文字列とする．
上で示したことから，s から変換可能な長さ b の文字列 t に対して，
「左から貪欲に切っていく分割」を対応させることができる．正確には，
$0 = p_0 < p_1 < ... < p_{b} \leq N$ であって，以下を満たすものを対応させる．

* $e(s[p_i:p_{i+1}]) = e(t[i]) \qquad  (i = 0, \ldots, b-1)$
* $e(s[p_i:q] \neq e(t[i]) \qquad      (i = 0, ..., b-1; p_i < q < p_{i+1})$
* $e(s[p_b:N]) = 0$

このような分割を数えれば良い．$p_b = i$ となるような分割の数
dp[i] を，配るDPを用いて数えよう．
t = 0, 1, 2, 3 と，$0 \leq i < N$ に対して，

* $\textrm{nxt}(i, t) := \min \\{ j \mid e(s[p:j]) = t,  i < j \\}$

とするとき，t = 1, 2, 3 に対して，

* `dp[nxt(i, t)] += dp[i]`

なる計算を行えば良い．求める答は，
$\sum \\{ dp[i] \mid 1 \leq i \leq N; e(s[i:N]) = 0 \\}$ である．

$e(s[i:N]) = 0$ を満たす i は，後ろから順に $O(N)$ で決定できる．
nxt(i, t) も，t = 0 も含めて後ろから順に，

* `nxt(i, e(s[i])) = i + 1`
* `nxt(i, (t XOR e(s[i])) % 4) = nxt(i + 1, t)`

と計算すれば，やはり $O(N)$ で求められる．
全体として $O(N)$ で問題を解くことができた．

## ACコード

Fp は，mod $10^9 + 7$ を取るためのクラスです．

```cpp
int main(/* int argc, char *argv[] */) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout << setprecision(20);

  ll N; cin >> N;
  string S; cin >> S;
  if (all_of(S.begin(), S.end(), [&](char t) -> bool {return t == S[0];})) {
    cout << 1 << endl;
    return 0;
  }
  vector<ll> E(N);
  for (ll i = 0; i < N; i++) E[i] = S[i] - 'A' + 1;
  vector nxt(4, vector<ll>(N + 1));
  for (ll t = 0; t < 4; t++) nxt[t][N] = N + 1;
  for (ll i = N-1; i >= 0; i--) {
    nxt[E[i]][i] = i + 1;
    for (ll t = 1; t < 4; t++) nxt[E[i] ^ t][i] = nxt[t][i + 1];
  }
  vector<Fp> tbl(N + 2);
  tbl[0] = 1;
  for (ll i = 0; i < N; i++) {
    for (ll t = 1; t < 4; t++) tbl[nxt[t][i]] += tbl[i];
  }
  vector<ll> accE(N + 1);
  for (ll i = N-1; i >= 0; i--) accE[i] = E[i] ^ accE[i + 1];
  Fp ans = 0;
  for (ll i = 1; i <= N; i++) if (accE[i] == 0) ans += tbl[i];
  cout << ans << endl;

  return 0;
}
```
