---
author: "yamate11"
title: "きたまさ法"
date: "2021-04-30"
tags: []
categories: ["topic"]
draft: false
---

きたまさ法に関する記事です．
[よすぽさんの記事](https://yosupo.hatenablog.com/entry/2015/03/27/025132)
を参照して書きました．

## 問題設定

整数 $ d_0 , \ldots, d\_{ k - 1 }$ と $a\_0, \ldots, a\_{k - 1}$ が与えられている．
漸化式 $ a\_{n + k} = d\_{0} a\_{n} + \cdots + d\_{ k - 1 } a\_{n + k - 1}$ で定義される数列の $a_n$ を
$O( k\^2 \log n )$ で求める．

## 行列

$$ A = 
\begin{bmatrix}
d\_{ k - 1 } &\cdots & \cdots & d\_{ 0 } \\\\
1 &   &  \Large{0} & 0 \\\\
   &  \ddots &  & 0\\\\
\Large{0} & & 1 & 0 \\\\
\end{bmatrix}
$$

とすれば，

$$
\begin{bmatrix}
a_n \\\\
\vdots \\\\
a\_{ n - k + 1}
\end{bmatrix}
= A\^{ n - k + 1 }
\begin{bmatrix}
a\_{ k - 1 } \\\\
\vdots \\\\
a\_{  0 }
\end{bmatrix}
$$

なので，$A\^n$ が計算できれば良い．あるいは，$A\^n$ の最上行だけでも良い．
計算量が $O( k\^2 \log n)$ で押さえられて欲しいが，
普通の行列累乗だと$O( k\^3 \log n)$ になる．

## 計算

$\newcommand{\bsww}{\boldsymbol{w}}$
$\newcommand{\bsx}{\boldsymbol{x}}$
$\newcommand{\bsy}{\boldsymbol{y}}$
$\newcommand{\bsdd}{\boldsymbol{d}}$
$\bsy\_i$ たちを行ベクトルとする．$\bsdd = [d\_{ k - 1 }, \ldots, d\_0]$ とする．
また，$\text{sft}([z_0, \ldots, z\_{ k - 1 }]) = [z_1, \ldots, z\_{ k - 1 }, 0]$ とする．
計算することによって以下がわかる:

$$ A \left[
\begin{array}{c}
\bsy_1 \\\\ \bsy\_2 \\\\ \vdots \\\\ \bsy\_k
\end{array}\right] = \left[
\begin{array}{c}  * \\\\ \bsy_1 \\\\ \vdots \\\\ \bsy\_{ k - 1 }
\end{array}\right] ,\quad
\left[\begin{array}{c}
\bsy_1 \\\\ \vdots \\\\ \bsy\_k
\end{array}\right] A = \left[\begin{array}{c} 
y\_{11}\bsdd + \text{sft}( \bsy\_{1} ) \\\\
\vdots \\\\
y\_{k1}\bsdd + \text{sft}( \bsy\_{k} ) \\\\
\end{array}\right]
\tag{1}$$

したがって，$ A\^n $ の最下行の行ベクトルを $\bsx(n)$ と書くと，以下が成り立つ:

$$ A\^n = \left[\begin{array}{c}
\bsx( n + k - 1) \\\\
\vdots \\\\
\bsx( n ) \\\\
\end{array}\right] \tag{2}
$$

(1)の右の式より， $\bsx(n)$ の第1成分を $x$ とすると，
$$ \bsx (n + 1) = x \bsdd + \text{sft}( \bsx(n) ) \tag{3}$$ であることが分かる．
また，$A\^n$ の列ベクトルを $\bsww\_1\^T, \ldots, \bsww\_k\^T$ とし，

$$ \left[\begin{array}{c}
\bsx(2n + k - 1) \\\\
\vdots \\\\
\bsx(2n) \\\\
\end{array}\right]
= A\^{2n} = (A\^{n})\^{2} = 
 \left[\begin{array}{c}
\bsx(n + k - 1) \\\\
\vdots \\\\
\bsx(n) \\\\
\end{array}\right]
 \left[\begin{array}{c}
~ \\\\
\bsww\_1\^T & \cdots & \bsww\_k\^T \\\\
~ \\\\
\end{array}\right] $$

と書いて，最下行を比較すると，

$$ \bsx(2n) = [ \bsx(n)\cdot \bsww\_1, \ldots, \bsx(n)\cdot \bsww\_k ] \tag{4}$$

である．

以上より，次の手順で $a_n$ を計算することができる．

* $a_n = \bsx(n - k + 1 + k - 1) \cdot [a\_{ k - 1 }, \cdots, a\_{ 0 }]$ なので，$\bsx(n)$ が求められれば良い．
* $n$ を，「$+1$」 と 「$\times 2$」 で書く．たとえば，$n = 18$ なら，$n = ((1 \times 2 \times 2 \times 2) + 1) \times 2$．
  この内側から順に $\bsx(n)$ を求めていく．
* $+1$ のときには，(3) を適用する．この計算量は，$O(k)$
* $\times 2$ のときには，まず (3) を $k - 1$ 回適用して，$\bsx(n), \ldots, \bsx(n + k - 1)$ を求める．
  すると(2) より $A\^{n}$ が決まるので，(4) の右辺が計算できる．この計算量は，$O(k\^2)$

