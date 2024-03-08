#include <GLFW/glfw3.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <math.h>

using namespace std;

void initialize(int w, int h) {
    glClearColor(1.0,1.0,1.0,1.0); // white background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,w,h,0,-1,1);
    glViewport(0,0,w,h);
    glMatrixMode(GL_MODELVIEW);
}


void drawCircle(float cx, float cy) {
    int numOfSegments = 10, r = 5;
    glBegin(GL_TRIANGLE_FAN); // allows for circle-like shape
    glColor3f(0.0, 0.0, 0.0);
    glVertex2f(cx, cy); // circle centre
    for (int i = 0; i <= numOfSegments; i++) {
        float theta = 2.0f * M_PI * static_cast<float>(i) / numOfSegments; // angle for each segment
        float x = r * cosf(theta), y = r * sinf(theta); // Compute y component
        glVertex2f(cx + x, cy + y); // Output vertex
    }
    glEnd();
}


void drawSquare(float sx, float sy) {
    float len = 10;
    glBegin(GL_QUADS);
        glColor3f(0.0, 0.0, 255.0);
        glVertex2f(sx - (len/2), sy - (len/2));
        glVertex2f(sx + (len/2), sy - (len/2));
        glVertex2f(sx + (len/2), sy + (len/2));
        glVertex2f(sx - (len/2), sy + (len/2));
    glEnd();
}


void drawDottedLine(float ax, float ay, float bx, float by) {
    glPushAttrib(GL_ENABLE_BIT); 
    glLineStipple(1, 0xAAAA);
    glEnable(GL_LINE_STIPPLE);
    glBegin(GL_LINES);
    glColor3f(0.0,0.9,0.0);
        glVertex2f(ax, ay);
        glVertex2f(bx, by);
    glEnd();

    glPopAttrib();
}


bool closeEnough(float mouseX, float mouseY, float pointX, float pointY) {
    return (fabs(mouseX - pointX) <= 5) && (fabs(mouseY - pointY) <= 5);
}


int main(int argc, char *argv[])
{
    int width, height;
    if (argc < 3) {
        cout << "Please include 2 parameters: screen width and height" << endl;
        return 1;
    } else {
        width = atoi(argv[1]);
        height = atoi(argv[2]);
    }

    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    
    void glfwGetCursorPos(GLFWwindow* window, double *xpos, double* ypos);

    window = glfwCreateWindow(width, height, "Bezier Curve Tool", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }


    // Make the window's context current
    glfwMakeContextCurrent(window);

    initialize(width,height);

    vector<vector<float>> points;
    vector<vector<vector<float>>> controlPoints;
    bool leftClickPressed= false;
    bool eWasOn = false;
    double mouseX, mouseY;


    // vector<float> p1 = {0.0, 0.0};
    // vector<float> p2 = {100.0, 200.0};
    // vector<float> p3 = {200.0, 100.0};
    // vector<float> p4 = {300.0, 0.0};


    int draggingIndex = -1, ctrlDraggingIndex = -1, ctrlXorY;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Poll for and process events */
        glfwPollEvents();

        int leftClickState = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
        if (leftClickState == GLFW_PRESS && leftClickPressed) { // left click is being held
            if (draggingIndex > -1) {
                vector<vector<int>> ctrls;

                // push vector<float> with index[0][1]

                int largestIndex = points.size()-1;
                if (draggingIndex == 0) { // first main point
                    if (controlPoints.size() > 0) {
                        vector<int> c = {0,0}; // control point [0][0]
                        ctrls.push_back(c);
                    }
                } else if (draggingIndex == largestIndex) { // last main point
                    vector<int> c = {largestIndex-1,1}; // control point [points.size()-2][1] = end point
                    ctrls.push_back(c);
                } else { // middle main point'
                    vector<int> c = {draggingIndex-1,1}; // control point [0][0]
                    ctrls.push_back(c);
                    c = {draggingIndex, 0};
                    ctrls.push_back(c);
                }

                glfwGetCursorPos(window, &mouseX, &mouseY);

                for (int i = 0; i < ctrls.size(); i++) {
                    float dx = points[draggingIndex][0] - controlPoints[ctrls[i][0]][ctrls[i][1]][0];
                    float dy = points[draggingIndex][1] - controlPoints[ctrls[i][0]][ctrls[i][1]][1];

                    controlPoints[ctrls[i][0]][ctrls[i][1]][0] = mouseX - dx;
                    controlPoints[ctrls[i][0]][ctrls[i][1]][1] = mouseY - dy;
                }

                points[draggingIndex][0] = mouseX; 
                points[draggingIndex][1] = mouseY;
            }

            else if (ctrlDraggingIndex > -1) {
                glfwGetCursorPos(window, &mouseX, &mouseY);
                
                if ( !(ctrlDraggingIndex == 0 && ctrlXorY == 0) && !(ctrlDraggingIndex == (controlPoints.size()-1) && ctrlXorY == 1) ) {
                    if (ctrlXorY == 0) { // 1st cntrl point. dragging ctrl index = parent index
                        // cout << "moving 1st" << endl;

                        float dx = controlPoints[ctrlDraggingIndex][ctrlXorY][0] - points[ctrlDraggingIndex][0];
                        float dy = controlPoints[ctrlDraggingIndex][ctrlXorY][1] - points[ctrlDraggingIndex][1];
                        
                        // dragging index -1, 1

                        controlPoints[ctrlDraggingIndex-1][1][0] = points[ctrlDraggingIndex][0] - dx;
                        controlPoints[ctrlDraggingIndex-1][1][1] = points[ctrlDraggingIndex][1] - dy;
                        
                    } else { // 2nd
                        // cout << "moving 2nd" << endl;

                        float dx = controlPoints[ctrlDraggingIndex][ctrlXorY][0] - points[ctrlDraggingIndex+1][0];
                        float dy = controlPoints[ctrlDraggingIndex][ctrlXorY][1] - points[ctrlDraggingIndex+1][1];
                        
                        // dragging index -1, 1

                        controlPoints[ctrlDraggingIndex+1][0][0] = points[ctrlDraggingIndex+1][0] - dx;
                        controlPoints[ctrlDraggingIndex+1][0][1] = points[ctrlDraggingIndex+1][1] - dy;

                    }

                }


                controlPoints[ctrlDraggingIndex][ctrlXorY][0] = mouseX;
                controlPoints[ctrlDraggingIndex][ctrlXorY][1] = mouseY;

            } // I think the X or Y thing is weather it is the near or far one


        }
        else if (leftClickState == GLFW_PRESS && !leftClickPressed) { // first frame left click is pressed
            
            leftClickPressed = true;

            glfwGetCursorPos(window, &mouseX, &mouseY);
            

            for(int i = 0; i < points.size(); i++) {
                if (closeEnough(mouseX, mouseY, points[i][0], points[i][1])) {
                    draggingIndex = i;
                    break;
                }
            }


            if (draggingIndex == -1) {
                for (int j = 0; j < controlPoints.size(); j++) {
                    if (closeEnough(mouseX, mouseY, controlPoints[j][0][0], controlPoints[j][0][1])) {
                        ctrlDraggingIndex = j;
                        ctrlXorY = 0;
                        break;
                    } else if (closeEnough(mouseX, mouseY, controlPoints[j][1][0], controlPoints[j][1][1])) {
                        ctrlDraggingIndex = j;
                        ctrlXorY = 1;
                        break;
                    }
                }

                if (ctrlDraggingIndex == -1) { // new point will be added

                    int prevIndex = points.size() - 1;

                    // add point
                    vector<float> newPoint = {static_cast<float>(mouseX), static_cast<float>(mouseY)};
                    points.push_back(newPoint);

                    if (prevIndex >= 0) {
                        vector<float> v = {newPoint[0] - points[prevIndex][0], newPoint[1] - points[prevIndex][1]};

                        vector<float> cp1;

                        if (!(prevIndex == 0)) {


                            float dx = controlPoints[points.size()-3][1][0] - points[prevIndex][0];
                            float dy = controlPoints[points.size()-3][1][1] - points[prevIndex][1];

                            cp1 = {points[prevIndex][0] - dx, points[prevIndex][1] - dy}; // should mirror previous

                        } else {
                            cp1 = {points[prevIndex][0] + v[0]/3, points[prevIndex][1] + v[1]/3};
                        }

                        vector<float> cp2 = {points[prevIndex][0] + 2*v[0]/3, points[prevIndex][1] + 2*v[1]/3};

                        vector<vector<float>> cpGroup = {cp1, cp2};

                        controlPoints.push_back(cpGroup);
                    }

                }

            }
        }
        else if (leftClickState == GLFW_RELEASE && leftClickPressed) { // first frame where left click is released
            leftClickPressed = false;
            draggingIndex = -1; 
            ctrlDraggingIndex = -1; 
        }
        else {
            // left click hasn't been and isn't being pressed

            if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS && !eWasOn) {
                points.resize(0);
                controlPoints.resize(0);

                eWasOn = true;
            } else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_RELEASE && eWasOn) {
                eWasOn = false;
            }
        }



		/* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        // Bezier curves
        glBegin(GL_LINE_STRIP);

            glColor3f(0.0,0.0,0.0);

            vector<float> p1, p2, p3, p4;
            int test = points.size() - 1;
            for (int x = 0; x < test; x++) {
                p1 = points[x];
                p2 = controlPoints[x][0];
                p3 = controlPoints[x][1];
                p4 = points[x+1];
                for (int i = 0; i <= 200; i++) {
                    float t = (float)i / 200;
                    float tCmpl = 1-t;

                    float s1 = 0.0, s2 = 0.0;
                    s1 += tCmpl * tCmpl * tCmpl * p1[0]; // (1/t)^3 * p1.x
                    s1 += 3 * tCmpl * tCmpl * t * p2[0]; // 3 * (1/t)^2 * t * p2.x
                    s1 += 3 * tCmpl * t * t * p3[0]; // 3 * (1/t) * t^2 * p3.x
                    s1 += t * t * t * p4[0]; // t^3 * p4.x

                    s2 += tCmpl * tCmpl * tCmpl * p1[1]; // (1/t)^3 * p1.y
                    s2 += 3 * tCmpl * tCmpl * t * p2[1]; // 3 * (1/t)^2 * t * p2.y
                    s2 += 3 * tCmpl * t * t * p3[1]; // 3 * (1/t) * t^2 * p3.y
                    s2 += t * t * t * p4[1]; // t^3 * p4.y

                    glVertex2f(s1, s2);

                }
            }


        glEnd();

        // Point Squares
        for (int i = 0; i < points.size(); i++) {
            drawSquare(points[i][0],points[i][1]);
        } 

        // Control Point Circles
        for (int i = 0; i < controlPoints.size(); i++) {
            drawCircle(controlPoints[i][0][0],controlPoints[i][0][1]);
            drawCircle(controlPoints[i][1][0],controlPoints[i][1][1]);
        } 

        // Dotted lines
        for (int i = 0; i < (int)(points.size()-2); i++) {
            drawDottedLine(controlPoints[i][1][0], controlPoints[i][1][1], controlPoints[i+1][0][0], controlPoints[i+1][0][1]);
        } 


		/* Swap front and back buffers */
        glfwSwapBuffers(window);

    }



    glfwTerminate();
    return 0;
}