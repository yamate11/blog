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
* `S` ... この trie で管理するデータの型．たいてい string だろうけれど，`vector<int>` とかでも可．ただし，値は from から from + bt_size までで，char の範囲に入っている必要がある．
この文書で，以下「文字列」とあるのは，正確には「型 S のデータ」である．
* `compact` ... たとえば全ノードに長さ26のベクトルを持たせるというのは無駄なので，ここを true にすると，もう少し領域を節約する．ただし，少し遅くなる (そんなには遅くないと思う)．false にすると，固定長 array になる．デフォルトは，文字種類数が8以上63以下のとき true．文字種類数が64以上あると，true では機能しない．また，文字種類数が4未満のときには Trie のサイズ自体が false の方が小さい．
* `has_offset` ... ノードに，何文字目であるかを持たせるかどうか．false にすると，持たせずに，必要なときには計算する．

### コンストラクタ

下の2つのコンストラクタがあるが，通常必要なのは root を作る時だけで，この時は，引数無しの方を用いる．

```cpp
  Trie() = default;
  Trie(Trie* p, int offset_);
```


### データメンバ

```cpp
  Trie* parent;  // 親
  int reside;    // このノードが表す文字列が含まれる数 (SINGLEなら0か1)．
  int size_st;   // 部分木に存在する要素の数．
  User user;     // ユーザデータ
```

* parent は親へのポインタ．根の parent は nullptr である．

* reside と size_t は，モードが TRIE_SET_SINGLE と TRIE_SET_MULTI のときのみ有効である．

  * 各ノードが表す文字列が，Trie が表す set/multiset の要素として存在する数を，`reside` が示している．

  * size_st は，部分木の reside の値の総和である．したがって，set/multiset 内にある，
    このノードを prefix として持つ文字列の数を示す．

* user はユーザーデータ．型 User はテンプレートパラメタで指定する．デフォルトは `monostate`．
  このフィールドは常に有効だが，特にモードが TRIE_SET_NONE のときには，reside と size_t が無効なので，
  このフィールドを使わないと，意味のあることはできないであろう．

### 挿入

文字列を挿入するには，`root->insert(s)` を実行する．集合に s が要素として挿入され，
そのノードへのポインタが返される．

TRIE_SET_SINGLE, TRIE_SET_MULTI のときは，
返されるノードのデータメンバ `reside` の値が 1 増やされる (MULTIのとき) か，1 に設定され (SINGLE のとき)，
先祖の `size_st` が更新される．

ルート以外のノード p に対して `p->insert(s)` を実行することもでき，p が表す文字列 に s を付加した文字列が
対象になる
たとえば，`p` が `"abc"` を表しているときに，`p->insert("def")` を実行すると，
`"abcdef"` が挿入されることになる．この場合も，`size_st` の更新は，p までではなく，ルートまで行われる．


### 削除

要素としての文字列 s を削除するには，

* その文字列を表すノード p に対して `p->erase()` を実行するか，または，
* `root->erase(s)` を実行する．

どちらも効果は同じである．
ルート以外のノード p に対して `p->insert(s)` を実行することもでき，p が表す文字列 に s を付加した文字列が
対象になる

TRIE_SET_SINGLE, TRIE_SET_MULTI のときは，
このノードの `reside` の値が 1 以上だった場合にそれが 1 減らされ，
先祖の `size_st` が (呼出かたにかかわらずルートまで) 更新される．

このメンバ関数は何も返さない．

### 検索

文字列 s に対し，

* `root->get_node(s)` を実行すると，s を表すノードが存在すればそのノードへのポインタが返る．
  存在しないときには nullptr が返る．
* `root->get_or_create_node(s)` を実行すると，s を表すノードが存在すればそのノードへのポインタが返る．
  存在しないときには，s を表すノードが作成されてそのノードへのポインタが返る．
* TRIE_SET_SINGLE, TRIE_SET_MULTI のときは，`root->search(s)` を実行すると，
  s を表すノードが存在してその reside の値が 1 以上であれば
  そのノードへのポインタが，そうでなければ nullptr が返る．

ルート以外のノード p に対しても実行でき，p が表す文字列に s を付加した文字列が対象となる．

### 親子関係

* 親を取るときには，データメンバ parent を参照する．
  ```cpp
    Trie* parent;
  ```
  ルートの parent は nullptr なので，「ルートまで順にたどる」のは，次のように書ける:
  ```cpp
    for ( ; p ; p = p->parent ) { .... }
  ```

* 1つの子供ノードを取るときは，次を用いる:
  ```cpp
    Trie* get_child_val(int c);
    Trie* get_child_offset(int d);
  ```
  `get_child_val` は，`c` に，文字を指定する．`get_child_offset` は，`d` にオフセットを指定する．
  これらは，`c == from + d` という関係にある(`from` はテンプレートパラメタで，最初の文字を表す)．

  該当の子供ノードが無いときには，nullptr が返る．

* 次の関数も同様であるが，該当の子供ノードが無いときには，ノードが作成されてそのノードへのポインタが返る．

  ```cpp
    Trie* get_or_create_child_val(int c);
    Trie* get_or_create_child_offset(int d);
  ```

* ノードが，自分の親に対して何番目の子供なのかを知るためには，次を用いる:
  ```cpp
    int get_offset();
  ```
  返される値 (int) はオフセットである．(ルート以外の場合) 自分が表す文字は `from + p->get_offset()` で得られる．

  ルートに対して実行されると -1 が返る．

### デバッグ用

* ノード p が表す文字列は，`p->repr()` で得られる．
* TRIE_SET_SINGLE, TRIE_SET_MULTI のときには，
  Trie が表す集合の要素を (重複の回数だけならべて) `vector<S>` に格納したものが，
  `root->elem_list()` で得られる．
* `root->show(bool elemonly = true)` では，各ノードの値 (表す文字列，reside, st_size, user) が表示された string
  が得られる．(User が monostate でないときには，g_show(User) が定義されていることが必要)
  TRIE_SET_SINGLE, TRIE_SET_MULTI モードで elemonly が true の場合には，reside の値が 1 以上のノードのみ，
  そうでなければすべてのノード情報が表示される．


