---
author: "yamate11"
title: "Snuketoon - ABC217 H"
date: "2021-09-05T10:44:32+09:00"
# date_init: "2021-09-05"
tags: ["slope trick", "DP"]
# categories: ["topic"]
categories: ["solution"]
summary: "slope trick というのは忘れていましたが，そもそもHまで到達しませんでした．この記事は公式解説そのままです．"
---

AtCoder Beginner Contest 217 - ABC 217 H - Snuketoon の解法です．
slope trick を使う公式解説そのままです．

## 問題概要

* [問題へのリンク](https://atcoder.jp/contests/abc217/tasks/abc217_h)

```
変数 P, S がある．時刻0には P = S = 0．
時刻1, 2, 3, ... に P に +1/-1/0 のいずれかを加えることができる．
列 ((T_i, D_i, X_i) : i ∈ [1, N]) が与えられる．
T_i は単調増加する正の整数，D_i は 0または1，X_i は整数．
時刻 T_i (Pの値の変化後) において，S に dmg(P, i) を加える．ただし，
  dmg(P, i) = max(0, X_i - P)        (D_i = 0 のとき)
              max(0, P - X_i)        (D_i = 1 のとき)
S を最小化するように P を変化させよ．
制約: N <= 2e5, 1 <= T_1 < T_2 < ... < T_N <= 1e9, | X_i | <= 1e9
```

## 解法

* [公式解説へのリンク](https://atcoder.jp/contests/abc217/editorial/2581)

次の自然なDPが考えられますが，状態空間が大きすぎて間に合いません．

* 定義: dp[i][p] := 時刻 T_i において P = p の時の S の最小値
* 遷移: dp[i][p] := dmg(p, i) + min { dp[i-1][q] : | q - p | <= T_i - T_{i+1} }

関数 f_i(p) := dp[i][p] が，各 i に対して，
折れ線凸関数になることを利用します．
折れ線凸関数は，次の3つで特徴付けられます．

* 最小値 min(f)
* 傾きが 0→1, 1→2, ... と変化する点のリスト pos(f)
* 傾きが -1→0, -2→-1, ... と変化する点のリスト neg(f)

今回の問題の場合，次を実施すれば良いです．

* T_{i-1} から T_i までの時間経過の間に，t := T_i - T_{i-1} だけ
  移動できます．これに対応して，pos(f) の各点が t だけ右に移動し，
  neg(f) の各点が t だけ左に移動します．
* dmg(p, i) が加えられることに対応して，X_i を pos(f) なり neg(f) なり
  の適切な位置に挿入します．さらに，
  * D_i = 1 で neg(f) に X_i を挿入した場合には，neg(f) の先頭を pos(f) の先頭に移します．
  * D_i = 0 で pos(f) に X_i を挿入した場合には，pos(f) の先頭を neg(f) の先頭移します．
  * これらの場合には，min(f) も適切に更新します．たとえば，pos(f) が
    {x0, x1, ... } だったときに，D_i = 0 で pos(f) に q が挿入されたとすると，
    x0 を neg(f) に移すとともに，min(f) に q - x0 を加えます．

第1点の移動を愚直に行うと間に合いませんので，移動距離を覚えておくだけにして，
先頭を移す操作や，X_i を挿入する操作の際には，移動距離を考慮に入れます．

f_N の最小値が求める答です．

実装は，pos(f) と neg(f) に優先度キューを用いました．
時刻 0 における f は，f(0) = 0 で，p != 0 のときには，f(p) = ∞
になっていてほしいです．
これは，pos(f) と neg(f) の初期値が (0,0,0,...) であることを意味します．
しかし，実際にたくさんの0を入れてしまっては効率が悪いので，
0 はpopしないことで対処しました．

## ACコード

```cpp
#include <bits/stdc++.h>
#include <cassert>
typedef long long int ll;
using namespace std;

int main(/* int argc, char *argv[] */) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout << setprecision(20);

  ll N; cin >> N;
  ll minf = 0;
  priority_queue<ll, vector<ll>, greater<ll>> posf;
  priority_queue<ll> negf;
  ll shift = 0;
  auto push_pos = [&](ll x) -> void { if (x < shift) posf.push(x - shift); };
  auto push_neg = [&](ll x) -> void {                negf.push(x + shift); };
  auto top_pos = [&]() -> ll { return posf.top() + shift; };
  auto top_neg = [&]() -> ll { return negf.top() - shift; };
  auto pop_pos = [&]() -> void { if (posf.top() != 0) posf.pop(); };
  auto pop_neg = [&]() -> void { if (negf.top() != 0) negf.pop(); };
  posf.push(0);
  negf.push(0);
  for ( ; N > 0; N--) {
    ll t, d, x; cin >> t >> d >> x;
    shift = t;
    if (d == 0) {
      ll y = top_pos();
      if (x <= y) {
        push_neg(x);
      }else {
        minf += x - y;
        push_pos(x);
        pop_pos();
        push_neg(y);
      }
    }else if (d == 1) {
      ll y = top_neg();
      if (y <= x) {
        push_pos(x);
      }else {
        minf += y - x;
        push_neg(x);
        pop_neg();
        push_pos(y);
      }
    }
  }
  cout << minf << endl;

  return 0;
}
```
