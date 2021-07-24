---
author: "yamate11"
title: "乱数の作り方"
date: "2021-01-13"
tags: []
categories: ["topic"]
draft: false
---
C++ での乱数の使い方のメモです．

## 典型的なコード

```cpp
ll n; cin >> n;

random_device rand_dev;
mt19937 rng(rand_dev());
uniform_int_distribution<ll> dist(1, n);

for (ll i = 0; i < 10; i++)  cout << dist(rng) << " ";
cout << endl;
```

## クラス random_device

* [マニュアル](https://en.cppreference.com/w/cpp/numeric/random/random_device)
* オブジェクトは乱数発生器．non-deterministic な乱数を生成する．
* operator() を実行すると，unsigned int の乱数が返り，状態が進む．
* 実行は高価である可能性がある．

## クラス mt19937

* [マニュアル](https://en.cppreference.com/w/cpp/numeric/random/mersenne_twister_engine)
* 32bitメルセンヌツィッター乱数発生器
* 64bitメルセンヌツィッター乱数発生器 の mt19937_64 というクラスもある．
* o.operator() を実行すると，uint_fast32_t の乱数が返り，状態が進む．
* コンストラクタに seed を渡す．
* デフォルトコンストラクタは引数をとらず，seed = 5489u を用いる．したがって，次のように書けば，どの実行でも同じ値が生成される．

```cpp
mt19937 rng;
```

## クラス uniform_int_distribution<T>

* [マニュアル](https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution)
* 乱数分布を一様分布とする．constructor に a, b を指定すると，a以上b以下の一様分布．
* T は int や ll など．デフォルトは int．
* operator() は，引数に乱数発生器を取り，一様分布を生成する．
* 他の乱数分布クラスとコンストラクタの例:

```cpp
uniform_real_distribution<double> dist1(a, b);
normal_distribution<double> dist2(mean, stddev);
```

