---
author: "yamate11"
title: "Shorten ABC - AtCoder Regular Contest 110 E"
date: "2021-08-26T06:08:51+09:00"
# date_init: "2021-08-26"
tags: ["DP", "文字置き換え", "数え上げ", "判定問題"]
categories: ["solution"]
description: "鹿島建設プログラミングコンテスト2020 (AtCoder Regular Contest 110 - ARC110) の E - Shorten ABC の解法です．"
---

## 問題概要

A, B, C からなる文字列がある．
隣り合った異なる文字を，どちらとも違う文字で置き換える操作ができる．
操作を0回以上行ってできる文字列の数を mod 10^9 + 7 で求めよ．

制約: 文字列の長さ <= 10^6

## 解法

皆さんが言っているとおり，

* 数え上げの前提として，判定問題を考えるのが良い．
* 文字の組合せの置き換えなので，
