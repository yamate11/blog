---
author: "yamate11"
title: "距離: BFSとダイクストラ"
date: "2021-07-03"
tags: []
categories: ["topic"]
draft: false
---
距離を求める際の，ダイクストラ, 0-1BFS, BFSのコーディング方法のまとめです．

## ダイクストラ

* 前提: ノード間の距離δ(x,y)が全部非負
* 距離の候補をキューに入れていく．あるノードがキューから初めて取り出されたときにそのノードへの距離が確定する．
* `priority_queue<P, vector<P>, greater<P>> pque` と `vector<ll> dist` を用いる．(`using P = pair<ll, ll>`)
    * pque の値 (d, x) は，「ノード x へ，長さ d のパスがある」ことを示す．
    * priority_queue のメソッドは，push(), pop(), top()
* 初期化
    * pque の中身は，(0, 始点) のみ
    * dist は，始点のみ0; 他は LLONG_MAX
* ループ
    * pque から取り出した (d, x) について，
        * d = dist[x] なら，このdが最短であることが分かるので，先に進む．そうでなければ単に捨てる．
        * x の successor y について，newd = x + δ(x, y) が新しい距離の候補なので以下を行う．
            * dist[y] < newd なら，単に捨てる
            * そうでなければ，dist[y] を newd に更新して，(newd, y) を pque に入れる．

## 0-1 BFS

* 前提: ノード間の距離が0または1
* 基本的にはダイクストラの考え方だが，priority_queue の代わりに，deque が使える．
* `deque<P> deq` と `vector<ll> dist` を用いる．(`using P = pair<ll, ll>`)
    * deque のメソッドは，push_back(), push_front(), pop_front(), front()
* 初期化
    * ダイクストラと同じ (ただし，pque→deq)
* ループ
    * ダイクストラと同じ．ただし，「(newd, y) を pque に入れる」ところは:
        * δ(x, y) = 0 ならば，deq の左から，δ(x, y) = 1 ならば，deq の右から入れる

## BFS

* 前提: ノード間の距離が全部1
* ノードを初めて見たときに距離が確定する．キューには距離を入れる必要が無く，ノードだけで良い．
* `queue<ll> que` と `vector<ll> dist` を用いる．
    * que の値はノード．「自分の距離は確定したが，successor は未処理」のもの
    * queue のメソッドは，push(), pop(), front()
* 初期化
    * que の中身は，始点のみ
    * dist は，始点のみ0; 他は -1 (未確定を表す)
* ループ
    * que から取り出したノードの successor について，距離が未確定ならば，自分の距離 + 1 に確定して，そのまた successor たちを que に入れる．

  
