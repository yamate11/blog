---
author: "yamate11"
title: "K番目..."
date: "2023-06-01T09:47:15+09:00"
# date_init: "2023-06-01"
tags: []
categories: ["topic"]
# categories: ["solution"]
summary: "K番目の要素の二分探索による求め方と，ベクトルのt付近の要素"
---

## K 番目の要素 (non explicit)

explicit ではない集合 $X$ の，小さい方から $K$ 番目の要素を，二分探索で求める．
ただし，$1 \leq K \leq |X|$ とする．

$K$ 番目の要素は，
「$X_i \leq t$ となる $i$ が $K$ 個以上となる最小の $t$」であるから，
$\text{binsearch}(\lambda t.\\; | \\{i : X_i \leq t \\} | \geq K,
\max(X), \min(X) - 1)$
で求められる．


```cpp
auto check = [&](ll t) -> bool {
  return "the number of i such that X[i] >= t";
};
ll ans = binsearch_i<ll>(check, "max of X", "min of X" - 1);
```

言い換えると，
「$X_i < t$ となる $i$ が $K$ 個未満となる最大の $t$」でもあるから，
$\text{binsearch}(\lambda t.\\; | \\{i : X_i < t \\} | < K,
\min(X), \max(X) + 1)$ 
でも求められる．

```cpp
auto check = [&](ll t) -> bool {
  return "the number of i such that X[i] < t";
};
ll ans = binsearch_i<ll>(check, "min of X", "max of X" + 1);
```

## ベクトル v の t 付近の要素

$v$ の要素は整数型とする．

基本は次のこと:

> $v_i < t$ となる $i$ の個数は，
> `lower_bound(ALL(v), t) - v.begin()` である．

$v_i \leq t$ については，$v_i < t + 1$ と言い換えれば良いし，
$v_i > t$ や $v_i \geq t$ については，$|v|$ から引けば良い．

また，添字の値については次の通り．

* $v_i < t$ となる最大の $i$ の値は，(上の個数 - 1) である．
存在しない場合には当然 -1 になる．
* $v_i \leq t$ となる最大の $i$ の値も同様．
* $v_i > t$ となる最小の $i$ の値は，もちろん，
  `upper_bound(ALL(v)) - v.begin()` である．
* $v_i \geq t$ となる最小の $i$ の値は，もちろん，
  `lower_bound(ALL(v)) - v.begin()` である．


keywords: k-th element, binary search, lower_bound, upper_bound
