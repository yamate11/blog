---
author: "yamate11"
title: "最大流・最小カット"
date: "2022-02-20T06:32:36+09:00"
# date_init: "2022-02-20"
tags: ["最大流", "最小カット", "残余グラフ"]
categories: ["topic"]
# categories: ["solution"]
summary: "最大流と最小カットについてのコンテスト用のまとめです"
---

最大流と最小カットについてのコンテスト用のまとめです．

## 記号など

* $G = (V, E, C)$: グラフ
  * $V$: 頂点の集合
  * $E \subseteq V \times V$: 辺の集合．向きあり
  * $C: E \to \mathbb{R}$: 容量

* $e = (v, w) \in E$ のとき，$v = e^S$, $w = e^D$ と書く．
  $(w, v)$ を $e^R$ と書く．

* $f: E \to \mathbb{R}$ に対して，$v \in V$ での流出量
  $\textrm{out}(v) := \sum\\{C(e) \mid e^S = v\\} - \sum\\{C(e) \mid e^D = v\\}$．
  

* $s, t \in V$ ($s \neq t$) について，
  $f: E \to \mathbb{R}$ が $s$ から $t$ への
  流量 $F$ のフローである，とは，
  * $0 \leq f(v) \leq C(v)\quad$ ($v \in V$)
  * $\textrm{out}(v) = 0\quad$ ($v \in V \setminus \\{s, t\\}$)
  * $\textrm{out}(s) = F$
  * $\textrm{out}(t) = -F$

* $G_f = (V, E', C')$: 残余グラフ
  * $E' = E \cup \\{ e^R \mid e \in E \\}$
  * $e \in E'$ に対して，
    $C'(e) = C(e) - f(e) + f(e^R)\quad$
    ($e^R \not\in E$ ならば $f(e^R) = 0$ と解する)

## 最大流と最小カットの関係

$f$ が$s$から$t$への最大流の時，

* $S := \\{s\\} \cup \\{ v \in V \mid 
 \text{ 残余グラフ } G_f \text{ において }
 s \text{ から } v \text{ への正の流量のフローが存在する } \\}$
* $T := V \setminus S$

とする．

* $t \not\in T$ である．
* $(S, T)$ が最小カットを与える．すなわち，
  $s \in S'$, $t \in T'$ なる分割 $(S', T')$ のなかで，
  $\sum\\{ u(e) \mid e \in E, e^S \in S', e^D \in T' \\}$
  の最小値を与える．

## ACL を用いたコード

ACL (AtCoder Library) を用いてコードを書く場合には次のようになる．

```cpp
#include <atcoder/maxflow>
using namespace atcoder;

...

  ll N; cin >> N; // 頂点は {0, ..., N-1}
  mf_graph<ll> graph(N);
  ll M; cin >> M;
  REP(i, M) { cin >> u >> v >> c; graph.add_edge(u, v, c); } // 辺の定義

  ll f = graph.flow(0, N-1); cout << f << endl; // 最大流
  for (const auto& e : graph.edges()) if (e.flow > 0)   // フローの表示
    cout << e.from << "->" << e.to << " flow:" << e.flow << " / cap:" << e.cap << endl;

  vector<bool> mc = graph.min_cut(0);
  // flow() の直後に呼ぶ．
  // mc.size() == N であり，上の (残余グラフから作った) S に対して，mc[i] == true <=> i \in S
  ll c = 0;
  for (const auto& e : graph.edges()) if (mc[e.from] and not mc[e.to]) {
    c += e.cap;
    cout << e.from << " " << e.to << endl; // 最小カットの表示 }
  assert(f == c);  // 最大流 == 最小カット
```

## リンク

* [AtCoder Library](https://atcoder.github.io/ac-library/production/document_ja/) ... <atcoder/maxflow>
* [Dinic法とその時間計算量 (みはつさん)](https://misawa.github.io/others/flow/dinic_time_complexity.html) 



