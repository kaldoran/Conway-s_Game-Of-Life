# Conway-s_Game-Of-Life

Here is the famous game of life with 3 differents method :
- Sequential method
- 2 Thread method :
  - One fined grained for task assignation
  - One medium grained for task assignation

##### Compilation: 
 - make test : 
    * Make the game of life and test the correct execution of the program
 - make test-rand :
    * Make the game of life and test it 10 time by default, using random board, random number of iteration it only compare that all board compute by the different method are the same.
 - make test-rand TOTAL=X :
    * Same as make test-rand but execute X test instead of the default Value.
 - make mesure : 
    * Benchmark that compare all method.
 - make display : 
    * Use it if you want to track a display of the grid.
 - make :
    * Compile the version without display on.
 - make clean :
    * Clean all OBJ file and program.
 - make rebuild : 
    * Rebuild the wall project without display mode.
 - make clear :
    * Clear the consol.
 - make dir : 
    * Creat usefull directory. (Auto done when make)
   
You could also edit the Makefile and change `DEBUG=no` to `DEBUG=yes`
Debug information will be print even if you don't use display version of the program.

##### Usage : 
    See : ./BIN/GameOfLife -h


#### /!\ All script should be launch from . [./Script/file]
### /!\ Please be sure to read the License file, this license apply to all files.
