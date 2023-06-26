
# Pthread vs OpenMP

This project was done as part of course **CS-3523** which was organized by **Dr. Sathya Peri** which aims to analyze performance difference between thread libraries **PThread** and **OpenMP** available for **C++**.

## About the project

In this project I have implemented if a sudoku is a valid sudoku or not using **PThread** and **OpenMP** thread libraries. Graphs are plotted on the basis of time of checking of the sudoku vs number of threads used to check the sudoku to visualize the performance difference between **PThread** and **OpenMP**.





## Authors

- [@anudeep512](https://www.github.com/anudeep512)


## Tech Stack

**Command Line:** C++
## Prerequisite

Check if a suitable compiler exists for compiling the C++ code

for g++ compiler:

    g++ --version

for clang compiler:

    clang --version

If there isn't any compiler installed, install it using the documentation for the compiler of C++ based on your OS.

## Install and Usage

### Installing project

Clone from repo:

    git clone https://github.com/anudeep512/PThread-vs-OpenMP/

### Running the Program

After cloning is done redirect control to project folder using:

    cd ./PThread-vs-OpenMP

For compiling the PThread file run:

    g++ -std=c++20 -o pthread.out  PThread.cpp -lpthread

For executing the program:

    ./pthread.out	

For compiling the OpenMP file run:

    g++ -std=c++20 -o openmp.out  OpenMP.cpp -lpthread

For executing the program:

    ./openmp.out	

**Note:** Before executing the programs please check if you have setted up the **input.txt** file.

### Input to the Program

Input to the program is read from the file **input.txt**. The **input.txt** is generated using the python file **sudoku.py**.

Run the python file by:

    python3 sudoku.py N

**N:** Size of the sudoku i.e., in the **input.txt** file we get a valid sudoku of size N*N.

**Note:** The python script **sudoku.py** always generates a valid N*N sudoku.

### Output of the Programs

Logs and time of execution of the program for check of sudoku for **OpenMP.cpp** is printed to the file **output_openMP.txt**.

Logs and time of execution of the program for check of sudoku for **PThread.cpp** is printed to the file **output_pthread.txt**.


## Documentation

The explanation and report for the whole project can be found in **report.pdf**