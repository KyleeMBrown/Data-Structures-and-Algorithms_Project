# CS-300 - Data Structures and Algorithms

### What was the problem you were solving in the projects for this course?

The problem I was aiming to solve was which data structure, out of a vector, a HashMap, and a Binary Search Tree, would properly and efficiently store and manipulate ABCU’s course data. For this specific project, I needed a data structure that would allow me to store the data, display the data in alphanumeric order, and search for a specific item in the data to display.

### How did you approach the problem? Consider why data structures are important to understand.

When approaching the problem, I began by researching data structures and analyzing algorithms and their runtimes. From this research, I learned that each data structure has its own strengths and weaknesses, and one doesn’t necessarily perform better than the other. This helped me conclude that a HashMap was not the right choice because of its unordered nature. Printing a HashMap in order would require more computations, putting a load on the runtime and memory. A vector could have fulfilled ABCUs requirements, but displaying the data in order would require a sorting algorithm, likely a merge sort for its efficiency, to be performed on the data prior.This leaves the Binary search tree, which holds data that is naturally ordered alphanumerically; therefore, no sorting method is required before printing or traversing the tree, which is why I chose this as the optimal data structure for the project. 

### How did you overcome any roadblocks you encountered while going through the activities or project?

To overcome roadblocks throughout activities and projects, I watched some of the videos that were linked in the supporting material. I found that the more ways I was able to see each data structure applied to real data, the more I would understand it. I would make sure to refer to the pseudocode examples in the Zybooks notes that helped describe and break down the different implementations of each data structure. This helped not only develop my own pseudocode for the projects but also implement the program in the

### How has your work on this project expanded your approach to designing software and developing programs?

This project has made me realize how these core data structures have been abstracted and used in popular programming languages today, like Python. This project also helped me understand command-line programs and how to take command-line arguments as input and use them in my program. This project has taught me how to transition my pseudocode into a full working program.The pseudocode helped get my ideas down and organized, which made implementing and even working through bugs smoother and quicker. Lastly, I learned that other factors contribute to the runtimes of algorithms, like CPU performance and hardware age, and programmers should be aware of this as well.

### How has your work on this project evolved the way you write programs that are maintainable, readable, and adaptable?

From now on, when developing a program, I will always consider the different types of data structures that could be implemented and how they could make the program more efficient. I will also make sure to utilize Big-O notation to analyze and compare an algorithm's runtime, memory, and overall efficiency. I am also now aware of the importance of parsing file data before storing it in a data structure, which ensures the data is clean for analysis. Software is always built to scale, so knowing how each data structure can progressively handle extensive amounts of data is crucial. 

