---
author: "yamate11"
title: "インタラクティブ問題のデバッグ"
date: "2023-04-21T18:29:42+09:00"
# date_init: "2023-04-21"
tags: ["インタラクティブ"]
categories: ["topic"]
# categories: ["solution"]
summary: "インタラクティブ問題のデバッグ方法"
---

インタラクティブ問題を解くスタイルについての，自分用のメモ．
いろいろ試行したが，現状 (2023年4月現在) はこれになっている．

## running example

> 長さ $N$ のソート済みの整数列 $P_1, \ldots, P_N$ が隠されている．
> $N$ と $x$ が最初に与えられる．
> 「$i$ 番目の整数は何か」との質問を，たかだか
> 10 回おこなって，$P_i = x$ となる $i$ を答えよ．
> 存在しない場合には -1 と答えよ．
> 
> * 質問の形式: `? i`
> * 答の形式: `! i`
> 
> 制約: $N \leq 1000$，$P_i < P_j (i < j)$，

## コーディング

特別なサポートは行っていない．

質問用の関数と解答用の関数は用意しておくと良い．

```cpp
ll ask(ll i) {
  cout << "? " << i + 1 << endl;   // 0-index 等はここで調整
  ll x; cin >> x;
  return x;
}

void fin(ll i) {
  cout << "! " << (i >= 0 ? i + 1 : -1) << endl;
  exit(0);
}
```

main 関数は，ask() と fin() を使って書く．

```cpp
int main(/* int argc, char *argv[] */) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout << setprecision(20);

  ll N, x; cin >> N >> x;
  ll lo = -1, hi = N;
  while (true) {
    if (lo + 1 == hi) fin(-1);
    ll mid = (lo + hi) / 2;
    ll y = ask(mid);
    if      (y < x)  lo = mid;
    else if (x < y)  hi = mid;
    else if (x == y) fin(mid);
  }

  return 0;
}
```

## ジャッジプログラム

デバッグするとなると，やはりジャッジプログラムが必要になると思われる．
ジャッジプログラムを動作させるスクリプト interun を作ってある．
この環境で動かすためには，ジャッジプログラムは次のように作成する．

* 問題を標準入力から読み込む．
  * 問題のフォーマットは自分で適当に決める．
  * 問題ファイルを din_x.txt として用意する．
* 解答プログラムとのやりとりも，標準入出力を使う．
* ユーザに読ませたい出力は，行頭に `#` を置いて
  (標準エラー出力ではなく) 標準出力に出す．
* judge という名前で実行するようにしておくと良い (オプションで指定も可能)

次を定義しておくと良い．

```cpp
void ac() {
  cout << "# AC" << endl;
  exit(0);
}

void wa(string msg = "") {
  cout << "# WA: " << msg << endl;
  exit(1);
}
```

main を書く．正解したら ac() を，不正解なら wa() を呼ぶ．

```cpp
int main() {
  ll N, x, ans; cin >> N >> x >> ans;  // 解答も与えられると想定
  vector<ll> P(N); REP(i, 0, N) cin >> P[i];
  cout << N << " " << x << endl;
  ll cnt = 0;
  while (true) {
    string tp; cin >> tp;
    if (tp == "?") {
      if (cnt++ >= 10) wa("Exceeds Limit");
      ll i; cin >> i;
      cout << P[i - 1] << endl;
    }else if (tp == "!") {
      ll i; cin >> i;
      if (i == ans) ac(); else wa();
    }else assert(0);
  }
}
```

`#` で始まる出力は，ユーザ向けである．
interun は，両プログラムのやりとりをログファイル (デフォルト a.log)
に出力するので，誤答の場合に渡された値などは必ずしも出力しなくても良い．

## 実行

`din_?.txt` ファイルを用意する．
ここでは，正解もファイルに書き込まれているという想定としているが，
ジャッジプログラムの作り方によっては不要にもできる．

```text
5 30 4
1 10 15 30 100
```

実行する:

```text
$ interrun < din_1.txt
```

`cans`, `judge`, `a.log` の名前は interun のオプションで変更できる．

## cmpNaive

デバッグ時の cmpNaive では，解答プログラム cans と
ジャッジプログラム judge は別プロセスとの想定である．
スレッド対応はしていない．

```text
$ cmpNaive -e -i -p $AtCoderTop/clib/tool/interun
```

interun は，judge プログラムと同じ終了コードを返すので，
`-e` (終了コードでの判定), `-i` (独立プロセス) を指定して，
interun の実行を指定して cmpNaive を実行すれば良い．
interun にオプションを指定したいときには次のようにする:

```text
$ cmpNaive -e -i -p "$AtcoderTop/clib/tool/interun -j ./my_judge"
```



keyword: interactive
