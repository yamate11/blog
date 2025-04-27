---
author: "yamate11"
title: "畳み込み・ゼータ変換・メビウス変換"
date: "2025-03-10T16:52:03+09:00"
# date_init: "2025-03-10"
tags: ["convolution"]
categories: ["topic"]
# categories: ["solution"]
summary: "畳み込みやゼータ変換やメビウス変換に関するメモ"
---

畳み込みやゼータ変換やメビウス変換に関するメモ

#### 書いたライブラリ

[fastTransform.cc](https://github.com/yamate11/compprog-clib/blob/master/fastTransform.cc)

```cpp
    vector<T> xor_conv(vector<T> vec1, vector<T> vec2);
    vector<T> and_conv(vector<T> vec1, vector<T> vec2);
    vector<T> or_conv(vector<T> vec1, vector<T> vec2);
```

これらは，{xor|and|or} convolution を返す．
`vec = xor_conv(vec1, vec2)` だったら，`vec[k] = \sum {vec1[i] * vec2[j] | i ^ j = k}` になる．
`vec1` や `vec2` のサイズは，2の冪乗でなくてはならない．

```cpp
    void xor_conv_dest(vector<T>& vec1, vector<T>& vec2);
    void and_conv_dest(vector<T>& vec1, vector<T>& vec2);
    void or_conv_dest(vector<T>& vec1, vector<T>& vec2);
```

これらは，{xor|and|or} convolution を行う．結果は `vec1` にセットされる．
もとの `vec1` と `vec2` は両方破壊される．
`vec1` や `vec2` のサイズは，2の冪乗でなくてはならない．
  
```cpp
    void hadamard(vector<T>& vec);
    void inv_hadamard(vector<T>& vec);
    void zeta_upper(vector<T>& vec);
    void moebius_upper(vector<T>& vec);
    void zeta_lower(vector<T>& vec);
    void moebius_lower(vector<T>& vec);
```

これらは，対応する変換を行う．上の畳み込みの関数の内部でも使用されている．
結果は `vec` にセットされ，元の値は破壊される．
`vec` のサイズは，2の冪乗でなくてはならない．
Hadamard 変換は，本来，自分自身が逆変換だが，
関数 `hadamard` では，定数倍して値が整数になるようにしているので，
定数倍だけ異なる逆変換 `inv_hadamard` がある．
  
```cpp
    int trans_resize(vector<T>& x);
```

x を，長さが2の冪乗になるように resize する．新しい長さを返す．

```cpp
    int trans_resize(vector<T>& x, vector<T>& y);
```

x と y を，長さが同じ2の累乗になるように resize する．新しい長さを返す．




#### 関連する問題

* [ABC393 E - GCD of Subset](https://atcoder.jp/contests/abc393/tasks/abc393_e) 素数ゼータ変換
* [ABC212 H - Nim Counting](https://atcoder.jp/contests/abc212/tasks/abc212_h) xor畳み込み

#### この blog の中の記事

* [xor畳み込み](../../2021/08-10-xor-conv/)
* [ゼータ変換，メビウス変換](../../2022/03-22-fast-zeta)
* [ARC185E - Adjacent GCD](../../2025/04-27-ret-arc185-e/)

#### 参考になる記事

* [色々な畳み込み](https://kazuma8128.hatenablog.com/entry/2018/05/31/144519) (kazuma8128's blog) ...
  これを参考にしてライブラリを書いた．
* [ゼータ変換・素数ゼータ変換について](https://hackmd.io/@tatyam-prime/H1EhuQAt1x) (tatyam)
  ... 素数ゼータ変換についてわかりやすい説明
* [私用メモ: 畳み込めるものまとめ](https://noshi91.hatenablog.com/entry/2020/10/27/175112) (noshi91のメモ)
  ... たくさん表になっている
* [添え字 gcd での畳み込みで AGC038-C を解く](https://noshi91.hatenablog.com/entry/2019/09/23/002445) (noshi91のメモ)
* [高速ゼータ変換の約数版 O(N log(log(N)))](https://noshi91.hatenablog.com/entry/2018/12/27/121649)  (noshi91のメモ)
* [エラトステネスの篩の活用法を総特集！ 〜 高速素因数分解・メビウスの反転公式 〜](https://qiita.com/drken/items/3beb679e54266f20ab63) (けんちょん)
* [倍数変換・約数変換](https://nyaannyaan.github.io/library/multiplicative-function/divisor-multiple-transform.hpp.html)  (Nyaan's Library)