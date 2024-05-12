#include <graphics.h>   
#include <conio.h>
#include <cmath>

#define FRAME 1000/24

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

void drawNNpin(int x, int y) {
    setcolor(WHITE);

    setfillstyle(SOLID_FILL, WHITE);
    fillellipse(x, y, 50, 50);

    line(x, y + 50, x, y + 175); //Body

    line(x - 75, y + 75, x + 75, y + 75); // Arms

    line(x, y + 175, x - 50, y + 250); // Left leg

    line(x, y + 175, x + 50, y + 250); // Right leg

    setfillstyle(SOLID_FILL, BLACK);
    fillellipse(x-20, y+5, 13, 13);
    fillellipse(x+20, y+5, 13, 13);

    setcolor(BLACK);
    setfillstyle(SOLID_FILL, WHITE);
    fillellipse(x-20, y, 13, 13);
    fillellipse(x+20, y, 13, 13);

    //solid rectangle
    bar(x - 50, y + 60, x - 40, y + 90);
    bar(x + 50, y + 60, x + 60, y + 90);

    setcolor(WHITE);
}

void drawContainer(int x, int y) {
    setcolor(WHITE);
    rectangle(x, y, x + 300, y + 400);
    line(x, y + 30, x + 300, y + 30);
    line(x, y + 370, x + 300, y + 370);
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
    while (1) {  // Second scene: UFO moving from right to left
        cleardevice();  // Clear the screen
        drawStickman(x2, y2);
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
    delay(1000);

    cleardevice();
    drawShearedRotatedRectangle(275, 75, 150, 175, -50, 90);
    drawTable(tableX, tableY);
    drawBook(bookX, bookY);
    delay(3000);
    cleardevice();
    delay(2000);
}

void drawScene3() {
    drawNNpin(getmaxx()/2, getmaxy()/2-100);
    drawContainer(getmaxx()/2-150, getmaxy()/2-200);
    delay(2000);

    setfillstyle(SOLID_FILL, GREEN);
    for (float i = 0; i <= 1; i += 0.01) {
        cleardevice();
        bar(getmaxx()/2-150, getmaxy()/2-200 + 370 - 340*i, getmaxx()/2-150 + 300, getmaxy()/2-200 + 370);
        drawNNpin(getmaxx()/2, getmaxy()/2-100);
        drawContainer(getmaxx()/2-150, getmaxy()/2-200);
        setfillstyle(SOLID_FILL, GREEN);
        delay(FRAME);
    }
    delay(2000);

    cleardevice();
    bar(0, 0, getmaxx(), getmaxy());
}

void drawScene4() {
    cleardevice();
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);  // Initialize graphics mode

    drawScene1();
    drawScene2();
    drawScene3();
    drawScene4();

    getch();  // Wait for a key press
    closegraph();  // Close graphics mode
    return 0;
}
