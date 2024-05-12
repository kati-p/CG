#include <graphics.h>
#include <conio.h>

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

void drawTable(int x, int y) {
    setcolor(WHITE);
    drawShearedRectangle(x, y, 500, 50, 50);
    drawShearedRectangle(x, y+50, 500, 50);
}

void drawBook(int x, int y) {
    setcolor(WHITE);
    drawShearedRectangle(x, y, 50, 50, 50);
    drawShearedRectangle(x+50, y, 50, 50);
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
        delay(1);  // Wait for 50 milliseconds
    }

    x = getmaxx()+150, y = 100;
    while (1) {  // Second scene: UFO moving from right to left
        cleardevice();  // Clear the screen
        drawUFO(x, y);  // Draw the UFO at the current position
        x -= 5;  // Update the x coordinate to move the UFO to the left
        if (x < -150) {
            break;
        }
        delay(1);  // Wait for 50 milliseconds
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
        delay(1);  // Wait for 50 milliseconds
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
        delay(1);  // Wait for 50 milliseconds
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
}

void drawScene2() {
    drawTable(100, getmaxy()-80);
    drawBook(200, getmaxy()-70);
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);  // Initialize graphics mode

    //drawScene1();
    drawScene2();

    getch();  // Wait for a key press
    closegraph();  // Close graphics mode
    return 0;
}
