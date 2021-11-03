---
author: "yamate11"
title: "String Cards - AtCoder Beginner Contest 225 F"
date: "2021-11-03T19:17:33+09:00"
# date_init: "2021-11-03"
tags: []
# categories: ["topic"]
categories: ["solution"]
summary: "解法です．公式解説ほぼそのままです．"
---

Atcoder Beginner Contest 225 F String Cards の解法です．公式解説ほぼそのままです．

## 問題概要

[問題へのリンク](https://atcoder.jp/contests/abc225/tasks/abc225_f)

小文字からなる文字列の列 $(S_i)_{i = 1}^N$ がある．
$K$個を選んで任意の順で連結して得られる文字列のうち，
辞書順最小のものを求めよ．

制約: $K \leq N \leq 50$, $ | S_i | \leq 50$

## 経緯

コンテスト中には解く時間が無く，
終了後に何時間かかけて，先頭から1文字ずつ決めていく解を実装
して，一応解けたのですが，公式解説を見たら，簡単に解く方法が載っていました．

## 予備知識

$K = N$ の場合は，次で求められるのだそうです:

文字列の集合に，$s \prec t \iff s + t < t + s$ で
順序を入れる時，この順序の昇順に連結したものが最小．
ただし，$s + t$ は文字列の連結，$s < t$ は通常の順序．

ちょっと注釈が必要で，$\prec$ は順序にはなります (後述) が，
全順序ではない（たとえば，$s = \texttt{abc}$，$t = \texttt{abcabc}$）
ので，$ (s\_i)\_i $ が「昇順」だというのは，$s_i \nsucc s_{i+1}$ を
意味します．

#### 命題
> $\prec$ は順序である．

公式解説で，鮮やかな証明が紹介されていました．

#### 証明

非反射律は明らかなので，推移律が成り立つことを言えば良い．
$s + t < t + s$ とする．$s + t$ と $t + s$ の長さは同じなので，
文字列 $x$ を26進の数値とみなした値を $v(x)$ と書き，
2^{|x|} を $l(x)$ と書くと，
$s + t < t + s \iff 
v(s)l(t) + v(t) < v(t)l(s) + v(s)\iff
v(s) - v(s) / l(s) < v(t) - v(t) / l(t)$ となる．
つまり，文字列から計算される値の比較で大小が決まるので，推移律が成り立つ．
(終)

#### 命題
> $K = N$ の場合，連結文字列のうち，辞書順最小のものは，
> 順序 $\prec$ の「昇順」に連結されている．

#### 証明
そうでないとすると，その組を入れ替えると辞書順がより小さくなる．(終)

#### 命題
> どのような列も，昇順に並べることができる．

#### 証明
列の長さに関する簡単な帰納法．ここで，順序であることを使う．(終)

## 解法

まず，$(S_i)_i$ を，$\prec$ に関して昇順に並べておきます．

$dp[p][q] := (S_i)_{i=p}^{N}$ から $q$ 個選んで連結して得られる
辞書順最小の文字列

とします．上の議論から，$q$ 個を選んだら，
並べる順は，全体の順と同一である必要があります．

$dp[p][q] := \min(S_p + dp[p + 1][q - 1], dp[p + 1][q]) $

であることが言えます．
辞書順最小の文字列 $t$ が $S_p$ を含まない場合には，当然，それは
$dp[p + 1][q]$ に一致します．
$t = S_p + t'$ である場合には，任意に $(S_i)_{i=p+1}^{N}$ から
$q-1$ 個を選んで連結した文字列 $w$ に対し，$t \preceq S_p + w$ ですから，
$t' \preceq w$ となります．すなわち，$t' = dp[p + 1][q-1]$ が成り立ちます．
$dp[1][K]$ が求める答で，計算量は $|S_i|$ の最大値を $A$ として，
$O(NKA + NA\log N)$ です．



なお，公式解説にたくさん嘘解法が紹介されています....


## ACコード

```cpp
#include <bits/stdc++.h>
typedef long long int ll;
using namespace std;
#define REP2(i, a, b) for (ll i = (a); i < (b); i++)
#define REP2R(i, a, b) for (ll i = (a); i >= (b); i--)
#define REP(i, b) REP2(i, 0, b)
#define ALL(coll) (coll).begin(), (coll).end()

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ll N, K; cin >> N >> K;
  vector<string> S(N); REP(i, N) cin >> S[i];
  sort(ALL(S), [&](const string& s, const string& t) -> bool { return s + t < t + s; });
  string bigs(1, char('z' + 1));
  vector tbl(N + 1, vector<string>(K + 1, bigs));
  REP(i, N + 1) tbl[i][0] = "";
  REP2R(i, N-1, 0) REP2(j, 1, min(K, N - i) + 1) tbl[i][j] = min(tbl[i+1][j], S[i] + tbl[i+1][j-1]);
  cout << tbl[0][K] << endl;

  return 0;
}
```
