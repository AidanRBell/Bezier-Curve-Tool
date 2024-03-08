# Bezier Curve Tool

## Description

This was created for my intro computer graphics course using C++ and GLFW. The program allows the user to create continuous bezier curves. Due to it being for a school assignment, it is not the most refined. but works well to just show off the mathematics. A video of the application being demonstrated can be found under "Bezier Curve Tool Demonstration.mp4". The source code is included, just being the one file "bezierCurve.cpp", but do note there are many libraries needed to run it, and needs to be ran on a UNIX based operating system or an emulator like Ubuntu.

If you are looking to run it. You can type in:
	g++ bezierCurve.cpp -o bez -lOpenGL -lglfw
	./bez 800 800
		The parameters can be replaced with what you wish to be the the width and height of the window


Here is what the program will do:
	- Can place new points down where you aren't clicking right on a new node
	- When new points are placed down, the point closest to the old point will align with the other old point's closest control point
	- Can move around points, and the control points associated with them will move with them with the same offset
	- Can move control points:
		- if a control point is associated with a start or end point, it will not move another control point with it
		- if a control point is an inner control point, then it will form a line with it's point and the corresponding control point
			-  this is signified by the green line
		- moving control points will alter the bezier curve with it
	- the entire structure remains a continuous bezier curve
	- Pressing E will delete all the currently placed points; essentially a reset.