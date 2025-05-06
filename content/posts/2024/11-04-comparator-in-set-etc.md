---
author: "yamate11"
title: "比較関数"
date: "2025-05-06"
date_init: "2024-11-04"
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


### 1.2. ラムダ式 lf を比較関数として使う

テンプレートパラメタとして `decltype(lf)` を，
コンストラクタのパラメタとして `lf` を用いる．

例:

```cpp
  auto lf = [](int a, int b) -> bool { return a > b; };
  set<int, decltype(lf)> xs{lf};
```

注意: コンストラクタに `f` を渡さないと，コンパイルエラーになる．
`decltype(f)` (ラムダ式) のコンストラクタは削除されているということらしい．


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


#### 1.3.1  構造体で包む

何らかの事情で，引数のないコンストラクタを使いたい場合，構造体をつかう．

```cpp
struct MyComp {
  bool operator()(int a, int b) const { return a > b; }
};
...
  set<int, MyComp> xs;
```

* const 指定子を忘れないこと
* ローカル変数の値に依存した比較はできないように思われる．
  `struct MyComp` をローカルにすることはできるが，`operator()` の中でローカル変数にアクセスするとエラーに
  なるようだ．
* 「何らかの事情」の例として，`vector<set<int, MyComp>> vsi(n);` のようにしたい場合があるかと思ったが，
  `vector vsi(n, set<int, decltype(&f)>{f});` とすれば不要だった．そういう事情はないかもしれない．

### 1.4 テンプレートパラメタを指定しない (上記共通)

set のコンストラクタには，第1引数に initializer_list を，第2引数に Compare オブジェクトを指定するものがあるので，
それを用いれば，テンプレートパラメタを指定しないですむ．

```cpp
  set xs(initializer_list<int>{}, greater<>{});
  set xs(initializer_list<int>{}, f);
  set xs(initializer_list<int>{}, lf);
  set xs(initializer_list<int>{}, MyComp{});
```

initializer_list が空でなければ，そこも推論してもらえることもある．

```cpp
  set xs({0, 1, 2}, greater<>{});
  set xs({0, 1, 2}, f);
  set xs({0, 1, 2}, lf);
  set xs({0, 1, 2}, MyComp{});
```

1.4 については，tatyamさんに教えていただきました
([これ](https://x.com/tatyam_prime/status/1919652371182862488) と
[これ](https://x.com/tatyam_prime/status/1919654295114269128))．
ありがとうございました．


## 2. sort() での比較関数と，{lower|upper}_bound()

関数 sort() は，第3引数に比較関数を渡すことができる．普通の関数でもラムダ式でも OK.
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

