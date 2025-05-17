---
author: "yamate11"
title: "Wavelet 行列ライブラリ"
date: "2025-05-17T11:23:05+09:00"
# date_init: "2025-05-17"
tags: []
categories: ["topic"]
# categories: ["solution"]
# summary: "要約を書いておく．ここには問題タイトル等は不要" 
---

Wavelet 行列ライブラリを書いた．

## 使用法

```cpp
vector<ll> vec{...};
WaveletMatrix wm(vec, -1);
cout << wm.kth_rank(10, 20) << endl;
```

### コンストラクタ

```cpp
WaveletMatrix wm(vec, amax);
```

* vec ... データを格納したベクトルなど．すべて非負整数であることが必要．
* amax ... 「データがこの値を超えない」という値．`-1` を与えると，ライブラリの方で最大値を取ってくれる

### データメンバ

* `wm.N` ... データの個数

他にもあるが，使わないと思う．

### データ値の取得

```cpp
wm.access(i);
```

i 番目の値を取得する．`vec[i]` と同じになるはずなので，あまり使いではない．

### 出現回数

```cpp
wm.rank(t, r);
```

* 区間 `[0, r)` に `t` が現れる回数を返す．
* `t` は非負整数であればよい．
* `r` は，`wm.N` 以下でなければならない．

### k番目

```cpp
wm.kth_smallest(k, l, r);
wm.kth_largest(k, l, r);
```

* 区間 `[l, r)` で，`k` 番目に小さい / 大きい 値を返す．
* `k` は 0-indexed.  たとえば最小値は `kth_smallest(0, l, r)`.
* `k` は意味がある値でなければならない．つまり，`0 <= k < r - l` が必要．
* `0 <= l < r <= wm.N` でなければならない．

### 出現回数

```cpp
wm.range_freq(hi, l, r);
wm.range_freq(lo, hi, l, r);
```

* 区間 `[l, r)` において各々，`t < hi` または `lo <= t < hi` であるような要素 t の個数を返す．
* `0 <= lo <= hi` でなければならない．(amax に関する制約は無い)
* `0 <= l <= r <= wm.N` でなければならない．
