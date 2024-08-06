---
author: "yamate11"
title: "平方分割ライブラリ"
date: "2024-08-06T17:29:16+09:00"
# date_init: "2024-08-06"
tags: []
categories: ["topic"]
# categories: ["solution"]
summary: "平方分割ライブラリを書きました"
---

## 概要

`SRD` という構造体を定義した．名前は，Square Root Decomposition から．

* 各ブロックに対応したデータを保存するためのデータ型 `S` を，テンプレート引数としてとる．
* もとのベクトル長を，コンストラクタの引数として取る．`srd.tot_size` で参照可能．
* ブロックサイズ `srd.bsize` は，デフォルトでは $\sqrt{\texttt{srd.tot_size}}$ だが，
  コンストラクタの引数で指定することもできる．
* ブロックの数は，`srd.numb` でアクセスできる．
* ブロック b (第 b 番目のブロック) の要素数は，`srd.block_size(b)` である．
  これは，たいてい `srd.bsize` に等しいが，最後のブロックだけは異なるかもしれない．
* ブロック b の第 i 要素は，もとのベクトルの添字で idx に対応している場合，次が成り立つ．
  * `idx == srd.pos2idx(b, i)`
  * `pair<int, int>{b, i} == srd.idx2pos(idx)`
* 型 `S` のデータのベクトル (ブロック数と同じ長さを持つ) が，自動的に作成される．
  (したがって，`S` は引数無しで構築できなければならない．)
  ブロック b に対応するデータは，`srd.data(b)` でアクセスできる．

### アルゴリズムの記述

多くの (?) 問題では，次の順で処理が進むと思われる．

* 左端のブロックを処理する．この際，対象となる要素を左から順に1つずつ処理する．
* (存在すれば) 中央のブロックを，左から順に処理する．
* (存在すれば) 右端のブロックを処理する．左端のブロックの処理と同じ内容を行う．

このパターンの場合には，次のように処理が書ける:

* まず，両端のブロックを処理するための関数を書く．
  関数は，ブロック番号，それに対応するデータへの参照，ブロック内添字，もとの添字
  を引数に取り，この要素の処理内容を記述する．
  ```cpp
  auto fe = [&](int b, S& s, int i, int idx) -> void { .... };
  ```
  なお，`s == srd.data(b)`, `idx == srd.pos2idx(b, i)` という関係がある．
* 次に，中央のブロックを処理するための関数を書く．
  関数は，ブロック番号と，それに対応するデータへの参照を引数に取り，このブロックの処理内容を記述する．
  ```cpp
  auto fb = [&](int b, S& s) -> void { .... };
  ```
  なお，`s == srd.data(b)` という関係がある．
* 最後に，これらの関数を実行する．
  ```cpp
  srd.exec(lo, hi, fe, fb);
  ```
  上に記述した順序で処理が実行される．(他にも引数が渡せる．下の説明を参照．)

## 使用例

ベクトル $A$ に対し，区間への加算と，区間和を求めるクエリを処理する，という例題で示す．

各ブロックで，「ブロックの要素の和」と「シフト量」を保持する．

```cpp
  struct S {
    ll shift;    // シフト量
    ll sum;      // このブロックの要素の和
    S() : shift(0), sum(0) {}
  };
};
```

「シフト量」は，ブロック全体に数を加えるときに，全部の要素に加えるのではなく，
「このブロックの各要素には実はこれだけの量が加えられている」というのを覚えるために使う．

```cpp
    vector<ll> A(a_size);
    REP(i, 0, a_size) cin >> A[i];
    SRD<S> srd(a_size);   // 平方分割用のオブジェクトを作成する．要素数を引数にする．
                          // テンプレートパラメタに，ブロック情報を保持するデータの型を指定する
    // 各ブロックに対して，`S.sum` を設定する．
    REP(i, 0, a_size) {
      auto [b, _j] = srd.idx2pos(i);
      srd.data(b).sum += A[i];
    }
    REP(_q, 0, Q) {
      ll tp, lo, hi; cin >> tp >> lo >> hi;
      if (tp == MODIFY) {
        ll val; cin >> val;
        // まず，両端のブロックで行うべき処理を，関数として書く．
        auto fe = [&](ll b, S& s, ll i, ll idx) {
          A[idx] += a;
          s.sum += a;
        };
        // 次に，両端以外のブロックで行うべき処理を書く．
        auto fb = [&](ll b, S& s) {
          s.sum += a * srd.block_size(b);
          s.shift += a;
        };
        // 最後に，書いた関数を実行する．
        srd.exec(lo, hi, fe, fb);      
      }else if (tp == ASK) {
        ll ret = 0;
        auto fe = [&](ll b, S& s, ll i, ll idx) { ret += s.shift + A[idx]; };
        auto fb = [&](ll b, S& s) { ret += s.sum; };
        srd.exec(lo, hi, fe, fb);
        cout << ret << "\n";
      }
    }
```

### その他

#### 範囲 range_pos

もとの添字の範囲 `[lo, hi)` に対応するブロック番号やブロック内添字の範囲は，`range_pos` で取得できる．

```cpp
auto [b0, l0, h0, b1, l1, h1] = range_pos(lo, hi);
```

* ブロックが1個になる場合，`b0 == b1` で，これがブロック番号である．
  ブロック `b0` の `[l0, h0)` が，要素の範囲となる．
  `l1` と `h1` には，0 が設定される．
* そうでない場合，`b0 < b1` となる．`b0` が左端のブロック，`b1` が右端のブロック，
  `b0 + 1` から `b1 - 1` までが中央のブロックとなる．
  ブロック `b0` の要素範囲は，`[l0, h0)` で，
  ブロック `b1` の要素範囲は，`[l1, h1)` である．
* (したがって，いずれの場合も l1 には 0 が返される．冗長であるが，わかりやすさを優先した．)  

#### exec

上述のパターンに近いが，必ずしもループが1回と限らない場合には，
`exec` にさらに関数を追加できる．

```cpp
  template<typename F0e = nullptr_t, typename F0c = nullptr_t,
           typename F1e = nullptr_t, typename F1c = nullptr_t>
  void exec(int lo, int hi, auto edge_body, auto core_body,
            F0e edge_pre = nullptr, F0c core_pre = nullptr,
            F1e edge_post = nullptr, F1c core_post = nullptr);
```

* 最初の4つの引数は，上で説明した．その後に4つの省略可能な引数がある．
* edge_pre と edge_post (順序に注意) には，次の形式の関数を渡す
  実行時には，引数には，端のブロック番号と対応するデータへの参照が渡される．
  ```cpp
  auto f = [&](ll b, S& s) -> void { ... };
  ```
* core_pre と core_post (順序に注意) には，次の形式の関数を渡す
  ```cpp
  auto f = [&]() -> void { ... };
  ```
* 実行される順序は次の通り
  * 左端ブロックに対して edge_pre
  * 左端の各要素に対して edge_core
  * 左端ブロックに対して edge_post
  * (中央ブロックが存在する場合) core_pre
  * 中央の各ブロックに対して core_body
  * (中央ブロックが存在する場合) core_post
  * 右端ブロックに対して edge_pre
  * 右端の各要素に対して edge_core
  * 右端ブロックに対して edge_post
* edge_body，edge_core も含め，実行が不要な場合には `nullptr` を渡せば良い．


