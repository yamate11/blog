---
author: "yamate11"
title: "Trie ライブラリ"
date: "2026-07-11"
date_init: "2025-06-28T10:51:24+09:00"
tags: ["trie"]
categories: ["topic"]
# summary: "要約を書いておく．ここには問題タイトル等は不要" 
---

ポインタベースの Trie ライブラリ．
[ソース](https://github.com/yamate11/compprog-clib/blob/master/trie.cc)

## ポイント

* ポインタと new で実装．Trie という構造体がノードを表す．
* 実装上，ノードは増やすだけで，削除はしない．
* (template parameter で指定する) 3つのモードがある．これらのモードは，メンバ関数 insert / erase / search の振舞に影響する
  * TRIE_SET_SINGLE ... set に相当
  * TRIE_SET_MULTI ... multiset に相当
  * TRIE_SET_NONE ... どちらにも該当しない
* ノードに格納するユーザデータを定義できる  (user というフィールドがある)

## 使用法

```cpp
  using MyTrie = Trie<26, 'a', TRIE_SET_SINGLE>;  // 文字種類数，先頭文字，モード
  MyTrie* root = new MyTrie;           // Trie の作成．
  MyTrie* p1 = root->insert("abcde");  // 挿入．必要なノードを作ると同時に，「要素」としても登録．
  MyTrie* p2 = root->search("abc");    // 要素ではないので p2 == nullptr
  MyTrie* p3 = root->search("abcde");  // 要素なので，p3 == p1
  MyTrie* p4 = root->get_node("abc");  // 要素かどうかに関係なくノードを取る
    // ノードがないときには nullptr が返るが，この場合は，p4 == p2 になる．
  assert(p3->reside == 1);          // p3が表す文字列は要素である．
  assert(p4->reside == 0);          // p4が表す文字列は要素でない．
  root->insert("abab");
  root->insert("abab");             // いまは SINGLE なので，何も起こらない
  assert(root->size_st == 2)        // 部分木に存在する要素の数．
  p3->erase();                      // 要素としての削除．葉であってもノードは削除しない．
  assert(p3->reside == 0);
  assert(p4->size_st == 1);

  // 文字列 s の全prefixを処理するループ
  // 長い方から:
  for (MyTrie* p = root->get_node(s); p; p = p->parent) // ...;
  // 短い方から:
  MyTrie* p = root; int i = 0;
  for (; i <= ssize(s); p = p->get_child_val(s[i++], true) // ...;
```

## インタフェース

### テンプレートパラメタ

```cpp
template <
  int bt_size,                 // 文字種類数
  char from,                   // 最初の文字
  int mode,                    // モード (TRIE_SET_SINGLE, TRIE_SET_MULTI, TRIE_SET_NONE)
  typename User = monostate,   // ユーザデータの型
  typename S = string,         // 管理するデータの型．string とか vector<char> とか
  bool compact = ...,          // 省メモリ型 (下記参照)
  bool has_offset = true       // オフセットの管理方法
>
struct Trie {
```

* `bt_size` ... 文字種類数．小文字の文字列なら `26`, 01列なら `2` など．
* `from` ... 最初の文字．小文字なら `'a'`, 01文字列なら `'0'`，整数の01列なら `0` など．
* `mode` ... TRIE_SET_SINGLE, TRIE_SET_MULTI, TRIE_SET_NONE のいずれか．
* `User` ... ユーザデータの型．引数無しで構築できなければならない．省略値は `monostate` で，これは，何も要素を持たない構造体．
* `S` ... この trie で管理するデータの型．たいてい string だろうけれど，`vector<int>` とかでも可．ただし，値は from から from + bt_size までで，char の範囲に入っていること．
* `compact` ... たとえば全ノードに長さ26のベクトルを持たせるというのは無駄なので，ここを true にすると，もう少し領域を節約する．ただし，少し遅くなる (そんなには遅くないと思う)．false にすると，固定長 array になる．デフォルトは，文字種類数が8以上63以下のとき true．文字種類数が64以上あると，true では機能しない．また，文字種類数が4未満のときには Trie のサイズ自体が false の方が小さい．
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
  bool reside;    // このノードが表す文字列が要素になっているか
  int size_st;    // 部分木に存在する要素の数．マルチセットでないことに注意
  User user;      // ユーザデータ
```

この Trie は，文字列の一つの集合を表すと考えて，
各ノードが表す文字列が，その集合の要素であるかどうかを `reside` が表している．
Trie で扱いたい処理はいろいろあるだろうが，文字列の集合の処理と，各ノードの部分木とその集合の共通部分のサイズは
比較的よく用いるだろう，ということで，だまってサービスすることになっている．
その他の処理をしたい場合には，`user` を使って自分で処理を書く．


### 挿入

文字列を挿入するには，root に対して，次を用いる:

```cpp
  Trie* insert(const auto& s);
```

実行対象のノードが表す文字列に `s` を付加した文字列を，集合に要素として挿入し，
そのノードへのポインタを返す．
たとえば，`p` が `"abc"` を表しているときに，`p->insert("def")` を実行すると，
`"abcdef"` が挿入されることになる．
通常は，root に対して実行されるだろうから，その時は `s` 自身が挿入される．

返されるノードのデータメンバ `reside` には，true が設定され，
その先祖のノードの `size_st` が更新される．
すでに存在している文字列を挿入しても，何も起こらない (が，そのノードへのポインタが返る)．


### 削除

要素としての文字列を削除するには，その文字列を表すノードに対して，次を用いる．

```cpp
  void erase();
```

このノードの `reside` に false が設定され，先祖のノードの `size_st` が更新される．
存在していない文字列を削除しても，何も起こらない．


### 検索

文字列を検索するには，次を用いる:

```cpp
  Trie* search(const auto& s);
```

実行対象が表す文字列に `s` を付加した文字列が要素であればそのノードへのポインタが，要素でなければ，nullptr が返る．

ノードがあるかどうかを知りたい (ある場合はそのノードが欲しい) ときには，次を用いる:

```cpp
  Trie* get_node(const auto& s, bool create = false)
```

* 実行対象が表す文字列に `s` を付加した文字列を表すノードがあれば，
  要素であるかどうかにかかわらず，そのノードへのポインタが返る．
* ノードが無いとき
  * `create` が false であれば，何も変更せず nullptr が返る．
  * `create` が true であれば，`s` を表すノードを作成して，そのノードへのポインタが返る．


### 親子関係

* 親を取るときには，データメンバ parent を参照する．
  ```cpp
    Trie* parent;
  ```
  root の parent は nullptr なので，「ルートまで順に辿る」のは，次のように書ける:
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
  これはオフセットである．文字は，`from + p->get_offset()` で得られる．
