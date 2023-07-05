---
author: "yamate11"
title: "誤りの記録"
date: "2023-07-05T09:03:15+09:00"
# date_init: "2023-07-05"
tags: []
categories: ["topic"]
# categories: ["solution"]
# summary: "要約を書いておく．ここには問題タイトル等は不要" 
---

デバッグに失敗した，ないし，長時間かかった間違いの記録

## ABC212E Safety Journey

[問題へのリンク](https://atcoder.jp/contests/abc212/tasks/abc212_e)

2023/07/05 あさかつ

無向グラフが，完全グラフからM本の辺を除いたものとして与えられている．
除く辺は $(u, v)$ の形で与えられている．
dp[i][j] = (i 回の繰返し後，頂点 j に到達できる方法の数) という DP で，
全体から 除いた辺の分を引く．
$(u, v)$ と $(v, u)$ の両方を引かなければならないところ，
$(u, v)$ しか引かなかった．

