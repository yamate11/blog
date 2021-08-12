---
author: "yamate11"
title: "Atcoder Beginner Contest 213 H - Stroll"
date: "2021-08-11"
tags: ["オンラインDP", "オフラインDP", "分割統治DP", "DP", "分割統治FFT", "FFT"]
categories: ["solution"]
draft: false
---

Atcoder Beginner Contest 213 (ABC-213) H - Stroll に関する記事です．

## 問題へのリンク

<div class="iframely-embed"><div class="iframely-responsive" style="height: 140px; padding-bottom: 0;"><a href="https://atcoder.jp/contests/abc213/tasks/abc213_h" data-iframely-url="//cdn.iframe.ly/HurOZMX"></a></div></div><script async src="//cdn.iframe.ly/embed.js" charset="utf-8"></script>

## 解法

[公式解説](https://atcoder.jp/contests/abc213/editorial/2396) 
を読んでもよくわからなかったのですが，
[Motsu_xeさんによる，オフライン・オンライン変換](https://motsu-xe.hatenablog.com/entry/2020/10/13/195949)
の説明がわかりやすかったです．
以下の説明は，ほとんど，上の2つの記事に依っています．


記法を定めます．

* $f(x, i) :=$ 地点$x$に距離$i$で到達する方法の数
* $p(x, y, i) :=$ 地点 $x$ と地点 $y$ を結ぶ距離 $i$ の道の数
* $X := \\{1, \ldots, N\\}$

したがって，$f(1, T)$ が求める答です．次の関係が成り立ちます:

* $f(1, 0) = 1$
* $f(y, 0) = 0\quad(y \neq 1)$
* $f(x, i) = \sum \\{ f(y, j) \cdot p(x, y, i - j) \mid y \in X, j \in [0, i) \\}$

最後の式は，一見，畳み込みですが，右辺にも $f$ が出てきてしまうので，
ただちには FFT に渡せません．ここを
分割統治FFTなる手法で求めようという趣旨であるようです．

さらに記法です．上の最後の式を少しいじります．

* $ s(x, i, l, m) := \sum \\{ f(y, j) \cdot p(x, y, i - j) \mid y \in X, j \in [l, m) \\}$

見比べて，次が成り立ちます:

* $ f(x, i) = s(x, i, 0, i) $

DPで，dp[x, i] を計算していきます．
2つの手続き solve(l, r) と induce(l, m, r) を次のように定めます．
`a:b` は，Python風に半開区間 `[a,b)` を表すものとします．
配列 v に対して，v[a:b] は，vの，添字a以上b未満の部分です．

```
procedure solve(l, r) {
    assume(forall i \in [0,l), x \in X.  dp[x, i] == f(x, i))
    assume(forall i \in [l,r), x \in X.  dp[x, i] == s(x, i, 0, l))
    if (l + 1 == r) return;
    m := floor((l + r) / 2);
    call solve(l, m);
    call induce(l, m, r);
    call solve(m, r);
    assert(forall i \in [0,r), x \in X.  dp[x, i] == f(x, i))
}

procedure induce(l, m, r) {
    assume(forall i \in [0,m), x \in X.  dp[x, i] == f(x, i))
    assert(forall i \in [m,r), x \in X.  dp[x, i] == s(x, i, 0, l))
    for (x,y such that p[x,y] is non-zero) {
        v1 = convolution(dp[x][l:m], p[x, y][0:r-l])
        dp[y][m:r] += v1[m-l:r-l]
        v2 = convolution(dp[y][l:m], p[x, y][0:r-l])
        dp[x][m:r] += v2[m-l:r-l]
    }
    assert(forall i \in [0,m), x \in X.  dp[x, i] == f(x, i))
    assert(forall i \in [m,r), x \in X.  dp[x, i] == s(x, i, 1, m))
}
```

$f(x, i) = s(x, i, 0, i)$ であることと，
assume と assert の主張から，
`dp[x, i] == s(x, i, 0, g(i))` (for all x \in X) となる関数 g が，
solve と induce によって，以下のように変化することが分かります．


<img src="fig1.png">

induce を実行する際に，dp[.][l:m] が f(.)[l:m] に一致しているので，
(オフラインになって)
ここに FFT が使える，ということになります．

以下を実行すると，答が `dp[1][T]` に求められます．

```
for x in 1:(N+1) { dp[x, 0] := if x == 1 then 1 else 0 }
solve(0, T + 1)
```

計算量については特に付け加えることはないので，参照している記事をご覧下さい．

## ACコード

https://atcoder.jp/contests/abc213/submissions/24966725

#### keywords

["オンラインDP", "オフラインDP", "分割統治DP", "DP", "分割統治FFT", "FFT"]
