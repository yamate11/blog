---
author: "yamate11"
title: "ポテンシャル付きUnionFind"
date: "2024-04-18T21:36:37+09:00"
# date_init: "2024-04-18"
tags: []
categories: ["topic"]
# categories: ["solution"]
# summary: "要約を書いておく．ここには問題タイトル等は不要" 
---

ポテンシャル付きUnionFindです．

## 使用法

```cpp
UnionFind uf(N);       // 普通のUnionFind (ポテンシャル無し)
ld = uf.merge(a, b);   // マージ．新しいリーダを返す
ld = uf.leader(a);     // リーダ
ng = uf.num_groups();  // 全体のグループ数 ( == リーダの数)
sz = uf.group_size(a); // a が属するグループのサイズ
```

グループの要素のリストを得るためには，前処理として，GroupInfo を作る必要がある．
これには，$O(N)$ かかる．

```cpp
auto gi = uf.group_info();
for (int i : gi.group(a)) cout << i << endl;  // a が属するグループの要素の列挙
```

ポテンシャル付きにするためには，テンプレートパラメタで，ポテンシャルの型を渡す．
(デフォルトの型は，UFDummyAlg なるものになっている)

```cpp
UnionFind<ll> uf1(N);
UnionFind<ftwo> uf2(N);
```

必要があれば，零元，和，単項マイナスを渡すこともできる:

```cpp
UnionFind<ll> uf3(N, 0LL, plus<ll>(), negate<ll>());
```

ポテンシャル付きの時には，merge のときの第3引数に，ポテンシャルを渡さなければならない (省略不可)

```cpp
ld = uf.merge(a, b, p);   // b を基準にした a のポテンシャルが p である．p の型は T
```

ポテンシャルの値は，pot メソッドで取る．これの返り値型は，`optional<T>` で，
ポテンシャルに矛盾がある時には，`nullopt` を返す．

```cpp
int ld = uf.merge(a, b, p);
auto p = uf.pot(a);
if (p) {
  cout << "The potential of " << a << " relative to " << ld << " is " << *p << endl;
} else {
  cout << "Potential is undefined because of inconsistency." << endl;
}
```

## ソース

[ソース](https://github.com/yamate11/compprog/blob/main/clib/UnionFind.cc)


キーワード: potential
