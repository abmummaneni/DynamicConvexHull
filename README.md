The core files in this program are:

- `ConcatenableQueue.cpp` and `ConcatenableQueue.h` 
- `TTree.cpp` and `TTree.h`
- `Point.cpp` and `Point.h` 
- `Angle.cpp` and `Angle.h`

The files `VisUtils.cpp` and `VisUtils.h` are used for visualization and are not necessary for the program to run should you decide to make your own driver file.
Similarly, `VisTTree.cpp` and `VisTTree.h` are a visualization of the TTree class and are not necessary for the program to run.

These files provide the functionality of the Dynamic Convex Hull program.
The driver files are:
- `minimalLeda.cpp`
- `mediumLeda.cpp`
- `timer.cpp`
- `randMatplot++.cpp`
- `HullGraph.cpp`


The first two drivers require Leda and are interactive programs where the user can add and remove points using left and right 
clicks. The second driver shows the process of the hulls being broken up and recombined.

The third driver inserts 2^18 points and times the programs execution time for each power of 2 insert.
It prints pairs of the form (log^2(n), time) to stdout. 
These can then be copy and pasted into Desmos which shows the linear relationship as expected.

The fourth driver uses the Matplot++ to randomly insert and delete points. I was using this before I had set up Leda, eventually I will convert this to use Leda as well.

The last driver draws the lower hull graph of a randomly generated point set.
## How to run the program
A makefile is provided which can compile the following executables:
- `minimalLeda`
- `mediumLeda`
- `timer`
- `HullGraph`

To compile any one of these, simply run `make <executable name>` while in the directory containing the files.

If you have Matplot++ installed you can compile `randMatplot++` with the included CMakeLists.txt file.

## How to use the program
`minimalLeda` and `mediumLeda` will open a window where you can add and remove points using left and right clicks.
If it is difficult to remove points, you can increase the variable "tolerance" defined at the top of the driver file.
Note that the visualizations increase the asymptotic complexity of the algorithm, 
however for practical use this will be unnoticeable.

`timer` will simply print out the pairs of the form (log^2(n), time) to stdout.

`randMatplot++` will open a window where you can watch the points being randomly added and removed.

`HullGraph` will open a window where you can watch the lower hull graph being constructed one layer at a time.
## What I learned
I will include speak about this in my presentation, but here are some of the things I learned from this project:
- The importance of dynamic data structures and the applications of dynamic algorithms to the real world.
- The importance of data structure selection and the absolute reliance of algorithmic efficiency on data structure choice
- How to conceptualize the interactions of multiple data structures
- How to read a paper with the intent of implementing the algorithm
- How to use Leda, Matplot++ and the importance of visualization