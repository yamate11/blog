---
author: "yamate11"
title: "小さい整数のベクトルライブラリ"
date: "2025-08-17T17:05:20+09:00"
# date_init: "2025-08-17"
tags: []
categories: ["topic"]
# categories: ["solution"]
# summary: "要約を書いておく．ここには問題タイトル等は不要" 
---

小さい整数のベクトルの実装2種:

* `small_vector_u64<bits>` ... unsigned long long の中にビットを分けて格納
* `small_vector_string` ... string の各文字に格納

ベクトル自身を safe_umap (unordered_map.cc) などのキーに使える．

### 使用法

* `small_vector_u64<bits>`

```cpp
  small_vector_u64<4> vec1;   // 4ビットずつ使用．長さは 64 / bits (この場合は 64/4 = 16) に固定
                              // 初期値は全要素が0
  vec1[0] = 3; vec1[1] = 15; vec1[2] = 20;
  cout << vec1[0] - vec1[2] << endl;
  cerr << vec1 << endl;       // << は定義済
  cerr << vec1.show(3);       // "[3, 15, 20]"．長さを引数で指定．省略すると 64/bits

  safe_umap<small_vector_u64<4>, ll> mp;
  mp[vec1] = 100;             // safe_umap などのキーとして使える．
```

* `small_vector_string`

```cpp
  small_vector_string vec2(3);   // 長さを指定．省略すると長さ0．
                                 // 初期値は全要素が0
  vec2[0] = 3; vec2[1] = 15; vec2[2] = 20;
  cout << vec2[0] - vec2[2] << endl;
  cerr << vec2 << endl;       // << は定義済

  safe_umap<small_vector_string, ll> mp;
  mp[vec2] = 100;             // safe_umap などのキーとして使える．
```

### 注意事項

* `small_vector_u64<bits>`
  * bits < 64 であること．(bits <= 32 でないと使う意味は無い)．64の約数でなくても良い．
  * ベクトルの長さは 64 / bits 固定．
  * 格納できる値は，0 以上 `1ULL << bits` 未満の整数．
* `small_vector_string`
  * 格納できる値は，0 以上 256 未満の整数．
  * string をほとんどそのまま使っている．`<<` 演算子で，ベクトル風に出力されるところだけが違う．