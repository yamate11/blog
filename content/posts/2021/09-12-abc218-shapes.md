---
author: "yamate11"
title: "Shapes -- AtCoder Beginner Contest 218 C"
date: "2021-09-12T15:03:35+09:00"
# date_init: "2021-09-12"
tags: []
# categories: ["topic"]
categories: ["solution"]
summary: "重実装への対処は，どうしたらよいのでしょうか?"
---

AtCoder Beginner Contest 218 - ABC 218 - C Shapes についてです．

## 問題概要

[問題へのリンク](https://atcoder.jp/contests/abc218/tasks/abc218_c)

2次元グリッドの，文字 # で示された2つの図形がある．
回転と平行移動で一致するかどうか判定せよ．

制約: グリッドサイズ <= 200．

## 経緯

コンテストでは，解けたのですが，30分以上かかりました．
S と T の bounding box を作って，0, 90, 180, 270 の各度の回転で
一致するかどうかの判定をしました．

この手の，特別な考察が必要ではないけれど，たくさんコードを書かなければ
問題で，速く解答できるようになるには，どうすればよいのでしょうか?
今回の反省点は:

* [公式解説](https://atcoder.jp/contests/abc218/editorial/2598)にも
あるように，bounding box を作るより，全体を回転した上で，
左上の # の位置を比較して
平行移動量を決めた方が簡単でした．
* 回転で一致するかどうかを，添字を動かす方向を変えることで調べたのですが，
  実際に回転したデータを作ってしまった方が簡単でした．

## ACコード

ライブラリに回転を実行する関数を
追加した後のコードです．ライブラリ部分は省略しています．
全ソースは 
https://atcoder.jp/contests/abc218/submissions/25806964
にあります．

```cpp
int main(/* int argc, char *argv[] */) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout << setprecision(20);

  auto solve = [&]() -> bool {
    ll N; cin >> N;
    Board<char> S(N, N, '.'); cin >> S;
    Board<char> T(N, N, '.'); cin >> T;

    auto left_top = [&](const auto& B) -> BrdIdx {
      auto p = [&](auto& bi) -> bool { return B.at(bi) == '#'; };
      return *find_if(ALL(BoardRange(B)), p);
    };

    BrdIdx biT = left_top(T);
    return any_of(ALL(ItRange(0, 4)), [&](ll i) -> bool {
      auto SS = S.rotate(i);
      BrdIdx diff = left_top(SS) - biT;
      return all_of(ALL(BoardRange(T)), [&](auto& bi) -> bool {
        return SS.at(bi + diff) == T.at(bi) && SS.at(bi) == T.at(bi - diff);
      });
    });
  };
  cout << (solve() ? "Yes" : "No") << endl;
  return 0;
}
```



