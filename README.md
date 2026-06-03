# Bezier Curve Manipulation Tool
_description_


https://github.com/user-attachments/assets/365cf60c-2043-41d4-b32d-57d344db8f65

## Running the Program
To run the program, a few libraries need to be installed:\
&emsp;1. A C++ compiler (g++ in this case)\
&emsp;2. OpenGL\
&emsp;3. FreeGLUT\
&emsp;4. GLFW\
\
With these installed, enter in the terminal:
- `g++ bezierCurve.cpp -o bez -lglfw3 -lfreeglut -lopengl32`
	- *Compiles the code*
 	- If you're still getting errors, try swapping:
  		- `-lglfw3` -> `-lglfw`
  		- `-lopengl32` -> `-lOpenGL`
- `./bez 1000 1000`
	- *Run the program*
	- the parameters can be replaced to adjust the width and height of the window (1000x1000 in this case)
\
## Using the Program
- Click anywhere on the screen (where there isn't a node directly there) to place a new anchor point.
- Clicking and holding on a point will let you adjust it's position.
- Tangent points will be created from newly placed anchor points, which can also be moved around.
- Pressing E will reset the entire board.


\ ( ^-^ ) /


## Description
This was created for my Intro Computer Graphics course in C++ and GLFW. The program allows the user to create continuous bezier curves. Due to it being for a school assignment, it is not the most refined. but works well to just show off the mathematics.

## Running the Program
If you are looking to run it, there is a fair bit that needs to be installed in order to run it; including OpenGL, GLFW, and a Linux platform (or something like Ubuntu to simulate it). You can type in:
You can type in:
	g++ bezierCurve.cpp -o bez -lOpenGL -lglfw
	./bez 800 800
		The parameters can be replaced with what you wish to be the width and height of the window

## Using the Program
- Can place new points down where you aren't clicking right on a new node
- When new points are placed down, the point closest to the old point will align with the other old point's closest control point
- Can move around points, and the control points associated with them will move with them with the same offset
- Can move control points:
	- if a control point is associated with a start or end point, it will not move another control point with it
	- if a control point is an inner control point, then it will form a line with its point and the corresponding control point
		-  this is signified by the green line
- moving control points will alter the bezier curve with it
- the entire structure remains a continuous bezier curve
- Pressing E will delete all the currently placed points; essentially a reset.
