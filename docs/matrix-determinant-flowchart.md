# Matrix Determinant Calculation Flowchart

## Recursive Determinant Calculation for 4×4 Matrix

```mermaid
flowchart TD
    Start([Calculate det 4×4 Matrix]) --> CheckSize{Size == 2?}
    
    CheckSize -->|Yes| Base[Base Case:<br/>det = a×d - b×c<br/>RETURN]
    
    CheckSize -->|No| InitLoop[Initialize:<br/>det = 0.0<br/>col = 0]
    
    InitLoop --> LoopCheck{col < size?}
    
    LoopCheck -->|No| ReturnDet[RETURN det]
    
    LoopCheck -->|Yes| GetElement[Get element:<br/>m.data\[0\]\[col\]]
    
    GetElement --> CalcCofactor[Calculate Cofactor:<br/>mat_cofactor_sized<br/>row=0, col, size]
    
    CalcCofactor --> CalcMinor[Calculate Minor:<br/>mat_minor_sized<br/>row=0, col, size]
    
    CalcMinor --> GetSubmatrix[Get Submatrix:<br/>Remove row 0<br/>and column col]
    
    GetSubmatrix --> RecursiveCall[Recursive Call:<br/>mat_determinant_sized<br/>submatrix, size-1]
    
    RecursiveCall --> CheckSize
    
    CalcMinor --> CheckSign{row + col<br/>is odd?}
    
    CheckSign -->|Yes| NegateMinor[cofactor = -minor]
    CheckSign -->|No| KeepMinor[cofactor = minor]
    
    NegateMinor --> MultiplyAdd
    KeepMinor --> MultiplyAdd[Add to det:<br/>det += element × cofactor]
    
    MultiplyAdd --> IncrementCol[col++]
    
    IncrementCol --> LoopCheck
    
    ReturnDet --> End([End])
    Base --> End

    style Start fill:#e1f5e1
    style End fill:#ffe1e1
    style Base fill:#fff3cd
    style CheckSize fill:#cfe2ff
    style RecursiveCall fill:#f8d7da
```

## Execution Tree for 4×4 Matrix

```
det(4×4)
├─── element[0][0] × cofactor(0,0)
│    └─── det(3×3) submatrix
│         ├─── element[0][0] × cofactor(0,0)
│         │    └─── det(2×2) ← BASE CASE
│         ├─── element[0][1] × cofactor(0,1)
│         │    └─── det(2×2) ← BASE CASE
│         └─── element[0][2] × cofactor(0,2)
│              └─── det(2×2) ← BASE CASE
│
├─── element[0][1] × cofactor(0,1)
│    └─── det(3×3) submatrix
│         ├─── det(2×2) ← BASE CASE
│         ├─── det(2×2) ← BASE CASE
│         └─── det(2×2) ← BASE CASE
│
├─── element[0][2] × cofactor(0,2)
│    └─── det(3×3) submatrix
│         ├─── det(2×2) ← BASE CASE
│         ├─── det(2×2) ← BASE CASE
│         └─── det(2×2) ← BASE CASE
│
└─── element[0][3] × cofactor(0,3)
     └─── det(3×3) submatrix
          ├─── det(2×2) ← BASE CASE
          ├─── det(2×2) ← BASE CASE
          └─── det(2×2) ← BASE CASE
```

## Function Call Hierarchy

```
mat_determinant_sized(4×4)
  │
  ├─→ mat_cofactor_sized(0, 0, 4)
  │     └─→ mat_minor_sized(0, 0, 4)
  │           └─→ mat_submatrix(0, 0)
  │                 └─→ mat_determinant_sized(3×3)
  │                       ├─→ mat_cofactor_sized(0, 0, 3)
  │                       │     └─→ mat_minor_sized(0, 0, 3)
  │                       │           └─→ mat_determinant_sized(2×2) ← BASE CASE
  │                       ├─→ mat_cofactor_sized(0, 1, 3)
  │                       │     └─→ mat_minor_sized(0, 1, 3)
  │                       │           └─→ mat_determinant_sized(2×2) ← BASE CASE
  │                       └─→ mat_cofactor_sized(0, 2, 3)
  │                             └─→ mat_minor_sized(0, 2, 3)
  │                                   └─→ mat_determinant_sized(2×2) ← BASE CASE
  │
  ├─→ mat_cofactor_sized(0, 1, 4) ... (similar structure)
  ├─→ mat_cofactor_sized(0, 2, 4) ... (similar structure)
  └─→ mat_cofactor_sized(0, 3, 4) ... (similar structure)
```

## Algorithm Complexity

**For 4×4 matrix:**
- Level 1: 4 elements (row 0)
- Level 2: 4 × 3 = 12 submatrices (3×3)
- Level 3: 12 × 3 = 36 submatrices (2×2)
- **Total 2×2 calculations: 24**

**Time Complexity:** O(n!) where n is matrix size
- 4×4: ~96 operations
- 3×3: ~18 operations  
- 2×2: 3 operations

## Key Functions

### mat_determinant_sized(m, size)
- **Purpose**: Calculate determinant recursively
- **Base case**: size == 2, return direct calculation
- **Recursive case**: Sum of (element × cofactor) for first row

### mat_cofactor_sized(m, row, col, size)
- **Purpose**: Calculate cofactor with sign
- **Sign rule**: `(-1)^(row+col)`
- **Returns**: `minor` or `-minor`

### mat_minor_sized(m, row, col, size)
- **Purpose**: Get determinant of submatrix
- **Process**: Remove row and column, then calculate determinant

### mat_submatrix(m, row, col)
- **Purpose**: Create submatrix by removing specified row and column
- **Result**: (size-1) × (size-1) matrix

## Example Calculation (2×2)

```
Matrix:
│ 1  2 │
│ 3  4 │

det = (1 × 4) - (2 × 3) = 4 - 6 = -2
```

## Example Calculation (3×3)

```
Matrix:
│ 1  2  3 │
│ 4  5  6 │
│ 7  8  9 │

det = 1×cofactor(0,0) + 2×cofactor(0,1) + 3×cofactor(0,2)

cofactor(0,0) = +minor(0,0) = det│5 6│ = (5×9 - 6×8) = -3
                                  │8 9│

cofactor(0,1) = -minor(0,1) = -det│4 6│ = -(4×9 - 6×7) = -(-6) = 6
                                   │7 9│

cofactor(0,2) = +minor(0,2) = det│4 5│ = (4×8 - 5×7) = -3
                                  │7 8│

det = 1×(-3) + 2×(6) + 3×(-3) = -3 + 12 - 9 = 0
```

## Visual Representation of Cofactor Sign Pattern

```
4×4 Matrix Cofactor Signs:
│ +  -  +  - │
│ -  +  -  + │
│ +  -  +  - │
│ -  +  -  + │

Pattern: (-1)^(row+col)
```

---

*This flowchart illustrates the recursive determinant calculation used in miniRT matrix operations.*
