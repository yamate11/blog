---
author: "yamate11"
title: "行列ライブラリ"
date: "2024-03-30T15:29:16+09:00"
# date_init: "2024-03-30"
tags: ["matrix"]
categories: ["topic"]
# categories: ["solution"]
# summary: "要約を書いておく．ここには問題タイトル等は不要" 
---

自分用の [行列ライブラリ](https://github.com/yamate11/compprog/blob/main/clib/matrix.cc) のメモです．

### 依存関係

AO.cc  (Algebra Operations) に依存する．

### 型

要素の型を `T` として，`Matrix<T>` が，行列の型になる．
(実装上，これは，`Mat<AO_def<T>>` として定義されているが，使うときは気にしなくて良い)

以下，要素の型を `T` とし，`MyMat = Matrix<T>` と定義されているものとする．
`mat` は `MyMat` 型とする．

### 構築子

* `MyMat(int dimI_, int dimJ_)` ... dimI_ 行 dimJ_ 列 の零行列
* `MyMat(int dimI_, int dimJ_, T t)`  ... dimI_ 行 dimJ_ 列 の，要素の値がすべて `t` である行列
* `MyMat(int dimI_, int dimJ_, const vector<T>& vec)`
  ... dimI_ 行，dimJ_ 列で，内部表現が vec である行列．
  内部表現は，$a_{00}, a_{01}, \dots, a_{10}, a_{11}, \dots a_{mn}$ の順に並べた1次元 vector.
  dimI_ と dimJ_ のどちらかは負の数にすることができて，その場合には計算される．
* `MyMat(int dimI_, int dimJ_, vector<T>&& vec)` ... 同上
* `MyMat(initializer_list<initializer_list<T>> il)`  ... 自然に
* `MyMat(const Part& cs)`  ... 構造体 Part については後述

### ベクトルと $(n, 1)$ 行列

* 長さ n のベクトル vec を，MyMat オブジェクトに変換するときには，
  * 縦長 (n, 1) 行列とみるときには，`MyMat m = MyMat(n, 1, vec)` もしくは
  `MyMat m = MyMat(-1, 1, vec)` とすればよい．
  * 横花 (1, n) 行列とみるときには，`MyMat m = MyMat(1, n, vec)` もしくは
  `MyMat m = MyMat(1, -1, vec)` とすればよい．
* (n, 1) 行列 もしくは (1, n) 行列を表す MyMat 型のオブジェクト `mat` を `vector<T>` に変換するときには，
  `mat.mem` を取れば良い．

ただし，$(n, n)$ 行列と$(n, 1)$ 縦ベクトルの積を作るときには，
`MyMat * vector<T>` のオーバーライドを使う方が簡単である．下の「演算」を参照．

### 零行列，単位行列

型には行列のサイズが含まれないので，これらを static member function として定義することは難しい．
そこで，何らかのオブジェクトを作って，「それと同じサイズの」零行列や単位行列が作れるようにしてある．

* `mat.zero()` ... mat と同じサイズの零行列
* `mat.unit()` ... mat と同じサイズの単位行列．行と列の大きさは一致していなければならない．

### その他，行列を作る関数

* `MyMat::from_vvec(const vector<vector<T>>& vvec)`  ... 2次元ベクトルからMyMat 型行列を作成する．
* `mat.rowVec(i)` ... 第 i 行目を表す MyMat 型行列
* `mat.colVec(i)` ... 第 i 列目を表す MyMat 型行列

### 小行列を表す構造体 Part

* 構築子:  `Part(const Mat& mat_, int i_size_ = -1, int j_size_ = -1, int i_0_ = 0, int j_0_ = 0)`;
  mat_ の小行列．左上は `(i_0_, j_0_)` で，サイズが `(i_size_, j_size_)`．
* Mat のメンバ関数
  * `mat.part(i_size, j_size, i0, j0)` ... `Part(mat, i_size, j_size, i0, j0)` と同じ．
  * `mat.memcopy(part, i_1, j_1)` ... `part` が表す小行列を，行列 `mat` の中の，左上 `(i_1, j_1)` の部分に埋め込む
  
### 演算

* `+`, `-`, `*`, `+=`, `-=`, `*=` をサポートする．
* 累乗: `mat.matpower(x)` ... mat の x 乗．正方行列に限る．
* `*` のオーバーライドで，MyMat と vector<T> のこの順の掛け算は，結果を vector<T> にとれるようにしてある．
  * 例: `auto v = Matrix<ll>{{1, 2}, {3, 4}} * vector<ll>{1, 1};` とすれば，`v` は `vector<ll>{3, 7}` に等しい．

### 転置

* `mat.self_transpose()` ... `mat` 自体を転置する
* `mat.transpose()` ... `mat` の転置行列を返す．

### 掃き出し，逆行列，一次方程式，....

* `[rank, det] = mat.self_sweepout();`
  ... `mat` は，縦方向に掃き出したものに置き換えられる．`rank` はランク，`det` は行列式．
* `[rank, det] = mat.sweepout();`
  ... `mat` は変化しない．(掃き出した結果の行列は捨てられる)．`rank` はランク，`det` は行列式．
* `omat = mat.inv();`
  ... 逆行列．`omat` の型は `optional<MyMat>` で，逆行列が存在しないときは `nullopt`．
* `mat.determinant()` ... 行列式
* `oo = mat.linSolution<flag>(bs);`
  * 一次方程式 `mat * X = bs` を解く．`bs` の型は `MyMat`．
  * 返り値 oo の型は `optional<pair<MyMat, vector<MyMat>>>`．
    * 解がない場合には，`oo` は，`nullopt`．
    * 解がある場合には，`oo = [sol, kernel]` として，`sol` は (1つの) 解．
      `flag` が true の場合には，`kernel` は解空間の基底．
      `flag` が false の場合には，`kernel` の値には意味が無い (計算が省略される)
  * 注意: コンパイラが，linSolution の後ろに付ける "<" を不等号と誤認しないよう，次のように
    `.template` を書く必要があるかもしれない:
    * `auto opt1 = mat.template linSolution<true>(bs);`




