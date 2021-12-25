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

## Controls
Following keyboard shortcuts works when 'Complex Plane window' is focused
* Restart the animation by pressing r
* Zoom in by pressing z
* Zoom out by pressing shift+z

## Examples
Here are some example equations with their transformations
```
 equation z
    y = (z*z)/100
    z = y*z*y
    !
```
![z5](https://user-images.githubusercontent.com/47611483/147382722-fa7b6a7d-f4bc-4b3e-a6ac-b42bac044592.gif)

```
equation z
   rot45 = 0.7072 + i0.7072
   inv = rot45/z
   z = inv*100
   !
```
![rot45](https://user-images.githubusercontent.com/47611483/147382731-edcd69d9-8fc7-4c7e-b14e-2ce83a773fc3.gif)

