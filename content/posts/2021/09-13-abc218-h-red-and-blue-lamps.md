---
author: "yamate11"
title: "Red and Blue Lamps - AtCoder Beginner Contest 218 H"
date: "2021-09-13T08:11:41+09:00"
# date_init: "2021-09-13"
tags: ["貪欲"]
# categories: ["topic"]
categories: ["solution"]
summary: "公式解説にある貪欲法の証明を詳しく書きました．"
---

AtCoder Beginner Contest 218 (ABC 218) H - Red and Blue Lamps 
に関する記事です．
コンテストでは解けませんでした (到達しませんでした) し，
後で考えても分かりませんでした．
まだ公式解説の3つの解法のうち，最初のしか読んでいませんが，
正当性証明が良く分からなかったので，少し詳しく書きます．

## 問題概要

```
2以上の整数N, 正の整数Rと 正の整数の列 (A_i : i ∈ [1,N-1])が与えられる．
X ⊆ [1,N] を，|X| = R となるようにとるとき，
S := \sum { A_i : i と i+1 のうち片方のみが X に属する．}
の最大値を求めよ．

制約: N <= 2×10^5, A_i <= 10^9
```

[問題へのリンク](https://atcoder.jp/contests/abc218/tasks/abc218_h) 

## 解法

R > N/2 なら，X の代わりに [1,N] - X を考えれば良いので，R <= N/2 として
良い．

i と i+1 が X に属しているような i は，無いとして良い．

理由: そういうものがあったとする．
R <= N/2 なので，以下のいずれかが成り立つ

* $1 \not\in X$
* $N \not\in X$
* $j \not\in X$, $j + 1 \not\in X$ なる $j$ がある．

どの場合も同様なので，3番目が成り立つ場合のみ扱う．
これをみたす $j$ を1つとる．以下のいずれかが成り立つ．

* $i+1 < j$, $i\in X$, $i+1\in X$ なる $i$ がある．
* $j+1 < i$, $i\in X$, $i+1\in X$ なる $i$ がある．

どちらも同様なので，上が成り立つ場合のみ扱う．これを満たす最大の $i$ を
とる．

$i+1$ を $X$ から取り除き，$i+2$ を $X$ に加える．$i+3\in X$ なら終了．
そうでなければ $i+3$ を $X$ から取り除き，$i+4$ を $X$ に加える．
以下同様にこの操作をできるだけ繰り返す．
遅くとも $j$ に到達するまでに，この操作は終了する．
この操作によって，Sの値は増加し，|X|の
値は変化しない．
(理由終わり)

$i \in [1,N]$ に対して，$B_i := A_{i-1} + A_{i}$ とする
(ただし，$A_0 := A_N := 0$)．
上のことから，問題を次のように言い換えられる: 
$|X| = R$ なる $X \subseteq [1, N]$ を，どの $i\in [1,N-1]$ に対しても
$i\not\in X$ と $i+1\not\in X$ のすくなくともどちらかが成り立つように
取るとき，$S(X) := \sum_{i \in X} B_i$ の最大値を求めよ．

記法として，$r - l$ が偶数の時，
$E(l, r) := \\{l, l + 2, \ldots, r - 2, r\\}$ と書くことにする．
特に $E(l, l) = \\{l\\}$．また，$l > r$ のとき，$E(l, r) = \varnothing$．

#### 主張1

$X$ が $R$ に対する最大値を与える選択方法，
$Z$ が $R + 1$ に対する最大値を与える選択方法であり，
区間$I = [p, q]$ について $|X\cap I| + 1 = |Z\cap I|$ であり，
$p \not\in X, q \not\in X, p \not \in Z, q \not\in Z$ とする．
$J := [1, N] \setminus I$ とするとき，
$Y := (X \cap J) \cup (Z \cap I)$ は，$R + 1$ に対する最大値を与える
選択方法である．

#### 証明

$|Y| = R+1$ であることと，$i\in Y, i+1\in Y$ となる $i$ が存在しない
ことは明らかであるから，
$S(X \cap J) \geq S(Z \cap J)$ を言えば良いが，そうでないとすると，
$X' := (Z \cap J) \cup (X \cap I)$ が，$R$ に対して $X$ よりも
良い解を与えることになってしまい，矛盾する．
(終)．

#### 主張2

$X$ が $R$ に対する最大値を与える選択方法であるとき，
$R+1$ に対する最大値を与える選択方法 $Y$ で，次のようなものが存在する:
$l, r \in [1, N]$ で，$l \leq r$ かつ $r - l$ が偶数となるものが存在して，
以下が成り立つ．

* $[1, l)$ と $(r, N]$ では，$X$ と $Y$ は一致する．すなわち，
  $ J := [1, l) \cup [r, N] $ と書くとき，$X \cap J = Y \cap J$
* $X \cap [l, r] = E(l + 1, r - 1)$
* $Y \cap [l, r] = E(l, r)$

#### 証明

$R+1$に対する最大値を与える選択方法 $Z$ を1つとる．
$X\cap Z$ = $\\{t_1, \ldots, t_k\\}$ と書いて，区間
$[1, t_1), (t_1, t_2), \ldots, (t_k, N]$ を考える．これらの区間の
少なくとも一つ $I$ においては，$|X\cap I| < |Z\cap I|$ が成り立つ．
$Z\cap I = \bigcup_{i = 1}^{m} E(l_i, r_i) $; 
ただし，$l_i \leq r_i$，$r_{i} +3 \leq l_{i+1}$ と書いたとき，
$[l_i - 1, r_i + 1]$ たちは共通部分を持たないので，
$|[l_i - 1, r_i + 1] \cap X| < |[l_i - 1, r_i + 1] \cap Z|$
となる $i$ が存在する．
ここで，$[l_i - 1, r_i + 1] \cap Z = E(l_i, r_i)$ であるから，
$p + 2 \leq q$ なる $p, q \in E(l_i - 1, r_i + 1) \setminus X $ 
をとることができ，
さらに，$[p + 2, q - 2] \cap X = E(p + 2, q - 2)$ とすることができる．
$ l := p + 1 $, $r := q - 1$, 
$ Y := (X \cap J) \cup E(l, r)$
とする．各種関係式は，それが成り立つようにとった．
$Y$ が $R+1$に対する最大値を与える選択方法であることは，主張1から従う．
(終)．

したがって，以下のように貪欲に取っていけば良い．

* 最初は，$E(i,i)$ たちが候補になる．実際に取るのは，これらのうち，
  値が最大のもの
* 最初の $E(i_0, i_0)$ が決まったら，新たに $E(i_0 - 1, i_0 + 1)$ が
  候補になる．この候補に対する得点は，
  $S(E(i_0 - 1, i_0 + 1)) - S(E(i_0, i_0))$ である．
  一般に，$E(l, r)$ を取ることが決まったら，新たに
  $E(l - 1, r + 1)$ が候補になる．ただし，たとえば，すでに
  $E(r + 1, m)$ が候補になっているときには，
  $E(r + 1, m)$ は候補から外され，
  $E(l - 1, r+ 1)$ ではなく，$E(l - 1, m)$ が新たな候補になる．
  左側についても同様．

候補とその得点のペアを (得点を優先度として) 優先度付きキューで
管理し，各端点がどの端点との組で候補になっているかをベクトルで
管理することで，全体として $O(R \log N)$ で答が求められる．

  
## ACコード

https://atcoder.jp/contests/abc218/submissions/25850606

```cpp
int main(/* int argc, char *argv[] */) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout << setprecision(20);

  ll N, R; cin >> N >> R;
  if (R > N / 2) R = N - R;
  vector<ll> A(N+1), B(N), P(N);
  for (ll i = 1; i < N; i++) cin >> A[i];
  for (ll i = 0; i < N; i++) B[i] = A[i] + A[i + 1];
  using sta = tuple<ll, ll, ll>;
  priority_queue<sta> pque;
  for (ll i = 0; i < N; i++) {
    P[i] = i;
    pque.emplace(B[i], i, i);
  }
  ll ans = 0, cnt = 0;
  while (true) {
    auto [m, p, q] = pque.top(); pque.pop();
    if (P[p] != q || P[q] != p) continue;
    ans += m;
    if (++cnt == R) break;
    assert(! (q == N-1 && p == 0));
    if (q == N-1) {
      assert(p - 1 >= 0);
      P[p - 1] = -1;
    }else if (p == 0) {
      assert(q + 1 < N);
      P[q + 1] = -1;
    }else {
      ll u = P[p - 1];
      ll v = P[q + 1];
      ll new_m = B[u] + B[v] - m;
      pque.emplace(new_m, u, v);
      P[u] = v;
      P[v] = u;
      B[u] = B[v] = new_m;
    }
  }
  cout << ans << endl;

  return 0;
}
```
