---
author: "yamate11"
title: "map と unordered_map の性能"
date: "2026-01-04T11:37:54+09:00"
# date_init: "2026-01-04"
tags: [map, unordered_map, performance]
categories: ["topic"]
# categories: ["solution"]
summary: "競技プログラミング用に，map と unordered_map がどの程度のサイズまで使えるかを測定した．"
---

競技プログラミング用に，map と unordered_map がどの程度のサイズまで使えるかを測定した．

## 0. おおざっぱな結論:

$2^{18}$ くらいなら多分大丈夫．$2^{20}$ あるとあぶない．$2^{22}$ だと多分無理．

## 1. 測定1

以下，ll で，long long int を表す．

### 1.1 測定方法

$N = 2^{18}$ から $N = 2^{22}$ までについて，2倍ずつ，
$0$ から $10^{18}$ くらいまでからとった一様乱数を長さ $N$ の `vector<ll> vec` に入れておいて，
測定対象 $o$ に対し，`o[vec[i]] = i;` を，$i \in [0, N)$ に対して実行し，トータルの時間を計る．
(コードは下に貼ってある．)

### 1.2 測定対象

* `map<ll, ll>`
* `unordered_map<ll, ll>`
* `safe_umap<ll, ll, false>`
  * `unordered_map` に，比較的安全と思われるハッシュ関数を指定したもの
* `safe_umap<ll, ll, true>`
  * PBDS の `gp_hash_table` に，上と同じハッシュ関数を指定したもの

### 1.3 測定結果

|   | $2^{18}$ | $2^{19}$ | $2^{20}$ | $2^{21}$ | $2^{22}$ |
|---|---:|---:|---:|---:|---:|
| `map<ll, ll>`              | 116 | 321 | 805 | 2093 | 4914 |
| `unordered_map<ll, ll>`    | 45  | 146 | 411 |  997 | 2253 |
| `safe_umap<ll, ll, false>` | 55  | 182 | 462 | 1080 | 2405 |
| `safe_umap<ll, ll, true>`  | 46  | 100 | 198 |  421 |  859 |


単位 ms．2秒間隔で10回実行して，平均を取った．
ローカルマシンで実行している．AtCoder の「コードテスト」の方がおおむね速い (が，安定しない)．
「コードテスト」での所要時間は，この表の50%から100%程度．

## 2. 測定2

mapなどのキーとして，少し複雑なものを指定してみた．
具体的には，`vector<int>` で，要素が小さく(6まで)長さも短い(10)ものを使ってみた (こういうのがときどき出てくると思う)．
unordered_map に入れるにはハッシュ関数が必要だが，上のハッシュ関数をベースにしている．詳細はコード参照．
また，これを軽くする目的で前に書いた2つの型(後述)を使う場合とも比較した (今まで比較してなかったのはひどいという話もある)．

### 2.1 測定方法

$N = 2^{18}$ から $N = 2^{22}$ までについて，4倍ずつ，
$1$ から $6$ からとった10個の一様乱数からなる列を$N$個とり，`vector<T> vec` に入れておいて，
測定対象 $o$ に対し，`o[vec[i]] = i;` を，$i \in [0, N)$ に対して実行し，トータルの時間を計る．

### 2.2 測定対象

* `map<vector<int>, int>`
* `unordered_map<vector<int>, int, H1>`
  * H1 は上述のハッシュ関数
* `unordered_map<small_vector_u64<3>, int, H2>`
  * データを unsigned long long int に 3 ビットずつ押し込んだもの．
* `unordered_map<small_vector_string, int, H3>`
  * データを string に格納したもの

### 2.3 測定結果

|   | $2^{18}$ | $2^{20}$ | $2^{22}$ 
|---|---:|---:|---:|
| `map<vector<int>, int>`                       | 201 | 1223 | 7392 |
| `unordered_map<vector<int>, int, H1>`         | 112 |  653 | 3282 |
| `unordered_map<small_vector_u64<3>, int, H2>` |  57 |  466 | 2419 |
| `unordered_map<small_vector_string, int, H3>` |  75 |  538 | 2736 |

単位 ms．2秒間隔で10回実行して，平均を取った．

がんばってデータ構造を作った甲斐はあまりなくて，単にハッシュ関数を定義しさえすれば良かったことがわかる．

## 3. 測定用コード

### 測定1

主要部分のみ．全体は[こちら](https://gist.github.com/yamate11/e3fad0581adedf61a2b2dd38e660cbe2#file-map_unordered_map_1-cc)．

```cpp
int main() {
  random_device the_random_device;
  mt19937_64 rng(the_random_device());
  uniform_int_distribution<ll> dist(0, (ll)(1e18));

  ll x; cin >> x;
  ll N = 1LL << x;
  vector<ll> vec(N);
  REP(i, 0, N) vec[i] = dist(rng);
  map<ll, ll> mp1;
  unordered_map<ll, ll> mp2;
  safe_umap<ll, ll, false> mp3;
  safe_umap<ll, ll, true> mp4;
  double t0 = get_time_sec();
  REP(i, 0, N) { mp1[vec[i]] = i; }
  double t1 = get_time_sec();
  REP(i, 0, N) { mp2[vec[i]] = i; }
  double t2 = get_time_sec();
  REP(i, 0, N) { mp3[vec[i]] = i; }
  double t3 = get_time_sec();
  REP(i, 0, N) { mp4[vec[i]] = i; }
  double t4 = get_time_sec();
  cerr << ssize(mp1) + ssize(mp2) + ssize(mp3) + ssize(mp4) << endl;
  cout << t1 - t0 << endl;
  cout << t2 - t1 << endl;
  cout << t3 - t2 << endl;
  cout << t4 - t3 << endl;
}
```

### 測定2

主要部分のみ．全体は[こちら](https://gist.github.com/yamate11/e3fad0581adedf61a2b2dd38e660cbe2#file-map_unordered_map_2-cc)．

```cpp
int main() {
  random_device the_random_device;
  mt19937_64 rng(the_random_device());
  const int len = 10;
  const ll vmin = 1;
  const ll vmax = 6;
  uniform_int_distribution<ll> dist(vmin, vmax);
  constexpr ll nbit = 3;
  assert(vmax < (1 << nbit) and nbit * len <= 64);
  using svu = small_vector_u64<nbit>;

  int x; cin >> x;
  int N = 1 << x;
  vector vec1(N, vi(len));
  REP(i, 0, N) REP(j, 0, len) vec1[i][j] = dist(rng);
  vector vec3(N, svu());
  REP(i, 0, N) REP(j, 0, len) vec3[i][j] = vec1[i][j];
  vector vec4(N, small_vector_string(len));
  REP(i, 0, N) REP(j, 0, len) vec4[i][j] = vec1[i][j];
  map<vi, int> mp1;
  unordered_map<vi, int, safe_custom_hash<vi>> mp2;
  safe_umap<svu, int> mp3;
  safe_umap<small_vector_string, int> mp4;
  double t0 = get_time_sec();
  REP(i, 0, N) { mp1[vec1[i]] = i; }
  double t1 = get_time_sec();
  REP(i, 0, N) { mp2[vec1[i]] = i; }
  double t2 = get_time_sec();
  REP(i, 0, N) { mp3[vec3[i]] = i; }
  double t3 = get_time_sec();
  REP(i, 0, N) { mp4[vec4[i]] = i; }
  double t4 = get_time_sec();
  cerr << ssize(mp1) + ssize(mp2) + ssize(mp3) + ssize(mp4) << endl;
  cout << t1 - t0 << endl;
  cout << t2 - t1 << endl;
  cout << t3 - t2 << endl;
  cout << t4 - t3 << endl;
}
```
