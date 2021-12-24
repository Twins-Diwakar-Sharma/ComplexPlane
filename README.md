# ComplexPlane
Visualize complex transformation

## What is it?
This is a compiler, which compiles equations of complex numbers, and displays the resultant transformation in a 2D grid

## How to use
This program currently works on Linux systems only.
Program will open a seperate 'Complex Plane window' displaying the complex plane.
You will write the equations in console window from where you launched the program, and see the output of equation in the 'Complex Plane window'.\
You need to specify a variable for the grid first. Let it be z, the you can tell the program that you want to write equation using variable z
```
equation z
```
Then you can start writing your equation, make sure to end equation with ! (exclamation mark). Hit enter and see transformation. For example:
```
equation z
   y = 2+3i
   z = y * z
   !
```

## Example
Here is an example equation, and the transformation which you will see
```
 equation z
    z = 1/z
    z = z*10
    !
```

![Complex](https://user-images.githubusercontent.com/47611483/147350158-dece3bba-7af5-49af-9b72-cbf38cb3ba61.gif)
