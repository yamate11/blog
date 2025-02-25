---
author: "yamate11"
title: "WolframAlpha への入力"
date: "2025-02-25T09:43:25+09:00"
# date_init: "2025-02-25"
tags: ["WolframAlpha"]
categories: ["topic"]
# categories: ["solution"]
summary: "WolframAlpha への入力方法のメモです"
---

WolframAlpha に入力する記法などのメモ

#### 連立方程式を x, y について解く．

* `solve { eq1, eq2, eq3 } for x, y, z` のような形式らしい．波括弧を使う．
* `a` かける `x` を `ax` と書いてしまうと誤解されることがある．`a x` と書いた方が良さそう．
* 例
  ```text
  solve { x = a x + b y + 1, y = c x + d y - 2 } for x, y
  ```

#### 微分する

```text
differentiate tan(x) for x
```

#### 積分する

```text
integrate tan(x) for x
```

```text
integrate x^2 from 0 to 1
```


