---
author: "yamate11"
title: "距離: BFSとダイクストラ"
date: "2021-08-09"
date_init: "2021-07-03"
tags: []
categories: ["topic"]
draft: false
---
距離を求める際の，ダイクストラ, 0-1BFS, BFSのコーディング方法のまとめです．

## 記法

ノードを表すデータ型を Node とする．`int` や `long long` や `pair<int, int>`
など．


## ダイクストラ

* 前提: ノード間の距離δ(x,y)が全部非負
* 距離の候補を優先度付きキューに入れていく．
あるノードがキューから初めて取り出されたときにそのノードへの距離が確定する．
* 使用するデータと初期化
    * priority_queue のメソッドは，push(), emplace(), pop(), top() など．

```cpp
using P = pair<ll, Node>;                      // 距離とノード
priority_queue<P, vector<P>, greater<P>> pque; // 優先度付きキュー
        // 値 (d, x) は，ノードxへ，長さdのパスがあることを示す．
pque.emplace(0, initial_node);                 // 始点をキューに
vector<ll> dist(N, LLONG_MAX);                 // 距離．始点以外は∞
        // Node型 によっては，map<Node, ll> dist; など．
dist[initial_node] = 0;                        // 始点の距離は0
```

* ループ
    * pque から取り出した (d, x) について，
        * dist\[x] < d なら，もっと良い d があるということなので，単に捨てる．
          そうでなければこの d が x への最短距離であることが確定したので，
          先に進む．
        * x の 隣接ノード y について，newd = x + δ(x, y) が
          y への距離の候補なので以下を行う．
            * dist[y] <= newd なら，単に捨てる
              そうでなければ，先に進む．
            * dist[y] を newd に更新する．
            * (newd, y) を pque に入れる．

* ゴール
    * キューから取り出した時点で判断する．
      キューに入れる時点では，後からもっと短いものがくるかもしれない．

## 0-1 BFS

* 前提: ノード間の距離 δ(x,y) がどれも 0 または 1．
* 基本的にはダイクストラの考え方だが，
  優先度付きキューの代わりに，両端キューが使える．
* 使用するデータと初期化
    * 基本的には，ダイクストラと同じ．
    * deque のメソッドは，
      { push | emplace | pop }_{ back | front }(), back(), front() 
      など．

```cpp
using P = pair<ll, Node>;                      // 距離とノード
deque<P> deq;                                  // 両端キュー
        // 値 (d, x) は，ノードxへ，長さdのパスがあることを示す．
deq.emplace_back(0, initial_node);             // 始点をキューに
vector<ll> dist(N, LLONG_MAX);                 // 距離．始点以外は∞
        // Node型 によっては，map<Node, ll> dist; など．
dist[initial_node] = 0;                        // 始点の距離は0
```

* ループ
    * 基本的にはダイクストラと同じ．違うのは，キューに入れるところだけ．
    * deq から取り出した (d, x) について，
        * dist\[x] < d なら，もっと良い d があったということなので，
          単に捨てる．
          そうでなければこの d が x への最短距離であることが確定したので，
          先に進む．
        * x の 隣接ノード y について，newd = x + δ(x, y) が
          y への距離の候補なので以下を行う．
            * dist[y] <= newd なら，単に捨てる．
              そうでなければ，先に進む．
            * dist[y] を newd に更新する．
            * (newd, y) を deq に挿入する．
              * δ(x, y) = 0 なら，deq の左から挿入する．
              * δ(x, y) = 1 なら，deq の右から挿入する．

* ゴール
    * ダイクストラと同じ．deq から取り出すときに判断する．
      (δ(x,y) = 0 なら入れるときに確定するが，気にしなくても良いであろう)

## BFS

* 前提: ノード間の距離が全部1
* ノードを初めて見たときに距離が確定する．
  FIFOキューには距離を入れる必要が無く，ノードだけで良い．
* 使用するデータと初期化
    * queue のメソッドは，push(), emplace(), pop(), front(), back() など．

```cpp
queue<Node> que;                   // FIFOキュー
    // キューに入っているノードは，
    // 「自分の距離は確定したが，隣接ノードは未処理」のもの
que.push(initial_node);            // 始点をキューに
vector<ll> dist(N, -1);            // 距離．始点以外は未確定
    // Node型 によっては，map<Node, ll> dist; など．
dist[initial_node] = 0;            // 始点の距離は0
```

* ループ
    * que から取り出したノード x の各隣接ノード y について，
        * dist\[y] >= 0 (すでに距離が確定) の場合は，単に捨てる．
          未確定ならば，先に進む．
        * dist\[y] に dist\[x] + 1 を設定する．
        * y をキューに入れる．

* ゴール
    * dist\[\] に値を設定するときに判断する．
