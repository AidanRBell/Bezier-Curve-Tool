# Bezier Curve Tool

## Description
This was created for my Intro Computer Graphics course using C++ and GLFW. The program allows the user to create continuous bezier curves. Due to it being for a school assignment, it is not the most refined. but works well to just show off the mathematics.

## Demonstration Video

Please view "Demonstration_Video.mp4" to view a demonstration of the program. I recommend this as it is much easier than setting up the software to run the actual program.

## Running the program
If you are looking to run it, there is a fair bit that needs to be installed in order to run it; including OpenGL, GLFW, and a Linux platform (or something like Ubuntu to simulate it). You can type in:
You can type in:
	g++ bezierCurve.cpp -o bez -lOpenGL -lglfw
	./bez 800 800
		The parameters can be replaced with what you wish to be the width and height of the window

## Using the program
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
