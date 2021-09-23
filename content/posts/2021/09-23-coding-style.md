---
author: "yamate11"
title: "コーディングスタイル"
date: "2021-09-23T12:16:45+09:00"
# date_init: "2021-09-23"
tags: []
categories: ["topic"]
# categories: ["solution"]
summary: "自分のコーディングスタイルについてです"
---

競技プログラミングのコードは，基本的には C++ で書いています．
とても Python の方が書きやすいときには Python で書くこともありますが，
ほとんどありません．

いろいろな方がコーディングスタイルの話をされていて，参考にしました．
ほとんど，今すぐ出てこないのですが，
競技プログラミングを始めた頃，
[koturnさんの記事](https://koturn.hatenablog.com/entry/2018/07/29/180000) 
はとても勉強になりました．また，
[kimiyuki さんの記事](https://kimiyuki.net/blog/2020/10/25/coding-style-for-competitive-programming/#fnref:juststyle)
に書かれていることは，実施するようにしたことが多いです．
(していないこともたくさんあります．)
以下，上記記事と多少重複しているところもあります．

## 整数型は long long 

整数型は，基本的には long long を使います．
例外はおおむね次のような感じです．

* bool で済む大きな vector で，スペースを節約したいとき (boolを使う)
* 64ビットフルに使うビット配列として用いるとき (unsigned long long を使う)
* ライブラリの中 (int や size_t も使う)

つまり，ループ変数なんかも，long long で回しています．
int にすると必要な領域が半分になる，とか，ループがひょっとして
多少遅いかもしれない，とか思わないこともありませんが，
ともかく「int を使わない」のを原則とすることで，
うっかりオーバーフローをしてしまうのを避けようとしています．

ソース中では実際には，先頭に次の定義を置いて，`ll` と表記しています．

```cpp
using ll = long long;
```

また，基本的には，符号付きの変数を使います．
たとえば (1) のようにと書くと警告が出ますが，
(2) のように書き足してしのぎます．
これは，
これは，符号無し変数を使って，うっかり (3) の用に書いてしまう
間違いが怖いからです．

```cpp
for (ll i = 0; i < vec.size(); i++) ...       // (1)
for (ll i = 0; i < (ll)vec.size(); i++) ...   // (2)
for (size_t i = N - 1; i >= 0; i--) ....      // (3)
```

## ラムダ関数を使う

一部の処理をくくり出したいことが当然ありますが，
普通の関数(?)ではなく，ラムダ関数を使います．若干乱暴かもしれませんが，
`[&]` を指定することで，その時点で有効な値を全部キャプチャしてしまいます．

ラムダ関数を使わないと，
たとえば，入力に N, M, K がパラメータとして与えられている場合に，
よく，以下のようなコードになります．

```cpp
int func(ll x, ll N, ll M, ll K, vector<vector<ll>>& A) {
  ...
}

int main() {
  ll N, M, K; cin >> N >> M >> K;
  vector<vector<ll>> A(N);
  for (ll i = 0; i < N; i++) cin >> A[i];
  ...
  int t1 = func(x1, N, M, K, A);
  int t2 = func(x2, N, M, K, A);
}
```

この，func の引数に N, M, K, A たちを渡すのが面倒に感じるのです．
おうおうにして，`int func (ll x) {` くらいで書き始めて，
書いていくうちに，「あ，Nが要る」「あ，Aも要る」と書き足していく
ことになりがちです．
ちゃんと設計して書かないのがいかん，という批判は当然あると思いますが，
現実としてそうなので...．

ラムダ関数を使えば以下のように書けるのでらくちんです．

```cpp
int main() {
  ll N, M, K; cin >> N >> M >> K;
  vector<vector<ll>> A(N);
  for (ll i = 0; i < N; i++) cin >> A[i];
  ...
  auto func = [&](ll x) -> ll {
    ... // N, M, K, A その他にアクセスできる．変更も可．
  };
  ll t1 = func(x1, N, M, K, A);
  ll t2 = func(x2, N, M, K, A);
}
```

よく最後のセミコロンを書き忘れてコンパイルやり直しますが．

再帰関数はちょっと書き方がトリッキーですが，
慣れれば手が勝手に動きます(?)．

```cpp
  ...
  auto dfs = [&](auto f, ll node) -> void {
             // 引数の先頭に auto f と書いておく
             // 再帰関数の時には復帰値型 (この場合は void) が省略不可
    ...
    for (ll child : children[node]) {
      f(f, child);  // 再帰呼び出し
    }
  };
  dfs(dfs, 0);   // 関数 dfs の呼び出し．f には dfs 自身を渡す．
  ...
```

めったにありませんが，相互再帰の例:

```cpp
  auto isOdd_rep  = [&](auto f, ll x) -> bool {
    if (x == 0) return false;
    return ! f(f, x - 1);       // f には isEven を入れて呼んでいる．
  };
  auto isEven_rep = [&](auto f, ll x) -> bool {
    if (x == 0) return true;
    return ! isOdd_rep(f, x - 1);   // ここは isOdd_rep を呼ぶ．
  };
  auto isOdd  = [&](ll x) -> bool { return isOdd_rep( isEven_rep, x); }
  auto isEven = [&](ll x) -> bool { return isEven_rep(isEven_rep, x); }

  assert(isOdd(5) == true);
  assert(isEven(6) == true);
```

もちろん，`isOdd` などを定義せずに，直接 
`isOdd_rep(isEven_rep, 5)` などと呼び出しても良いです．

## デバッグ出力

ときどき，「デバッグ用の printf を消し忘れてWA」という話を聞きます．
私は注意力散漫なので，なにかしないと絶対やってしまうにきまっているので，
対策しています．

* コンパイルは，必ず make で行う．
  ソースファイル名は固定 (`cans.cc` にしている)．
* Makefile を次のように書いておく:
  * 単に `make` を実行すると，識別子 `DEBUG` の値が真で，
    識別子 `_GLIBCXX_DEBUG` が定義
    された状態でコンパイルされる．その他，`-g` と `-O0` も指定される．
  * `make DEBUG= ` で実行すると，上記識別子は定義されず，`-O2` で
    コンパイルされる．
* デバッグ用のライブラリを用意する:
  * 識別子 `DEBUG` の値が真ならば，`DLOGK()` などのマクロが
    定義される．`DLOGK(e)` などと呼び出すと，「e」という文字列と
    eの値が，標準エラー出力に出力される．
  * 識別子 `DEBUG` が定義されていない状況では，デバッグ出力は
    行われない．

識別子 `_GLIBCXX_DEBUG` は，C++ の STL をデバッグモードで動かすことを
指示するものです．これが定義されていると，vector のサイズを超えた
アクセスなどがエラーとして報告されて，便利です．
gdb を使えばソース上の位置などもわかります．

こうしておくと，ソースを修正することなく，
手元では，デバッグ出力などが見えますし，提出先では
DEBUG という識別子は定義されていないので，出力されません．
また，標準エラー出力に出力しているので，想定回答との比較を行う
プログラムで標準出力だけを見るようにすれば，デバッグ出力があっても
(速度を除けば)問題無く機能します．速度に問題がある場合には
`make clean; make DEBUG= ` でコンパイルし直します．


あまりきれいじゃないかもしれませんが，コードです:

Makefile (GNU make用):

```
CXX := g++

ifeq ($(DEBUG),)
  DEBUGFLAGS := -O2
else
  DEBUGFLAGS := -g -O0 -D_GLIBCXX_DEBUG -DDEBUG=1
  ifneq ($(DEBUG_LIB),)
    DEBUGFLAGS := $(DEBUGFLAGS) -DDEBUG_LIB=1
  endif
endif

WARNINGS := -Wall -Wno-format-security -Wshadow -fconcepts
CXXFLAGS := -std=gnu++17 $(DEBUGFLAGS) $(WARNINGS)
CXXFLAGS := $(CXXFLAGS) -I/full/path/to/ac-library

all: cans

clean:
	$(RM) cans.o cans
```

DLOGKなどの定義

```cpp
template <class Head>
void dbgLog(bool with_nl, Head&& head) {
  cerr << head;
  if (with_nl) cerr << endl;
}

template <class Head, class... Tail>
void dbgLog(bool with_nl, Head&& head, Tail&&... tail)
{
  cerr << head << " ";
  dbgLog(with_nl, forward<Tail>(tail)...);
}

#if DEBUG
  #define DLOG(...)        dbgLog(true, __VA_ARGS__)
#else
  #define DLOG(...)
#endif

#define DUP1(E1)       #E1 "=", E1
#define DUP2(E1,E2)    DUP1(E1), DUP1(E2)
#define DUP3(E1,...)   DUP1(E1), DUP2(__VA_ARGS__)
#define DUP4(E1,...)   DUP1(E1), DUP3(__VA_ARGS__)
#define DUP5(E1,...)   DUP1(E1), DUP4(__VA_ARGS__)
#define DUP6(E1,...)   DUP1(E1), DUP5(__VA_ARGS__)
#define DUP7(E1,...)   DUP1(E1), DUP6(__VA_ARGS__)
#define DUP8(E1,...)   DUP1(E1), DUP7(__VA_ARGS__)
#define DUP9(E1,...)   DUP1(E1), DUP8(__VA_ARGS__)
#define DUP10(E1,...)   DUP1(E1), DUP9(__VA_ARGS__)
#define DUP11(E1,...)   DUP1(E1), DUP10(__VA_ARGS__)
#define DUP12(E1,...)   DUP1(E1), DUP11(__VA_ARGS__)
#define GET_MACRO(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,NAME,...) NAME
#define DUP(...)          GET_MACRO(__VA_ARGS__, DUP12, DUP11, DUP10, DUP9, DUP\
8, DUP7, DUP6, DUP5, DUP4, DUP3, DUP2, DUP1)(__VA_ARGS__)
#define DLOGK(...)        DLOG(DUP(__VA_ARGS__))
#define DLOGKL(lab, ...)  DLOG(lab, DUP(__VA_ARGS__))
```
