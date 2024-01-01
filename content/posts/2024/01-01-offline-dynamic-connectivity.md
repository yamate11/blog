---
author: "yamate11"
title: "Offline Dynamic Connectivity"
date: "2024-01-01T12:09:02+09:00"
# date_init: "2024-01-01"
tags: []
categories: ["topic"]
# categories: ["solution"]
summary: "オフライン動的連結ライブラリです"
---

## 要約

Offline dynamic connectivity のライブラリです．

次のクエリを処理します．

* type 1 : ノード x と y を無向辺でつなぐ
* type 2 : ノード x と y の間の無向辺を削除する
* type 3 : この時点での接続関係に関する UnionFind 木にアクセスできるので，
  それを用いてなんらかの判定を行う．たとえば，ノード x と y
  が同一連結成分に属するかどうか，などが判定できる．

「offline」なので，クエリ全体を最初に全部読めることが必要です．

