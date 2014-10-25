Slither
=======
To execute the program:

1. Navigate to directory containing program files
2. Execute make
3. Run ./main
4. Input PracBoard.txt (or any other data files in the format explained below)
5. Run make clean


Data File Format:

The file should contain the data listed within the lines below (do not type out those lines with hypens)
--------
m x n 
Squares:
(a, b, c)
...
---------

m - width
n - height
a - square row
b - square column
c - square value

... means as many squares as you need (just don't make a square with coordinates greater than the board size or less than 0)

PracBoard.txt provides the example 2 x 2 board specified in the project handout