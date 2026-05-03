---
author: "yamate11"
title: "行列ライブラリ"
date: "2025-08-09"
date_init: "2024-03-30"
tags: ["matrix"]
categories: ["topic"]
# categories: ["solution"]
# summary: "要約を書いておく．ここには問題タイトル等は不要" 
---

自分用の [行列ライブラリ](https://github.com/yamate11/compprog/blob/main/clib/matrix.cc) のメモです．

### 依存関係

AO.cc  (Algebra Operations) に依存する ... と思う (最近チェックしていない．ひょっとしたら違うかも)

### 型

要素の型を `T` として，`Matrix<T>` が，行列の型になる．

以下，要素の型を `T` とし，`MyMat = Matrix<T>` と定義されているものとする．
`mat` は `MyMat` 型とする．

### 使用法

```cpp
using MyMat = Matrix<ll>;
MyMat mat1(n, m);
REP(i, 0, n) REP(j, 0, m) cin >> mat1.rs(i, j);
MyMat cvec1(n, 1);
REP(i, 0, n) cin >> cvec1.rs(i, 0);
auto cvec2 = mat1 * cvec1;
REP(i, 0, n) cout << cvec2.at(i, 0) << " ";
cout << endl;
```

### 行列を作る

* m 行 n 列の零行列
  ```cpp
  MyMat mat(m, n);
  ```
* 各要素を指定したものにする．
  ```cpp
  MyMat mat(m, n);
  REP(i, 0, m) REP(j, 0, n) mat.rs(i, j) = i * n + j;
  ```
* initializer list
  ```cpp
  MyMat mat{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  ```
* vector<vector<ll>> から
  ```cpp
  vector<vector<ll>> v{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  auto mat = MyMat::from_vvec(v);
  ```
* 要素を1列に並べた長さ m * n の1次元配列 (先に横) v を持っている．
  (特に m = 1 や n = 1 のとき有用)
  ```cpp
  MyMat mat(m, n, move(v));  //  mat(m, -1, v) や mat(-1, n, v) でも良い．
  ```
* 既にある m × n 行列の i 行目を取り出した 1× n 行列や，j 列目を取り出した m × 1 行列
  ```cpp
  MyMat row_3 = mat.rowVec(3);
  MyMat col_2 = mat.colVec(2);  
  ```

### 要素へのアクセス

* `mat.at(i, j)` ... (i, j) 要素の値
* `mat.rs(i, j)` ... (i, j) 要素への代入
  * rs は，実際，`MyMat&` を返すので，値も取れる．`mat.rs(i, j) += 1;` のようなコードも書ける．

### ベクトルと $(n, 1)$ 行列

* ベクトル → 行列: 長さ n のベクトル vec を，MyMat オブジェクトに変換するときには，
  * 縦長 (n, 1) 行列とみるときには，`MyMat m = MyMat(n, 1, vec)` もしくは
  `MyMat m = MyMat(-1, 1, vec)` とすればよい．
  * 横長 (1, n) 行列とみるときには，`MyMat m = MyMat(1, n, vec)` もしくは
  `MyMat m = MyMat(1, -1, vec)` とすればよい．
* 行列 → ベクトル: (n, 1) 行列 もしくは (1, n) 行列を表す MyMat 型のオブジェクト `mat` を `vector<T>` に変換するときには，
  `mat.mem` を取れば良い．

ただし，$(m, n)$ 行列 (`Matrix<T>`) と$(n, 1)$ ベクトル (`vector<T>`) の積を `vector<T>` で得たいときには，
`MyMat * vector<T>` のオーバーライドを使う方が簡単である．下の「演算」を参照．

### 零行列，単位行列

零行列は，構築子で作れる:

```cpp
MyMat mat_zero(4, 3);  // 4行3列の零行列
```

型には行列のサイズが含まれないので，これらを static member function として定義することは難しい．
何らかのオブジェクトを作って，「それと同じサイズの」零行列や単位行列が作れるようにしてある．

```cpp
MyMat some_matrix = ....; // some_matrix は4行4列の行列とする．
MyMat mat_44_zero = some_matrix.zero();  // 4行4列の零行列
MyMat mat_44_one  = some_matrix.one();   // 4行4列の単位行列．some_matrix は正方行列でなければならない．
```

### 小行列を表す構造体 Part

* 構築子:
  ```cpp
  Part(const Mat& mat, int i_size = -1, int j_size = -1, int i_0 = 0, int j_0 = 0)`;
  ```
  mat の小行列．サイズが `(i_size, j_size)`で，左上が `(i_0, j_0)` ．
  サイズの -1 は，mat と同じサイズを意味する．
* Mat のメンバ関数
  * `mat.part(i_size, j_size, i0, j0)` ... `Part(mat, i_size, j_size, i0, j0)` と同じ．
  * `mat.memcopy(part, i_1, j_1)` ... `part` が表す小行列を，行列 `mat` の中の，左上 `(i_1, j_1)` の部分に埋め込む
  
### 演算

* `+`, `-`, `*`, `+=`, `-=`, `*=` をサポートする．
* 累乗: `power(mat, x)` を使えば良い．`mat.matpower(x)` もあるが，単に `power(mat, x)` を呼んでいる．
* `*` のオーバーライドで，MyMat と vector<T> のこの順の掛け算は，結果を vector<T> にとれるようにしてある．
  * 例: `auto v = Matrix<ll>{{1, 2}, {3, 4}} * vector<ll>{1, 1};` とすれば，`v` は `vector<ll>{3, 7}` に等しい．

### 転置

* `mat.self_transpose()` ... `mat` 自体を転置する
* `mat.transpose()` ... `mat` の転置行列を返す．

### 掃き出し，逆行列，一次方程式，....

* T が体になっていないときには，正しい結果にならなかったりコンパイルエラーになったりする．
* `[rank, det] = mat.self_sweepout();`
  ... 縦方向への掃き出しを行い，`mat` は掃き出したものに置き換えられる．`rank` はランク，`det` は行列式．
* `[rank, det] = mat.sweepout();`
  ... 同上だが，`mat` は変化しない．掃き出した結果の行列は捨てられる．ランクや行列式を得るための関数．
* `omat = mat.inv();`
  ... 逆行列．`omat` の型は `optional<MyMat>` で，逆行列が存在しないときは `nullopt`．
* `mat.determinant()` ... 行列式
* `oo = mat.linSolution(bs);`
  * 一次方程式 `mat * X = bs` を解く．`bs` の型は `MyMat`．
  * 返り値 `oo` の型は `optional<MyMat>`．
    * 解がない場合には，`oo` は，`nullopt`．
    * 解がある場合には，`*oo` が (1つの) 解を表す．
* `oo = mat.linSolution_ex(bs);`
  * 上と同じだが，返り値 `oo` の型は `optional<pair<Matrix, vector<Matrix>>>`．
    * 解がない場合には，`oo` は，`nullopt`．
    * 解がある場合には，`[sol, kernel]` を `*oo` として，`sol` は (1つの) 解．
      解空間を sol + V として，`kernel` は V の基底．

### max-plus, min-pus 代数

行列と直接関係あるわけではないが，min-plus 代数は，次のように定義できる．
(algOp ライブラリを使う．matrix ライブラリは algOp を要求しているので特に何もしなくて良い)

```cpp
struct MinPlusLL {
  using value_type = ll;
  static constexpr ll mpll_big = 1LL << 60;
  static value_type zero(      const value_type& u)                      { return mpll_big; }
  static value_type one(       const value_type& u)                      { return 0; }
  static value_type add(       const value_type& u, const value_type& v) { return min(u, v); }
  static void       subst_mult(      value_type& u, const value_type& v) { u += v; }
};
using MMP = MyAlg<MinPlusLL>;
```

これで，MMP が min-plus の型になる．(MinPlusLL は，演算を定義した型．MMP が実際の型)

次のように行列計算ができる:

```cpp
  using Mat = Matrix<MMP>;
  Mat some(2, 2);   // 2行2列の行列．全要素 0．(long long の既定値が 0 だから)
  Mat zero = some.zero();  // 零行列．全部の要素が mpll_big で埋められている．
  Mat unit = some.one();   // 単位行列．対角要素は 0 (min-plus の単位元)，他は mpll_big．
  Mat mat{{p, q}, {r, s}};
  vector<MMP> vec{t, u};
  vector<MMP> result = mat * vec;   // (m,n)行列 × (n,1)行列は，Matrix * vector でできる．
```




Keywords: minplus maxplus tropical semiring

