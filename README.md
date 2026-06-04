# Bezier Curve Manipulation Tool
This tool allows users to create a large Bezier curve. Users can place and move the curve's anchor points, as well as adjust the tangent handles between anchor points to further refine its shape.
The program is written in C++ and uses OpenGL along with the GLEW and GLFW libraries. This assignment provided an opportunity to practice real-time matrix and curve calculations based on user input while applying fundamental computer graphics concepts covered in my undergraduate degree.

https://github.com/user-attachments/assets/365cf60c-2043-41d4-b32d-57d344db8f65

## Using the Program
- Click anywhere on the screen (provided there is not already a point or handle at that location) to place a new anchor point.
- Click and hold an anchor point to adjust its position.
- Tangent handles are automatically created for newly placed anchor points and can also be moved to refine the shape.
- Press `E` to reset the entire curve.

## Running the Program
To run the program, a few libraries need to be installed:\
&emsp;1. A C++ compiler (g++ in this case)\
&emsp;2. OpenGL\
&emsp;3. FreeGLUT\
&emsp;4. GLFW\
\
With these installed, enter in the terminal:
- *Optional*: `g++ bezierCurve.cpp -o bez -lglfw3 -lfreeglut -lopengl32`
	- *Compiles the program*
 	- If you're still getting errors, try swapping:
  		- `-lglfw3` -> `-lglfw`
  		- `-lopengl32` -> `-lOpenGL`
- `./bez 1000 1000`
	- *Runs the program*
	- The parameters can be replaced to adjust the width and height of the window (1000x1000 in this example).
