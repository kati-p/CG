#include <graphics.h>   
#include <conio.h>
#include <cmath>

#define FRAME 1000/24
#define PI 3.14159265

void rotatePoint(int px, int py, int &x, int &y, double angle) {
    float rad = angle * PI / 180;

    int tempX = x - px;
    int tempY = y - py;
    x = px + (int)(tempX * cos(rad) - tempY * sin(rad));
    y = py + (int)(tempX * sin(rad) + tempY * cos(rad));
}

void drawMarkX(int x, int y, int length) {
    int r = (int) length / 2;
    line(x - r, y - r, x + r, y + r);
    line(x + r, y - r, x - r, y + r);
}

// Function to draw a stickman
void drawStickman(int x, int y) {
    setcolor(WHITE);

    // Draw the head
    circle(x, y, 30); // head is a circle with radius 30

    // Draw the body
    line(x, y + 30, x, y + 100); // body is a line from just below the head to the torso length

    // Draw arms
    line(x, y + 50, x - 40, y + 70); // left arm
    line(x, y + 50, x + 40, y + 70); // right arm

    // Draw legs
    line(x, y + 100, x - 40, y + 150); // left leg
    line(x, y + 100, x + 40, y + 150); // right leg
}

void drawStickmanWalking(int x, int y, double angle) {
    setcolor(WHITE);

    // Draw the head
    circle(x, y, 30); // head is a circle with radius 30

    // Draw the body
    line(x, y + 30, x, y + 100); // body is a line from just below the head to the torso length

    // Draw arms
    line(x, y + 50, x - 40, y + 70); // left arm
    line(x, y + 50, x + 40, y + 70); // right arm

    // Draw legs
    int xl1 = x;
    int yl1 = y + 100;
    int xl2 = x - 40;
    int yl2 = y + 150;
    rotatePoint(xl1, yl1, xl1, yl1, -angle);
    rotatePoint(xl1, yl1, xl2, yl2, -angle);
    line(xl1, yl1, xl2, yl2); // left leg

    int xr1 = x;
    int yr1 = y + 100;
    int xr2 = x + 40;
    int yr2 = y + 150;
    rotatePoint(xr1, yr1, xr1, yr1, angle);
    rotatePoint(xr1, yr1, xr2, yr2, angle);
    line(xr1, yr1, xr2, yr2); // right leg
}

// Function to draw a UFO
void drawUFO(int x, int y) {
    // Draw the main body of the UFO
    setcolor(WHITE);
    ellipse(x, y, 0, 360, 100, 40);

    // Draw the dome of the UFO
    setfillstyle(SOLID_FILL, LIGHTGRAY);
    fillellipse(x, y-30, 40, 20);
}

void drawBeam(int x, int y, float scale=1) {
    // Define the points of the polygon
    int points[8];

    points[0] = x;       // Starting x point
    points[1] = y;       // Starting y point
    points[2] = x - 150*scale; // Left endpoint x of the beam
    points[3] = y + 400*scale; // Left endpoint y of the beam
    points[4] = x + 150*scale; // Right endpoint x of the beam
    points[5] = y + 400*scale; // Right endpoint y of the beam
    points[6] = x;       // Close the polygon back at the starting x point
    points[7] = y;       // Close the polygon back at the starting y point

    // Set the color for the beam
    setcolor(YELLOW);
    setfillstyle(SOLID_FILL, YELLOW);

    // Draw the beam sides
    line(x, y, x - 150*scale, y + 400*scale);
    line(x, y, x + 150*scale, y + 400*scale);

    // Fill the beam with color
    fillpoly(4, points); // 4 is the number of points in the polygon
}

// Function to draw a sheared rectangle
void drawShearedRectangle(int x, int y, int width, int height, int shear=0) {
    // Points for the original rectangle
    int left = x;
    int right = x + width;
    int top = y;
    int bottom = y + height;

    // Calculate the sheared coordinates
    int topRightX = right + shear; // Shearing the top-right corner
    int topLeftX = left + shear; // Shearing the top-left corner

    // Set a different color for the sheared rectangle
    line(topLeftX, top, topRightX, top);    // Top edge
    line(left, bottom, right, bottom);  // Bottom edge
    line(topLeftX, top, left, bottom);  // Left edge
    line(topRightX, top, right, bottom); // Right edge (sheared)
}

// Function to draw a sheared and rotated rectangle
void drawShearedRotatedRectangle(int x, int y, int width, int height, int shear=0, double angle=0) {
    // Convert angle from degrees to radians
    double radians = angle * M_PI / 180;

    // Points for the original rectangle
    int left = x;
    int right = x + width;
    int top = y;
    int bottom = y + height;

    // Calculate the sheared coordinates
    int topRightX = right + shear; // Shearing the top-right corner
    int topLeftX = left + shear;  // Shearing the top-left corner

    // Calculate rotated positions for each corner
    // Rotation matrix application [cos θ, -sin θ, sin θ, cos θ]
    int rotatedTopLeftX = (int)(x + (topLeftX - x) * cos(radians) - (top - y) * sin(radians));
    int rotatedTopLeftY = (int)(y + (topLeftX - x) * sin(radians) + (top - y) * cos(radians));

    int rotatedTopRightX = (int)(x + (topRightX - x) * cos(radians) - (top - y) * sin(radians));
    int rotatedTopRightY = (int)(y + (topRightX - x) * sin(radians) + (top - y) * cos(radians));

    int rotatedBottomLeftX = (int)(x + (left - x) * cos(radians) - (bottom - y) * sin(radians));
    int rotatedBottomLeftY = (int)(y + (left - x) * sin(radians) + (bottom - y) * cos(radians));

    int rotatedBottomRightX = (int)(x + (right - x) * cos(radians) - (bottom - y) * sin(radians));
    int rotatedBottomRightY = (int)(y + (right - x) * sin(radians) + (bottom - y) * cos(radians));

    // Draw the sheared and rotated rectangle
    setcolor(WHITE);
    line(rotatedTopLeftX, rotatedTopLeftY, rotatedTopRightX, rotatedTopRightY); // Top edge
    line(rotatedBottomLeftX, rotatedBottomLeftY, rotatedBottomRightX, rotatedBottomRightY); // Bottom edge
    line(rotatedTopLeftX, rotatedTopLeftY, rotatedBottomLeftX, rotatedBottomLeftY); // Left edge
    line(rotatedTopRightX, rotatedTopRightY, rotatedBottomRightX, rotatedBottomRightY); // Right edge (sheared)
}

// Function to draw a sheared and rotated rectangle
void drawWindowWithClipping(int x, int y, int width, int height, int shear=0, double angle=0) {
    // Convert angle from degrees to radians
    double radians = angle * M_PI / 180;

    // Points for the original rectangle
    int left = x;
    int right = x + width;
    int top = y;
    int bottom = y + height;

    // Calculate the sheared coordinates
    int topRightX = right + shear; // Shearing the top-right corner
    int topLeftX = left + shear;  // Shearing the top-left corner

    // Calculate rotated positions for each corner
    // Rotation matrix application [cos θ, -sin θ, sin θ, cos θ]
    int rotatedTopLeftX = (int)(x + (topLeftX - x) * cos(radians) - (top - y) * sin(radians));
    int rotatedTopLeftY = (int)(y + (topLeftX - x) * sin(radians) + (top - y) * cos(radians));

    int rotatedTopRightX = (int)(x + (topRightX - x) * cos(radians) - (top - y) * sin(radians));
    int rotatedTopRightY = (int)(y + (topRightX - x) * sin(radians) + (top - y) * cos(radians));

    int rotatedBottomLeftX = (int)(x + (left - x) * cos(radians) - (bottom - y) * sin(radians));
    int rotatedBottomLeftY = (int)(y + (left - x) * sin(radians) + (bottom - y) * cos(radians));

    int rotatedBottomRightX = (int)(x + (right - x) * cos(radians) - (bottom - y) * sin(radians));
    int rotatedBottomRightY = (int)(y + (right - x) * sin(radians) + (bottom - y) * cos(radians));

    // Draw the sheared and rotated rectangle
    setcolor(WHITE);
    line(rotatedTopLeftX, rotatedTopLeftY, rotatedTopRightX, rotatedTopRightY); // Top edge
    line(rotatedBottomLeftX, rotatedBottomLeftY, rotatedBottomRightX, rotatedBottomRightY); // Bottom edge
    line(rotatedTopLeftX, rotatedTopLeftY, rotatedBottomLeftX, rotatedBottomLeftY); // Left edge
    line(rotatedTopRightX, rotatedTopRightY, rotatedBottomRightX, rotatedBottomRightY); // Right edge (sheared)


    // Do Clipping 90 degree
    if (angle != 90) return;
    // Define the points of the polygon
    int points[8];
    // Set the color for the beam
    setcolor(BLACK);
    setfillstyle(SOLID_FILL, BLACK);

    // clip bottom
    points[0] = rotatedBottomRightX;
    points[1] = rotatedBottomRightY + 1;
    points[2] = rotatedTopRightX;
    points[3] = rotatedTopRightY + 1;
    points[4] = getmaxx()/2;
    points[5] = getmaxy();
    points[6] = 0;      
    points[7] = getmaxy();       
    // Fill the beam with color
    fillpoly(4, points); // 4 is the number of points in the polygon

    // clip right
    points[0] = rotatedTopLeftX + 1;
    points[1] = 0;
    points[2] = getmaxx();
    points[3] = 0;
    points[4] = getmaxx();
    points[5] = getmaxy()/2;
    points[6] = rotatedTopLeftX + 1;      
    points[7] = getmaxy()/2;       
    // Fill the beam with color
    fillpoly(4, points); // 4 is the number of points in the polygon

    // clip left
    points[0] = 0;
    points[1] = 0;
    points[2] = rotatedBottomLeftX - 1;
    points[3] = 0;
    points[4] = rotatedBottomLeftX - 1;
    points[5] = getmaxy();
    points[6] = 0;      
    points[7] = getmaxy();       
    // Fill the beam with color
    fillpoly(4, points); // 4 is the number of points in the polygon

    // clip top
    points[0] = 0;
    points[1] = 0;
    points[2] = getmaxx();
    points[3] = 0;
    points[4] = rotatedTopLeftX;
    points[5] = rotatedTopLeftY - 1;
    points[6] = rotatedBottomLeftX;      
    points[7] = rotatedBottomLeftY -1;       
    // Fill the beam with color
    fillpoly(4, points); // 4 is the number of points in the polygon

    

    
}

void drawTable(int x, int y) {
    setcolor(WHITE);
    drawShearedRectangle(x, y, 500, 50, 50);
    drawShearedRectangle(x, y+50, 500, 50);
}

void drawBook(int x, int y) {
    setcolor(WHITE);
    drawShearedRectangle(x, y, 50, 25, 25);
    drawShearedRectangle(x+50, y, 50, 25, 25);
}

void drawNNMan(int x, int y) {
    setcolor(WHITE);
    circle(x, y, 30); // head is a circle with radius 30
    line(x, y + 30, x, y + 100); // body is a line from just below the head to the torso length
    line(x, y + 50, x - 40, y + 70); // left arm
    line(x, y + 50, x + 40, y + 70); // right arm
    line(x, y + 100, x - 40, y + 150); // left leg
    line(x, y + 100, x + 40, y + 150); // right leg
}

// Function to draw the sun
void drawSun(int x, int y, int radius) {
    int angle, xEnd, yEnd;

    // Draw sun circle
    setcolor(YELLOW);
    setfillstyle(SOLID_FILL, YELLOW);
    fillellipse(x, y, radius, radius);

    // Draw rays
    for(angle = 0; angle < 360; angle += 30) {
        xEnd = x + (int)(radius * 1.5 * cos(angle * M_PI / 180));
        yEnd = y + (int)(radius * 1.5 * sin(angle * M_PI / 180));
        line(x, y, xEnd, yEnd);
    }
}

// Function to draw the crescent moon
void drawMoon(int x, int y, int radius) {
    // Draw full moon in white
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, WHITE);
    fillellipse(x, y, radius, radius);

    // Overlay part of the moon with black to form a crescent
    setcolor(BLACK);
    setfillstyle(SOLID_FILL, BLACK);
    fillellipse(x + radius / 2, y, radius, radius);
}

int interpolate( int from , int to , float percent ) {
    int difference = to - from;
    return from + ( difference * percent );
}

int curve( int a, int b, int c, float percent ) {
    int xa, xb, x;
    xa = interpolate( a , b , percent );
    xb = interpolate( b , c , percent );

    x = interpolate( xa , xb , percent );
    return x;
}

void drawNNsit(int x, int y, int move=0) {
    setcolor(WHITE);

    setfillstyle(SOLID_FILL, WHITE);
    fillellipse(x, y, 70, 70);

    line(x, y + 70, x, y + 200);
    line(x, y + 120, x - 40, y + 150);
    line(x - 40, y + 150, x + move, y + 225);
    line(x, y + 120, x + 40, y + 150);
    line(x + 40, y + 150, x + 50, y+ 225);

    setfillstyle(SOLID_FILL, BLACK);
    fillellipse(x-30, y+25, 21, 21);
    fillellipse(x+25, y+25, 21, 21);

    setcolor(BLACK);
    setfillstyle(SOLID_FILL, WHITE);
    fillellipse(x-30, y+20, 20, 20);
    fillellipse(x+25, y+20, 20, 20);
}

void drawNNpin(int x, int y, float scale=1, char color=WHITE) {
    setcolor(color);

    setfillstyle(SOLID_FILL, color);
    fillellipse(x, y, 50 * scale, 50 * scale);

    line(x, y + 50 * scale, x, y + 175 * scale); //Body

    line(x - 75 * scale, y + 75 * scale, x + 75 * scale, y + 75 * scale); // Arms

    line(x, y + 175 * scale, x - 50 * scale, y + 250 * scale); // Left leg

    line(x, y + 175 * scale, x + 50 * scale, y + 250 * scale); // Right leg

    setfillstyle(SOLID_FILL, BLACK);
    fillellipse(x - 20 * scale, y + 5 * scale, 13 * scale, 13 * scale);
    fillellipse(x + 20 * scale, y + 5 * scale, 13 * scale, 13 * scale);

    setcolor(BLACK);
    setfillstyle(SOLID_FILL, WHITE);
    fillellipse(x - 20 * scale, y, 13 * scale, 13 * scale);
    fillellipse(x + 20 * scale, y, 13 * scale, 13 * scale);

    setcolor(WHITE);
}

void drawNNManDead(int x, int y, int px, int py, double angle, bool isDead, float scale=1, char color=WHITE) {
    setcolor(color);

    setfillstyle(SOLID_FILL, color);

    int xh = x;
    int yh = y;
    rotatePoint(px, py, xh, yh, angle);
    fillellipse(xh, yh, 50 * scale, 50 * scale); // Head
    
    int xb1 = x;
    int yb1 = y + 50 * scale;
    int xb2 = x;
    int yb2 = y + 175 * scale;
    rotatePoint(px, py, xb1, yb1, angle);
    rotatePoint(px, py, xb2, yb2, angle);
    line(xb1, yb1, xb2, yb2); //Body

    int xa1 = x - 75 * scale;
    int ya1 = y + 75 * scale;
    int xa2 = x + 75 * scale;
    int ya2 = y + 75 * scale;
    rotatePoint(px, py, xa1, ya1, angle);
    rotatePoint(px, py, xa2, ya2, angle);
    line(xa1, ya1 , xa2 , ya2); // Arms

    int xl1 = x;
    int yl1 = y + 175 * scale;
    int xl2 = x - 50 * scale;
    int yl2 = y + 250 * scale;
    rotatePoint(px, py, xl1, yl1, angle);
    rotatePoint(px, py, xl2, yl2, angle);
    line(xl1, yl1, xl2, yl2); // Left leg

    int xr1 = x;
    int yr1 = y + 175 * scale;
    int xr2 = x + 50 * scale;
    int yr2 = y + 250 * scale;
    rotatePoint(px, py, xr1, yr1, angle);
    rotatePoint(px, py, xr2, yr2, angle);
    line(xr1, yr1, xr2, yr2); // Right leg

    // eyes
    if (isDead) {
        int xel = x - 20 * scale;
        int yel = y;
        int xer = x + 20 * scale;
        int yer = y;
        rotatePoint(px, py, xel, yel, angle);
        rotatePoint(px, py, xer, yer, angle);
        setcolor(BLACK);
        drawMarkX(xel, yel, 13 * scale);
        drawMarkX(xer, yer, 13 * scale);

    } else {
        int xel1 = x - 20 * scale;
        int yel1 = y + 5 * scale;
        int xer1 = x + 20 * scale;
        int yer1 = y + 5 * scale;
        rotatePoint(px, py, xel1, yel1, angle);
        rotatePoint(px, py, xer1, yer1, angle);
        setfillstyle(SOLID_FILL, BLACK);
        fillellipse(xel1, yel1, 13 * scale, 13 * scale);
        fillellipse(xer1, yer1, 13 * scale, 13 * scale);

        int xel2 = x - 20 * scale;
        int yel2 = y;
        int xer2 = x + 20 * scale;
        int yer2 = y;
        rotatePoint(px, py, xel2, yel2, angle);
        rotatePoint(px, py, xer2, yer2, angle);
        setcolor(BLACK);
        setfillstyle(SOLID_FILL, WHITE);
        fillellipse(xel2, yel2, 13 * scale, 13 * scale);
        fillellipse(xer2, yer2, 13 * scale, 13 * scale);
    }

    setcolor(WHITE);
}

void drawFiringBullet(int x, int y) {
    // Define the points of the polygon
    int points[8];

    points[0] = x;          // Starting x point
    points[1] = y;          // Starting y point
    points[2] = x + 30;    // Left endpoint x of the beam
    points[3] = y - 30;     // Left endpoint y of the beam
    points[4] = x + 35;    // Right endpoint x of the beam
    points[5] = y - 25;     // Right endpoint y of the beam
    points[6] = x + 5;     // Close the polygon back at the starting x point
    points[7] = y + 5;     // Close the polygon back at the starting y point

    // Set the color for the beam
    setcolor(GREEN);
    setfillstyle(SOLID_FILL, GREEN);

    // Fill the beam with color
    fillpoly(4, points); // 4 is the number of points in the polygon
}

void drawNNAction(int x, int y, float scale=1, char color=WHITE) {
    setcolor(color);

    setfillstyle(SOLID_FILL, color);
    fillellipse(x, y, 50 * scale, 50 * scale);

    line(x, y + 50 * scale, x, y + 175 * scale); //Body

    line(x, y + 75 * scale, x + 75 * scale, y + 75 * scale); // Arm1

    line(x, y + 75 * scale, x + 75 * scale, y + 50 * scale); // Arm2

    line(x, y + 175 * scale, x - 50 * scale, y + 250 * scale); // Left leg

    line(x, y + 175 * scale, x + 50 * scale, y + 250 * scale); // Right leg

    setfillstyle(SOLID_FILL, BLACK);
    fillellipse(x + 20 * scale, y + 5 * scale, 13 * scale, 13 * scale);

    setcolor(BLACK);
    setfillstyle(SOLID_FILL, WHITE);
    fillellipse(x + 20 * scale, y, 13 * scale, 13 * scale);

    // end
    setcolor(WHITE);
}

void drawNNhead(int x, int y, float scale=1, char color=WHITE) {
    setcolor(color);

    setfillstyle(SOLID_FILL, color);
    fillellipse(x, y, 50 * scale, 50 * scale);

    setfillstyle(SOLID_FILL, BLACK);
    fillellipse(x - 20 * scale, y + 5 * scale, 13 * scale, 13 * scale);
    fillellipse(x + 20 * scale, y + 5 * scale, 13 * scale, 13 * scale);

    setcolor(BLACK);
    setfillstyle(SOLID_FILL, WHITE);
    fillellipse(x - 20 * scale, y, 13 * scale, 13 * scale);
    fillellipse(x + 20 * scale, y, 13 * scale, 13 * scale);

    setcolor(WHITE);
}

void drawContainer(int x, int y) {
    setcolor(WHITE);
    rectangle(x, y, x + 300, y + 400);
    line(x, y + 30, x + 300, y + 30);
    line(x, y + 370, x + 300, y + 370);
}

void drawNNdead(int x, int y, float scale=1, int color=WHITE, float angle=0) {
    setcolor(color);

    double radians = angle * M_PI / 180;

    int rotatedX = (int)(x + (0) * cos(radians) - (0) * sin(radians));
    int rotatedY = (int)(y + (0) * sin(radians) + (0) * cos(radians));

    setfillstyle(SOLID_FILL, color);
    fillellipse(x, y, 50 * scale, 50 * scale);

    line(x, y + 50 * scale, x, y + 175 * scale); //Body

    line(x - 75 * scale, y + 75 * scale, x + 75 * scale, y + 75 * scale); // Arms

    line(x, y + 175 * scale, x - 50 * scale, y + 250 * scale); // Left leg

    line(x, y + 175 * scale, x + 50 * scale, y + 250 * scale); // Right leg

    setfillstyle(SOLID_FILL, BLACK);
    fillellipse(x - 20 * scale, y + 5 * scale, 13 * scale, 13 * scale);
    fillellipse(x + 20 * scale, y + 5 * scale, 13 * scale, 13 * scale);

    setcolor(BLACK);
    setfillstyle(SOLID_FILL, WHITE);
    fillellipse(x - 20 * scale, y, 13 * scale, 13 * scale);
    fillellipse(x + 20 * scale, y, 13 * scale, 13 * scale);

    setcolor(WHITE);
}

void drawNNsleep(int x, int y, boolean isSleep=true) {
    setcolor(LIGHTGREEN);

    line(x, y + 160, x - 100, y + 190);
    line(x - 100, y + 190, x - 25, y + 250);
    line(x, y + 160, x + 100, y + 170);
    line(x + 100, y + 170, x + 100, y + 275);

    setfillstyle(SOLID_FILL, LIGHTGREEN);
    fillellipse(x, y + 160, 70, 70);

    setfillstyle(SOLID_FILL, BLACK);
    fillellipse(x - 30, y + 165, 21, 21);
    fillellipse(x + 30, y + 165, 21, 21);

    if(!isSleep) {
        setcolor(BLACK);
        setfillstyle(SOLID_FILL, WHITE);
    } else {
        setfillstyle(SOLID_FILL, LIGHTGREEN);
    }
    fillellipse(x - 30, y + 160, 20, 20);
    fillellipse(x + 30, y + 160, 20, 20);
}

void drawScene1() {
    int x = -150, y = 100;  // Initial position of the UFO
    while (1) {  // First scene: UFO moving from left to right
        cleardevice();  // Clear the screen
        drawUFO(x, y);  // Draw the UFO at the current position
        x += 5;  // Update the x coordinate to move the UFO to the right
        if (x > getmaxx()+150) {
            break;
        }
        delay(FRAME);  // Wait for 50 milliseconds
    }

    x = getmaxx()+150, y = 100;
    while (1) {  // Second scene: UFO moving from right to left
        cleardevice();  // Clear the screen
        drawUFO(x, y);  // Draw the UFO at the current position
        x -= 5;  // Update the x coordinate to move the UFO to the left
        if (x < -150) {
            break;
        }
        delay(FRAME);  // Wait for 50 milliseconds
    }
    delay(2000);  // Wait for 1 second (1000 milliseconds

    x = getmaxx()+150, y = 100;
    while (1) {  // Second scene: UFO moving from right to left
        cleardevice();  // Clear the screen
        drawUFO(x, y);  // Draw the UFO at the current position
        x -= 5;  // Update the x coordinate to move the UFO to the left
        if (x < 50) {
            break;
        }
        delay(FRAME);  // Wait for 50 milliseconds
    }

    int x2 = -100, y2 = 300;
    int i = 1;
    double angle = 0;
    while (1) {  // Second scene: UFO moving from right to left
        cleardevice();  // Clear the screen
        drawStickmanWalking(x2, y2, angle);
        drawUFO(x, y);
        switch (i) {
            case 1:
                x += 5;
                if (x >= getmaxx()*3/4) i++;
                break;
            case 2:
                x -= 5;
                if (x <= getmaxx()/4) i++;
                break;
            case 3:
                x += 5;
                if (x >= getmaxx()/2) i++;
                break;
        }
        if (i == 4) break;
        if (x2 <= getmaxx()/2) {
            x2 += 3;
            if (angle < 90) {
                angle += 10;
            } else if (angle > 0){
                angle =- 10;
            }
        }
        delay(FRAME);  // Wait for 50 milliseconds
    }

    float scale = 0.05;
    while (1) {
        cleardevice();
        drawStickman(x2, y2);
        drawUFO(x, y);
        drawBeam(x, y+40, scale);
        if (scale >= 1) break;
        scale += 0.05;
        delay(FRAME);
    }
    delay(2000);

    cleardevice();
    drawUFO(x, y);
    delay(3000);
    cleardevice();
    delay(2000);
}

void drawScene2() {
    int x1 = 100, y1 = getmaxy()*3/4, x2 = 100, y2 = 100, x3 = getmaxx()/2, y3 = 100;
    int tableX = 100, tableY = getmaxy()-80;
    int bookX = 300, bookY = getmaxy()-70;
    int arm = 0, armX = 0;
    for(int i = 0; i < 4 ; i++){
        for(float j = 0; j < 1 ; j += 0.01) {
            cleardevice();

            switch(i%2) {
                case 0:
                    drawSun(curve(x1, x2, x3, j), curve(y1, y2, y3, j), 30);
                    break;
                case 1:
                    drawMoon(curve(x1, x2, x3, j), curve(y1, y2, y3, j), 30);
                    break;
            }

            drawWindowWithClipping(275, 75, 150, 175, -50, 90);
            drawTable(tableX, tableY);
            drawBook(bookX, bookY);
            drawNNsit(400, tableY-200, armX);

            if (armX >= 0) {
                arm = 0;
            } else if (armX <= -100) {
                arm = 1;
            }
            switch(arm) {
                case 0:
                    armX -= 5;
                    break;
                case 1:
                    armX += 5;
                    break;
            }

            delay(FRAME);
        }
    }

    for (float i = 0.1; i < 2; i += 0.1) {
        cleardevice();
        drawShearedRotatedRectangle(275, 75, 150, 175, -50, 90);
        drawTable(tableX, tableY);
        drawBook(bookX, bookY);
        drawNNsit(400, tableY-200, armX);
        drawBeam(getmaxx()/2+100, -200, i);
        delay(FRAME);
    }
    delay(2000);

    cleardevice();
    drawShearedRotatedRectangle(275, 75, 150, 175, -50, 90);
    drawTable(tableX, tableY);
    drawBook(bookX, bookY);
    delay(3000);
    cleardevice();
    delay(2000);
}

void drawScene3() {
    int x = getmaxx();
    int y = getmaxy();

    drawNNpin(x/2, y/2-100);
    bar(x/2 - 50, y/2 - 40, x/2 - 40, y/2 - 10);
    bar(x/2 + 50, y/2 - 40, x/2 + 60, y/2 - 10);
    drawContainer(x/2-150, y/2-200);
    delay(2000);

    setfillstyle(SOLID_FILL, GREEN);
    for (float i = 0; i <= 1; i += 0.01) {
        cleardevice();
        bar(x/2-150, y/2-200 + 370 - 340*i, x/2-150 + 300, y/2-200 + 370);
        drawNNpin(x/2, y/2-100);
        setfillstyle(SOLID_FILL, WHITE);
        bar(x/2 - 50, y/2 - 40, x/2 - 40, y/2 - 10);
        bar(x/2 + 50, y/2 - 40, x/2 + 60, y/2 - 10);
        drawContainer(x/2-150, y/2-200);
        setfillstyle(SOLID_FILL, GREEN);
        delay(FRAME);
    }
    delay(2000);

    cleardevice();
    bar(0, 0, x, y);
    delay(1000);
}

void drawScene4() {
    int x = getmaxx(), y = getmaxy();

    cleardevice();
    drawNNhead(x/4, y/2, 1);
    setfillstyle(SOLID_FILL, GREEN);
    bar(x*3/4, y/2-40, x*3/4+50, y/2+40);
    delay(1000);

    for (int i = 0; i < 150; i += 3) {
        cleardevice();
        drawNNhead(x/4 + i, y/2, 1);
        setfillstyle(SOLID_FILL, GREEN);
        bar(x*3/4 - i, y/2 - 40, x*3/4 + 50 - i, y/2 + 40);
        delay(FRAME);
    }

    cleardevice();
    drawNNpin(x/2, y/2-100, 1, LIGHTGREEN);
    delay(2000);
    
    cleardevice();
    delay(2000);
}

void drawScene5() {
    int x = getmaxx(), y = getmaxy();
    int ufoX = x*3/4, ufoY = 100;

    cleardevice();
    drawUFO(ufoX, ufoY);
    delay(1000);

    setfillstyle(SOLID_FILL, RED);
    fillellipse(ufoX - 20, ufoY, 30, 30);
    delay(1000);
    
    int nnX = ufoX - 20, nnY = ufoY - 50;
    cleardevice();
    drawUFO(ufoX, ufoY);
    drawNNpin(ufoX - 20, ufoY - 50, 0.2, LIGHTGREEN);
    delay(500);

    float scale = 0.2;
    for (float i = 0; i <= 1; i += 0.02) {
        cleardevice();
        drawUFO(ufoX, ufoY);
        if (scale < 0.8) scale += 0.01;
        drawNNpin(curve(nnX, 100, x/4, i), curve(nnY, nnY, 250, i), scale, LIGHTGREEN);
        delay(FRAME);
    }
    delay(1000);
}

void drawScene6() {
    cleardevice();

    int xM = 100;
    int yM = getmaxy() - 150;

    // interation n times
    for (int n = 0; n < 10; n++) {
        
        // firing bullets
        int xB = xM + 40;
        int yB = yM + 10;

        int xB1 = xB;
        int yB1 = yB;
        int xB2 = xB;
        int yB2 = yB + 50;
        int xB3 = xB;
        int yB3 = yB - 50;
        int xB4 = xB;
        int yB4 = yB + 100;
        bool c1 = false;
        bool c2 = false;
        bool c3 = false;
        bool c4 = false;

        int fireRate = 40;

        // ufo
        int xU = getmaxx() - 20;
        int yU = -20;

        int xU1 = xU;
        int yU1 = yU;
        int xU2 = xU + 100;
        int yU2 = yU + 100;
        int xU3 = xU -150;
        int yU3 = yU;

        // loop Frame
        int i = 0;
        while (1) {
            // start loop
            cleardevice();
            drawNNAction(xM, yM, 0.5, LIGHTGREEN);
            
            // firing 1
            if (yB1 <= 0 || xB1 >= getmaxx()) {
                c1 = true;
            } else if (i > 0) {
                drawFiringBullet(xB1, yB1);
                xB1 += fireRate;
                yB1 -= fireRate;
            }

            // firing 2
            if (yB2 <= 0 || xB2 >= getmaxx()) {
                c2 = true;
            } else if (i > 10) {
                drawFiringBullet(xB2, yB2);
                xB2 += fireRate;
                yB2 -= fireRate;
            }

            // firing 3
            if (yB3 <= 0 || xB3 >= getmaxx()) {
                c3 = true;
            } else if (i > 5) {
                drawFiringBullet(xB3, yB3);
                xB3 += fireRate;
                yB3 -= fireRate;
            }

            // firing 4
            if (yB4 <= 0 || xB4 >= getmaxx()) {
                c4 = true;
            } else if (i > 15) {
                drawFiringBullet(xB4, yB4);
                xB4 += fireRate;
                yB4 -= fireRate;
            }

            // ufo 1
            if (yU1 < yB && xU1 > xB && i > 0) {
                drawUFO(xU1, yU1);
                xU1 -= fireRate;
                yU1 += fireRate;
            }

            // ufo 2
            if (yU2 < yB && xU2 > xB && i > 5) {
                drawUFO(xU2, yU2);
                xU2 -= fireRate;
                yU2 += fireRate;
            }

            // ufo 3
            if (yU3 < yB && xU3 > xB && i > 10) {
                drawUFO(xU3, yU3);
                xU3 -= fireRate;
                yU3 += fireRate;
            }

            // end loop
            delay(FRAME);
            i++;
            if (c1 && c2 && c3 && c4) break;
        }
    }
    
    delay(1000);

}

void drawScene7() {
    int xm = getmaxx() / 2;
    int ym = getmaxy() / 3;
    double angle = 0;
    for (int i = 0; i < 181; i++) {
        cleardevice();
        if (angle == 90) {
            drawNNManDead(xm, ym, xm, ym + 200, angle, true, 1, LIGHTGREEN);
        } else{
            drawNNManDead(xm, ym, xm, ym + 200, angle, false, 1, LIGHTGREEN);
        }
        delay(FRAME);
        angle += 0.5;
    }
    delay(3000);

    cleardevice();

    delay(200);
}

void drawScene8() {
    cleardevice();
    int tableX = 100, tableY = getmaxy()-80;
    int bookX = 300, bookY = getmaxy()-70;
    drawWindowWithClipping(275, 75, 150, 175, -50, 90);
    drawTable(tableX, tableY);
    drawBook(bookX, bookY);
    drawNNsleep(400, tableY-200);
    delay(3000);

    cleardevice();
    drawWindowWithClipping(275, 75, 150, 175, -50, 90);
    drawTable(tableX, tableY);
    drawBook(bookX, bookY);
    drawNNsleep(400, tableY-200, false);
    delay(1500);

    cleardevice();
    delay(2000);
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);  // Initialize graphics mode

    drawScene1(); 
    drawScene2();
    drawScene3();
    drawScene4();
    drawScene5();
    drawScene6();
    drawScene7();
    drawScene8();
    
    getch();  // Wait for a key press
    closegraph();  // Close graphics mode
    return 0;
}
