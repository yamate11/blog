---
author: "yamate11"
title: "文字列，数値変換"
date: "2021-02-07"
tags: []
categories: ["topic"]
draft: false
---

C++ での型の変換などのいろいろな変換方法を書いておきます．

## 文字列→数値

std::stoi, std::stoll を使う．2進数などを読みたいときは，base を指定すれば良い．

```
int       stoi( const string& str, size_t* pos=0, int base=10 );
long long stoll( const string& str, size_t* pos=0, int base=10 );
```

似たような名前で std::strtoll などがあるが，そちらは引数に const char* を取るので，stoll の方が便利だろう．

実数への変換は，std::stod, std::stold を使う．

```
double      stod( const string& str, size_t* pos = 0 );
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

16進にしたいとか8進にしたいとかだと，関数一発というわけにはいかないように思う．

```
stringstream ss;
ss << hex << value;
string s = ss.str()
```
のような感じだろうか．8進の場合には hex の代わりに oct．

2進の場合は次のようにする．この場合，valueの2進表現が長さ64の文字列になる．

```
string s = bitset<64>(value).to_string();
```

## 実数→整数

普通にキャストすれば良い場合も多いが，いろいろ罠がある．

```
double d = ...;
ll x = ll(d + 0.5);  // DANGER!!
```

これは，dが負の場合に機能しない．0に向かって丸められてしまうから．次のいずれかを用いる．

```
double d = ...;
ll x = ll(floor(d + 0.5));
// または
ll x = llround(d);
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

$10\^9 + 7$ などを書くのが面倒で
```
const ll mod = 1e9 + 7;
```
などと書いてしまうことが多い．上の例は意図したように動くようであるが，
```
const ll big = 1e18;
const ll big2 = 1e18 + 1;
```
については，両方同じ値になってしまう．(gccの場合) double の精度は15桁くらい，long double の精度は18桁くらい．
