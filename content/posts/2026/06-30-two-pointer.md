---
author: "yamate11"
title: "尺取り法について"
date: "2026-06-30T13:47:37+09:00"
# date_init: "2026-06-30"
tags: []
categories: ["topic"]
# categories: ["solution"]
# summary: "要約を書いておく．ここには問題タイトル等は不要" 
---

## 概要

a <= b なる整数 a, b に関する命題 P(a, b) が単調であるとき，尺取り法を用いることができる．単調な命題は2種類ある．

* 種類1 (広い方が成り立ちやすい):
  * P(a, b) かつ a' <= a かつ b <= b' ならば P(a', b')
* 種類2 (狭い方が成り立ちやすい):
  * P(a, b) かつ a <= a' かつ b' <= b ならば P(a', b')

種類1 については「各 a について P(a, b) が成り立つ最小の b を求めたい」，
種類2 については「各 a について P(a, b) が成り立つ最大の b を求めたい」という状況になることが多い．

いくつか実装の選択肢があるので迷ってしまうが，次のように決めておくと良いかもしれない．

* 種類2 についても，￢P を考えることによって，種類1 とみなす．
  こうすると，P(a, b) が成り立たない最小の b が得られてしまうので，b - 1 が求めるものと考える．
* a を表す変数は，なるべく for ループで回す．(増分が1にできるとはかぎらないが....)
* b を表す変数は外側で回す．常に左から右側に動かす．左に戻すことはしない．
* 境界では，P(a_0, b_0 - 1) が成り立たず P(a_0, b_0) が成り立つわけだが，静止状態になったら，
  変数 b は境界の右側，つまり b_0 を指すようにする．
  (繰返しになるが，種類2 であれば，b - 1 が欲しいものになる)
* とくに種類2の場合に，b が b_0 - 1 を指していたときのなんらかの値が欲しいケースもある．
  そういうときには，値をどこかに記録しておいて使うことにして，ともかく，静止状態では，b = b_0 にする．

Rationale

* 戻すというのは常には可能ではないかもしれないし，戻すとなると右端を減らすという新たな処理が必要．
．決して戻さないと決めておいた方が楽．
* 変数の値を増やしてみないと性質が成り立つかどうかわからないということがある．
* b_0 - 1 のときの何かの値が欲しいというケースは，おそらく，少ない．

## 実装

手間だが，命題 P を表す関数を用意しておくと確実であるように思う．
その際，(種類1の場合) 以下を成り立たせるようにする．

* b の動く範囲が lo <= b <= hi であるとき， (たいてい，lo = a であろう)
  * b < lo なら P(a, b) は false を返す    (種類2なら true)
  * hi < b なら P(a, b) は true を返す     (種類2なら false)

そうすれば，主たるループは次のように書くことができる．
ここでは，r の動く範囲を [l, N) としている．
P の先頭2行を置いておくことで，安全度が増す．

```cpp
  auto P = [&](ll l, ll r) -> bool {
    if (N <= r) return true;
    if (r < l) return false;
    // A[l], A[r] などにアクセスして適切に true/false を返す
  };
  
  ll r = 0;
  for (ll l = 0; l < N; l++) {
    while (not P(l, r)) r++;
    // r が，P(l, r) を成り立たせる最小の r
  }
```

くどいが，種類2なら次のようになる．

```cpp
  auto P = [&](ll l, ll r) -> bool {
    if (N <= r) return false;
    if (r < l) return true;
    // A[l], A[r] などにアクセスして適切に true/false を返す
  };
  
  ll r = 0;
  for (ll l = 0; l < N; l++) {
    while (P(l, r)) r++;
    // r - 1 が，P(l, r) を成り立たせる最小の r
  }
```

l や r を増やすときに，同時になにか行わなければいけないことがあることもある．
次のように書く．

```cpp
  auto P = [&](ll l, ll r) -> bool { ... /* 上と同じ */ };
  auto incr_l = [&]() -> void { l++; ... };
  auto incr_r = [&]() -> void { r++; ... };
  
  ll r = 0;
  for (ll l = 0; l < N; ) {
    while (not P(l, r)) incr_r();
    /* l と r を使って必要な処理を実施 */
    incr_l();
  }
```

incr_* の中で，なにかのデータを管理して，それを
「l と r を使って必要な処理を実施」の中で参照することもあるだろう．
とくに種類2では， incr_r() で，一つ前の値を保存しておく必要があるかもしれない．



## 例題

### ABC032-C

[ABC032-C - 列](https://atcoder.jp/contests/abc032/tasks/abc032_c)

$K$ と列 $(S_i)$ が与えられる．$S_i \times S_{i + 1} \times \dots S_{j} \leq K$
となる $(i, j)$ について，長さ $j - i + 1$ の最大値を求める．

```cpp
  if (EXISTS(i, 0, N, S[i] == 0)) {
    cout << N << endl;
    return 0;
  }
  ll ans = 0;
  ll val = S[0];
  ll j = 0;
  for (ll i = 0; i < N; ) {
    auto cond = [&]() -> bool {
      if (j < i) return true;
      if (N <= j) return false;
      return val <= K;
    };
    auto incr_i = [&]() -> void { val /= S[i++]; };
    auto incr_j = [&]() -> void {
      if (++j >= N) return;
      val *= S[j];
    };

    while (cond()) incr_j();
    ans = max(ans, j - i);
    incr_i();
  }
  cout << ans << endl;
```

### ABC369-C

[ABC369-C - Count Arithmetic Subarrays](https://atcoder.jp/contests/abc369/tasks/abc369_c)

$[l, r]$ で，$A_l, A_{l + 1}, \dots, A_r$ が等差数列となるものを数える．

```cpp
  ll ans = 0;
  ll j = 0;
  for (ll i = 0; i < N; i++) {
    auto sat = [&]() -> bool {
      if (N <= j) return false;
      if (j <= i + 1) return true;
      return (A[i + 1] - A[i] == A[j] - A[j - 1]);
    };
    while (sat()) j++;
    ans += j - i;
  }
  cout << ans << endl;
```

### ARC022-B

[ARC022-B - 細長いお菓子](https://atcoder.jp/contests/arc022/tasks/arc022_2)

$A_l, A_{l + 1}, \dots, A_r$ に重複が無い $[l, r]$ について，$r - l + 1$ の最大値．


```cpp
  ll lim = 1e5 + 1;
  vector B(lim, false);   // B[a] = true <-> 範囲内に a が入っている
  ll dup = -1;            // 範囲内で重複している要素．なければ -1．
                          //   そういうものはたかだか1つ．
  ll ans = 0;
  ll j = 0;         // 半開区間 [i, j) で考える．
  for (ll i = 0; i < N; ) {
    auto cond = [&]() -> bool {
      if (j >= N + 1) return false;
      if (j <= i) return true;
      return dup < 0;
    };
    auto inc_j = [&]() -> void {
      if (++j > N) return;
      if (ll a = A[j - 1]; B[a]) dup = a;
      else                       B[a] = true;
    };
    auto inc_i = [&]() -> void {
      if (A[i] == dup) dup = -1;
      else             B[A[i]] = false;
      i++;
    };

    while (cond()) inc_j();
    ans = max(ans, j - 1 - i);   // [i, j - 1) が条件を満たす
    inc_i();
  }
  cout << ans << endl;
```


----

keywords: two pointers two-pointer technique
