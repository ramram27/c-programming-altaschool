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



## 1. Character Arrays

A **character array** is a collection of `char` elements stored in contiguous memory locations.

```c
char name[6] = {'H','e','l','l','o','\0'};
```

**Key points**
- Each element occupies 1 byte.
- Indexing starts at 0.
- Without a terminating `'\0'`, the array is just a character array, not a string.

| Declaration | Meaning |
|---|---|
| `char a[5];` | Uninitialized array of 5 chars |
| `char a[5] = {'a','b'};` | Remaining elements are set to `'\0'` |
| `char a[] = "Hi";` | Size is auto-set to 3 (`H`, `i`, `\0`) |

---

## 2. Strings

A **string** in C is a **null-terminated character array**. The null character `'\0'` (ASCII 0) marks the end of the string.

### Declaration and initialization
```c
char s1[10];                    // declaration
char s2[10] = "Hello";          // string literal; '\0' added automatically
char s3[] = "Hello";            // size = 6
char s4[] = {'H','e','l','l','o','\0'};
char *s5 = "Hello";             // pointer to a string literal (read-only)
```

Memory layout of `"Hello"`:

| Index | 0 | 1 | 2 | 3 | 4 | 5 |
|---|---|---|---|---|---|---|
| Value | H | e | l | l | o | \0 |

### Reading and writing strings

```c
#include <stdio.h>
int main() {
    char name[30];
    printf("Enter name: ");
    scanf("%s", name);      // stops at whitespace; no & needed
    printf("Hello %s\n", name);

    char line[50];
    getchar();              // consume leftover newline
    fgets(line, sizeof(line), stdin);   // reads whole line with spaces
    puts(line);
    return 0;
}
```

| Function | Behaviour |
|---|---|
| `scanf("%s", s)` | Reads until whitespace |
| `scanf("%[^\n]", s)` | Reads a line with spaces |
| `gets(s)` | Reads a line, but **unsafe and removed in C11** |
| `fgets(s, n, stdin)` | Safe line input; keeps the `\n` |
| `puts(s)` | Prints the string plus a newline |
| `printf("%s", s)` | Prints the string |

### Difference: array vs pointer string

| `char s[] = "Hi";` | `char *s = "Hi";` |
|---|---|
| Copy stored in a modifiable array | Points to a read-only literal |
| `s[0]='X';` is valid | `s[0]='X';` is undefined behaviour |
| `sizeof(s)` = 3 | `sizeof(s)` = pointer size |

---

## 3. String Handling Functions (`<string.h>`)

| Function | Purpose | Example |
|---|---|---|
| `strlen(s)` | Returns the length, excluding `'\0'` | `strlen("abc")` → 3 |
| `strcpy(d, s)` | Copies `s` into `d` | `strcpy(a, "Hi");` |
| `strncpy(d, s, n)` | Copies at most `n` chars | |
| `strcat(d, s)` | Appends `s` to the end of `d` | |
| `strncat(d, s, n)` | Appends at most `n` chars | |
| `strcmp(a, b)` | Compares two strings | Returns 0 if equal, <0 if a<b, >0 if a>b |
| `strncmp(a, b, n)` | Compares the first `n` chars | |
| `strchr(s, c)` | Pointer to first occurrence of `c` | |
| `strrchr(s, c)` | Pointer to last occurrence of `c` | |
| `strstr(s, sub)` | Pointer to first occurrence of a substring | |
| `strrev(s)` | Reverses the string (non-standard; works in Turbo C) | |
| `strupr / strlwr` | Upper/lower case (non-standard) | |

### Example using the library functions
```c
#include <stdio.h>
#include <string.h>
int main() {
    char a[30] = "Hello", b[] = "World", c[30];
    printf("%zu\n", strlen(a));      // 5
    strcpy(c, a);                    // c = "Hello"
    strcat(c, " ");                  // "Hello "
    strcat(c, b);                    // "Hello World"
    printf("%s\n", c);
    printf("%d\n", strcmp(a, b));    // negative, since 'H' < 'W'
    return 0;
}
```

### Character functions (`<ctype.h>`)
`isalpha()`, `isdigit()`, `isalnum()`, `isspace()`, `isupper()`, `islower()`, `toupper()`, `tolower()`

### Writing your own versions (frequently asked)

**String length**
```c
int myStrlen(char s[]) {
    int i = 0;
    while (s[i] != '\0') i++;
    return i;
}
```

**String copy**
```c
void myStrcpy(char d[], char s[]) {
    int i = 0;
    while ((d[i] = s[i]) != '\0') i++;
}
```

**String reverse**
```c
void rev(char s[]) {
    int i = 0, j = strlen(s) - 1;
    while (i < j) {
        char t = s[i]; s[i] = s[j]; s[j] = t;
        i++; j--;
    }
}
```

**Palindrome check**: reverse the string and compare using `strcmp`, or compare `s[i]` with `s[n-1-i]`.

**Common mistakes**
- Forgetting space for `'\0'`.
- Comparing strings with `==` (this compares addresses). Use `strcmp`.
- Using `strcpy` when the destination is too small, which causes buffer overflow.
- Using `&` with `%s` in `scanf`.

---

## 4. Introduction to Functions

A **function** is a self-contained block of code that performs a specific task. `main()` is itself a function.

**Advantages**
- Modularity: a large problem is broken into smaller parts.
- Reusability: write once, call many times.
- Easier debugging and maintenance.
- Reduces code size and redundancy.
- Supports team development.

### Three parts of a function

**1. Function declaration (prototype)**
```c
return_type function_name(parameter_list);
int add(int, int);
```

**2. Function definition**
```c
int add(int a, int b) {
    return a + b;
}
```

**3. Function call**
```c
int s = add(5, 3);
```

### Complete example
```c
#include <stdio.h>
int square(int n);          // prototype

int main() {
    printf("%d", square(4)); // call
    return 0;
}
int square(int n) {          // definition
    return n * n;
}
```

### The `return` statement
- Sends a value back to the caller and ends the function.
- A function can return only **one value** directly.
- A `void` function returns nothing.

---

## 5. Types of Functions

### A. Based on origin
1. **Library (built-in) functions**: `printf()`, `sqrt()`, `strlen()`, `pow()`
2. **User-defined functions**: written by the programmer.

### B. Based on arguments and return value (4 categories)

| Type | Arguments | Return value | Example |
|---|---|---|---|
| 1 | No | No | `void show();` |
| 2 | Yes | No | `void show(int x);` |
| 3 | No | Yes | `int getNum();` |
| 4 | Yes | Yes | `int add(int a, int b);` |

```c
// Type 1: no args, no return
void hello() { printf("Hello\n"); }

// Type 2: args, no return
void printSum(int a, int b) { printf("%d", a + b); }

// Type 3: no args, return
int readNum() { int n; scanf("%d", &n); return n; }

// Type 4: args and return
int mul(int a, int b) { return a * b; }
```

---

## 6. Formal and Actual Arguments

| Actual Arguments | Formal Arguments |
|---|---|
| Appear in the function **call** | Appear in the function **definition** |
| Hold the real values or addresses | Receive the values; act as local variables |
| Can be constants, variables, or expressions | Must be variables with declared types |

```c
int main() {
    int x = 5, y = 3;
    int r = add(x, y);   // x, y are ACTUAL arguments
}
int add(int a, int b) {  // a, b are FORMAL arguments
    return a + b;
}
```

**Rules**
- The number, order, and types of arguments must match.
- Formal parameters are created when the function is called and destroyed when it returns.
- Actual arguments are copied into formal arguments (in call by value).

---

## 7. Parameter Passing in Functions

C supports two techniques:
1. **Call by Value**
2. **Call by Reference** (simulated with pointers)

### 7.1 Call by Value
- A **copy** of the actual argument is passed.
- Changes made in the function **do not affect** the original variables.
- This is the **default** in C.

```c
void swap(int a, int b) {
    int t = a; a = b; b = t;
}
int main() {
    int x = 10, y = 20;
    swap(x, y);
    printf("%d %d", x, y);   // 10 20 (unchanged)
}
```

### 7.2 Call by Reference (using pointers)
- The **address** of the variable is passed.
- The function accesses the original memory through the pointer, so changes **are reflected** in the caller.

```c
void swap(int *a, int *b) {
    int t = *a; *a = *b; *b = t;
}
int main() {
    int x = 10, y = 20;
    swap(&x, &y);
    printf("%d %d", x, y);   // 20 10
}
```

> C has no true call by reference as in C++ (`int &a`). It is simulated by passing addresses, which is technically still call by value of the pointer.

### Comparison

| Feature | Call by Value | Call by Reference |
|---|---|---|
| What is passed | Copy of value | Address of variable |
| Formal parameters | Normal variables | Pointers |
| Effect on original | None | Original gets modified |
| Memory | Extra memory for copies | No copy of data |
| Call syntax | `f(x)` | `f(&x)` |
| Safety | Safer | Risk of unintended changes |

---

## 8. Passing Arrays to Functions

Array names decay to a **pointer to the first element**. So arrays are effectively passed by reference: the function works on the original array, not a copy.

### Three equivalent ways to declare the parameter
```c
void f(int a[10]);
void f(int a[]);
void f(int *a);
```

The **size is not passed**, so it must be sent as a separate argument.

### Example: 1-D array
```c
#include <stdio.h>
void display(int a[], int n) {
    for (int i = 0; i < n; i++) printf("%d ", a[i]);
}
void doubleIt(int a[], int n) {
    for (int i = 0; i < n; i++) a[i] *= 2;   // modifies original
}
int main() {
    int arr[5] = {1, 2, 3, 4, 5};
    doubleIt(arr, 5);
    display(arr, 5);       // 2 4 6 8 10
}
```

### Passing a single element (call by value)
```c
void f(int x);
f(arr[2]);        // passes a copy of one element
```

### Passing a 2-D array
The **column size is mandatory**.
```c
void show(int a[][3], int rows) {
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < 3; j++)
            printf("%d ", a[i][j]);
}
int main() {
    int m[2][3] = {{1,2,3},{4,5,6}};
    show(m, 2);
}
```

### Passing strings
```c
void printStr(char s[]) { puts(s); }
```

### Example: finding the largest element
```c
int max(int a[], int n) {
    int m = a[0];
    for (int i = 1; i < n; i++)
        if (a[i] > m) m = a[i];
    return m;
}
```

**Remember:** `sizeof(a)` inside the function gives the pointer size, not the array size.

---

## 9. Nested Functions

### Meaning
"Nested function" can mean two things:

**(a) Nested function calls**: one function calling another. This is fully supported in C.

```c
int square(int x) { return x * x; }
int sumOfSquares(int a, int b) {
    return square(a) + square(b);   // nested call
}
int main() {
    printf("%d", sumOfSquares(3, 4));   // 25
}
```

A call can also be an argument of another call:
```c
printf("%d", max(max(a, b), c));
```

**(b) Nested function definitions** (a function defined inside another function): **not allowed in standard C**. It is available only as a GCC extension.

```c
int main() {
    void inner() { }    // ERROR in standard C
}
```

**Call flow of nested calls** (using the stack):
```
main() → sumOfSquares() → square()
                       ← returns to sumOfSquares()
         ← returns to main()
```

---

## 10. Recursion

**Recursion** is a technique where a function **calls itself**, directly or indirectly, to solve a problem by breaking it into smaller subproblems of the same type.

### Two essential parts
1. **Base case**: the condition that stops the recursion.
2. **Recursive case**: the function calls itself with a smaller or simpler input.

Without a base case, the result is infinite recursion and a **stack overflow**.

### Example 1: Factorial
n! = n × (n−1)!, and 0! = 1

```c
int fact(int n) {
    if (n == 0 || n == 1)    // base case
        return 1;
    return n * fact(n - 1);  // recursive case
}
```

**Trace of `fact(4)`:**
```
fact(4) = 4 * fact(3)
              = 3 * fact(2)
                    = 2 * fact(1)
                          = 1
Returns: 1 → 2 → 6 → 24
```

### Example 2: Fibonacci
```c
int fib(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    return fib(n - 1) + fib(n - 2);
}
```
Time complexity is O(2ⁿ), which is inefficient.

### Example 3: Sum of digits
```c
int sumDigits(int n) {
    if (n == 0) return 0;
    return (n % 10) + sumDigits(n / 10);
}
```

### Example 4: GCD (Euclid's algorithm)
```c
int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}
```

### Example 5: Power
```c
int power(int x, int n) {
    if (n == 0) return 1;
    return x * power(x, n - 1);
}
```

### Example 6: Tower of Hanoi
```c
void hanoi(int n, char from, char to, char aux) {
    if (n == 1) {
        printf("Move disk 1 from %c to %c\n", from, to);
        return;
    }
    hanoi(n - 1, from, aux, to);
    printf("Move disk %d from %c to %c\n", n, from, to);
    hanoi(n - 1, aux, to, from);
}
```
Number of moves = 2ⁿ − 1.

### Types of recursion

| Type | Description |
|---|---|
| **Direct** | A function calls itself |
| **Indirect** | A calls B, and B calls A |
| **Tail recursion** | The recursive call is the last statement, so there is no pending work |
| **Non-tail (head) recursion** | Work remains after the recursive call returns |
| **Linear / Tree recursion** | One call per invocation (factorial) / multiple calls (Fibonacci) |

**Indirect recursion example**
```c
void A(int n) { if (n > 0) { printf("%d ", n); B(n - 1); } }
void B(int n) { if (n > 1) { printf("%d ", n); A(n / 2); } }
```

**Tail recursion example**
```c
int factTail(int n, int acc) {
    if (n == 0) return acc;
    return factTail(n - 1, acc * n);
}
```

### How recursion works in memory
Each call creates a **stack frame** holding parameters, local variables, and the return address. Frames are pushed on each call and popped on each return (LIFO).

### Recursion vs Iteration

| Recursion | Iteration |
|---|---|
| Function calls itself | Uses loops (`for`, `while`) |
| Needs a base case | Needs a loop condition |
| More memory (stack frames) | Less memory |
| Slower due to call overhead | Faster |
| Code is shorter and elegant | Code is longer |
| Risk of stack overflow | No such risk |
| Suits trees, divide and conquer, backtracking | Suits simple repetition |

**Advantages**
- Simple, clean code for naturally recursive problems.
- Useful for trees, graphs, backtracking, and divide-and-conquer.

**Disadvantages**
- High memory usage and function call overhead.
- Harder to debug.
- Can overflow the stack.

---

## 11. Quick Revision: Important Points

1. A string is a char array ending with `'\0'`.
2. Use `strcmp()` to compare strings, never `==`.
3. `strlen` excludes `'\0'`, while `sizeof` includes it.
4. A function needs a declaration, definition, and call.
5. Formal parameters are in the definition and actual arguments are in the call.
6. C is **call by value** by default, and call by reference is done with pointers.
7. Arrays are passed by address, so the function changes the original.
8. Nested function calls are allowed, but nested definitions are not in standard C.
9. Every recursive function must have a base case.
10. Recursion uses the stack, and each call creates a new frame.

---

## 12. Common Exam Questions

**Short**
1. Differentiate between a character array and a string.
2. Define formal and actual parameters.
3. Why is `scanf("%s")` unsuitable for reading a full line?
4. What is a base case in recursion?

**Long**
1. Explain any 5 string handling functions with examples.
2. Explain call by value and call by reference with a swap program.
3. Write a program to pass an array to a function and find the sum and largest element.
4. Explain recursion. Write recursive programs for factorial and Fibonacci.
5. Differentiate between recursion and iteration.

**Programs to practice**
- Count vowels, consonants, and words in a string.
- Check a palindrome without using library functions.
- Sort strings alphabetically.
- Binary search using recursion.
- Reverse a string recursively.
- Convert a decimal to binary using recursion.