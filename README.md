# K-map-based-logic-minimization
利用卡諾圖將布林代數化為最簡
## Description
利用卡諾圖的方式找出等價於原布林代數的各個布林代數刪除不必要即可找出最簡
## Getting Started

### Prerequisites
* 布林代數函式檔
```
4    # 多少布林代數函式
1 0 1 1 0 1 1 0 0 1 1 0 1 1 1 1    # k-map format: 0 for 0, 1 for 1, 2 for X
2 1 1 2 0 2 1 0 0 0 1 0 0 0 1 0
1 0 0 1 0 0 0 0 1 1 0 1 1 0 0 1
0 0 0 0 0 1 1 0 0 1 0 0 0 1 0 0 
```
### Compile & Execute
``` 
$ g++ main.cpp
$ a.exe [布林代數函式檔]
```
## Roadmap

## Known Bugs
