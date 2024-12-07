Ant Colony Simulation with OpenGL

This project demonstrates a simplified simulation of the Ant Colony Optimization (ACO) algorithm using OpenGL. The simulation showcases ants moving towards a target and depositing pheromones, illustrating how ant colonies work together to find optimal paths.
Features

Ant movement: Three ants (red spheres) move towards a target (blue sphere).
Pheromone system: Ants deposit pheromones along their paths, which evaporate over time.
Interactive controls: Move the target using the arrow keys.
Screen boundaries: Ants and the target remain within the visible area.
How It Works

Ant Movement:
Each ant calculates its direction towards the target based on its current position.
Ants move step-by-step, influenced by the target's location.
Pheromones:
A virtual grid represents pheromone levels.
As ants move, they deposit pheromones at their current positions.
Pheromones evaporate over time to simulate dynamic changes in the environment.
Target Object:
The blue sphere represents the goal or food source for the ants.
Its position can be adjusted interactively.
Visualization:
Ants are red spheres.
The target is a blue sphere.
Controls

Arrow Keys:
Move the target:
Right: Move the target to the right.
Left: Move the target to the left.
Up: Move the target upwards.
Down: Move the target downwards.

Installation

1.Clone the repository

2.Compile and run the program:
  On macOS: g++ -framework OpenGL -framework GLUT ant_colony_simulation.cpp -o ant_colony_simulation
          ./ant_colony_simulation
  On Linux: 
    g++ -lGL -lGLU -lglut ant_colony_simulation.cpp -o ant_colony_simulation
    ./ant_colony_simulation

Instructions for Windows

Prerequisites
Install a Compiler:
Install MinGW or another GCC-based compiler.
Add the compiler's bin directory (e.g., C:\MinGW\bin) to your system's PATH.
Install FreeGLUT:
Download and install FreeGLUT from FreeGLUT Downloads.
Copy the required files:
Headers: Place GL/freeglut.h in the compiler's include directory.
Libraries: Place freeglut.lib and freeglut.dll in the compiler's lib directory.
DLL: Place freeglut.dll in the same folder as your executable.
Compilation and Execution
Open a terminal or command prompt.
Navigate to the folder containing ant_colony_simulation.cpp.
Compile the program: g++ ant_colony_simulation.cpp -lfreeglut -lopengl32 -o ant_colony_simulation.exe

Run the executable:
 ant_colony_simulation.exe


Project Structure

Ant Logic:
Ants follow the target and update their positions based on a simple distance calculation.
Pheromones guide the ants' movement, and evaporation simulates real-world behavior.
Rendering:
OpenGL handles the rendering of ants, the target, and the environment.
Future Improvements

Add more ants to the simulation.
Implement a more sophisticated pheromone-based decision-making algorithm.
Visualize the pheromone trails.
Add obstacles that 
ants must navigate around.
Screenshots
<img width="1651" alt="Screenshot 1403-09-17 at 21 03 41" src="https://github.com/user-attachments/assets/5b2337d5-038d-455a-ba4f-2ed8e534771c">



Author

This project was created as a visual representation of the Ant Colony Optimization algorithm. Contributions and feedback are welcome!
  
