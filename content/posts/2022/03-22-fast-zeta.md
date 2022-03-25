---
author: "yamate11"
title: "ゼータ変換，メビウス変換，高速ゼータ変換, 高速メビウス変換"
date: "2022-03-22T19:59:40+09:00"
# date_init: "2022-03-22"
tags: ["ゼータ変換", "高速ゼータ変換"]
categories: ["topic"]
# categories: ["solution"]
summary: "高速ゼータ変換について，自分用にまとめた記事です．"
---

(高速)ゼータ変換，(高速)メビウス変換については，
良い記事がたくさんありますので，1つ足してもしょうがないのですが，
自分用にまとめました．

## ゼータ変換，メビウス変換

$F$ を有限集合とする．その冪集合を $\mathcal{P}(F)$ と書く．
$x \in \mathbb{N}$ に対して $\bar{x} := \\{0, 1, \ldots, x-1\\}$ と書く．

$M$ を加群として，
関数 $f: \mathcal{P}(F) \to M$ に対して，そのゼータ変換
$\zeta(f): \mathcal{P}(F) \to M$ を，

\begin{equation}
\zeta(f)(X) = \sum \\{ f(Y) \mid Y \subseteq X\\}
\end{equation}

で定義する．あるいは，

\begin{equation}
\zeta(f)(X) = \sum \\{ f(Y) \mid Y \supseteq X\\}
\end{equation}

で定義することもある．
$f$ のメビウス変換 $\mu(f): \mathcal{P}(F) \to M$
を，ゼータ変換の定義が(1)のときには，

\begin{equation}
\mu(f)(X) = \sum\\{ (-1)^{|X \setminus Y|}f(Y) \mid Y \subseteq X \\}
\end{equation}

で，(2)のときには

\begin{equation}
\mu(f)(X) = \sum\\{ (-1)^{|X \setminus Y|}f(Y) \mid Y \supseteq X \\}
\end{equation}

で定義する．

#### 定理1

> $\zeta$ と $\mu$ は互いに他の逆変換である．

#### 系2 (包除原理)

> 各 $i = 0, \ldots, n-1$ に対して $A_i \subseteq U$ が定められている時，
  $$ \left|\bigcup_{i \in \overline{n}} A_i\right| =
     \sum \left\\{ (-1)^{|X| + 1} \left|\bigcap_{i \in X} A_i\right| \mid X \in \mathcal{P}(\bar{n}) \setminus \\{ \emptyset \\} \right\\} $$

#### 系2の証明

(2),(4)の定義を用いる．

$X \subseteq \bar{n}$ に対し，
$f(X) := |\bigcap_{i \in X} A_i \cap \bigcap_{i \not\in X} (U \setminus A_i)|$
とすれば，$|\bigcap_{i \in X} A_i| = \zeta(f)(X)$ となる．
特に $|U| = \zeta(f)(\emptyset) $ である．

$|U| - \text{(左辺)} % = |\bigcup_{i \in \overline{n}} A_i|
= |\bigcap_{i \in \overline{n}} (U \setminus A_i)|
= f(\emptyset)
$

$|U| - \text{(右辺)} = 
   \sum \\{ (-1)^{|X|} |\bigcap_{i \in X} A_i| \mid X \in \mathcal{P}(\bar{n}) \\} 
= \sum \\{ (-1)^{|X|} \zeta(f)(X) \mid X \in \mathcal{P}(\bar{n}) \\}
$ $= \mu(\zeta(f))(\emptyset)
= f(\emptyset)
$

(終)

## 定理1の証明

以下，この節では(1)と(3)を採用する．(2)と(4)の場合も同様にできる．

簡単のため $F = \bar{n}$ の場合で考える．

$X, Y \subseteq \bar{n}$ に対して，
$Y\subseteq^i X$ を，以下の2条件が成り立つこととして定義する:

* $Y \cap \bar{i} \subseteq X \cap \bar{i}$
* $Y \cap (\bar{n} \setminus \bar{i}) =
   X \cap (\bar{n} \setminus \bar{i})
  $

補題1は定義から従う．

#### 補題1

> \begin{align*}
  Y \subseteq^0 X &\iff Y = X \\\\
  Y \subseteq^n X &\iff Y \subseteq X \\\\
  Y \subseteq^{i+1} X &\iff \begin{cases}
    Y \subseteq^{i} X & \text{ if } i \not\in X \\\\
    Y \subseteq^{i} X \text{ or } Y \subseteq^{i} X \setminus \\{i\\}
    & \text{ if } i \in X \\\\
  \end{cases}
\end{align*}

次のように定義する:

\begin{align*}
\zeta^i(f)(X) &= \sum \\{f(Y) \mid Y \subseteq^i X\\} \\\\
\mu^i(f)(X) &= \sum \\{(-1)^{|X \setminus Y|}f(Y) \mid Y \subseteq^i X\\} \\\\
\end{align*}

補題2は，定義から従う．

#### 補題2

> \begin{align*}
  \zeta^0(f)(X) &= f(X) \\\\ \mu^0(f)(X) &= f(X) \\\\
  \zeta^n(f)(X) &= \zeta(f)(X) \\\\ \mu^n(f)(X) &= \mu(f)(X) \\\\
  \zeta^{i+1}(f)(X) &= \begin{cases}
    \zeta^{i}(f)(X) & \text{ if } i \not\in X \\\\
    \zeta^{i}(f)(X) + \zeta^{i}(f)(X \setminus \\{i\\}) & \text{ if } i \in X \\\\
  \end{cases}\\\\
  \mu^{i+1}(f)(X) &= \begin{cases}
    \mu^{i}(f)(X) & \text{ if } i \not\in X \\\\
    \mu^{i}(f)(X) - \mu^{i}(f)(X \setminus \\{i\\}) & \text{ if } i \in X \\\\
  \end{cases}
\end{align*}

#### 補題3

> \begin{align*}
\zeta^{i + 1}(\mu^{i + 1}(f))(X) &= \zeta^{i}(\mu^{i}(f))(X) \\\\
\mu^{i + 1}(\zeta^{i + 1}(f))(X) &= \mu^{i}(\zeta^{i}(f))(X) \\\\
\end{align*}

#### 証明

上のみ示す．下も同様．

$i \not\in X$ のときは，補題1,2より

\begin{align*}
\zeta^{i + 1}(\mu^{i + 1}(f))(X)
= \sum\\{\mu^{i}(f)(Y) \mid Y \subseteq^{i} X \\} 
= \zeta^{i}(\mu^{i}(f))(X)
\end{align*}

$i \in X$ のときは，補題1より

\begin{align*}
\zeta^{i + 1}(\mu^{i + 1}(f))(X)
& = \sum\\{\mu^{i+1}(f)(Y) \mid Y \subseteq^{i+1} X \\} \\\\
& = \sum\\{\mu^{i+1}(f)(Y) \mid i \in Y \subseteq^{i+1} X \\}
  \+ \sum \\{\mu^{i+1}(f)(Y) \mid i \not\in Y \subseteq^{i+1} X \\} \\\\
\end{align*}

となり，ここで補題2より

\begin{align*}
\text{第1項}
& = \sum\\{\mu^{i+1}(f)(Y) \mid Y \subseteq^{i} X \\} \\\\
& = \sum\\{\mu^{i}(f)(Y) - \mu^{i}(f)(Y \setminus \\{i\\})
           \mid Y \subseteq^{i} X\\} \\\\
\end{align*}

\begin{align*}
\text{第2項}
& = \sum\\{\mu^{i+1}(f)(Y) \mid Y \subseteq^{i} X \setminus \\{i\\} \\} \\\\
& = \sum\\{\mu^{i}(f)(Y) \mid Y \subseteq^{i} X \setminus \\{i\\} \\} \\\\
& = \sum\\{\mu^{i}(f)(Y \setminus \\{i\\} ) \mid Y \subseteq^{i} X \\} \\\\
\end{align*}

であるから，

$$
\zeta^{i + 1}(\mu^{i + 1}(f))(X) = 
\sum\\{\mu^{i}(f)(Y) \mid  Y \subseteq^{i} X \\}
= \zeta^{i}(\mu^{i}(f))(X)
$$

(終)

定理1は，補題2, 3 より数学的帰納法で証明された．

## 高速ゼータ変換，高速メビウス変換

補題2を用いてゼータ変換，メビウス変換の各点の値を計算することができる．
計算量は，各 $i = 0, \ldots, n$ に対して $X \subseteq \bar{n}$ での
値を計算するので，$O(n 2^n)$ である．

なお，定義が(2),(4)の場合の補題2の漸化式を明記すればは次のとおり．

\begin{align*}
  \zeta^{i+1}(f)(X) &= \begin{cases}
    \zeta^{i}(f)(X) & \text{ if } i \in X \\\\
    \zeta^{i}(f)(X) + \zeta^{i}(f)(X \cup \\{i\\}) & \text{ if } i \not\in X \\\\
  \end{cases}\\\\
  \mu^{i+1}(f)(X) &= \begin{cases}
    \mu^{i}(f)(X) & \text{ if } i \in X \\\\
    \mu^{i}(f)(X) - \mu^{i}(f)(X \cup \\{i\\}) & \text{ if } i \not\in X \\\\
  \end{cases}
\end{align*}

## 実装

```cpp
template<typename T, int p1, int p2, int p3, int p4, int div>
void _trans_form(vector<T>& f) {
  int n = f.size();
  for (int i = 1; i < n; i *= 2) {
    for (int j = 0; j < n; j++) {
      if ((j & i) == 0) {
        T x = f[j];
        T y = f[j | i];
        f[j    ] = (p1 * x + p2 * y) / div;
        f[j | i] = (p3 * x + p4 * y) / div;
      }
    }
  }
}

template <typename T>
void hadamard(vector<T>& f) { _trans_form<T, 1, 1, 1, -1, 1>(f); }

template <typename T>
void inv_hadamard(vector<T>& f) { _trans_form<T, 1, 1, 1, -1, 2>(f); }

template<typename T>
void zeta_upper(vector<T>& f) { _trans_form<T, 1, 1, 0, 1, 1>(f); }

template<typename T>
void moebius_upper(vector<T>& f) { _trans_form<T, 1, -1, 0, 1, 1>(f); }

template<typename T>
void zeta_lower(vector<T>& f) { _trans_form<T, 1, 0, 1, 1, 1>(f); }

template<typename T>
void moebius_lower(vector<T>& f) { _trans_form<T, 1, 0, -1, 1, 1>(f); }
```

(1), (3) が zeta_lower と moebius_lower で，
(2), (4) が zeta_upper と moebius_upper．
im-place で計算が行われる．
Hadamard変換がおまけでついている．

## 今後の課題

たぶん，約数に関する話もまとめる必要があるだろう．
今は，まとめられるほど理解していない．
