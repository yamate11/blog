---
author: "yamate11"
title: "std::mapへの挿入と更新"
date: "2025-02-14T13:39:25+09:00"
# date_init: "2025-02-14"
tags: ["map"]
categories: ["topic"]
# categories: ["solution"]
# summary: "要約を書いておく．ここには問題タイトル等は不要" 
---

std::map に「挿入か更新をする」ときの idiom をすぐに忘れてしまうのでメモしておく．

```cpp
std::map<S, T> mp;
```

と宣言されているとする．

## 1. 無条件で，s の値を t にする

通常は次で良い:

```cpp
  mp[s] = t;
```

もともと s が有ったか無かったのかも知りたい場合や，s へのイタレータも欲しい場合には，次のようにする:

```cpp
  auto [it, b] = mp.insert_or_assign(s, t);
```

b には，挿入が行われたかどうかが設定されるので，b が false なら，もともとキー s が存在していたことがわかる．it は s へのイタレータ．

## 2. キー s が無ければ，値を t にする．

次のように書くと，s の探索が2回走ってしまう．

```cpp
  if (mp.find(s) == mp.end()) mp[s] = t;
```

次のようにすれば 1回ですむ．

```cpp
  mp.emplace(s, t);
```

もともと s が有ったか無かったのかも知りたい場合や，s へのイタレータも欲しい場合には，次のようにする:

```cpp
  auto [it, b] = mp.emplace(s, t);
```

b には，挿入が行われたかどうかが設定されるので，b が false なら，もともとキー s が存在していたことがわかる．it は s へのイタレータ．

## 3. キー s が無く，さらになんらかの条件も成り立てば，s の値を t にする．

次のように書くと，s の探索が2回走ってしまう．

```cpp
  if (mp.find(s) == mp.end() and some_condition()) mp[s] = t;
```

次のようにすれば 1 回ですむ．

```cpp
  auto it = mp.lower_bound(s);
  if ((it == mp.end() or it->first != s) and some_condition()) mp.emplace_hint(it, s, t);
```

lower_bound の戻り値を hint に使うのがポイント．(ChatGPTに教えてもらいました)


