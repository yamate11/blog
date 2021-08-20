---
author: "yamate11"
title: "文字列，数値変換"
date: "2021-08-20T10:52:00+09:00"
date_init: "2021-02-07"
tags: []
categories: ["topic"]
draft: false
---

C++ での型の変換などのいろいろな変換方法を書いておきます．
競技プログラミング用途です．ソース冒頭に次のように書いてあるものとします．

```cpp
#include <bits/stdc++.h>
typedef long long int ll;
using namespace std;
```

## 文字列→数値

std::stoi, std::stoll を使う．2進数などを読みたいときは，base を指定すれば良い．

```
int       stoi(  const string& str, size_t* pos=0, int base=10 );
long long stoll( const string& str, size_t* pos=0, int base=10 );
```

使用例

```cpp
  string s1 = "101";
  ll x = stoll(s1);         // x == 101
  ll y = stoll(s1, 0, 2);   // y == 5
```

似たような名前で std::strtoll などもあるが，
これらは引数に const char* を取る．
const string& を引数に取る stoll などの方が便利だろう．

実数への変換は，std::stod, std::stold を使う．

```
double      stod(  const string& str, size_t* pos = 0 );
long double stold( const string& str, size_t* pos = 0 );
```

## 数値→文字列

std::to_string を用いる．

```
string to_string( int value );
string to_string( long long value );
string to_string( unsigned value );
string to_string( unsigned long long value );
string to_string( double value );
string to_string( long double value );
```

16進表記文字列にしたいとか
8進にしたいとかいう場合には，
1つの関数を適用して終わりというわけにはいかないように思う．
次のような感じだろう．

```cpp
  ll value = 256;
  stringstream ss;
  ss << hex << value;
  string s = ss.str();  // s == "100"
```

8進にするときには hex の代わりに oct を用いる．

2進の場合はbitsetを用いる．
下の例では，value2 の2進表現が長さ8の文字列になる．

```cpp
  ll value2 = 30;
  string s2 = bitset<8>(value2).to_string(); // s2 == "00011110"
```

## 実数→整数

普通にキャストすれば良い場合も多いが，いろいろ罠がある．

```cpp
  double d = -26.001;
  ll x = ll(d + 0.5);  // x == -25  (!!)
```

これは，dが負の場合には意図したようには動作しない．
0に向かって丸められてしまうからである．
次を用いる．

```cpp
  double d = -26.001;
  ll x = llround(d);   // x == -26
```

round関数などのsignature は以下のようになっている．

```
double        round ( double arg );
long double   roundl( long double arg );
long         lround ( double arg );
long         lroundl( long double arg );
long long   llround ( double arg );
long long   llroundl( long double arg );
```

定数の 1,000,000,007 などを書くのが面倒で，

```cpp
  const ll mod = 1e9 + 7;
```
などと書いてしまうことがある．上の例は意図したように動くようであるが，

```cpp
  const ll big1 = 1e18;
  const ll big2 = 1e18 + 1;
```
については，big1 も big2 も
同じ値になってしまう．
(gccの場合) double の精度は十進で15桁くらい，long double は18桁くらいである．
