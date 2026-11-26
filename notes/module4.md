# C Programming Notes: Storage Classes, Structures, Unions, Bit-fields & Enums

---

## Table of Contents

1. Introduction
2. Storage Classes in C
3. Introduction to Structures
4. Advantages of Structures
5. Accessing Elements of a Structure
6. Nested Structures
7. Array of Structures
8. Functions and Structures
9. Unions
10. Bit-fields
11. Enumerated Data Types
12. Quick Revision Tables
13. Important Exam Questions

---

## 1. Introduction

C provides three categories of data types:

| Category | Examples |
|---|---|
| **Primary (basic)** | `int`, `char`, `float`, `double`, `void` |
| **Derived** | arrays, pointers, functions |
| **User-defined** | `struct`, `union`, `enum`, `typedef` |

Primary data types store only **one value of one type**. Real-world data is usually a **collection of related items of different types** (for example, a student has a name, roll number and marks). To handle this, C lets the programmer create **user-defined data types**: structures, unions and enumerations.

This unit also covers **storage classes**, which control *where* a variable lives in memory, *how long* it lives (lifetime) and *which part of the program can see it* (scope).

---

## 2. Storage Classes in C

### 2.1 What is a Storage Class?

A **storage class** tells the compiler four things about a variable:

1. **Storage location**: where the variable is stored (memory or CPU register)
2. **Default (initial) value**: value held if not initialised
3. **Scope**: the region of the program in which the variable is accessible
4. **Lifetime**: how long the variable exists in memory

**Syntax:**

```c
storage_class data_type variable_name;
```

C has **four** storage classes: `auto`, `register`, `static`, `extern`.

### 2.2 `auto` Storage Class

- Default storage class for all **local variables**.
- Stored in **memory (stack)**.
- Default value: **garbage** (unpredictable).
- Scope: **local** to the block in which it is declared.
- Lifetime: until the block ends.

```c
#include <stdio.h>

int main() {
    auto int a = 10;   // same as: int a = 10;
    {
        auto int a = 20;   // different variable, inner block
        printf("Inner a = %d\n", a);   // 20
    }
    printf("Outer a = %d\n", a);       // 10
    return 0;
}
```

### 2.3 `register` Storage Class

- Requests the compiler to store the variable in a **CPU register** for faster access.
- It is only a **request**; if no register is free, it behaves like `auto`.
- Default value: **garbage**.
- Scope: local to the block. Lifetime: until the block ends.
- **The address-of operator (`&`) cannot be used** on a register variable, because registers have no memory address.
- Used for frequently accessed variables such as loop counters.

```c
#include <stdio.h>

int main() {
    register int i;
    for (i = 0; i < 5; i++)
        printf("%d ", i);
    // printf("%p", &i);   // ERROR: cannot take address of register variable
    return 0;
}
```

### 2.4 `static` Storage Class

- Stored in **data segment** (not on the stack).
- Default value: **zero**.
- Initialised **only once** (at compile time / program start).
- Scope: **local** to the block/function (for static local) or **file** (for static global).
- Lifetime: **entire program execution**. The variable retains its value between function calls.

```c
#include <stdio.h>

void counter() {
    static int count = 0;   // initialised only once
    count++;
    printf("Count = %d\n", count);
}

int main() {
    counter();   // Count = 1
    counter();   // Count = 2
    counter();   // Count = 3
    return 0;
}
```

If `count` were `auto`, the output would be `1 1 1`.

**Static global variable / function:** accessible only within the same source file (internal linkage).

### 2.5 `extern` Storage Class

- Declares a variable that is **defined elsewhere** (in another file or later in the same file). It does **not** allocate memory; it only refers to the existing definition.
- Default value: **zero**.
- Scope: **global** (across files). Lifetime: **entire program**.
- Used to share global variables between multiple source files.

**File1.c**
```c
int x = 50;     // definition
```

**File2.c**
```c
#include <stdio.h>
extern int x;   // declaration (refers to x in File1.c)

int main() {
    printf("x = %d\n", x);   // 50
    return 0;
}
```

### 2.6 Summary Table of Storage Classes

| Storage Class | Storage | Default Value | Scope | Lifetime |
|---|---|---|---|---|
| `auto` | Stack (memory) | Garbage | Local (block) | End of block |
| `register` | CPU register (if available) | Garbage | Local (block) | End of block |
| `static` | Data segment | 0 | Local (or file if global) | Entire program |
| `extern` | Data segment | 0 | Global (multiple files) | Entire program |

### 2.7 Key Points

- Local variables default to `auto`; global variables default to `extern`-like behaviour (static storage duration).
- `static` is the only class that preserves a value between function calls.
- `register` variables cannot have their address taken.

---

## 3. Introduction to Structures

### 3.1 Definition

A **structure** is a **user-defined data type** that groups **related variables of different data types** under a single name. Each variable inside a structure is called a **member** (or field or element).

### 3.2 Declaring a Structure

**Syntax:**

```c
struct structure_name {
    data_type member1;
    data_type member2;
    ...
    data_type memberN;
};            // semicolon is mandatory
```

**Example:**

```c
struct student {
    int  roll_no;
    char name[30];
    float marks;
};
```

> Declaring a structure **does not allocate memory**. It only creates a template (blueprint). Memory is allocated when variables are created.

### 3.3 Defining Structure Variables

**Method 1: After declaration**

```c
struct student s1, s2;
```

**Method 2: Along with declaration**

```c
struct student {
    int roll_no;
    char name[30];
    float marks;
} s1, s2;
```

**Method 3: Using `typedef`**

```c
typedef struct {
    int roll_no;
    char name[30];
    float marks;
} Student;

Student s1, s2;     // no need to write 'struct'
```

### 3.4 Initialising a Structure

```c
struct student s1 = {101, "Amit", 88.5};
```

Members are assigned **in the order of declaration**. Uninitialised members of a partially initialised structure are set to 0.

**Designated initialisation (C99):**

```c
struct student s2 = { .name = "Riya", .roll_no = 102, .marks = 91.0 };
```

### 3.5 Size of a Structure

The size of a structure is **at least** the sum of the sizes of its members. Because of **padding** (alignment), it may be larger.

```c
struct demo {
    char c;     // 1 byte  (+3 padding)
    int  i;     // 4 bytes
};
printf("%zu", sizeof(struct demo));   // typically 8, not 5
```

Use `sizeof(struct name)` to get the exact size.

### 3.6 Memory Layout

Members are stored in **contiguous but separate** memory locations, in the order declared.

```
struct student s1:
| roll_no (4 B) | name (30 B) | (padding) | marks (4 B) |
```

---

## 4. Advantages of Structures

1. **Group heterogeneous data**: different data types can be stored together under one name (an array cannot do this).
2. **Logical organisation**: related data is kept together, giving clear, readable code (for example, student, employee, book records).
3. **Easier data handling**: the entire record can be copied with one assignment (`s2 = s1;`) and passed to or returned from functions.
4. **Supports complex data structures**: basis for linked lists, stacks, queues, trees and graphs (using self-referential structures).
5. **Arrays of records**: an array of structures represents a database table.
6. **Reduces number of variables**: one structure variable replaces many separate variables.
7. **Modularity and reusability**: one structure definition can be reused to create many variables.
8. **Nesting**: a structure can contain other structures, modelling real-world hierarchy.
9. **Better program maintenance**: changing the record layout needs modification at one place only.
10. **File handling**: whole records can be written to and read from files using `fwrite()` and `fread()`.

---

## 5. Accessing Elements of a Structure

### 5.1 Dot Operator (`.`): with structure variable

**Syntax:** `structure_variable.member_name`

```c
#include <stdio.h>
#include <string.h>

struct student {
    int roll_no;
    char name[30];
    float marks;
};

int main() {
    struct student s1;

    s1.roll_no = 101;
    strcpy(s1.name, "Amit");      // strings cannot be assigned with '='
    s1.marks = 88.5;

    printf("Roll No : %d\n", s1.roll_no);
    printf("Name    : %s\n", s1.name);
    printf("Marks   : %.2f\n", s1.marks);
    return 0;
}
```

**Reading input:**

```c
scanf("%d", &s1.roll_no);
scanf("%s", s1.name);          // no & for character array
scanf("%f", &s1.marks);
```

### 5.2 Arrow Operator (`->`): with pointer to structure

**Syntax:** `pointer->member_name`, which is equivalent to `(*pointer).member_name`

```c
struct student s1 = {101, "Amit", 88.5};
struct student *ptr = &s1;

printf("%d\n", ptr->roll_no);      // 101
printf("%s\n", (*ptr).name);       // Amit (same as ptr->name)
```

> Parentheses are needed in `(*ptr).name` because `.` has higher precedence than `*`.

### 5.3 Structure Assignment

One structure variable can be assigned to another of the **same type**:

```c
struct student s2;
s2 = s1;     // copies all members
```

> Structures **cannot be compared** using `==`. Compare member by member.

---

## 6. Nested Structures

A **nested structure** is a structure that contains another structure as a member.

### 6.1 Method 1: Separate Structure Definitions

```c
#include <stdio.h>

struct date {
    int day, month, year;
};

struct employee {
    int id;
    char name[30];
    struct date dob;      // nested structure variable
};

int main() {
    struct employee e1 = {1, "Ravi", {15, 8, 1995}};

    printf("ID   : %d\n", e1.id);
    printf("Name : %s\n", e1.name);
    printf("DOB  : %d/%d/%d\n", e1.dob.day, e1.dob.month, e1.dob.year);
    return 0;
}
```

The inner structure must be **defined before** the outer one.

### 6.2 Method 2: Embedded (Structure Inside Structure)

```c
struct employee {
    int id;
    char name[30];
    struct {
        int day, month, year;
    } dob;                   // anonymous inner structure
};
```

Access is the same: `e1.dob.year`.

### 6.3 Accessing Nested Members

Use the dot operator repeatedly, from outer to inner:

```
outer_var.inner_var.member
```

With pointers: `ptr->dob.year`

### 6.4 Points to Remember

- A structure **cannot contain itself** as a member (it would have infinite size), but it **can contain a pointer to itself** (self-referential structure, used in linked lists):

```c
struct node {
    int data;
    struct node *next;
};
```

---

## 7. Array of Structures

An **array of structures** stores multiple records of the same structure type. It is like a table: each element is one record.

### 7.1 Declaration

```c
struct student s[3];        // array of 3 student records
```

### 7.2 Initialisation

```c
struct student s[3] = {
    {101, "Amit", 88.5},
    {102, "Riya", 91.0},
    {103, "Karan", 76.5}
};
```

### 7.3 Example: Reading and Displaying n Records

```c
#include <stdio.h>

struct student {
    int roll_no;
    char name[30];
    float marks;
};

int main() {
    struct student s[50];
    int n, i;

    printf("Enter number of students: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("\nStudent %d\n", i + 1);
        printf("Roll No: ");
        scanf("%d", &s[i].roll_no);
        printf("Name: ");
        scanf("%s", s[i].name);
        printf("Marks: ");
        scanf("%f", &s[i].marks);
    }

    printf("\n%-8s %-15s %-8s\n", "Roll", "Name", "Marks");
    for (i = 0; i < n; i++)
        printf("%-8d %-15s %-8.2f\n", s[i].roll_no, s[i].name, s[i].marks);

    return 0;
}
```

### 7.4 Example: Finding the Topper

```c
int top = 0;
for (i = 1; i < n; i++)
    if (s[i].marks > s[top].marks)
        top = i;
printf("Topper: %s with %.2f marks\n", s[top].name, s[top].marks);
```

## Example : Define a structure named Student containing Roll Number, Name, and Marks. Write a C program to input details of five students and display the details of the student who scored the highest marks.


```c


#include <stdio.h>


struct Student
{
   int roll;
   char name[50];
   float marks;
};


int main()
{
   struct Student s[5];
   int i, maxIndex = 0;


   for(i = 0; i < 5; i++)
   {
       printf("\nEnter Student %d Details\n", i + 1);


       printf("Enter Roll Number: ");
       scanf("%d", &s[i].roll);


       printf("Enter Name: ");
       scanf(" %49[^\n]", s[i].name);


       printf("Enter Marks: ");
       scanf("%f", &s[i].marks);
   }


   for(i = 1; i < 5; i++)
   {
       if(s[i].marks > s[maxIndex].marks)
       {
           maxIndex = i;
       }
   }


   printf("\nStudent with Highest Marks\n");
   printf("Roll Number: %d\n", s[maxIndex].roll);
   printf("Name: %s\n", s[maxIndex].name);
   printf("Marks: %.2f\n", s[maxIndex].marks);


   return 0;
}


```


### 7.5 Memory Layout

Elements are stored **contiguously**. Total size = `n * sizeof(struct student)`.

```
s[0] | s[1] | s[2] | ...
```

### 7.6 Pointer to Array of Structures

```c
struct student *p = s;      // points to s[0]
for (i = 0; i < n; i++)
    printf("%s\n", (p + i)->name);
```

---

## 8. Functions and Structures

Structures can interact with functions in three ways:

1. Passing **individual members** to a function
2. Passing the **whole structure** (by value)
3. Passing a **pointer to a structure** (by reference / address)

A function can also **return a structure**.

### 8.1 Passing Individual Members

```c
void show(int roll, float marks) {
    printf("%d %.2f\n", roll, marks);
}
...
show(s1.roll_no, s1.marks);
```

### 8.2 Passing a Structure by Value

A **copy** of the entire structure is sent. Changes inside the function **do not** affect the original.

```c
#include <stdio.h>

struct student {
    int roll_no;
    float marks;
};

void display(struct student s) {
    printf("Roll: %d, Marks: %.2f\n", s.roll_no, s.marks);
    s.marks = 0;           // modifies only the copy
}

int main() {
    struct student s1 = {101, 85.5};
    display(s1);
    printf("After call: %.2f\n", s1.marks);    // still 85.5
    return 0;
}
```

*Disadvantage:* copying large structures wastes time and memory.

### 8.3 Passing a Structure by Reference (Pointer)

The **address** is passed. Changes made inside the function **affect the original**. Efficient for large structures.

```c
void update(struct student *s) {
    s->marks += 5;             // modifies the original
}

int main() {
    struct student s1 = {101, 85.5};
    update(&s1);
    printf("%.2f\n", s1.marks);     // 90.50
    return 0;
}
```

### 8.4 Returning a Structure from a Function

```c
#include <stdio.h>

struct complex {
    float real, imag;
};

struct complex add(struct complex a, struct complex b) {
    struct complex result;
    result.real = a.real + b.real;
    result.imag = a.imag + b.imag;
    return result;
}

int main() {
    struct complex c1 = {2.5, 3.0}, c2 = {1.5, 4.0}, c3;
    c3 = add(c1, c2);
    printf("Sum = %.1f + %.1fi\n", c3.real, c3.imag);    // 4.0 + 7.0i
    return 0;
}
```

### 8.5 Passing an Array of Structures

An array of structures is passed like any array (the **address of the first element** is passed), so changes are reflected in the original.

```c
void printAll(struct student s[], int n) {
    int i;
    for (i = 0; i < n; i++)
        printf("%d %s %.2f\n", s[i].roll_no, s[i].name, s[i].marks);
}
...
printAll(s, 3);
```

### 8.6 Comparison

| Method | What is passed | Original modified? | Efficiency |
|---|---|---|---|
| By members | Individual values | No | Good for few members |
| By value | Copy of whole structure | No | Slow for large structures |
| By pointer | Address | Yes | Fast |
| Array of structures | Address of first element | Yes | Fast |

---

## 9. Unions

### 9.1 Definition

A **union** is a user-defined data type similar to a structure, but **all members share the same memory location**. Only **one member can hold a valid value at a time**.

### 9.2 Syntax

```c
union union_name {
    data_type member1;
    data_type member2;
    ...
};
```

**Example:**

```c
union data {
    int   i;
    float f;
    char  c;
};
```

### 9.3 Memory Allocation

The size of a union = **size of its largest member** (plus any padding).

```c
#include <stdio.h>

union data {
    int i;        // 4 bytes
    float f;      // 4 bytes
    char c;       // 1 byte
};

int main() {
    union data d;
    printf("Size of union = %zu\n", sizeof(d));    // 4
    return 0;
}
```

```
Union memory (4 bytes):
| byte0 | byte1 | byte2 | byte3 |
  <------ i, f share all 4 ----->
  <c> uses only byte0
```

### 9.4 Accessing Members

Same as structures: `.` for variables and `->` for pointers.

```c
#include <stdio.h>

union data {
    int i;
    float f;
};

int main() {
    union data d;

    d.i = 10;
    printf("i = %d\n", d.i);       // 10

    d.f = 3.14;                    // overwrites d.i
    printf("f = %.2f\n", d.f);     // 3.14
    printf("i = %d\n", d.i);       // garbage (data overwritten)
    return 0;
}
```

### 9.5 Initialisation

Only the **first member** can be initialised at declaration:

```c
union data d = {25};     // initialises d.i
```

### 9.6 Structure vs Union

| Feature | Structure | Union |
|---|---|---|
| Keyword | `struct` | `union` |
| Memory | Separate memory for each member | All members share one memory block |
| Size | Sum of all members (plus padding) | Size of the largest member |
| Access | All members usable at the same time | Only one member valid at a time |
| Modifying a member | Does not affect others | Overwrites the other members |
| Initialisation | All members can be initialised | Only the first member (traditionally) |
| Memory efficiency | Less efficient | More efficient |
| Use | Records, database-like data | Memory-saving, type conversion, hardware registers |

### 9.7 Uses of Unions

- Saving memory when only one of several values is needed at a time
- Accessing the same data in different forms (for example, viewing a `float` as bytes)
- Interpreting hardware registers and communication protocols
- Implementing variant (tagged) data types

**Tagged union example:**

```c
struct value {
    int type;              // 0 = int, 1 = float
    union {
        int i;
        float f;
    } data;
};
```

---

## 10. Bit-fields

### 10.1 Definition

A **bit-field** lets you specify the **exact number of bits** that a structure (or union) member should occupy. It is used to **save memory** when a variable needs only a few bits (for example, flags, or a value that is only 0 to 7).

### 10.2 Syntax

```c
struct structure_name {
    data_type member_name : width_in_bits;
};
```

- `data_type` must be an **integer type** (`int`, `unsigned int`, `signed int`; `_Bool` in C99).
- `width` is a constant number of bits (cannot exceed the size of the data type).

### 10.3 Example

Storing a date compactly:

```c
#include <stdio.h>

struct date {
    unsigned int day   : 5;    // 0 to 31
    unsigned int month : 4;    // 0 to 15
    unsigned int year  : 12;   // 0 to 4095
};

int main() {
    struct date d = {17, 11, 2026};

    printf("%u/%u/%u\n", d.day, d.month, d.year);
    printf("Size = %zu bytes\n", sizeof(d));    // typically 4 bytes (21 bits used)
    return 0;
}
```

Without bit-fields, three `int` members would need 12 bytes.

### 10.4 Flag Example

```c
struct flags {
    unsigned int isReady  : 1;
    unsigned int isError  : 1;
    unsigned int mode     : 2;    // values 0 to 3
};
```

### 10.5 Unnamed and Zero-Width Bit-fields

```c
struct s {
    unsigned int a : 3;
    unsigned int   : 2;     // unnamed: 2 bits of padding
    unsigned int b : 3;
    unsigned int   : 0;     // zero width: next field starts in a new unit
    unsigned int c : 4;
};
```

### 10.6 Restrictions

1. You **cannot take the address** of a bit-field (`&s.day` is an error), so pointers and `scanf("%d", &s.day)` do not work directly.
2. You cannot create an **array** of bit-fields.
3. Bit-field **width cannot exceed** the size of its type.
4. If a value is larger than the field can hold, it is **truncated** (overflow wraps around).
5. The **layout** (order of bits, packing across units) is **implementation-defined**, so it is not portable.
6. Bit-fields cannot be members of a function's return type in a portable way, and `sizeof` cannot be applied to a bit-field itself.

### 10.7 Advantages and Disadvantages

| Advantages | Disadvantages |
|---|---|
| Saves memory | Not portable (machine-dependent layout) |
| Convenient for flags and hardware registers | No address-of operator |
| Readable compared with manual bit masking | Slower access (extra shifting/masking) |

---

## 11. Enumerated Data Types (`enum`)

### 11.1 Definition

An **enumeration** is a user-defined data type that consists of a set of **named integer constants**. It makes programs more readable by replacing "magic numbers" with meaningful names.

### 11.2 Syntax

```c
enum enum_name { constant1, constant2, ..., constantN };
```

**Example:**

```c
enum day { SUN, MON, TUE, WED, THU, FRI, SAT };
```

By default, the first constant has value **0**, and each next constant is **one more** than the previous one:

| Name | SUN | MON | TUE | WED | THU | FRI | SAT |
|---|---|---|---|---|---|---|---|
| Value | 0 | 1 | 2 | 3 | 4 | 5 | 6 |

### 11.3 Declaring Enum Variables

```c
enum day today;            // variable of enum type
today = WED;
printf("%d", today);       // 3
```

Or together with the declaration:

```c
enum color { RED, GREEN, BLUE } c1, c2;
```

### 11.4 Assigning Custom Values

```c
enum month { JAN = 1, FEB, MAR, APR };      // 1, 2, 3, 4
enum status { OK = 200, NOT_FOUND = 404, ERROR = 500 };
enum level { LOW = 5, MEDIUM, HIGH = 20, CRITICAL };   // 5, 6, 20, 21
```

If a value is given explicitly, the following constants continue counting from it (unless they are assigned too). Two constants may have the same value.

### 11.5 Complete Example

```c
#include <stdio.h>

enum weekday { MON = 1, TUE, WED, THU, FRI, SAT, SUN };

int main() {
    enum weekday d;

    for (d = MON; d <= SUN; d++)
        printf("Day %d\n", d);

    d = WED;
    switch (d) {
        case SAT:
        case SUN:
            printf("Weekend\n");
            break;
        default:
            printf("Weekday\n");
    }
    return 0;
}
```

### 11.6 Using `typedef` with `enum`

```c
typedef enum { FALSE, TRUE } Bool;

Bool flag = TRUE;
```

### 11.7 Important Points

1. Enum constants are of type **`int`**, and a variable of enum type is stored as an integer (typically 4 bytes).
2. Enum constants are **compile-time constants** and cannot be changed at runtime.
3. Names must be **unique** within the same scope.
4. Enum constants have **no separate memory** and you cannot take their address.
5. In C, any integer value can be assigned to an enum variable without a compile error (C does not enforce strict type checking); C++ is stricter.
6. Enum values can be used in `switch` statements, loops, and comparisons.

### 11.8 Advantages

- Improves readability and self-documentation
- Easier to maintain (change a value in one place)
- Automatically numbers constants
- Safer than scattered `#define` constants (scoped and debuggable)

### 11.9 `enum` vs `#define`

| Feature | `enum` | `#define` |
|---|---|---|
| Processed by | Compiler | Preprocessor |
| Auto-numbering | Yes | No |
| Scope rules | Follows block scope | No scope (textual replacement) |
| Debugger visibility | Visible | Not visible |
| Type | `int` | No type |

---

## 12. Quick Revision Tables

### 12.1 Operators for Structures

| Operator | Use | Example |
|---|---|---|
| `.` (dot) | Access member through variable | `s1.marks` |
| `->` (arrow) | Access member through pointer | `ptr->marks` |

### 12.2 `struct` vs `union` vs `enum`

| | `struct` | `union` | `enum` |
|---|---|---|---|
| Purpose | Group different data | Share memory between members | Named integer constants |
| Memory | Sum of members | Largest member | Size of `int` |
| Members | All active | One active | Constants only |

### 12.3 Common Mistakes

1. Forgetting the **semicolon** after the closing brace of a structure or union.
2. Using `s.name = "Amit";` instead of `strcpy(s.name, "Amit");`.
3. Comparing structures with `==`.
4. Using `.` with a pointer (use `->`).
5. Expecting a union to hold several values at once.
6. Taking the address of a `register` variable or of a bit-field.
7. Forgetting `&` in `scanf` for numeric members (but not for character arrays).

---

## 13. Important Exam Questions

**Short Questions**

1. Define a storage class. List the four storage classes in C.
2. What is the default storage class for local variables?
3. Why can't the address of a `register` variable be taken?
4. What is a structure? How does it differ from an array?
5. State any four advantages of structures.
6. Differentiate between `.` and `->` operators.
7. What is a self-referential structure?
8. Define union. How is its size calculated?
9. What is a bit-field? Write its syntax.
10. What is an enumerated data type? What is the default value of its first constant?

**Long Questions**

1. Explain all storage classes in C with suitable examples and a comparison table.
2. Explain how a structure is declared, defined, initialised and accessed. Give a program.
3. What is a nested structure? Write a program that uses a nested structure `employee` containing `date of joining`.
4. Write a program to read and display the details of *n* students using an array of structures and find the student with the highest marks.
5. Explain the different ways of passing structures to functions, with examples.
6. Differentiate between structure and union with examples.
7. Explain bit-fields with an example. State their restrictions.
8. Explain `enum` with an example. Compare it with `#define`.

**Output-Based Questions**

```c
// Q1
#include <stdio.h>
void f() {
    static int x = 5;
    x++;
    printf("%d ", x);
}
int main() { f(); f(); f(); return 0; }
// Output: 6 7 8
```

```c
// Q2
union u { int i; char c; };
union u v;
v.i = 65;
printf("%c", v.c);
// Output: A   (on a little-endian machine)
```

```c
// Q3
enum e { A, B = 5, C, D };
printf("%d %d %d", A, C, D);
// Output: 0 6 7
```

---

*End of notes. Practise by writing and running each program yourself.*