以后还是不做Div2的ABC了，没意思，不如省下几分钟读读论文。

这场我没打VP，直接做DE。

##【Codeforces Round #280 (Div. 2)】D. Vanya and Computer Game

>两个人以$1/x$秒和$1/y$每秒为间隔攻击需要$a$次击打死亡的怪，请告知谁给了最后一击或同时击杀怪物

想复杂了，看别人的代码，写的非常简洁但是巧妙。或许做CF也能提高人的思维敏感度吧。

##【Codeforces Round #280 (Div. 2)】E. Vanya and Field

>$n\times n$的棋盘上有$m$颗苹果树，每次走向量$(\Delta x,\Delta y)$，到达$((x+\Delta x)%n,(y+\Delta y)%n)$，保证$gcd(n,\Delta x)=gcd(n,\Delta y)=1$，求一个起点路过最多苹果树。（$n\le 10^6,m\le 1e5, 1\le \Delta x,\Delta y\le n$）

注意到$gcd(n,\Delta x)=gcd(n,\Delta y)=1$，由于若$(n,c)=1$，且$ac\equiv	bc\mod n$，那么$a\equiv b\mod n$，所以若$p \Delta x\equiv k \Delta x \mod n$，那么$p\equiv k\mod n$，所以无论如何路径长度定为$n$且每行每列只经过一次。因此，只需考虑出发点在$x=0,y=k$的情况，求最大通过特殊点的个数的起点，对于每个特殊点就可以知道要选到所需的在$x=0$上需要增加的量，算贡献取最大值即可。复杂度$O(n+m)$。


