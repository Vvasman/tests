# ORDERBOOK

Compile and Run

```bash
g++ orderbook.cpp -o orderbook
./orderbook
```

Usage:
"id" "amount" "price for 1" "BUY or SELL"
```bash
1 5 0.03 BUY
2 12 0.02 SELL
BalanceChange{2;0.1;USD}
BalanceChange{1;-0.1;USD}
3 15 0.4 BUY
BalanceChange{2;0.14;USD}
BalanceChange{3;-0.14;USD}
```

2 Heaps are used to store BUY and SELL orders. Since the best price is always at the root, accessing those orders is an O(1), push() and pop() are O(log n) operations

Completed in 3 hours
