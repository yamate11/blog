---
author: "yamate11"
title: "約数の個数"
date: "2023-06-03T16:16:36+09:00"
date_init: "2019-12-01"
tags: []
# categories: ["topic"]
categories: ["solution"]
summary: "nまでの約数の個数の表と，求めるためのコード"
---

$n$ 以下の整数での，約数の個数の最大値を計算しておく．たとえば，$n = 10$ のときには，6 と 8 がおのおの 1,2,3,6 および 1,2,4,8 と，4個の約数を持ち，これが最大．$n=100$なら，たとえば72が12個の約数 1,2,3,4,6,8,9,12,18,24,36,72 を持つ．

## 結果

|$n$ | 個数 |
|---|---|
| $10$ | 4 |
| $10\^2$ | 12 |
| $10\^3$  | 32 |
| $10\^4$  | 64 |
| $10\^5$  | 128 |
| $10\^6$  | 240 |
| $10\^7$  | 448 |
| $10\^8$  | 768 |
| $10\^9$  | 1344 |
| $10\^{10}$ | 2304 |
| $10\^{11}$ | 4032 |
| $10\^{12}$ | 6720 |
| $10\^{13}$ | 10752 |
| $10\^{14}$ | 17280 |
| $10\^{15}$ | 26880 |
| $10\^{16}$ | 41472 |
| $10\^{17}$ | 64512 |


たとえば $n \leq 10\^5$ なら，$n$ の約数全体を二重ループで回しても 20,000回くらいで終わる，とかがわかる．

## コード

```cpp
#include <bits/stdc++.h>
#include <cassert>
using namespace std;

// Prime numbers up to 100.
// Note that their product is larger than 2^64.
vector<int> primes({2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43,
      47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97});

// Returns the maximum number of divisors of number s such that
// t * s <= n and all prime divisors of s are greater than or equal
// to primes[i]
int num_div(long long int n, long long int t, int i) {
  int p = primes[i];
  int ret = 1;
  int r = 1;
  long long int q = p;   // q = p ^ r
  while (t * q <= n) {
    ret = max(ret, (r + 1) * num_div(n, t * q, i + 1));
    q *= p;
    r++;
  }
  return ret;
}

// Returns 10^n
long long int pow10(int n) {
  long long int ret = 1;
  while (n-- > 0) ret *= 10;
  return ret;
}

int main(/* int argc, char *argv[] */) {
  for (int k = 1; k <= 18; k++) {
    cout << "10^" << k << " " << num_div(pow10(k), 1, 0) << endl;
  }
  return 0;
}

```

EDIT (2020/08/22): 単独でコンパイルできるようにコードを修正．

