---
author: "yamate11"
title: "boost の多倍長計算"
date: "2023-11-05T16:37:09+09:00"
date_init: "2020-03-16"
tags: ["多倍長"]
categories: ["topic"]
# categories: ["solution"]
# summary: "要約を書いておく．ここには問題タイトル等は不要" 
---

AtCoderでは C++ で boost が使えるので，多倍長計算をすることができます．

## ヘッダ部分

先頭付近に次のように書いておきます．(競技プログラミングなので，これで良いことにしてください．)

```cpp
#include <boost/multiprecision/cpp_int.hpp>           // 整数を使う時
#include <boost/multiprecision/cpp_bin_float.hpp>     // 浮動小数点数を使う時
using namespace boost::multiprecision;
```

## 整数

多倍長整数として，cpp_int というものが用意されています．普段 int とか long long と書くところを，cpp_int にすればOKです．コンストラクタには文字列も使えます．

### 例

「[AtCoder Regular Contest 057-C 2乗根](https://atcoder.jp/contests/arc057/tasks/arc057_c)」を解いてみたコードです．

```cpp
template<typename T>
T power(T a, ll b) {
  T twoPow = a;
  T rv = 1;
  while (b > 0) {
    if (b & 1LL) rv *= twoPow;
    twoPow *= twoPow;
    b >>= 1;
  }
  return rv;
}

cpp_int solve() {
  string s; cin >> s;
  cpp_int lo(s);        // 読み込んだ文字列をcpp_intに変換
  cpp_int lo2 = lo * lo;
  cpp_int hi2 = (lo + 1) * (lo + 1);
  cpp_int th = power(cpp_int(100), s.size());
  while (true) {
    cpp_int p = lo2 / th;
    cpp_int q1 = th * p;
    if (lo2 <= q1 && q1 < hi2)  return p;
    cpp_int q2 = th * (p+1);
    if (lo2 <= q2 && q2 < hi2)  return p+1;
    th /= 100;
  }
}

int main(int argc, char *argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout << solve() << endl;
  return 0;
}
```

## 実数

cpp_bin_floatなんちゃら，という型が使えます．

* `cpp_bin_float_quad` ... 4倍精度浮動小数点数 (仮数113ビット，指数15ビット)
* `cpp_bin_float_50` ... 精度50桁 (十進で)．指数部は整数 (だいたい INT_MIN から INT_MAX まで．正確には少し狭い．)
* `cpp_bin_float_100` ... 精度100桁 (十進で)．指数部は上と同じ

もっと必要な場合 (どんな場合だろうか?)，自分で定義できます．精度200桁で指数部に long long を使いたい場合:

```cpp
using mydouble = number<cpp_bin_float<200, digit_base_10, void, long long>>;
mydouble x = 10;
cout << setprecision(205);
for (ll i = 0; i < 32; i++) {
  x = x * x;
  cout << x << endl;
}
```

### 例

こんなんでいいのかどうかわかりませんが，パナソニックプログラミングコンテスト2020 の
[C - Sqrt Inequality](https://atcoder.jp/contests/panasonic2020/tasks/panasonic2020_c) は，以下で通ります．

```cpp
#include <bits/stdc++.h>
#include <boost/multiprecision/cpp_bin_float.hpp>
using namespace std;
using namespace boost::multiprecision;
using mydouble = cpp_bin_float_100;

int main(int argc, char *argv[]) {
  mydouble err("1e-80");
  mydouble a, b, c; cin >> a >> b >> c;
  cout << (sqrt(a) + sqrt(b) + err < sqrt(c) ? "Yes" : "No") << endl;
  return 0;
}

```

