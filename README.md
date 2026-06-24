# CS-300-DataStruct
CourseWork for ABCU Advising
This repository contains the software that was implemented as well as my analysis for ABC university Advising Sys.
<br>
**Course Reflection**


1. ***What was the problem you were solving in the projects for this course?***
     The main problem I was solving was how to organize and manage course info for the academic advisors at the university. The developed program needs to read course data from a csv file, store it in the most efficient data structure, and allow the advisors to quickly find info about individual courses as well as their prerequisites. It also needs to print the entire course catalog in a alphanumeric order so the advisors could easily review the course curriculum with their respective students.
   
***How did you approach the problem? Consider why data structures are important to understand.***
     I approached the problem by comparing different data structures and looking at how each one handled the searching, sorting, and storing of the data. Throughout the course, I worked with vectors, binary search trees, and hash tables. I compared and contrasted the strengths and weaknesses of each one to aid my decision. Understanding data structures is important because the structure someone chooses will directly affect how efficient a program will be. A solution might work as intended, but if the wrong structure is used, performance can suffer as the amount of data gets greater and greater. After finishing the analysis, I chose a binary search tree (BST) because it provided a good balance between search performance and maintaining course data in sorted order.

***How did you overcome any roadblocks you encountered while going through the activities or project?***
     One of the biggest challenges I ran into was reading and parsing the course data file correctly. Since each row could contain a different number of prerequisites, I had to make sure the program could handle multiple formats while still validating the data. I also spent time troubleshooting the pointer logic while building the BST. I worked through these issues by breaking the program into smaller functions, testing one section at a time, and using some debugging tools to follow the programs flow and verify that nodes were being inserted correctly. I also created a .csv file and input it into the project file and used that to my benefit in making sure the program ran as I expected it to.

***How has your work on this project expanded your approach to designing software and developing programs?***
     This project changed the way I think about software design. Before this course, I mainly focused on getting a program to just work correctly, no matter the cost. Now I am spending more time thinking about efficiency and the scalability before I start writing code. Learning how different data structures impact the performance helped me understand why planning is important during the design phase as opposed to trying to solve performance related issues after the app / program is already built.


***How has your work on this project evolved the way you write programs that are maintainable, readable, and adaptable?***
     This project has helped me become more comfortable and organized when writing code. Instead of placing everything inside the main function, I now feel good enough to separate tasks into smaller functions that each have a specific purpose. Functions like loading data, searching for courses, and printing course information are all handled independently. This makes the code easier to read, debug, and test. This approach also makes future updates easier because individual parts of the program can be modified without affecting the rest of the application. 
