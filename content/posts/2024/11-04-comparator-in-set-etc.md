---
author: "yamate11"
title: "比較関数"
date: "2024-11-04T15:51:56+09:00"
# date_init: "2024-11-04"
tags: ["comparator"]
categories: ["topic"]
# categories: ["solution"]
summary: "set, multiset, priority_queue などの比較関数の指定方法"
---

set, multiset, priority_queue などでは，比較関数を指定することができる．
また，vector の sort でも比較関数を指定することができる．
この指定の仕方はなかなかに面倒であるように思う．

## 1. set, multiset, priority_queue などの比較関数

### 1.1. 降順

大きい順に要素を並べたい場合には，`greater<T>` を指定すれば良い．

例:

```cpp
  set<int, greater<int>> xs;
```

注意:

コンストラクタにはパラメタを渡す必要は無いが，
渡すのなら丸括弧でなく波括弧で渡す必要がある．

```cpp
  set<int, greater<int>> xs{greater<int>()};   // OK
  set<int, greater<int>> xs(greater<int>());   // NG
```

丸括弧を使うと，「greater<int> を返す関数を引数にとる関数 xs を宣言する」という
意味になるらしい．


### 1.2. closure f を比較関数として使う

テンプレートパラメタとして `decltype(f)` を，
コンストラクタのパラメタとして `f` を用いる．

例:

```cpp
  auto f = [](int a, int b) -> bool { return a > b; };
  set<int, decltype(f)> xs{f};
```

注意: コンストラクタに `f` を渡さないと，コンパイルエラーになる．
`decltype(f)` (closure) のコンストラクタは削除されているということらしい．


### 1.3. 普通の関数 f を比較関数として使う

テンプレートパラメタとして `decltype(&f)` を，
コンストラクタのパラメタとして `f` を用いる．


例:

```cpp
bool f(int a, int b) { return a > b; }
...
  set<int, decltype(&f)> xs(f);  
  // set<int, bool (*)(int, int)> xs(f);  としても同じ
```



注意: テンプレートパラメタの `&` を忘れないこと．実際に渡される f は関数ポインタであるから，
関数のクラス `delctype(f)` ではなく，
関数ポインタのクラス `decltype(&f)` になる，ということらしい．

注意: コンストラクタに f を渡さないと，コンパイルは通るが，実行時エラー (SEGV) になる．
これは，`decltype(f)` から関数ポインタを作成するが，それが `f` で初期化されないから，ということらしい．


## 2. sort() での比較関数と，{lower|upper}_bound()

関数 sort() は，第3引数に比較関数を渡すことができる．普通の関数でも closure でも OK.
lower_bound() や，upper_bound() の第4引数に，sort で使った比較関数を与えることで，
その順序に関する二分探索を実行することができる．

```cpp
bool f(int a, int b) { return a > b; }
...
  vector<int> vec;
  ...

  // 以下の3行はどれも同じ結果を与える:
  auto mycomp0 = greater<int>();
  auto mycomp0 = f;
  auto mycomp0 = [](int a, int b) -> bool { return a > b; };

  sort(vec.begin(), vec.end(), mycomp0);
  auto it = lower_bound(vec.begin(), vec.end(), x, mycomp0);
```

