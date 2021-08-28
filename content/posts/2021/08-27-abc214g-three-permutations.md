---
author: "yamate11"
title: "Three Permutations - ABC 214 G"
date: "2021-08-27T19:04:12+09:00"
# date_init: "2021-08-27"
tags: ["DP", "円環DP", "順列", "包除原理"]
# categories: ["topic"]
categories: ["solution"]
summary: "調べた結果分かった解法を記述します．いろいろ勉強になりました．" 
---

AtCoder Beginner Contest 214 - ABC 214 G - Three Permutations の解法です．

解説ACです．
[公式解説](https://atcoder.jp/contests/abc214/editorial/2442)
も参考になりましたが，それだけでは解答は作れませんでした．
[kmjpさんのブログ](https://kmjp.hatenablog.jp/entry/2021/08/16/0900)
が助けになりました．ありがとうございます．

## 問題へのリンク

https://atcoder.jp/contests/abc214/tasks/abc214_g

## 問題概要

$1, \ldots, N$ の順列の全体を $\textrm{Perm}$ と書く．
$p, q \in \text{Perm}$ が与えられる．
条件「$x = p(i)$ または $x = q(i)$」を，$\text{Coi}(x, i)$ と書く
ことにする．
$r \in \text{Perm}$ に対して，
$C(r) := \\{ i \in [1, N] \mid \text{Coi}(r(i), i) \\}$
とする．
集合 $\\{r \in \text{Perm} \mid C(r) = \varnothing \\}$
の要素数を mod $10^9 + 7$ で求めよ．

## 解法

$r \in \text{Perm}$，
$X \subseteq [1, N]$， $k \in [0, N]$ に対して，次のように書くことにする:
* $S(X) := \\{r \in\text{Perm} \mid X \subseteq C(r) \\}$
* $R_k := \sum \\{ |S(X)| \mid X \subseteq [1, N],\\; |X| = k \\}$
* $r \downarrow X := r$ の定義域を $X$ に制限したもの 
* $\text{Perm}'(X) := \\{ r \downarrow X \mid r \in \text{Perm} \\}$
* $S'(X) := \\{ r \downarrow X \mid r \in S(X) \\}
         = \\{r' \in \text{Perm}'(X) \mid \forall i \in X.\\; 
         \text{Coi}(r'(i), i) \\} $

包除原理により，求める答は
$N! - \sum_{k=1}^{N} (-1)^{k - 1} R_k$
となるから，各$k$ に対する $R_k$ を求めれば良い．
また，$|S(X)| = |S'(X)| \times (N - |X|)!$ であるから，
$\sum\\{ |S'(X)| \mid X \subseteq [1, N],\\; |X| = k \\}$
を求めれば良い．

集合 $[1, N]$ 上で，すべての $(p_i, q_i)$ を
結んだグラフを考える．どの頂点も次数は2以下である．
連結成分は，自己ループか，サイクルかのいずれかである．
連結成分全体の集合を $\mathcal{Z}$ と書く．
$Z\in \mathcal{Z}$ に対して，
$Z$内にある辺に対応する番号の集合を
$I(Z) := \\{ i \in [1, N] \mid p(i), q(i) \in Z \\}$ と書く．
$S'(X)$ の要素 $r$ は，各連結成分$Z$に，
$\sum_{Z \in \mathcal{Z}} t_Z = |X|$ となるように非負整数 $t_Z$ を
割り当てて，$Z$から$t_Z$本の辺に対して端点を選択することによって
決まる．正確には，

* $Q(Z, t) := \\{ r \in S'(Y) \mid Y \subseteq I(Z), \\; |Y| = t \\}$
* $Q(t) := \\{ ((Z, r_Z) \mid Z \in \mathcal{Z} )
           \mid r_Z \in Q(Z, t_Z),\\; \sum_{Z \in \mathcal{Z}} t_Z = t\\}$
* $\rho_t : \bigcup \\{ S'(X) \mid |X| = t \\}  \to Q(t), \\;
  \rho(r) = ( r \downarrow I(Z) \mid Z \in \mathcal{Z} )$

と書いたときに，$\rho_t$ が全単射を与える．したがって，
$|Q(t)|$ を求めれば良い．

まず，$|Q(Z, t)|$ を求めよう．これは，$t$ にはもちろん依存するが，
$Z$ に関しては，そのサイズ $s = |Z|$ にしか依存しないのは明らかであるので，
$|Q(Z, t)|$ を $f(s, t)$ と書くことにする．

まず，あきらかに，$ f(1, 1) = 1$であり，$t > 1$ のとき，$f (1, t) = 0$ である．
$s >= 2$ については，DP で求める．
$Z$ が円環状になっているので，次のように構成する．
$I(Z)$ を $\\{ x_1, x_2, \ldots, x_s \\}$ と，
$q(x_{i}) = p(x_{i+1})$ が成り立つように列挙する．

* dp1[i][t][a][b] := 次を満たす r の数:   ($a, b \in \\{0, 1, 2\\}$)
  * $ \text{dom}(r) \subseteq \\{ x_1, \ldots, x_i \\} $
  * $ t = |\text{dom}(r)| $
  * a = 0: $x_s \not\in \text{dom}(r)$ と矛盾しない．
  * a = 1: $r(x_s) = p(x_s)$ と矛盾しない．
  * a = 2: $r(x_s) = q(x_s)$ と矛盾しない．
  * b = 0: $x_i \not\in \text{dom}(r)$
  * b = 1: $r(x_i) = p(x_i)$
  * b = 2: $r(x_i) = q(x_i)$
* 初期値
  * dp1[0][0][a][0] = 1   (a = 0,1,2)
  * dp1[0][1][a][1] = 1   (a = 0,1)
  * dp1[0][1][a][2] = 1   (a = 0,1,2)
* 遷移
  * dp1[i+1][t][a][0] += dp[i][a][b]  (b = 0,1,2)
  * dp1[i+1][t+1][a][1] += dp[i][a][b]  (b = 0,1)
  * dp1[i+1][t+1][a][2] += dp[i][a][1]  (b = 0,1,2)

DP実行後，$f(s, t) = dp1[s][t][0][0] + dp1[s][t][1][1] + dp1[s][t][2][2]$
で，$f$ が決定できる．
計算を振り返ってみると，$s$ ごとに別々にDPを実行する必要はなく，
1回のDPを $\max(|Z|)$ まで実行することで，
すべての必要な $f(s, t)$ を計算することができる．
このDPの計算量は $O(N)$ である．

この準備のもとで，$|Q(t)|$ は，次のDPで求めることができる．

* $\text{dp2}\[i][t] := |\\{ ((j, r_j \mid j \leq i) \mid r_j \in Q(Z, t_j),\\;
                  \sum_{j\leq i}t_j = t \\} |$
* 遷移: $\text{dp2}\[i][t] = 
          \sum_{s < t} (\text{dp2}\[i-1][s] \times f(|Z_i|, t - s))$

このDP実行終了後，$u := |\mathcal{Z}|$ として，
$|Q(t)| = \text{dp2}[u][t]$ である．
計算量が心配になるが，遷移の式に現れる積の計算の回数は，
$|Z_i| = a_i$ として，
$a_1 + a_1 * a_2 + (a_1 + a_2) * a_3 + ...+ (a_1 + ... + a_{u-1}) * a_u
 \leq (a_1 + ... + a_u)^2 = N^2$ なので，$O(N^2)$ である．

## ACコード

https://atcoder.jp/contests/abc214/submissions/25379311

