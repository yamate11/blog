---
author: "yamate11"
title: "vector<vector<*>> はあんまり速くない"
date: "2021-08-16"
tags: ["性能", "2次元", "vector", "SCC", "CSR"]
categories: ["topic"]
draft: false
---

## 発端

自分で書いた SCC (強連結成分分解) ライブラリを使っているのですが，
これが，AC-library の SCC に比べて，4倍くらい遅いのです．
どこが遅いのか調べてみたら，意外なところにもネックがありました．

最初は，主に使っているアルゴリズムのせいだと思ったのです．
深さ優先探索を2回行うアルゴリズム
(たとえば[ここ](https://manabitimes.jp/math/1250)を参照)
を使っていました．
AC-library は，[Tarjan のアルゴリズム](https://en.wikipedia.org/wiki/Tarjan%27s_strongly_connected_components_algorithm)
を使っているようなので，合わせれば速くなるだろう，と思って
書きかえました．

たしかに速くなったのですが，それでもまだAC-libraryより3倍ほど遅いです．

## vector<vector<*> >

部分に分けて測定してみたところ，どうも，グラフの情報を設定しているところも
遅い，ということが分かりました．
こんな感じのコードなのですが:

```cpp
int N, M; cin >> N >> M; // N は頂点数, M は辺の数
vector<pair<int, int>> edges;
for (int i = 0; i < M; i++) {
  int u, v; cin >> u >> v;  // 0-indexed で入力されると仮定
  edeges.emplace_back(u, v);
}
vector<vector<int>> fwd(N);  // fwd[i] は，i から直接行ける頂点たち．
// (1)
for (auto [u, v] : edges) {
  fwd[u].push_back(v);
}
// (2)
```

この，(1)から(2)までの部分で，結構時間を食っています．
Tarjan のアルゴリズムを実行するのと同程度の時間がかかっているように見えました．

## CSR

AC-library はそこをどう処理しているのか，と，見てみましたら，
CSR なる構造体を使っていました．
おそらく，
[Compressed Sparse Row](https://en.wikipedia.org/wiki/Sparse_matrix#Compressed_sparse_row_(CSR,_CRS_or_Yale_format))
のことだと思います．
すべて1次元のベクトルでの処理になります．


たとえば，`{(0, 5), (0, 7), (1, 4), (2, 3), (2, 8)}` を格納する場合には，
まず，遷移先の `{5, 7, 4, 3, 8}` を `vector<int>` に格納します．
それで，別の `vector<int>` に，`{0, 2, 3, 5}` を格納します．
これは，遷移元が 0 の遷移先は `[0, 2)` に格納されており，
遷移元が1 の遷移先は `[2, 3)` に格納されており，遷移元が2の
遷移先は，`[3, 5)` に格納されている，ということを示しています．

ちょっと上のリンクで説明されているCSRより簡略になっていますが，
考え方は同じだと思います．

## 性能比較

ここで，CSR と `vector<vector<int>>` を使った場合の
SCC の性能比較を書くべきところですが，
ちょっといろいろあって，まだできていないので，
代わりに木DPで試してみました．

ランダムに作成した木の辺を与えて，各ノードの子孫のノードの数を
数えるというプログラムです．
木のノード数を$2\times 10^5$ 程度にしてみると，次のようになりました:

| Sとして何を使うか | `vector<vector<int>>` | CSR |
|---|---|---|
| 標準入力から `vector<pair<int, int>>` への読み込み | 47ms | 47ms (左と同じコード) |
| `vector<pair<int, int>>` から S への変換 | 48ms | 31ms |
| S を使って子孫ノード数を数える | 47ms | 14ms |


.... あっと驚くほどには違っていませんね．羊頭狗肉でした．

下は，性能比較に使ったファイルです．

* <a href="./cans.cc" download>ソースコード</a>
* <a href="./gen.py" download>テストデータ生成スクリプト</a>





