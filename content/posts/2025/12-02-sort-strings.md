---
author: "yamate11"
title: "文字列をソートするときの計算量"
date: "2025-12-02T20:00:25+09:00"
# date_init: "2025-12-02"
tags: []
categories: ["topic"]
# summary: "要約を書いておく．ここには問題タイトル等は不要" 
---

文字列のリスト $(s_i \mid i < N)$ をソートする場合の時間計算量についての雑多なまとめ．
$S := \sum_i |s_i|$ とする．

## 1. 辞書順ソート

2つの文字列 $s$, $t$ の比較は，$O(\min(|s|, |t|))$ でできると仮定する．
もちろん，全体の計算量が $O(SN \log N)$ であるとはいえる．

### 1.1 一般

一般のソートアルゴリズムについては，それ以上のことはあまり言えないらしい．

### 1.2 マージソート

#### 1.2.1 計算量

マージソートならば，計算量は $O(S \log N)$ になる．
全体で $\log N$ 段のマージを行うわけだが，各段の 長さ $L \to 2L$ のマージを考えると，
毎回1つずつが処理されてマージ済の方に送られるのだが，この処理は，
どちらの文字列の長さについてもそれ以下のコストで行えるので，とくに，マージ済の方に送られる文字列の
長さ以下のコストである．したがって，このマージにかかるコストは $2L$ 以下であり，つまり，
この段のコストは $S$ 以下である．

#### 1.2.2 実装

もちろんマージソートを書いても良いわけではあるが，
[ABC354-B の解説「文字列をソートする計算量について」](https://atcoder.jp/contests/abc354/editorial/10001) 
によると，C++ の `std::stable_sort` は，マージソートで実装されていることが多いそうである．

## 2. 連結最小

$\sigma = (s_i \mid i < N)$ を任意の順序で連結したときの (辞書順による) 最小のものを求める，という典型問題がある．
関係する問題には，次がある:

* Educational Codeforces 9-C "The smallest String Concatenation"
  ( [問題](https://codeforces.com/contest/632/problem/C))
* ABC225-F "String Cards" ( [問題](https://atcoder.jp/contests/abc225/tasks/abc225_f))
* ABC434-F "Concat (2nd)" ( [問題](https://atcoder.jp/contests/abc434/tasks/abc434_f))

この場合，$s \prec t$ を，$s + t < t + s$ ($+$ は連結，$<$ は通常の辞書順) で定義すると，
これは半順序になる (たとえば `"abc"` と `"abcabc"` は比較不能で，全順序ではない)．
なお，$s \prec t \iff s^\infty < t^\infty$ が成り立つ．

この順序で $\sigma$ をソートして連結したものが，求めるものになる．
忘れていたが，以前[証明を書いた](http://localhost:5080/blog/posts/2021/11-03-abc225-f-string-cards/) ようだ
(頑張って書いたのはABC225-Fの解法で，この証明はまあ簡単)．

このソートは，マージソートを使ったとしても，$O(S \log N)$ では済まない (らしい．ABC434-F でたくさん TLE を出した)．
長い文字列がずっと比較対象になると，たとえ相手が短くても要する時間は長い方に引っ張られる．
いろいろ手があるらしい．

* [公式解説その1](https://atcoder.jp/contests/abc434/editorial/14670):
  各 $s_i$ の Z-string を保持しておく．$s_i \prec s_j$ の判定を，短い方の長さ分までは愚直に見ていって，
  そこが尽きると，長い方の文字列の Z-string を利用できる形になる．
  結局，判定が $O(\min(|s_i|, |s_j|))$ で可能になるので，辞書順ソートの場合と同じ計算量になる．
* [公式解説その2](https://atcoder.jp/contests/abc434/editorial/14680):
  マージソートを少し変更する．先頭同士を比べるのでなく，片方の先頭が，もう片方の列のどこまでより小さいか二分探索する．
  これを両方の先頭について交互に行う．こうすることで，特定の要素がたかだか $\log N$ 回しか比較されないようになるので，
  全体として $O(S\log^2N)$．
* [PCTprobabilityさんのtweet](https://x.com/PCTprobability/status/1994763603766088093):
  各 $s_i$ のローリングハッシュを作っておけば，$s_i \prec s_j$ の判定が $O(\log S)$ で可能だから，
  トータルで $O(N \log N \log S)$．


keywords: complexity, string, sort
