---
author: "yamate11"
title: "尺取り法のコーディング"
date: "2024-02-03T13:30:38+09:00"
# date_init: "2024-02-03"
tags: []
# categories: ["topic"]
# categories: ["solution"]
# summary: "要約を書いておく．ここには問題タイトル等は不要" 
---


## 前提

自然数 $N$ に対して，$\bar{N} := \\{0, 1, \dots, N - 1\\}$ とする．
$x \leq y$ なる $(x, y) \in \bar{N} \times \bar{N}$ に対する
述語 $P(x, y)$ が，次を満たすとする．

* $P(x, y)$ かつ $x \leq x'$，$y' \leq y$ ならば，$P(x', y')$

このとき，やはり $(x, y)$ に対して定まる値 $F(x, y)$ について，
$\bigoplus \\{ F(x, y) \mid P(x, y) \\}$ を求めるのが問題．
$\oplus$ は，和や最小値や最大値など．
ここで，$P(x, y)$ は，$P(x - 1, y)$ や $P(x, y - 1)$
などから，少ない手間で求められるものとする．

## 考え方

* 1つの while ループで書く．
* $P(x, y)$ が成り立ったら，次は $P(x, y + 1)$ を調べる．
  成り立たなかったら，次は $P(x + 1, y + 1)$ を調べる．
* $P(x, y)$ が成り立ったら，
  $F(x, y) \oplus F(x + 1, y) \oplus \dots \oplus F(y, y)$
  を答えに加える．

## 擬似コード



```text
ll i = 0, j = 0;   // (i, j) を調べる．
ll ans = oplus の単位元;
ll a = 初期値, b = 初期値;   // F(i, j) や P(i, j) を計算するのに必要な値を用意しておく．
                            // ここでは a, b とする．この位置で用意するのは，(0, 0) 用．
while (true) {   // 一つのループ
  if (i > j)  {              // 例外的処理
    // P(i, i) が成り立たないことがある場合，このアルゴリズムは，i > j となる組に来る．
    // この場合は，単に j を増やす．
    j++;
  }else if (calc_P(a, b))  { // P(i, j) が成り立ったら
    v = calc_val(a, b);      // F(i, j) oplus F(i + 1, j) oplus ... oplus F(j, j) の値を計算
    ans = oplus(ans, v);     // 答を更新
    if (j == N) break;       // 右が端に到達したらループを抜ける
    (a, b) = update_ab_yes(a, b, i, j);
                             // a や b を更新．更新された (a, b) は，(i, j + 1) 用のもの
    j++;                     // 次は (i, j + 1) の処理
  }else {                    // P(i, j) が成り立たなかったら
    (a, b) = update_ab_no(a, b, i, j);
                             // a や b を更新．更新された (a, b) は，(i + 1, j) 用のもの
    i++;                     // 次は (i + 1, j) の処理
  }
}
cout << ans << endl;
```


## 問題3

[ABC 032 C - 列](https://atcoder.jp/contests/abc032/tasks/abc032_c)

$K$ と列 $(S_i)$ が与えられる．$S_i \times S_{i + 1} \times \dots S_{j} \leq K$
となる $(i, j)$ について，長さ $j - i + 1$ の最大値を求める．


```cpp
int main() {
  ll N, K; cin >> N >> K;
  vector S(N, 0LL); REP(i, 0, N) cin >> S[i];
  
  // S[i] == 0 なる i がある場合には別扱い
  if (EXISTS(i, 0, N, S[i] == 0)) {
    cout << N << endl;
    return 0;
  }

  // ここから尺取り法
  // P(i, j) は，S[i] * S[i + 1] * ... * S[j - 1] <= K．
  // F(i, j) は，j - i
  // oplus は，max
  ll i = 0, j = 0;
  ll ans = 0;
  ll val = 1;   // val は，S[i] * S[i + 1] * ... * S[j - 1] を保持する．
  while (true) {
    if (i > j) {   // この問題では，S[i] > K のときにはこのケースが生じる．
      val = 1;              // 次回の val
      j++;                  // 次回の j
    }else if (val <= K) {   // P(i, j) が成り立つとき
      ans = max(ans, j - i);
      if (j == N) break;
      val = val * S[j];     // 次回の val
      j++;                  // 次回の j
    }else {
      val = val / S[i];     // 次回の val
      i++;                  // 次回の i
    }
  }
  cout << ans << endl;

  return 0;
}
```

このコードでは，val に
`S[i] * S[i + 1] * ... * S[j]` ではなく
`S[i] * S[i + 1] * ... * S[j - 1]` を保持するようにしている．
前者にしてしまうと，(0, 0) に対して 1 でなく S[0] を与える必要があるので面倒．

[提出](https://atcoder.jp/contests/abc032/submissions/49900000)


## 問題4

[ABC 038 C - 単調増加](https://atcoder.jp/contests/abc038/tasks/abc038_c)

```cpp
int main() {
  ll N; cin >> N;
  vector A(N, 0LL); REP(i, 0, N) cin >> A[i];
  
  // P(i, j) <-> A[i] < A[i + 1] < ... < A[j]
  ll i = 0, j = 0;
  ll ans = 0;
  ll cond = true;
  while (true) {
    if (cond) {
      ans += j - i + 1;
      j++;
      if (j == N) break;
      cond = A[j - 1] < A[j];
    }else {
      i++;
      cond = i == j;
    }
  }
  cout << ans << endl;
  return 0;
}
```

[提出](https://atcoder.jp/contests/abc038/submissions/49903053)

## 問題5

[ARC 022 B - 細長いお菓子](https://atcoder.jp/contests/arc022/tasks/arc022_2)

```cpp
int main() {
  ll N; cin >> N;
  vector A(N, 0LL); REP(i, 0, N) cin >> A[i];
  
  ll i = 0, j = 0;
  ll dup = -1;
  set<ll> ss;
  ll ans = 0;
  while (true) {
    if (dup < 0) {
      ans = max(ans, j - i);
      if (j == N) break;
      if (ss.contains(A[j])) dup = A[j];
      else                   ss.insert(A[j]);
      j++;
    }else {
      if (A[i] == dup)       dup = -1;
      else                   ss.erase(A[i]);
      i++;
    }
  }
  cout << ans << endl;
  return 0;
}
```

[提出](https://atcoder.jp/contests/arc022/submissions/49901735)

## 問題6

[ABC 098D - Xor Sum 2](https://atcoder.jp/contests/abc098/tasks/arc098_b)

```cpp
int main() {
  ll N; cin >> N;
  vector A(N, 0LL);
  for (int i = 0; i < N; i++) { ll v; cin >> v; A[i] = v; }

  ll ans = 0;
  ll i = 0;
  ll j = 0;
  ll s = 0;
  ll t = 0;
  while (true) {
    if (s == t) {
      ans += j - i;
      if (j == N) break;
      s += A[j];
      t ^= A[j];
      j++;
    }else {
      s -= A[i];
      t ^= A[i];
      i++;
    }
  }

  cout << ans << endl;
  return 0;
}
```

[提出](https://atcoder.jp/contests/abc098/submissions/49898478)

## 問題8

[JOI 2013 本選 C バウムクーヘン](https://atcoder.jp/contests/joi2014ho/tasks/joi2014ho3)

```cpp
```

