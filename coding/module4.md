## A. Introduction to Structures & Advantages (5 Questions)

1. Write a C program to create a structure named Student containing student ID, name, and age. Input and display the details of a student.

2. Write a C program to create a structure named Employee containing employee ID, name, and salary. Accept and display employee details.

3. Write a C program to create a structure named Book containing book ID, book name, author name, and price. Display all book details.

4. Write a C program to create a structure named Rectangle containing length and breadth. Calculate and display its area and perimeter.

5. Write a C program to create a structure named Complex containing real and imaginary parts. Perform addition of two complex numbers.

## B. Accessing Elements of a Structure (5 Questions)

6. Write a C program to create a structure named Student containing roll number, name, and marks in three subjects. Calculate and display the total and average marks.

7. Write a C program to create a structure named Employee containing employee ID, name, and salary. Calculate the annual salary of the employee.

8. Write a C program to create a structure named Product containing product ID, name, price, and quantity. Calculate and display the total bill.

9. Write a C program to create a structure named Date containing day, month, and year. Input and display the date in DD/MM/YYYY format.

10. Write a C program to create a structure named Student containing roll number, name, and marks. Compare the marks of two students and display the student who scored higher marks.

## C. Nested Structures & Array of Structures (5 Questions)

11. Write a C program to create a nested structure named Student containing roll number, name, and address. The address structure should contain city, state, and PIN code. Input and display student details.

12. Write a C program to create a structure named Employee containing employee ID, name, and date of joining. Use a nested structure for the date of joining.

13. Write a C program to create an array of structures to store details of 5 students, including roll number, name, and marks. Display the details of all students.

14. Write a C program to store details of 5 employees using an array of structures. Find and display the employee who receives the highest salary.

15. Write a C program to store details of n students using an array of structures. Calculate the average marks and display all students who scored above the average.

## D. Functions and Structures (5 Questions)

16. Write a C program to pass a structure containing student details to a function and display the student information using that function.

17. Write a C program to create a structure named Rectangle and pass it to a function to calculate and return its area.

18. Write a C program to pass two structure variables containing complex numbers to a function and perform their addition.

19. Write a C program to create a structure named Employee and pass its address to a function. Update the employee's salary by increasing it by 10%.

20. Write a C program to create a structure named Student containing roll number, name, and marks. Pass an array of structures to a function and display the details of all students who scored more than 60 marks.


## A. Introduction to Structures & Accessing Elements (1–3)

1. Student Details: Write a C program to create a structure named Student containing student ID, name, age, and marks. Accept details of one student and display all information.

2. Employee Salary: Write a C program to create a structure named Employee containing employee ID, name, and salary. Accept employee details and calculate and display the annual salary.

3. Book Information: Write a C program to create a structure named Book containing book ID, title, author name, and price. Accept and display the book details. Also, display the book price after applying a 10% discount.

## B. Nested Structures & Array of Structures (4–7)

4. Student Address: Write a C program to create two structures, Address and Student. The Address structure should contain city, state, and pincode. The Student structure should contain student ID, name, and an Address structure. Accept and display student details along with the address.

5. Multiple Students: Write a C program to create a structure named Student containing roll number, name, and marks. Use an array of structures to accept and display details of 5 students.

6. Employee Management: Write a C program to create a structure named Employee containing employee ID, name, and salary. Accept details of 5 employees using an array of structures and display the employee who receives the highest salary.

7. Student Result: Write a C program to create a structure named Student containing roll number, name, and marks in three subjects. Accept details of 5 students and calculate and display the total marks and percentage of each student.

## C. Functions and Structures (8–10)

8. Passing Structure to Function: Write a C program to create a structure named Student containing roll number, name, and marks. Create a function displayStudent() that accepts a structure variable as an argument and displays the student details.

9. Returning Structure from Function: Write a C program to create a structure named Employee containing employee ID, name, and salary. Create a function getEmployee() that accepts employee details from the user and returns the structure variable. Display the returned employee details in main().

10. Structure with Array and Function: Write a C program to create a structure named Student containing roll number, name, and marks. Accept details of 5 students using an array of structures. Create separate functions to:
- Accept student details.
- Display all student details.
- Find and display the student who scored the highest marks.

### ############ Unions

1. Student Details: Write a C program to create a union named Student containing student ID, name, and marks. Accept and display each member separately. Observe how assigning a value to one member affects the other members.

2. Employee Information: Write a C program to create a union named Employee containing employee ID, employee name, and salary. Accept and display employee details one member at a time.

3. Book Information: Write a C program to create a union named Book containing book ID, book price, and book rating. Accept a value for each member separately and display the assigned value.

4. Union vs Structure: Write a C program to create both a union and a struct named Data, containing an integer, a float, and a character. Display the size of both using the sizeof() operator and compare their memory usage.

5. Union with Array: Write a C program to create a union named Data containing an integer, a float, and a character array of 20 characters. Accept and display each member separately. Also, display the total size of the union.