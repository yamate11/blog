---
author: "yamate11"
title: "K番目の要素"
date: "2026-08-27"
date_init: "2023-06-01"
tags: []
categories: ["topic"]
# categories: ["solution"]
summary: "K番目の要素の二分探索による求め方と，ベクトルのt付近の要素"
---

## 1. K 番目の要素 (non explicit)

explicit ではない多重集合 $X$ の，小さい方から $K$ 番目の値を，二分探索で求める．

* 整数 $a$, $b$ ($a \neq b$) と，整数上の単調な述語 $P$ に対し，
  $\text{binsearch}(P; a, b)$ を，
  [ライブラリ binsearch](https://yamate11.github.io/blog/posts/2024/02-19-binary-search/) 
  の仕様に合わせて，次のように定義する:
    * $a < b$ のとき: 「$P$ が$[a, x]$ では成り立ち$[x + 1, b]$ では成り立たない」ような $x$ を返す．
    * $b < a$ のとき: 「$P$ が$[b, x]$ では成り立たず$[x + 1, a]$ で成り立つ」ような $x$ を返す．

#### 1(a). 1-based index

先頭を「1番目」と数える場合．
$X = \\{X_1, X_2, \dots \\}$

$K$ 番目の要素は，
「$X_i < t$ となる $i$ が $K$ 個未満となる最大の $t$」であるから，
$\text{binsearch}(\lambda t.\\; | \\{i : X_i < t \\} | < K,\\;\\;
\min(X),\\; \max(X) + 1)$ 
で求められる．

```cpp
auto check = [&](ll t) -> bool {
  return `the number of i such that X[i] < t' < K;
};
ll ans = binsearch<ll>(check, `min of X', `max of X' + 1);
```

モノイド演算が整数の加法であるセグメント木 `st` で，`st.at(i)` が，値が `i` である要素の数を保持している場合，
上を適用すると，次のコードになる．

```cpp
auto check = [&](ll t) -> bool { return t < K; };
ll ans = st.binsearch_r_until(check, 0);
```

「$X_i \leq t$ となる $i$ が $K$ 個以上となる最小の $t$」でもあるから，
$\text{binsearch}(\lambda t.\\; | \\{i : X_i \leq t \\} | \geq K;\\;\\;
\max(X),\\; \min(X) - 1)$
でも求められる．

```cpp
auto check = [&](ll t) -> bool {
  return `the number of i such that X[i] <= t' >= K;
};
ll ans = binsearch<ll>(check, `max of X', `min of X' - 1);
```

セグメント木は半開区間なので，このままのコードにはしにくい．
もちろん，「($X_i < t$ となる $i$ が $K$ 個以上となる最小の $t$) - 1 」とすれば良いのではあるが．
あえてそう書かなくてもよいであろう．

<img src="fig1.jpg" width="450px">

#### 1(b). 0-based index

先頭を「0番目」と数える場合．
$X = \\{X_0, X_1, \dots \\}$．
$K$ 番目というよりは，添字が $K$ である要素という感じか．

コードは，0-based index のコードの `K` を `K + 1` で置き換えれば良い．

絵は次のようになる．

<img src="fig2.jpg" width="450px">


## 2. ベクトル v の，値 t 以下/以上/未満 の要素数

$v$ の要素は整数型とする．
整数型については，常に `upper_bound(*, t) == lower_bound(*, t + 1)` となるので，
lower_bound だけを使うことにしても良い．


基本は次のこと:

> * $v_i < t$ となる $i$ の個数は，
>   `lower_bound(ALL(v), t) - v.begin()` である．
> * $t \leq v_i$ となる $i$ の個数は，
>   `v.end() - lower_bound(ALL(v), t)` である．

$v_i \leq t$ や $t < v_i$ については，$v_i < t + 1$ や $t + 1 \leq v_i$ に言い換えれば良い．



keywords: k-th element, binary search, lower_bound, upper_bound
