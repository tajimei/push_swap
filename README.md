*This project has been created as part of the 42 curriculum by mtajima, yusakaki.*

---

# push_swap

A sorting program that sorts integers on two stacks using a limited set of operations, with the minimum number of moves possible.

---

## Description

**push_swap** sorts a list of integers using two stacks (`a` and `b`) and 11 allowed operations. The program selects the most efficient sorting strategy based on the disorder level of the input, aiming to minimize the total number of operations.

The available operations are:

| Operation | Description |
|-----------|-------------|
| `sa` | Swap the top 2 elements of stack a |
| `sb` | Swap the top 2 elements of stack b |
| `ss` | `sa` and `sb` at the same time |
| `pa` | Push the top of stack b onto stack a |
| `pb` | Push the top of stack a onto stack b |
| `ra` | Rotate stack a upward by one |
| `rb` | Rotate stack b upward by one |
| `rr` | `ra` and `rb` at the same time |
| `rra` | Reverse rotate stack a by one |
| `rrb` | Reverse rotate stack b by one |
| `rrr` | `rra` and `rrb` at the same time |

---

## Instructions

### Compilation

```bash
# Build push_swap
make

# Clean object files
make clean

# Clean everything including binary
make fclean

# Rebuild from scratch
make re
```

### Usage

```bash
# Basic usage (adaptive strategy by default)
./push_swap 4 67 3 87 23

# Force a specific strategy
./push_swap --simple   5 4 3 2 1
./push_swap --medium   5 4 3 2 1
./push_swap --complex  5 4 3 2 1
./push_swap --adaptive 5 4 3 2 1

# Enable benchmark mode (outputs metrics to stderr)
./push_swap --bench 4 67 3 87 23

# Combine flags
./push_swap --bench --complex 4 67 3 87 23

# Count the number of operations
ARG="4 67 3 87 23"; ./push_swap $ARG | wc -l

# Test with large random input
shuf -i 0-9999 -n 500 > args.txt
./push_swap $(cat args.txt) | wc -l
```

### Error handling

```bash
# Non-integer argument → prints "Error" to stderr
./push_swap 1 two 3

# Duplicate values → prints "Error" to stderr
./push_swap 3 2 3

# Value out of int range → prints "Error" to stderr
./push_swap 2147483648
```

---

## Algorithms

This program implements four sorting strategies. The strategy is selected at runtime via a flag, or automatically by the adaptive algorithm based on the measured disorder of the input.

### Disorder metric

Before sorting, the program computes a **disorder score** between `0.0` and `1.0` that measures how unsorted the input is. A score of `0` means the stack is already sorted; `1` means it is in the worst possible order. The score is the ratio of inverted pairs to total pairs:

```
disorder = (number of pairs where a[i] > a[j] for i < j) / total pairs
```

---

### 1. Simple — O(n²) · `--simple`

**Algorithm:** Selection sort adaptation.

All elements except the top 3 are moved to stack b by repeatedly finding the current minimum in stack a and pushing it. The minimum is brought to the top using `ra` or `rra` depending on which direction requires fewer rotations. Once 3 elements remain in a, they are sorted with a hard-coded 3-element sort. Finally, all elements in b are pushed back to a with `pa`.

**Complexity:**
- Time: O(n²) — for each of n elements, finding the minimum scans up to n nodes, and rotating costs up to n/2 operations.
- Space: O(n) — uses stack b to hold elements during sorting.

**When to use:** Best for very small inputs (≤ ~10 elements) or nearly-sorted inputs where disorder < 0.2.

---

### 2. Chunk — O(n√n) · `--medium`

**Algorithm:** Chunk-based sorting using √n buckets.

The rank-transformed values (0 to n-1) are divided into chunks of size √n. Each chunk is pushed to stack b in order from the smallest chunk to the largest. Within each chunk, elements with a rank in the upper half of the chunk are pushed to b's top and left there; elements in the lower half are pushed and then rotated to b's bottom with `rb`. This keeps b partially sorted by rank, reducing the cost of the final retrieval step.

Once all elements are in b, the algorithm repeatedly finds the element with the highest rank remaining in b, rotates it to the top using `rb` or `rrb` (whichever costs fewer operations), and pushes it to a with `pa`. This refills a in descending rank order, resulting in a ascending-sorted stack.

**Complexity:**
- Time: O(n√n) — pushing n elements in √n chunks costs O(n) per chunk × √n chunks = O(n√n). Retrieving from b costs O(√n) per element × n elements = O(n√n).
- Space: O(n) — all elements are temporarily held in stack b.

**When to use:** Disorder between 0.2 and 0.5. Good balance between implementation complexity and performance.

**Performance targets:**
- 100 elements: ~700–900 operations
- 500 elements: ~6000–8000 operations

---

### 3. Radix — O(n log n) · `--complex`

**Algorithm:** LSD (Least Significant Bit) radix sort.

All values are first converted to rank indices (0 to n-1). Then, for each bit position from LSB to MSB, the algorithm performs one pass over stack a:
- If the current bit of the top element's rank is **0** → `pb` (move to stack b)
- If the current bit is **1** → `ra` (rotate to the bottom of a)

After each pass, all elements in b are pushed back to a with `pa`. Since `pa` reverses the order of b (LIFO), the bit logic is inverted from a standard radix sort — `0 → pb` and `1 → ra` — to compensate for this reversal and maintain correct ordering.

The number of passes equals the number of bits needed to represent n-1, which is ⌈log₂(n)⌉.

**Complexity:**
- Time: O(n log n) — ⌈log₂(n)⌉ passes, each scanning all n elements = O(n log n) total operations.
- Space: O(n) — uses stack b as a temporary buffer per pass.

**When to use:** High disorder (≥ 0.5) or large inputs. Most consistent operation count regardless of input order.

**Performance targets:**
- 100 elements: ~900–1200 operations
- 500 elements: ~6000–7000 operations

---

### 4. Adaptive — O(n²) / O(n√n) / O(n log n) · `--adaptive` (default)

**Algorithm:** Selects a strategy based on the measured disorder score.

| Disorder | Strategy used | Complexity |
|----------|--------------|------------|
| < 0.2 | Simple (selection sort) | O(n²) |
| 0.2 ≤ d < 0.5 | Chunk sort | O(n√n) |
| ≥ 0.5 | Radix sort | O(n log n) |

**Rationale for thresholds:**
- Below 0.2, the input is nearly sorted. Selection sort is fast on nearly-sorted data because the minimum is usually already near the top, keeping rotation costs low.
- Between 0.2 and 0.5, chunk sort provides an excellent balance between simplicity and performance; the partial ordering allows chunks to be pushed efficiently.
- Above 0.5, the input is too disordered for chunk or selection sort to be competitive. Radix sort's consistent O(n log n) cost makes it the reliable choice.

This is the default behavior when no strategy flag is given.

---

## Performance Benchmark

Measured over random inputs. Results may vary slightly per run.

| Elements | Simple | Chunk | Radix | Adaptive |
|----------|--------|-------|-------|----------|
| 100 | ~1400 | ~750 ✅ | ~1080 ✅ | ~750–1080 ✅ |
| 500 | ~31000 | ~7300 ✅ | ~6800 ✅ | ~6800–7300 ✅ |

Grading targets:

| Elements | Pass | Good | Excellent |
|----------|------|------|-----------|
| 100 | < 2000 | < 1500 | < 700 |
| 500 | < 12000 | < 8000 | < 5500 |

---

## Contributions

| Login | Contributions |
|-------|--------------|
| mtajima | (describe your contributions here) |
| yusakaki | (describe your contributions here) |

---

## Resources

### References

- [Wikipedia — Sorting algorithm](https://en.wikipedia.org/wiki/Sorting_algorithm)
- [Wikipedia — Radix sort](https://en.wikipedia.org/wiki/Radix_sort)
- [Wikipedia — Algorithmic complexity / Big-O notation](https://en.wikipedia.org/wiki/Big_O_notation)
- [Visualgo — Sorting visualizations](https://visualgo.net/en/sorting)
- Donald E. Knuth, *The Art of Computer Programming, Vol. 3: Sorting and Searching*

### AI Usage

AI (Claude) was used during this project for the following tasks:

- **Algorithm design discussion** — comparing the trade-offs between radix sort, chunk sort, and Turkish sort for this specific problem model.
- **Debugging** — identifying the LSD radix sort bit-inversion issue caused by `pa` reversing stack b order.
- **Code review** — checking for Norm compliance (variable declaration placement, function length).
- **README drafting** — structuring the algorithm explanations and complexity arguments.

All generated code and explanations were reviewed, tested, and understood by both team members before inclusion in the project.

*このプロジェクトは、42カリキュラムの一環として \<login1\>、\<login2\> によって作成されました。*

---

# push_swap

限られた操作セットを使い、2つのスタック上の整数を最小の操作回数でソートするプログラムです。

---

## 概要

**push_swap** は、スタック `a` と `b` の2つ、および11種類の操作を使って整数のリストをソートします。入力の無秩序度に基づいて最も効率的なソート戦略を自動選択し、操作回数の最小化を目指します。

使用できる操作は以下の通りです：

| 操作 | 説明 |
|------|------|
| `sa` | スタックaの先頭2要素を交換する |
| `sb` | スタックbの先頭2要素を交換する |
| `ss` | `sa` と `sb` を同時に実行する |
| `pa` | スタックbの先頭をスタックaの先頭へ移す |
| `pb` | スタックaの先頭をスタックbの先頭へ移す |
| `ra` | スタックaを上方向に1つ回転させる |
| `rb` | スタックbを上方向に1つ回転させる |
| `rr` | `ra` と `rb` を同時に実行する |
| `rra` | スタックaを下方向に1つ回転させる |
| `rrb` | スタックbを下方向に1つ回転させる |
| `rrr` | `rra` と `rrb` を同時に実行する |

---

## 使い方

### コンパイル

```bash
# push_swapをビルド
make

# オブジェクトファイルを削除
make clean

# バイナリも含めて全削除
make fclean

# 全削除してから再ビルド
make re
```

### 実行

```bash
# 基本的な使い方（デフォルトはadaptive戦略）
./push_swap 4 67 3 87 23

# 戦略を指定して実行
./push_swap --simple   5 4 3 2 1
./push_swap --medium   5 4 3 2 1
./push_swap --complex  5 4 3 2 1
./push_swap --adaptive 5 4 3 2 1

# ベンチマークモードを有効にする（メトリクスをstderrに出力）
./push_swap --bench 4 67 3 87 23

# フラグを組み合わせる
./push_swap --bench --complex 4 67 3 87 23

# 操作数をカウントする
ARG="4 67 3 87 23"; ./push_swap $ARG | wc -l

# 大きなランダム入力でテスト
shuf -i 0-9999 -n 500 > args.txt
./push_swap $(cat args.txt) | wc -l
```

### エラー処理

```bash
# 整数でない引数 → stderrに "Error" を出力
./push_swap 1 two 3

# 重複した値 → stderrに "Error" を出力
./push_swap 3 2 3

# int範囲外の値 → stderrに "Error" を出力
./push_swap 2147483648
```

---

## アルゴリズム

このプログラムは4つのソート戦略を実装しています。戦略はフラグで明示指定するか、adaptiveアルゴリズムが入力の無秩序度を測定して自動選択します。

### 無秩序度メトリクス

ソート前に、入力がどの程度乱れているかを示す **無秩序度スコア**（0.0〜1.0）を計算します。スコアが `0` の場合はすでにソート済み、`1` の場合は最悪の順序を意味します。計算式は以下の通りです：

```
disorder = (i < j かつ a[i] > a[j] となるペアの数) / 全ペア数
```

---

### 1. Simple — O(n²) · `--simple`

**アルゴリズム：** 選択ソートの適応版

スタックaの最小値を繰り返し見つけ、`ra` または `rra`（少ない方）で先頭に持ってきて `pb` でbへ送ります。残り3要素になったら専用のハードコードロジックでソートし、最後にbの全要素を `pa` でaに戻します。

**計算量：**
- 時間：O(n²) — n要素それぞれについて最小値探索（最大n回）と回転（最大n/2回）が必要
- 空間：O(n) — ソート中にスタックbを一時バッファとして使用

**適した場面：** 非常に小さい入力（10要素以下程度）や、disorderが0.2未満のほぼソート済みの入力

---

### 2. Chunk — O(n√n) · `--medium`

**アルゴリズム：** √n個のチャンクに分割するチャンクソート

rank変換済みの値（0〜n-1）を √n 個のチャンクに分割します。小さいチャンクから順にbへpushします。各チャンク内で、rankがチャンクの上半分にある要素はbの先頭に残し、下半分にある要素は `rb` でbの底に回します。これによりbが部分的にrank順になり、後の取り出しコストを削減できます。

全要素がbに移ったら、残っているbの最大rankを繰り返し探し、`rb` または `rrb`（少ない方）で先頭に持ってきて `pa` でaに戻します。aはrank降順で埋まっていくため、最終的に昇順ソートが完成します。

**計算量：**
- 時間：O(n√n) — n要素を√nチャンクに分けてpushするコストO(n√n) + bからの取り出しコストO(n√n)
- 空間：O(n) — 全要素を一時的にスタックbに保持

**適した場面：** disorder が 0.2〜0.5 の範囲。実装の簡潔さとパフォーマンスの良いバランス。

**パフォーマンス目安：**
- 100要素：約700〜900操作
- 500要素：約6000〜8000操作

---

### 3. Radix — O(n log n) · `--complex`

**アルゴリズム：** LSD（最下位ビット優先）基数ソート

全値をまずrank値（0〜n-1）に変換します。その後、LSBからMSBに向かって各ビット位置ごとに1パスを行います：
- 先頭要素のrankの対象ビットが **0** → `pb`（スタックbへ移す）
- 対象ビットが **1** → `ra`（aの末尾へ回す）

各パスの後、bの全要素を `pa` でaに戻します。`pa` はLIFO構造のためbの順序を反転させます。この反転を補正するため、通常の基数ソートとビット判定を入れ替え（`0 → pb`、`1 → ra`）て正しい順序を維持しています。

パス数はn-1を表すのに必要なビット数 ⌈log₂(n)⌉ に等しくなります。

**計算量：**
- 時間：O(n log n) — ⌈log₂(n)⌉パス × 各パスでn要素を処理
- 空間：O(n) — 各パスでスタックbを一時バッファとして使用

**適した場面：** disorder が 0.5以上、または大きな入力。入力の順序に関わらず操作数が安定している。

**パフォーマンス目安：**
- 100要素：約900〜1200操作
- 500要素：約6000〜7000操作

---

### 4. Adaptive — O(n²) / O(n√n) / O(n log n) · `--adaptive`（デフォルト）

**アルゴリズム：** 無秩序度スコアに基づいて戦略を自動選択

| 無秩序度 | 使用戦略 | 計算量 |
|----------|---------|--------|
| < 0.2 | Simple（選択ソート） | O(n²) |
| 0.2 ≤ d < 0.5 | Chunk ソート | O(n√n) |
| ≥ 0.5 | Radix ソート | O(n log n) |

**閾値の根拠：**
- 0.2未満：入力がほぼソート済みのため、最小値は先頭付近にあることが多く、選択ソートの回転コストが小さく抑えられる。
- 0.2〜0.5：ある程度の秩序が残っているため、チャンク単位でまとめてbへ送る戦略が効率的に機能する。
- 0.5以上：入力が十分に乱れており、チャンクや選択ソートでは競争力がなくなる。基数ソートのO(n log n)の安定したコストが最も信頼できる。

フラグを指定しない場合のデフォルト動作です。

---

## パフォーマンスベンチマーク

ランダム入力での実測値（実行ごとに多少変動します）：

| 要素数 | Simple | Chunk | Radix | Adaptive |
|--------|--------|-------|-------|----------|
| 100 | ~1400 | ~750 ✅ | ~1080 ✅ | ~750〜1080 ✅ |
| 500 | ~31000 | ~7300 ✅ | ~6800 ✅ | ~6800〜7300 ✅ |

採点基準：

| 要素数 | 合格 | 良好 | 優秀 |
|--------|------|------|------|
| 100 | < 2000 | < 1500 | < 700 |
| 500 | < 12000 | < 8000 | < 5500 |

---

## 貢献者

| ログイン | 担当内容 |
|----------|---------|
| mtajima | （ここに担当内容を記載） |
| yusakaki | （ここに担当内容を記載） |

---

## 参考資料

### 参考文献

- [Wikipedia — ソートアルゴリズム](https://ja.wikipedia.org/wiki/%E3%82%BD%E3%83%BC%E3%83%88)
- [Wikipedia — 基数ソート](https://ja.wikipedia.org/wiki/%E5%9F%BA%E6%95%B0%E3%82%BD%E3%83%BC%E3%83%88)
- [Wikipedia — ランダウの記号（Big-O記法）](https://ja.wikipedia.org/wiki/%E3%83%A9%E3%83%B3%E3%83%80%E3%82%A6%E3%81%AE%E8%A8%98%E5%8F%B7)
- [Visualgo — ソートの可視化](https://visualgo.net/en/sorting)
- Donald E. Knuth, *The Art of Computer Programming, Vol. 3: Sorting and Searching*

### AIの活用について

このプロジェクトでは、以下の用途でAI（Claude）を使用しました：

- **アルゴリズム選定の議論** — radixソート・チャンクソート・Turkish sortの比較検討と、このスタックモデルにおけるトレードオフの整理
- **デバッグ** — `pa` によるスタックb反転が原因のLSD基数ソートのビット反転バグの特定
- **コードレビュー** — Normへの準拠（変数宣言位置、関数の長さ）の確認
- **README作成** — アルゴリズム説明と計算量引数の構造化

生成されたコードや説明はすべて、両メンバーがプロジェクトへの組み込み前にレビュー・テスト・理解を行っています。