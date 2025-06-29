---
author: "yamate11"
title: "Trie ライブラリ"
date: "2025-06-28T10:51:24+09:00"
# date_init: "2025-06-28"
tags: ["trie"]
categories: ["topic"]
# summary: "要約を書いておく．ここには問題タイトル等は不要" 
---

ポインタベースの Trie ライブラリ．
[ソース](https://github.com/yamate11/compprog-clib/blob/master/trie.cc)

## 使用法

```cpp
  auto root = new Trie<26, 'a'>();
  auto p1 = root->insert("abcde");  // 挿入
  auto p2 = root->search("abc");    // 存在しないので p2 == nullptr
  auto p3 = root->search("abcde");  // 存在するので，p3 == p1
  auto p4 = root->get_node("abc");  // 存在に関係無くノードを取る
  assert(p3->reside);               // そのノードは存在ノードか?
  assert(not p4->reside);
  root->insert("abab");
  assert(root->size_st == 2)        // 部分木に存在する数
  p3->erase();                      // 削除
  assert(not p3->reside);
  assert(p4->size_st == 1);
```

## インタフェース

### テンプレートパラメタ

```cpp
template <
  int bt_size,                 // 文字種
  char from,                   // 最初の文字
  typename User = monostate,   // ユーザデータの型
  typename S = string,         // 管理するデータの型．string とか vector<char> とか
  bool compact = 2 < bt_size,  // 省メモリ型
  bool has_offset = true       // オフセットの管理方法
>
struct Trie {
```

* `bt_size` ... 文字種．小文字の文字列なら `26`, 01列なら `2` など．
* `from` ... 最初の文字．小文字なら `'a'`, 01文字列なら `'0'`，整数の01列なら `0` など．
* `User` ... ユーザデータの型．引数無しで構築できなければならない．省略値は `monostate` で，これは，何も要素を持たない構造体．
* `S` ... この trie で管理するデータの型．たいてい string だろうけれど，`vector<int>` とかでも可．ただし，値は from から from + bt_size までで，char の範囲に入っていること．
* `compact` ... たとえば全ノードに長さ26のベクトルを持たせるというのはちょっと無駄なので，ここを true にすると，もう少し領域を節約する．ただし，少しは遅くなる (そんなには遅くないと思う) ので，false にすると，固定長 array になる．
* `has_offset` ... ノードに，何文字目であるかを持たせるかどうか．これはノードごと 4 バイトしか違わないので，いつでも true でも良かったか....

### コンストラクタ

```cpp
  Trie() = default;
  Trie(Trie* p, int offset_);
```

この2つが有るが，通常，ルートを引数無しで作る他は，明示的にコンストラクタを呼ぶ場面はないと思う．

### データメンバ

```cpp
  Trie* parent;   // 親
  bool reside;    // このノードが表す文字列が存在しているか
  int size_st;    // 部分木に存在する文字列の数
  User user;      // ユーザデータ
```

「存在」というのは，変な表現だが，この Trie は，文字列の一つの集合を表すと考えて，
各ノードが表す文字列が，その集合に属することを「存在する」と表現している
Trie で扱いたい処理はいろいろあるだろうが，文字列の集合の処理と，各ノードの部分木とその集合の共通部分のサイズは
比較的よく用いるだろう，ということで，だまってサービスすることになっている．
その他の処理をしたい場合には，`user` を使って自分で処理を書く．


### 挿入

文字列を挿入するには，root に対して，次を用いる:

```cpp
  Trie* insert(const auto& s);
```

挿入した文字列を表すノードを返す．返されるノードのデータメンバ `reside` には，true が設定され，
その先祖のノードの `size_st` が更新される．
すでに存在している文字列を挿入しても，何も起こらない (が，そのノードが返る)．

たとえば，`p` が `"abc"` を表しているときに，`p->insert("def")` を実行すると，
`"abcdef"` が挿入されることになる．

### 削除

文字列を削除するには，その文字列を表すノードに対して，次を用いる．

```cpp
  void erase();
```

このノードの `reside` は false が設定され，先祖のノードの `size_st` が更新される．
存在していない文字列を削除しても，何も起こらない．


### 検索

文字列を検索するには，root に対して次を用いる:

```cpp
  Trie* search(const auto& s);
```

存在すればそのノードへのポインタが，存在しなければ，nullptr が返る．
この「存在する」は，上述の意味なので，ノードがあったとしても，nullptr が返ることはある．
ノードが欲しい (あるいは，ノードがあるかどうかを知りたい) ときには，次を用いる:

```cpp
  Trie* get_node(const auto& s, bool create = false)
```

`create` に true を与えると，無ければ作る．


### 親子関係

* 親を取るときには，データメンバ parent を参照する．
  ```cpp
    Trie* parent;
  ```
  ルートでは，parent は nullptr になるので，「ルートまで順に辿る」のは，次のように書ける:
  ```cpp
    for ( ; p ; p = p->parent ) { .... }
  ```

* 1つの子供ノードを取るときは，次を用いる:
  ```cpp
    Trie* get_child_val(int c, bool create = false);
    Trie* get_child_offset(int d, bool create = false);
  ```
  `get_child_val` は，`c` に，文字を指定する．`get_child_offset` は，`d` にオフセットを指定する．
  これらは，`c == from + d` という関係にある(`from` はテンプレートパラメタで，最初の文字を表す)．
  どちらも，`create` に true を指定すると，ノードがなければ作る．

* 子供をループするときには，次を用いる:
  ```cpp
    for (auto [p, c] : node->children_w_val()) { ... }
  ```
  名前は，children with value というつもり．
  p に node の子供が，c にはその子供が表す文字が，順に設定される (`p` と `node` は，`Trie*` 型)．
  `c == from + p->get_offset()` の関係がある．(返すのは p だけで良かったなあ....)

* ノードが，自分の親に対してどの文字に対応する子供なのかを知るためには，次を用いる:
  ```cpp
    int get_offset();
  ```
  正確には，これはオフセットだから，文字を知りたければ `from` を加える．