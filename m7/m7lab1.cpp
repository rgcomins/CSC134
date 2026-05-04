/*
 * MazeBuilder - Binary Tree Maze Generator
 * 
 * This program generates a random maze using the Binary Tree algorithm.
 * The algorithm creates a "perfect maze" where there is exactly one path
 * between any two cells, with no isolated areas or circular paths.
 * 
 * The program uses bitwise operations and enum values to efficiently represent
 * connections between cells in the maze.
 */

#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <cstring>
using namespace std;

// Direction constants - Using powers of 2 to enable bitwise operations
// Each direction has a unique bit flag that we can use with & and | operators
// This allows us to efficiently store which directions a cell is linked to
enum Direction {
    NORTH = 1,  // Binary: 0001
    SOUTH = 2,  // Binary: 0010
    EAST = 4,   // Binary: 0100
    WEST = 8    // Binary: 1000
};

// Mapping of direction enum values to coordinate offsets
// This table uses the enum values (1, 2, 4, 8) as array indices to look up
// how many rows (vertical) and columns (horizontal) to move for each direction.
// Note: Column changes are stored first, then row changes {col_offset, row_offset}
const std::pair<int, int> DIRECTION_OFFSETS[] = {
    {0, 0},     // Index 0: Placeholder (not a valid direction)
    {0, -1},    // Index 1 (NORTH): Move up one row (row - 1)
    {0, 1},     // Index 2 (SOUTH): Move down one row (row + 1)
    {0, 0},     // Index 3: Placeholder
    {1, 0},     // Index 4 (EAST): Move right one column (col + 1)
    {0, 0},     // Index 5: Placeholder
    {0, 0},     // Index 6: Placeholder
    {0, 0},     // Index 7: Placeholder
    {-1, 0}     // Index 8 (WEST): Move left one column (col - 1)
};

// Mapping of directions to their opposite directions
// When we link two cells together, we need to link them from both sides.
// This table helps us find the opposite direction (e.g., if we link NORTH,
// the adjacent cell needs to link SOUTH back to us).
const Direction OPPOSITES[] = {
    (Direction)0,     // Index 0: Placeholder (no opposite)
    SOUTH,            // Index 1 (NORTH): Opposite is SOUTH
    NORTH,            // Index 2 (SOUTH): Opposite is NORTH
    (Direction)0,     // Index 3: Placeholder
    WEST,             // Index 4 (EAST): Opposite is WEST
    (Direction)0,     // Index 5: Placeholder
    (Direction)0,     // Index 6: Placeholder
    (Direction)0,     // Index 7: Placeholder
    EAST              // Index 8 (WEST): Opposite is EAST
};

// Cell class - Represents a single rectangular cell in the maze grid
// Each cell tracks which neighboring cells it is "linked" to (connected).
// We use bitwise operations to efficiently store up to 4 link directions.
class Cell {
private:
    int row;        // The row position of this cell in the grid
    int col;        // The column position of this cell in the grid
    int links;      // A set of bit flags indicating which directions have links
                    // If bit for NORTH is set, this cell is linked to its northern neighbor

public:
    Cell(int row, int col) : row(row), col(col), links(0) {}

    int getRow() const { return row; }
    int getCol() const { return col; }

    // Check if this cell is linked to another cell in the given direction
    // Uses bitwise AND (&) to check if the direction's bit is set in links
    bool linked(Direction direction) const {
        return (links & direction) != 0;
    }

    // Create a link between this cell and a neighbor in the given direction
    // Uses bitwise OR (|=) to set the direction's bit in the links variable
    void link(Direction direction) {
        links |= direction;
    }

    // Remove a link between this cell and a neighbor in the given direction
    // Uses bitwise AND with NOT (~) to clear the direction's bit in links
    void unlink(Direction direction) {
        links &= ~direction;
    }

    // Return a vector of all directions where this cell has links
    // Useful for iteration when we need to know all connected neighbors
    std::vector<Direction> getLinks() const {
        std::vector<Direction> result;
        if (linked(NORTH)) result.push_back(NORTH);
        if (linked(SOUTH)) result.push_back(SOUTH);
        if (linked(EAST)) result.push_back(EAST);
        if (linked(WEST)) result.push_back(WEST);
        return result;
    }
};

// Grid class - Manages the entire maze grid with all its cells
// Provides methods to access cells, randomly generate numbers,
// and create links between cells. Uses Mersenne Twister for random generation.
class Grid {
private:
    int rows;                              // Number of rows in the grid
    int cols;                              // Number of columns in the grid
    std::vector<std::vector<Cell>> cells;  // 2D vector of cells: cells[row][col]
    std::mt19937 rng;                      // Mersenne Twister random number generator

public:
    // Constructor: Initialize the grid with a given number of rows and columns
    Grid(int rows, int cols) : rows(rows), cols(cols) {
        // Seed the random number generator with the current time
        // This ensures different mazes are generated on each run
        rng.seed(static_cast<unsigned int>(std::time(nullptr)));
        
        // Create and initialize all cells in the grid
        cells.resize(rows);  // Create space for each row
        for (int r = 0; r < rows; r++) {
            cells[r].reserve(cols);  // Reserve space for columns
            for (int c = 0; c < cols; c++) {
                // Create a new cell with its row and column coordinates
                // All cells start with no links (links = 0)
                cells[r].emplace_back(r, c);
            }
        }
    }

    int getRows() const { return rows; }
    int getCols() const { return cols; }

    // Check if the given row and column coordinates are within the grid bounds
    // Returns true if the position is valid, false otherwise
    bool isValid(int row, int col) const {
        return row >= 0 && row < rows && col >= 0 && col < cols;
    }

    // Retrieve a reference to the cell at the given position (non-const version)
    // Allows modification of the cell
    Cell& at(int row, int col) {
        return cells[row][col];
    }

    // Retrieve a constant reference to the cell at the given position
    // Prevents modification of the cell (used for reading only)
    const Cell& at(int row, int col) const {
        return cells[row][col];
    }

    // Generate a random integer between min and max (inclusive)
    // Uses uniform distribution to ensure each number has equal probability
    int random(int min, int max) {
        std::uniform_int_distribution<int> dist(min, max);
        return dist(rng);
    }

    // Create a bidirectional link between two cells in the grid
    // Parameters: starting cell position (row1, col1) and the direction to link
    // This function creates a passage between the two adjacent cells
    void linkCells(int row1, int col1, Direction dir) {
        // Verify the starting cell is within the grid
        if (!isValid(row1, col1)) return;

        // Calculate the row and column of the neighboring cell
        // DIRECTION_OFFSETS stores {col_change, row_change} pairs
        int row2 = row1 + DIRECTION_OFFSETS[dir].second;
        int col2 = col1 + DIRECTION_OFFSETS[dir].first;

        // Verify the neighbor cell is within the grid
        if (!isValid(row2, col2)) return;

        // Create the link from the first cell to the second
        // AND create the reciprocal link from the second cell back to the first
        // This ensures both cells "know" about the connection
        at(row1, col1).link(dir);
        at(row2, col2).link(OPPOSITES[dir]);
    }

    // Display the maze in ASCII art format to the console
    // Uses | for vertical walls, --- for horizontal walls, and + for corners
    // Open passages are shown as spaces where walls would normally be
    void display() const {
        // Draw the top border of the maze
        std::cout << "+";
        for (int c = 0; c < cols; c++) {
            std::cout << "---+";
        }
        std::cout << std::endl;

        // Process each row of cells
        for (int r = 0; r < rows; r++) {
            // Draw the horizontal line for this row (walls on the east side of cells)
            std::cout << "|";
            for (int c = 0; c < cols; c++) {
                std::cout << "   ";  // Draw cell contents (empty space)
                // Check if there's a link to the east (right)
                if (c < cols - 1 && cells[r][c].linked(EAST)) {
                    std::cout << " ";  // No wall to the east - draw passage
                } else {
                    std::cout << "|";  // Wall to the east
                }
            }
            std::cout << std::endl;

            // Draw the southern boundary line (walls on the south side of cells)
            std::cout << "+";
            for (int c = 0; c < cols; c++) {
                // Check if there's a link to the south (down)
                if (r < rows - 1 && cells[r][c].linked(SOUTH)) {
                    std::cout << "   +";  // No wall to the south - draw passage
                } else {
                    std::cout << "---+";  // Wall to the south
                }
            }
            std::cout << std::endl;
        }
    }
};

// BinaryTreeMaze - Implements the Binary Tree maze generation algorithm
// This algorithm creates a perfect maze by randomly choosing to carve a passage
// either north or east from each cell. The result has a distinctive bias toward
// the northeast corner of the maze.
class BinaryTreeMaze {
public:
    // Apply the Binary Tree algorithm to generate a maze in the grid
    // The algorithm iterates through each cell and randomly carves either north or east
    static void on(Grid& grid) {
        // Visit every cell in the grid
        for (int r = 0; r < grid.getRows(); r++) {
            for (int c = 0; c < grid.getCols(); c++) {
                // Build a list of valid directions we can carve from this cell
                std::vector<Direction> neighbors;
                
                // Can only carve north if we're not in the top row
                if (r > 0) {
                    neighbors.push_back(NORTH);
                }
                
                // Can only carve east if we're not in the rightmost column
                if (c < grid.getCols() - 1) {
                    neighbors.push_back(EAST);
                }
                
                // If we have at least one valid direction, randomly pick one and carve
                if (!neighbors.empty()) {
                    int index = grid.random(0, neighbors.size() - 1);
                    Direction direction = neighbors[index];
                    grid.linkCells(r, c, direction);
                }
                // If we have no valid directions (top-left cell), nothing to do
            }
        }
    }
};

// Print a help message explaining how to use the program
// This is displayed when the user provides the -h or --help flag
void print_help(const char* program_name) {
    cout << "MazeBuilder - A maze generation tool using the Binary Tree algorithm\n\n";
    cout << "Usage: " << program_name << " [OPTIONS] [rows] [columns]\n\n";
    cout << "Arguments:\n";
    cout << "  rows          Number of rows in the maze (default: 10)\n";
    cout << "  columns       Number of columns in the maze (default: 10)\n\n";
    cout << "Options:\n";
    cout << "  -h, --help    Show this help message and exit\n\n";
    cout << "Examples:\n";
    cout << "  " << program_name << "                    Generate a 10x10 maze\n";
    cout << "  " << program_name << " 20                 Generate a 20x20 maze\n";
    cout << "  " << program_name << " 15 25              Generate a 15x25 maze\n";
    cout << "  " << program_name << " --help             Show this help message\n\n";
    cout << "Algorithm:\n";
    cout << "  Binary Tree: For each cell, randomly carve a passage either north or east.\n";
    cout << "  Creates a perfect maze with exactly one path between any two points.\n";
    cout << "  Has a bias toward the northeast corner.\n";
}

// Main function - Entry point for the maze generation program
int main(int argc, char* argv[]) {
    // Set default maze dimensions
    int rows = 10;
    int cols = 10;
    
    // Check if the user requested help information
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            print_help(argv[0]);  // argv[0] is the program name
            return 0;              // Exit after showing help
        }
    }
    
    // Parse command line arguments to override default dimensions
    if (argc > 1) {
        rows = std::atoi(argv[1]);  // Convert first argument to integer
    }
    if (argc > 2) {
        cols = std::atoi(argv[2]);  // Convert second argument to integer
    }
    
    // Create a grid with the specified dimensions
    Grid grid(rows, cols);
    
    // Generate the maze using the Binary Tree algorithm
    BinaryTreeMaze::on(grid);
    
    // Display the generated maze to the user
    grid.display();
    
    // Return 0 to indicate successful completion
    return 0;
}