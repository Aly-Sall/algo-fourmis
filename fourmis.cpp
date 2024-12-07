#include<iostream>
#include<stdlib.h>
#include<cmath>

#ifdef __APPLE__
#include<openGL/openGL.h>
#include<GLUT/glut.h>
#else
#include<GL/glut.h>
#endif

using namespace std;

const int numAnts = 3; // Number of ants
float ballX[numAnts] = {-0.3f, -0.1f, 0.1f}; // Initial X positions of ants
float ballY[numAnts] = {0.0f, 0.2f, -0.2f}; // Initial Y positions of ants
float ballZ[numAnts] = {-1.0f, -1.0f, -1.0f}; // All ants are at the same Z-depth
float targetX = 0.5f; // Target X position
float targetY = 0.0f; // Target Y position
float targetZ = -1.0f; // Target Z position

// Matrix for pheromone levels
float pheromone[400][400] = {0.0}; // 2D grid for pheromone concentration

static int flag = 1;

// Function to draw an ant
void drawAnt(int i) {
    glColor3f(1.0, 0.0, 0.0); // Ant color
    glTranslatef(ballX[i], ballY[i], ballZ[i]); // Set ant position
    glutSolidSphere(0.05, 10, 10); // Draw the ant as a small sphere
}

// Function to update the pheromone levels (evaporation)
void updatePheromone() {
    for (int i = 0; i < 400; i++) {
        for (int j = 0; j < 400; j++) {
            pheromone[i][j] *= 0.99; // Evaporation, decrease the pheromone level
        }
    }
}

// Function to deposit pheromone at the current position
void depositPheromone(int x, int y) {
    if (x >= 0 && x < 400 && y >= 0 && y < 400) {
        pheromone[x][y] += 0.1; // Add some pheromone
    }
}

// Function to calculate the distance between two points
float distance(float x1, float y1, float x2, float y2) {
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

// Fonction pour déplacer les fourmis
void moveAnt(int i) {
    float dx = targetX - ballX[i]; // Direction X vers la cible
    float dy = targetY - ballY[i]; // Direction Y vers la cible
    float dist = distance(ballX[i], ballY[i], targetX, targetY);

    if (dist > 0.05f) { // Déplacer la fourmi si elle est suffisamment loin
        ballX[i] += dx / dist * 0.01f; // Déplacer en X
        ballY[i] += dy / dist * 0.01f; // Déplacer en Y
    }

    // Empêcher la fourmi de sortir de l'écran
    if (ballX[i] < -1.0f) ballX[i] = -1.0f; // Limiter à gauche
    if (ballX[i] > 1.0f) ballX[i] = 1.0f;  // Limiter à droite
    if (ballY[i] < -1.0f) ballY[i] = -1.0f; // Limiter en bas
    if (ballY[i] > 1.0f) ballY[i] = 1.0f;  // Limiter en haut

    // Déposer des phéromones sur la grille
    int px = (int)(ballX[i] * 100 + 200); // Convertir X en indice de grille
    int py = (int)(ballY[i] * 100 + 200); // Convertir Y en indice de grille
    depositPheromone(px, py);
}


// Function to display the pheromone grid
void drawPheromoneGrid() {
    glColor3f(0.0, 1.0, 0.0); // Green color for pheromones
    for (int i = 0; i < 400; i++) {
        for (int j = 0; j < 400; j++) {
            if (pheromone[i][j] > 0.05) {
                glPushMatrix();
                glTranslatef(i / 100.0f - 2.0f, j / 100.0f - 2.0f, -1.0f);
                glutSolidSphere(0.02 * pheromone[i][j], 10, 10); // Visualize pheromone as small spheres
                glPopMatrix();
            }
        }
    }
}

// Fonction appelée lors de la pression d'une touche
void keyPress(int key, int x, int y) {
    if (key == GLUT_KEY_RIGHT) targetX += 0.05f;
    if (key == GLUT_KEY_LEFT) targetX -= 0.05f;
    if (key == GLUT_KEY_UP) targetY += 0.05f;
    if (key == GLUT_KEY_DOWN) targetY -= 0.05f;

    // Empêcher la cible de sortir de l'écran
    if (targetX < -1.0f) targetX = -1.0f; // Limiter à gauche
    if (targetX > 1.0f) targetX = 1.0f;  // Limiter à droite
    if (targetY < -1.0f) targetY = -1.0f; // Limiter en bas
    if (targetY > 1.0f) targetY = 1.0f;  // Limiter en haut

    glutPostRedisplay();
}


void initRendering() {
    glEnable(GL_DEPTH_TEST);
}

// Called when the window is resized
void handleResize(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}

void drawScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Draw the target (goal) as a blue sphere
    glColor3f(0.0, 0.0, 1.0);
    glTranslatef(targetX, targetY, targetZ);
    glutSolidSphere(0.1, 10, 10);

    // Draw the pheromone grid
    drawPheromoneGrid();

    // Draw each ant
    for (int i = 0; i < numAnts; i++) {
        glLoadIdentity();
        drawAnt(i);
    }

    glutSwapBuffers();
}

// Function to update the simulation
void update(int value) {
    updatePheromone(); // Update pheromone levels (evaporation)

    // Move ants towards the target
    for (int i = 0; i < numAnts; i++) {
        moveAnt(i);
    }

    glutPostRedisplay();
    glutTimerFunc(25, update, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Ant Colony Simulation");

    initRendering();

    glutDisplayFunc(drawScene);
    glutSpecialFunc(keyPress);
    glutReshapeFunc(handleResize);

    glutTimerFunc(25, update, 0);
    glutMainLoop();

    return 0;
}
