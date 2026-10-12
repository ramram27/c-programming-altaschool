# Arrays in C – Notes

---

## 1. Introduction to Arrays

### Definition
An **array** in C is a collection of elements of the **same data type**, stored in **contiguous memory locations** and accessed using a single name with an **index**.

### Why arrays?
Without arrays, storing 5 marks needs 5 variables:
```c
int m1, m2, m3, m4, m5;
```
With an array:
```c
int marks[5];
```

### Features
- Elements have the **same data type**
- Stored in **consecutive memory locations**
- Index starts from **0** (first element) to **size − 1** (last element)
- Size is **fixed** at compile time (C89); C99 allows variable-length arrays (VLAs)
- Name of the array = **address of the first element** (`arr == &arr[0]`)
- C does **not** perform bounds checking

### Memory layout
`int a[5] = {10, 20, 30, 40, 50};` (assume `int` = 4 bytes, base address = 1000)

| Index   | 0    | 1    | 2    | 3    | 4    |
|---------|------|------|------|------|------|
| Value   | 10   | 20   | 30   | 40   | 50   |
| Address | 1000 | 1004 | 1008 | 1012 | 1016 |

```
Address of a[i] = Base Address + i × sizeof(data_type)
```

### Types of arrays
1. One-dimensional (1D)
2. Two-dimensional (2D)
3. Multi-dimensional (3D and more)

### Advantages
- Fast random access, O(1)
- Easy traversal using loops
- Compact code for many values of the same type

### Disadvantages
- Fixed size, cannot grow or shrink
- Insertion/deletion requires shifting elements, O(n)
- Stores only one data type

---

## 2. One-Dimensional Arrays

### Syntax
```c
data_type array_name[size];
```
```c
int  roll[10];
float price[5];
char  grade[3];
```

### Initialization
```c
int a[5] = {10, 20, 30, 40, 50};   // full initialization
int b[]  = {1, 2, 3};              // size is 3 (inferred)
int c[5] = {1, 2};                 // {1, 2, 0, 0, 0}
int d[5] = {0};                    // all elements 0
```
> An uninitialized local array contains **garbage values**. Global/static arrays are zero-initialized.

### Accessing elements
```c
a[0] = 100;               // assign
printf("%d\n", a[2]);     // read
```

### Program 1: Read and display an array
```c
#include <stdio.h>

int main() {
    int a[5], i;

    printf("Enter 5 numbers: ");
    for (i = 0; i < 5; i++) {
        scanf("%d", &a[i]);
    }

    printf("Array elements: ");
    for (i = 0; i < 5; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
    return 0;
}
```
**Output:**
```
Enter 5 numbers: 3 8 1 9 4
Array elements: 3 8 1 9 4
```

### Program 2: Sum, average and largest element
```c
#include <stdio.h>

int main() {
    int a[5] = {4, 9, 2, 7, 5};
    int i, sum = 0, max = a[0];

    for (i = 0; i < 5; i++) {
        sum += a[i];
        if (a[i] > max)
            max = a[i];
    }

    printf("Sum     = %d\n", sum);
    printf("Average = %.2f\n", (float)sum / 5);
    printf("Largest = %d\n", max);
    return 0;
}
```
**Output:**
```
Sum     = 27
Average = 5.40
Largest = 9
```

### Program 3: Linear search
```c
#include <stdio.h>

int main() {
    int a[6] = {12, 45, 7, 23, 89, 56};
    int i, key = 23, found = 0;

    for (i = 0; i < 6; i++) {
        if (a[i] == key) {
            printf("%d found at index %d\n", key, i);
            found = 1;
            break;
        }
    }
    if (!found)
        printf("%d not found\n", key);
    return 0;
}
```

### Program 4: Reverse an array
```c
#include <stdio.h>

int main() {
    int a[5] = {1, 2, 3, 4, 5};
    int i;

    printf("Reversed: ");
    for (i = 4; i >= 0; i--) {
        printf("%d ", a[i]);
    }
    printf("\n");
    return 0;
}
```

### Program 5: Insert an element at a position
```c
#include <stdio.h>

int main() {
    int a[10] = {10, 20, 30, 40, 50};
    int n = 5, pos = 2, x = 99, i;

    for (i = n - 1; i >= pos; i--) {
        a[i + 1] = a[i];          // shift right
    }
    a[pos] = x;
    n++;

    for (i = 0; i < n; i++)
        printf("%d ", a[i]);      // 10 20 99 30 40 50
    printf("\n");
    return 0;
}
```

### Program 6: Delete an element at a position
```c
#include <stdio.h>

int main() {
    int a[10] = {10, 20, 30, 40, 50};
    int n = 5, pos = 1, i;

    for (i = pos; i < n - 1; i++) {
        a[i] = a[i + 1];          // shift left
    }
    n--;

    for (i = 0; i < n; i++)
        printf("%d ", a[i]);      // 10 30 40 50
    printf("\n");
    return 0;
}
```

### Passing a 1D array to a function
Only the **base address** is passed, so changes made in the function affect the original array.
```c
#include <stdio.h>

void display(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int a[5] = {1, 2, 3, 4, 5};
    display(a, 5);
    return 0;
}
```

### Finding the size of an array
```c
int a[5];
int n = sizeof(a) / sizeof(a[0]);   // 5
```
> This works only where `a` is a real array. Inside a function, the parameter is a pointer, so `sizeof` does not give the array size.

### Operations and time complexity
| Operation        | Time |
|------------------|------|
| Access / Update  | O(1) |
| Traversal        | O(n) |
| Linear search    | O(n) |
| Insertion        | O(n) |
| Deletion         | O(n) |

---

## 3. Two-Dimensional Arrays

### Definition
A 2D array is an **array of arrays**, arranged as a **table (matrix) of rows and columns**. Each element is accessed using two indices: `a[row][col]`.

### Syntax
```c
data_type array_name[rows][columns];
```
```c
int matrix[3][4];    // 3 rows × 4 columns = 12 elements
```

### Initialization
```c
int m[2][3] = {
    {1, 2, 3},
    {4, 5, 6}
};

int n[2][3] = {1, 2, 3, 4, 5, 6};      // filled row by row
int p[][3]  = {{1, 2, 3}, {4, 5, 6}};  // row size optional, column size mandatory
```

### Visual representation of `int m[2][3]`
|            | Col 0       | Col 1       | Col 2       |
|------------|-------------|-------------|-------------|
| **Row 0**  | m[0][0] = 1 | m[0][1] = 2 | m[0][2] = 3 |
| **Row 1**  | m[1][0] = 4 | m[1][1] = 5 | m[1][2] = 6 |

### Memory representation
C stores 2D arrays in **row-major order**: `1 2 3 4 5 6`

```
Address of a[i][j] = Base + (i × COLS + j) × sizeof(data_type)
```

### Accessing elements
```c
m[1][2] = 60;              // row 1, column 2
printf("%d\n", m[0][1]);   // 2
```

### Program 1: Read and display a matrix
```c
#include <stdio.h>

int main() {
    int m[2][3], i, j;

    printf("Enter 6 elements:\n");
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 3; j++) {
            scanf("%d", &m[i][j]);
        }
    }

    printf("Matrix:\n");
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 3; j++) {
            printf("%d\t", m[i][j]);
        }
        printf("\n");
    }
    return 0;
}
```
**Output:**
```
Enter 6 elements:
1 2 3 4 5 6
Matrix:
1	2	3
4	5	6
```

### Program 2: Matrix addition
```c
#include <stdio.h>

int main() {
    int A[2][2] = {{1, 2}, {3, 4}};
    int B[2][2] = {{5, 6}, {7, 8}};
    int C[2][2], i, j;

    for (i = 0; i < 2; i++)
        for (j = 0; j < 2; j++)
            C[i][j] = A[i][j] + B[i][j];

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++)
            printf("%d ", C[i][j]);
        printf("\n");
    }
    return 0;
}
```
**Output:**
```
6 8
10 12
```

### Program 3: Transpose of a matrix
```c
#include <stdio.h>

int main() {
    int A[2][3] = {{1, 2, 3}, {4, 5, 6}};
    int T[3][2], i, j;

    for (i = 0; i < 2; i++)
        for (j = 0; j < 3; j++)
            T[j][i] = A[i][j];

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 2; j++)
            printf("%d ", T[i][j]);
        printf("\n");
    }
    return 0;
}
```
**Output:**
```
1 4
2 5
3 6
```

### Program 4: Matrix multiplication
```c
#include <stdio.h>

int main() {
    int A[2][2] = {{1, 2}, {3, 4}};
    int B[2][2] = {{5, 6}, {7, 8}};
    int C[2][2], i, j, k;

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            C[i][j] = 0;
            for (k = 0; k < 2; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++)
            printf("%d ", C[i][j]);
        printf("\n");
    }
    return 0;
}
```
**Output:**
```
19 22
43 50
```
> Rule: multiplication is possible only if **columns of A = rows of B**. For A (m×n) and B (n×p), the result is C (m×p). Time complexity: O(m·n·p).

### Program 5: Row sum and column sum
```c
#include <stdio.h>

int main() {
    int m[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int i, j, rs, cs;

    for (i = 0; i < 3; i++) {
        rs = 0;
        for (j = 0; j < 3; j++)
            rs += m[i][j];
        printf("Row %d sum = %d\n", i, rs);
    }

    for (j = 0; j < 3; j++) {
        cs = 0;
        for (i = 0; i < 3; i++)
            cs += m[i][j];
        printf("Column %d sum = %d\n", j, cs);
    }
    return 0;
}
```

### Passing a 2D array to a function
The **column size must be specified**.
```c
#include <stdio.h>

void display(int arr[][3], int rows) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < 3; j++)
            printf("%d ", arr[i][j]);
        printf("\n");
    }
}

int main() {
    int m[2][3] = {{1, 2, 3}, {4, 5, 6}};
    display(m, 2);
    return 0;
}
```

### Applications
- Matrices in mathematics and graphics
- Game boards (tic-tac-toe, chess)
- Tables of marks / data
- Image pixels

---

## 4. Comparison: 1D vs 2D Arrays

| Feature          | 1D Array       | 2D Array                |
|------------------|----------------|-------------------------|
| Structure        | Single list    | Table (rows × columns)  |
| Declaration      | `int a[5];`    | `int a[3][4];`          |
| Indices          | 1 → `a[i]`     | 2 → `a[i][j]`           |
| Total elements   | `n`            | `rows × cols`           |
| Traversal        | Single loop    | Nested loops            |
| Traversal time   | O(n)           | O(rows × cols)          |

---

## 5. Important Points
- Index range is **0 to size − 1**; going outside it is **undefined behaviour**.
- Array name is a constant pointer to the first element; arrays **cannot be assigned** to each other directly (`a = b;` is invalid, copy element by element).
- Use `&` with `scanf` for array elements (`&a[i]`).
- Arrays are passed to functions **by address**, not by value.
- 2D arrays are stored in **row-major order**; the **column size is required** in function parameters.
- Use `sizeof(a) / sizeof(a[0])` to get the number of elements.


# Calculating Array Size in C

## Using `sizeof`

The standard way is to divide the total size of the array by the size of one element:

```c
#include <stdio.h>

int main() {
    int a[] = {10, 20, 30, 40, 50};

    int n = sizeof(a) / sizeof(a[0]);

    printf("Number of elements = %d\n", n);          // 5
    printf("Total size in bytes = %zu\n", sizeof(a)); // 20 (if int = 4 bytes)
    return 0;
}
```

- `sizeof(a)` gives the total bytes of the array (5 × 4 = 20).
- `sizeof(a[0])` gives the bytes of one element (4).
- 20 / 4 = **5 elements**.

You can also write `sizeof(a) / sizeof(int)`, but `sizeof(a[0])` is safer because it stays correct if you change the data type.

## 2D Arrays

```c
int m[3][4];

int total = sizeof(m) / sizeof(m[0][0]);    // 12 (total elements)
int rows  = sizeof(m) / sizeof(m[0]);       // 3
int cols  = sizeof(m[0]) / sizeof(m[0][0]); // 4
```

## Common Mistake: Inside Functions

When you pass an array to a function, it decays into a **pointer**, so `sizeof` no longer gives the array size:

```c
void test(int arr[]) {
    // WRONG: sizeof(arr) is the size of a pointer (8 bytes on 64-bit), not the array
    int n = sizeof(arr) / sizeof(arr[0]);   // gives 2, not the real count
}
```

**Fix:** calculate the size in the calling function and pass it as an argument.

```c
#include <stdio.h>

void display(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
}

int main() {
    int a[] = {1, 2, 3, 4, 5};
    int n = sizeof(a) / sizeof(a[0]);
    display(a, n);
    return 0;
}
```

## Special Case: Character Arrays (Strings)

For strings, use `strlen()` to count characters (excluding the `'\0'`), and `sizeof` for the total allocated size:

```c
#include <string.h>

char s[20] = "Hello";
strlen(s);   // 5  (characters in the string)
sizeof(s);   // 20 (total array size)
```

## Summary

| Goal | Formula |
|------|---------|
| Number of elements (1D) | `sizeof(a) / sizeof(a[0])` |
| Total bytes | `sizeof(a)` |
| Rows of 2D array | `sizeof(m) / sizeof(m[0])` |
| Columns of 2D array | `sizeof(m[0]) / sizeof(m[0][0])` |
| String length | `strlen(s)` |