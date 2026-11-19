# C Programming Notes: Pointers & File Handling

---

## Table of Contents

1. [Pointers](#part-1-pointers)
   - Idea of Pointers
   - Defining Pointers
   - Use of Pointers
2. [File Handling](#part-2-file-handling-in-c)
   - Introduction
   - File Modes
   - Reading from Files
   - Writing to Files
3. [Important Questions](#important-exam-questions)
4. [Quick Revision](#quick-revision-cheat-sheet)

---

# Part 1: Pointers

## 1.1 Idea of Pointers

### Memory basics

Every variable in a C program is stored in the computer's memory (RAM). Memory is divided into small units called **bytes**, and each byte has a unique number called its **address**.

```
Address   :  1000   1004   1008   1012
Value     :   10     25     'A'    3.5
Variable  :   a      b      c      d
```

When you write `int a = 10;`, the compiler:
1. Reserves memory (4 bytes for an `int` on most systems)
2. Names that location `a`
3. Stores the value `10` there

### What is a pointer?

> A **pointer** is a variable that stores the **memory address** of another variable.

A normal variable holds a **value**. A pointer variable holds an **address**.

```
      int a = 10;            int *p = &a;

   +--------+                +--------+
   |   10   |  <-------------| 0x1000 |
   +--------+                +--------+
   a (addr 0x1000)           p (addr 0x2000)
```

Here `p` "points to" `a`.

### Why do we need pointers?

- Direct access to memory
- Efficient handling of arrays and strings
- Passing large data to functions without copying
- Allowing a function to modify its caller's variables
- Dynamic memory allocation
- Building data structures (linked lists, trees, graphs)

### Two key operators

| Operator | Name | Meaning |
|----------|------|---------|
| `&` | Address-of operator | Gives the address of a variable |
| `*` | Dereference (indirection) operator | Gives the value stored at an address |

---

## 1.2 Defining (Declaring) Pointers

### Syntax

```c
data_type *pointer_name;
```

The `data_type` is the type of the variable the pointer will point to.

```c
int    *p;     // pointer to an int
float  *q;     // pointer to a float
char   *ch;    // pointer to a char
double *d;     // pointer to a double
```

> The `*` in a declaration means "this is a pointer". The same `*` in an expression means "value at the address".

### Initialization

```c
int a = 10;
int *p;        // declaration
p = &a;        // initialization (store address of a)

int *q = &a;   // declaration + initialization together
```

> **Always initialize pointers.** An uninitialized pointer (called a *wild pointer*) holds a garbage address and can crash your program.

### Complete example

```c
#include <stdio.h>

int main() {
    int a = 10;
    int *p = &a;

    printf("Value of a          : %d\n", a);
    printf("Address of a (&a)   : %p\n", (void*)&a);
    printf("Value of p (address): %p\n", (void*)p);
    printf("Value at p (*p)     : %d\n", *p);
    printf("Address of p (&p)   : %p\n", (void*)&p);

    *p = 50;   // changes a through the pointer
    printf("New value of a      : %d\n", a);

    return 0;
}
```

**Output (addresses will vary):**
```
Value of a          : 10
Address of a (&a)   : 0x7ffe5c3a1b4c
Value of p (address): 0x7ffe5c3a1b4c
Value at p (*p)     : 10
Address of p (&p)   : 0x7ffe5c3a1b50
New value of a      : 50
```

### Important relationships

If `p = &a`, then:

| Expression | Meaning |
|-----------|---------|
| `p` | Address of `a` |
| `*p` | Value of `a` |
| `&a` | Address of `a` |
| `&p` | Address of the pointer `p` itself |
| `*&a` | Same as `a` |

### Special pointers

**1. NULL pointer** — points to nothing.
```c
int *p = NULL;
if (p == NULL) printf("Pointer is empty");
```

**2. Void pointer** — generic pointer that can hold the address of any type.
```c
void *vp;
int a = 5;
vp = &a;
printf("%d", *(int*)vp);   // must typecast before dereferencing
```

**3. Wild pointer** — uninitialized pointer (dangerous).
```c
int *p;     // wild pointer
*p = 10;    // undefined behaviour!
```

**4. Dangling pointer** — points to memory that has been freed or gone out of scope.
```c
int *p = malloc(sizeof(int));
free(p);
// p is now dangling; set p = NULL after free
```

**5. Pointer to pointer (double pointer)**
```c
int a = 10;
int *p = &a;
int **pp = &p;

printf("%d", **pp);   // 10
```

### Size of a pointer

All pointers have the same size regardless of the type they point to (typically 8 bytes on 64-bit systems, 4 bytes on 32-bit).

```c
printf("%zu %zu", sizeof(int*), sizeof(char*));  // same value
```

---

## 1.3 Use of Pointers

### (a) Pointer arithmetic

Valid operations on pointers: `++`, `--`, `+ n`, `- n`, and subtraction of two pointers (same array).

When you do `p + 1`, the address increases by `sizeof(data_type)` bytes, not by 1.

```c
int arr[3] = {10, 20, 30};
int *p = arr;        // same as &arr[0]

printf("%d\n", *p);        // 10
p++;                       // moves 4 bytes ahead
printf("%d\n", *p);        // 20
printf("%d\n", *(p + 1));  // 30
```

> Adding two pointers, multiplying or dividing a pointer is **not allowed**.

### (b) Pointers and arrays

The name of an array is a constant pointer to its first element.

```c
int arr[5] = {1, 2, 3, 4, 5};
int *p = arr;

for (int i = 0; i < 5; i++) {
    printf("%d ", *(p + i));   // same as arr[i]
}
```

| Array notation | Pointer notation |
|----------------|------------------|
| `arr[i]` | `*(arr + i)` |
| `&arr[i]` | `arr + i` |

### (c) Pointers and strings

```c
char *str = "Hello";
while (*str != '\0') {
    printf("%c", *str);
    str++;
}
```

### (d) Call by value vs Call by reference

**Call by value** — function gets a *copy*; original is unchanged.

```c
void swap(int a, int b) {
    int t = a; a = b; b = t;
}
// swap(x, y) does NOT change x and y
```

**Call by reference** — pass addresses using pointers; the function changes the original.

```c
#include <stdio.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int x = 10, y = 20;
    swap(&x, &y);
    printf("x = %d, y = %d", x, y);   // x = 20, y = 10
    return 0;
}
```

### (e) Returning multiple values from a function

```c
void calc(int a, int b, int *sum, int *diff) {
    *sum  = a + b;
    *diff = a - b;
}

int main() {
    int s, d;
    calc(10, 4, &s, &d);
    printf("%d %d", s, d);   // 14 6
}
```

### (f) Dynamic memory allocation

Pointers allow memory to be allocated **at runtime** from the heap. Header: `<stdlib.h>`.

| Function | Purpose |
|----------|---------|
| `malloc(size)` | Allocates `size` bytes (uninitialized) |
| `calloc(n, size)` | Allocates `n` blocks, initialized to 0 |
| `realloc(ptr, new_size)` | Resizes previously allocated memory |
| `free(ptr)` | Releases memory |

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    printf("Enter size: ");
    scanf("%d", &n);

    int *arr = (int*)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        arr[i] = i * 2;
    }
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    free(arr);
    arr = NULL;
    return 0;
}
```

### (g) Pointers to structures

```c
struct Student {
    int roll;
    char name[20];
};

struct Student s = {1, "Amit"};
struct Student *ptr = &s;

printf("%d %s", ptr->roll, ptr->name);   // arrow operator
// equivalent: (*ptr).roll
```

### (h) Pointers to functions

```c
int add(int a, int b) { return a + b; }

int main() {
    int (*fp)(int, int) = add;
    printf("%d", fp(3, 4));   // 7
}
```

### (i) Array of pointers

```c
char *names[] = {"Ram", "Shyam", "Mohan"};
for (int i = 0; i < 3; i++)
    printf("%s\n", names[i]);
```

### Advantages and disadvantages

| Advantages | Disadvantages |
|-----------|---------------|
| Faster, efficient access to data | Easy to make mistakes (crashes, segmentation faults) |
| Dynamic memory management | Memory leaks if `free()` is forgotten |
| Enables data structures | Harder to read and debug |
| Call by reference | Wild/dangling pointers are dangerous |

### Common mistakes

1. Using an uninitialized pointer
2. Dereferencing a `NULL` pointer
3. Forgetting `free()` (memory leak)
4. Using memory after `free()` (dangling pointer)
5. Writing beyond array bounds
6. Confusing `*p` (value) with `p` (address)

---

# Part 2: File Handling in C

## 2.1 Introduction

### Why files?

Variables live in RAM, so data is **lost** when the program ends. A **file** stores data permanently on disk (secondary storage).

Uses: saving records, reading input data, logging, configuration, databases.

### Types of files

| Type | Description | Example |
|------|-------------|---------|
| **Text file** | Data stored as readable characters; newline is translated | `.txt`, `.c`, `.csv` |
| **Binary file** | Data stored in raw memory format (as bytes); faster, compact, not human-readable | `.dat`, `.bin`, images |

### The `FILE` pointer

C handles files through a pointer of type `FILE` (defined in `<stdio.h>`).

```c
FILE *fp;
```

`fp` is the **file pointer** and holds all information about the opened file (position, buffer, errors).

### Basic steps of file handling

```
1. Declare a FILE pointer
2. Open the file          -> fopen()
3. Check if opened        -> fp == NULL ?
4. Read / Write           -> fscanf, fgets, fprintf, fputs ...
5. Close the file         -> fclose()
```

---

## 2.2 Opening a File: `fopen()`

### Syntax

```c
FILE *fopen(const char *filename, const char *mode);
```

- Returns a `FILE*` on success
- Returns `NULL` on failure (file missing, no permission, etc.)

```c
FILE *fp;
fp = fopen("data.txt", "r");
if (fp == NULL) {
    printf("Error opening file!\n");
    return 1;
}
```

### Closing a file: `fclose()`

```c
fclose(fp);
```

Closing flushes buffered data to disk and frees resources. Always close files.

---

## 2.3 Different Modes of Opening a File

### Text file modes

| Mode | Name | Meaning | If file exists | If file doesn't exist |
|------|------|---------|----------------|----------------------|
| `"r"` | Read | Open for reading only | Opens; pointer at start | Returns `NULL` (error) |
| `"w"` | Write | Open for writing only | **Erases all content** | Creates new file |
| `"a"` | Append | Open for writing at end | Keeps content; writes at end | Creates new file |
| `"r+"` | Read + Write | Reading and writing | Opens; pointer at start; content preserved | Returns `NULL` |
| `"w+"` | Write + Read | Reading and writing | **Erases all content** | Creates new file |
| `"a+"` | Append + Read | Reading and appending | Keeps content; writes always go at end | Creates new file |

### Binary file modes

Add a `b` to the mode:

| Mode | Meaning |
|------|---------|
| `"rb"` | Read binary |
| `"wb"` | Write binary |
| `"ab"` | Append binary |
| `"rb+"` or `"r+b"` | Read and write binary |
| `"wb+"` or `"w+b"` | Write and read binary (truncates) |
| `"ab+"` or `"a+b"` | Append and read binary |

### Easy way to remember

- **r** = read (file must exist)
- **w** = write (file is wiped or created)
- **a** = append (add to the end)
- **+** = adds the other ability (read *and* write)
- **b** = binary

### Mode behaviour at a glance

| Mode | Can Read | Can Write | Creates File | Truncates | Start Position |
|------|:-------:|:--------:|:-----------:|:---------:|:--------------:|
| r  | Yes | No  | No  | No  | Beginning |
| w  | No  | Yes | Yes | Yes | Beginning |
| a  | No  | Yes | Yes | No  | End |
| r+ | Yes | Yes | No  | No  | Beginning |
| w+ | Yes | Yes | Yes | Yes | Beginning |
| a+ | Yes | Yes | Yes | No  | End (writes); start (reads) |

---

## 2.4 Writing to Files

### Functions for writing

| Function | Purpose | Syntax |
|----------|---------|--------|
| `fputc()` | Write one character | `fputc(ch, fp);` |
| `fputs()` | Write a string | `fputs("text", fp);` |
| `fprintf()` | Write formatted data | `fprintf(fp, "%d %s", n, s);` |
| `fwrite()` | Write blocks (binary) | `fwrite(&data, size, count, fp);` |

### Example 1: `fputc()` — character by character

```c
#include <stdio.h>

int main() {
    FILE *fp = fopen("char.txt", "w");
    if (fp == NULL) {
        printf("Cannot open file\n");
        return 1;
    }

    char ch;
    printf("Enter text (press Enter to stop): ");
    while ((ch = getchar()) != '\n') {
        fputc(ch, fp);
    }

    fclose(fp);
    printf("Data written successfully.\n");
    return 0;
}
```

### Example 2: `fputs()` — strings

```c
#include <stdio.h>

int main() {
    FILE *fp = fopen("text.txt", "w");
    if (fp == NULL) return 1;

    fputs("Hello, this is line 1.\n", fp);
    fputs("This is line 2.\n", fp);

    fclose(fp);
    return 0;
}
```

### Example 3: `fprintf()` — formatted output

```c
#include <stdio.h>

int main() {
    FILE *fp = fopen("student.txt", "w");
    if (fp == NULL) return 1;

    int roll = 101;
    char name[] = "Amit";
    float marks = 85.5;

    fprintf(fp, "Roll: %d\nName: %s\nMarks: %.1f\n", roll, name, marks);

    fclose(fp);
    return 0;
}
```

### Example 4: Appending data

```c
FILE *fp = fopen("student.txt", "a");   // old content stays
fprintf(fp, "Added later\n");
fclose(fp);
```

### Example 5: `fwrite()` — binary write

```c
#include <stdio.h>

struct Student {
    int roll;
    char name[20];
    float marks;
};

int main() {
    struct Student s = {1, "Riya", 91.5};

    FILE *fp = fopen("student.dat", "wb");
    if (fp == NULL) return 1;

    fwrite(&s, sizeof(struct Student), 1, fp);

    fclose(fp);
    return 0;
}
```

`fwrite(ptr, size, count, fp)`:
- `ptr` — address of the data
- `size` — size of each element
- `count` — number of elements
- `fp` — file pointer

---

## 2.5 Reading from Files

### Functions for reading

| Function | Purpose | Syntax |
|----------|---------|--------|
| `fgetc()` | Read one character | `ch = fgetc(fp);` |
| `fgets()` | Read a line / string | `fgets(str, size, fp);` |
| `fscanf()` | Read formatted data | `fscanf(fp, "%d", &n);` |
| `fread()` | Read blocks (binary) | `fread(&data, size, count, fp);` |

### The end-of-file (EOF)

`fgetc()` returns `EOF` (usually -1) at the end of the file. You can also use `feof(fp)`.

> Store the result of `fgetc()` in an `int`, not a `char`, so that `EOF` can be detected correctly.

### Example 1: `fgetc()` — read a whole file

```c
#include <stdio.h>

int main() {
    FILE *fp = fopen("text.txt", "r");
    if (fp == NULL) {
        printf("File not found\n");
        return 1;
    }

    int ch;
    while ((ch = fgetc(fp)) != EOF) {
        putchar(ch);
    }

    fclose(fp);
    return 0;
}
```

### Example 2: `fgets()` — read line by line

```c
#include <stdio.h>

int main() {
    FILE *fp = fopen("text.txt", "r");
    if (fp == NULL) return 1;

    char line[100];
    while (fgets(line, sizeof(line), fp) != NULL) {
        printf("%s", line);
    }

    fclose(fp);
    return 0;
}
```

### Example 3: `fscanf()` — formatted input

```c
#include <stdio.h>

int main() {
    FILE *fp = fopen("student.txt", "w");
    fprintf(fp, "101 Amit 85.5\n102 Neha 90.0\n");
    fclose(fp);

    fp = fopen("student.txt", "r");
    int roll;
    char name[20];
    float marks;

    while (fscanf(fp, "%d %s %f", &roll, name, &marks) == 3) {
        printf("%d %s %.1f\n", roll, name, marks);
    }

    fclose(fp);
    return 0;
}
```

### Example 4: `fread()` — binary read

```c
#include <stdio.h>

struct Student {
    int roll;
    char name[20];
    float marks;
};

int main() {
    struct Student s;

    FILE *fp = fopen("student.dat", "rb");
    if (fp == NULL) return 1;

    while (fread(&s, sizeof(struct Student), 1, fp) == 1) {
        printf("%d %s %.1f\n", s.roll, s.name, s.marks);
    }

    fclose(fp);
    return 0;
}
```

---

## 2.6 Complete Program: Write then Read

```c
#include <stdio.h>

int main() {
    FILE *fp;
    char line[100];

    // WRITE
    fp = fopen("notes.txt", "w");
    if (fp == NULL) {
        printf("Error!\n");
        return 1;
    }
    fprintf(fp, "C is a powerful language.\n");
    fprintf(fp, "Files store data permanently.\n");
    fclose(fp);

    // READ
    fp = fopen("notes.txt", "r");
    if (fp == NULL) {
        printf("Error!\n");
        return 1;
    }
    printf("File contents:\n");
    while (fgets(line, sizeof(line), fp) != NULL) {
        printf("%s", line);
    }
    fclose(fp);

    return 0;
}
```

---

## 2.7 Other Useful File Functions

| Function | Purpose |
|----------|---------|
| `feof(fp)` | Returns non-zero if end of file reached |
| `ferror(fp)` | Checks if an error occurred |
| `rewind(fp)` | Moves the file position to the beginning |
| `fseek(fp, offset, origin)` | Moves the position to a specific place |
| `ftell(fp)` | Returns current position (in bytes from start) |
| `remove("file")` | Deletes a file |
| `rename("old", "new")` | Renames a file |
| `fflush(fp)` | Forces buffered data to be written |

### `fseek()` origins

| Constant | Meaning |
|----------|---------|
| `SEEK_SET` | Beginning of file |
| `SEEK_CUR` | Current position |
| `SEEK_END` | End of file |

```c
fseek(fp, 0, SEEK_END);       // go to end
long size = ftell(fp);        // file size in bytes
rewind(fp);                   // back to start
```

### Counting characters, words, lines

```c
#include <stdio.h>

int main() {
    FILE *fp = fopen("text.txt", "r");
    if (fp == NULL) return 1;

    int ch, chars = 0, words = 0, lines = 0, inWord = 0;

    while ((ch = fgetc(fp)) != EOF) {
        chars++;
        if (ch == '\n') lines++;
        if (ch == ' ' || ch == '\n' || ch == '\t')
            inWord = 0;
        else if (!inWord) {
            inWord = 1;
            words++;
        }
    }

    printf("Characters: %d\nWords: %d\nLines: %d\n", chars, words, lines);
    fclose(fp);
    return 0;
}
```

### Copying one file to another

```c
#include <stdio.h>

int main() {
    FILE *src = fopen("a.txt", "r");
    FILE *dst = fopen("b.txt", "w");

    if (src == NULL || dst == NULL) {
        printf("Error opening files\n");
        return 1;
    }

    int ch;
    while ((ch = fgetc(src)) != EOF)
        fputc(ch, dst);

    fclose(src);
    fclose(dst);
    return 0;
}
```

---

## 2.8 Text File vs Binary File

| Feature | Text File | Binary File |
|---------|-----------|-------------|
| Storage | Characters (ASCII) | Raw bytes |
| Readable by humans | Yes | No |
| Functions | `fprintf`, `fscanf`, `fgets`, `fputs` | `fwrite`, `fread` |
| Size | Larger | Smaller |
| Speed | Slower | Faster |
| Portability | High | Lower |
| Mode | `"r"`, `"w"`, `"a"` | `"rb"`, `"wb"`, `"ab"` |

## 2.9 Difference: `scanf/printf` vs `fscanf/fprintf`

| `scanf` / `printf` | `fscanf` / `fprintf` |
|---|---|
| Work on keyboard / screen (stdin/stdout) | Work on any file pointer |
| No file pointer needed | First argument is a `FILE*` |

> `stdin`, `stdout`, and `stderr` are predefined file pointers. `fprintf(stdout, "Hi")` is the same as `printf("Hi")`.

## 2.10 Good practices

1. Always check if `fopen()` returned `NULL`.
2. Always `fclose()` every opened file.
3. Use the correct mode (`"w"` destroys existing data!).
4. Use `fgets()` instead of `gets()` (which is unsafe and removed).
5. Check return values of `fscanf`, `fread`.
6. Use binary mode for structures.

---

# Important Exam Questions

### Short answer
1. What is a pointer? How is it declared?
2. Differentiate between `&` and `*` operators.
3. What is a NULL pointer? A void pointer?
4. What is the difference between call by value and call by reference?
5. What happens when `p++` is executed on an `int` pointer?
6. Write the syntax of `fopen()`. What does it return on failure?
7. Differentiate between `"w"` and `"a"` modes.
8. What is the use of `fclose()`?
9. Differentiate between text and binary files.
10. What is `EOF`?

### Long answer
1. Explain pointers with example. List their advantages and uses.
2. Write a program to swap two numbers using pointers.
3. Explain pointer arithmetic with a program.
4. Explain the relationship between arrays and pointers.
5. Explain all file opening modes in C with a table.
6. Write a program to read a text file and count its characters, words, and lines.
7. Write a program to copy the contents of one file into another.
8. Write a program to store student records in a binary file and read them back.

### Output prediction practice

```c
int a = 5, *p = &a;
*p = *p + 10;
printf("%d", a);
```
**Answer:** `15`

```c
int arr[] = {10, 20, 30};
int *p = arr;
printf("%d", *(p + 2));
```
**Answer:** `30`

---

# Quick Revision Cheat Sheet

### Pointers

```c
int a = 10;
int *p = &a;     // p holds address of a
*p               // value at that address
p++              // moves by sizeof(int)
int **pp = &p;   // pointer to pointer
int *q = NULL;   // null pointer
p = malloc(n * sizeof(int));  free(p);
ptr->member      // struct pointer access
```

### File handling

```c
FILE *fp = fopen("file.txt", "r");   // r, w, a, r+, w+, a+ (+b for binary)
if (fp == NULL) { /* error */ }

fprintf(fp, "%d", x);   fscanf(fp, "%d", &x);
fputs(str, fp);         fgets(str, n, fp);
fputc(ch, fp);          ch = fgetc(fp);
fwrite(&s, sizeof(s), 1, fp);   fread(&s, sizeof(s), 1, fp);

fseek(fp, 0, SEEK_SET);  ftell(fp);  rewind(fp);  feof(fp);
fclose(fp);
```

### Mode memory trick

| Want to... | Use |
|-----------|-----|
| Read existing file | `r` |
| Create / overwrite | `w` |
| Add at end | `a` |
| Do both read & write | add `+` |
| Binary data | add `b` |

---

