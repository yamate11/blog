---
author: "yamate11"
title: "インタラクティブな問題に対するソーススケルトン"
date: "2022-08-07T16:15:45+09:00"
# date_init: "2022-08-07"
tags: ['interactive']
categories: ["topic"]
---

インタラクティブな問題がたまに出題される．
特別扱いする必要があるか，ということだが，
何も考えずに書いてしまうとデバッグが難しい，ということがあるので，
やはり形式を整えておきたい感じである．

先日の [Codeforces R.812 (Div 2) Tournament Countdown](https://codeforces.com/contest/1713/problem/D) で，TLE というめにあった．
virtual base class を持つオブジェクトのメソッド呼び出しがあったりしたのが
良くなかったのではないかと思う．

ということで，軽く実行できるようにしたい．

ポイントとしては，ask() 関数と answer() 関数を用意する．
これらで，問と答の入出力部分をラップする．
実装するときには，ask_i() と answer_i() という名前で書く．
通常はこちらを ask(), answer() として使い，
自動テストのと期には ask_judge(), answer_judge() に切り替える．

典型的な実装はこんな感じ．二分探索数当てゲームを想定．

```cpp
bool judge = false;

ll ask(ll x) { return judge ? ask_judge(x) : ask_i(x); }
ll answer(ll x) { if (judge) answer_judge(x); else answer_i(x); }

ll ask_i(ll x) {
  cout << "? " << x << endl;
  string s; cin >> s;
  if (s == "SMALL") return -1;
  else if (s == "LARGE") return 1;
  else if (s == "EQUAL") return 0;
  else assert(0);
}

void answer_i(ll x) {
  cout << "! " << x << endl;
}
#endif
```

solve() 関数では，初期入力を受け取ったのち，ask() と answer() を
使って解を組み立てる．

```cpp
ll L, R;
void solve() {
  cin >> L >> R;
  if (judge) read_judge();

  ll lo = L, hi = R;
  while (true) {
    ll mid = (lo + hi) / 2;
    ll resp = ask(mid);
    if (resp == 0) { answer(mid); return; }
    else if (resp < 0) { lo = mid; }
    else { hi = mid; }
  }
}
```

自動テストに関して．本来の入力の後に問題情報を，
渡すようにするので，それを読む関数 read_judge() を，適切な位置に
置いておく(上の solve() 関数参照)．

```cpp
void read_judge() {
  cin >> expected;
}
```

自動テストでは，ask() 関数と answer() 関数を差し替えて，
自動テストに適した形にする．つまり，ask() は，追加情報を参照して，
適切な答を作成して返す．また，answer() は，不正解の場合には
異常終了するようにする．

```cpp
ll ask_judge(ll x) {
  if (x < expected) return -1;
  else if (x == expected) return 0;
  else return 1;  
}

void answer_judge(ll x) {
  if (x == expected) return;
  else               exit(1);
}
```

自動テストのときには，./cans の引数に judge を与えるようにする．
int main(int argc, char *argv[]) {
  // ...
  if (stcmp(argv[1], "judge") == 0) { judge = true; }

  solve();  // multiple-question のときには，ここでループ．
}

cmpNaive を使用するときには，コマンドとして
`cmpNaive -i -e -p './cans judge'` のように使う．ソースコードは
これ以上書き直す必要は無い (naive関数は不要)．


たとえば
[Codeforces R.#449 Ithea Plays with Chtholly](https://codeforces.com/problemset/problem/896/B)
のように，先に相手側から質問が来て，こちらはそれに答える，というタイプの
ものもある．最後のこちらの答を入力したら，
直ちにプログラムを終了せよ，とか指示される．
この場合は，

* 最初の質問までを初期入力と考える．
* こちらの n 番目の答を ask() で渡して，その戻り値として，相手の n + 1 番目の
  質問を得る．
* こちらの最後の答は answer() で渡す．

というふうにすれば良いであろう．

