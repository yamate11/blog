---
author: "yamate11"
title: "cmpNaive (judge) 実行前確認方法メモ"
date: "2026-09-05T09:59:03+09:00"
# date_init: "2026-09-05"
tags: []
categories: ["topic"]
# categories: ["solution"]
# summary: "要約を書いておく．ここには問題タイトル等は不要" 
---

メモ

cmpNaive の judge バージョンを使おうとしているとき，実行前に，`din_*.txt` でテストをする方法．


```text
{ cat din_1.txt; ./cans < din_1.txt; } | ./cans naive
```

複数あるなら:

```text
for f in din_*.txt; do echo $f; { cat $f; ./cans < $f; } | ./cans naive ; done
```

