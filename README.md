# Bezier Curve Manipulation Tool
The tool allows you to create one large bezier curve. The user can set and move the anchor points of the curve, and can play with the tangent lines between anchor points to further adjust it's shape.\
The program is written in C++, and uses the OpenGL library, and focused on rudimentary and fundamental graphic displaying, allowing me to practice real-time matrix and curve calculations based on user input.

https://github.com/user-attachments/assets/365cf60c-2043-41d4-b32d-57d344db8f65

## Using the Program
- Click anywhere on the screen (where there isn't a node directly there) to place a new anchor point.
- Clicking and holding on an anchor point will let you adjust it's position.
- Tangent points will be created from newly placed anchor points, which can also be moved around.
- Pressing E will reset the entire board.
\

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
