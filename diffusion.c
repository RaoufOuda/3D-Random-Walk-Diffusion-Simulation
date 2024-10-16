#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//TODO
//Implement the below function
//Simulate one particle moving n steps in random directions
//Use a random number generator to decide which way to go at every step
//When the particle stops at a final location, use the memory pointed to by grid to 
//record the number of particles that stop at this final location
//Feel free to declare, implement and use other functions when needed

void one_particle(int *grid, int n)
{
    int x = 0;
    int y = 0;
    int z = 0;
    
    // Now, we simulate n steps of the particle
    for (int i = 0; i < n; i++) {
        // Get a random direction (0 to 5)
        int direction = rand() % 6;
        
        // Move the particle based on the direction
        if (direction == 0) {
            x--;  // Move left on the x-axis
        } else if (direction == 1) {
            x++;  // Move right on the x-axis
        } else if (direction == 2) {
            y--;  // Move backward on the y-axis
        } else if (direction == 3) {
            y++;  // Move forward on the y-axis
        } else if (direction == 4) {
            z--;  // Move down on the z-axis
        } else if (direction == 5) {
            z++;  // Move up on the z-axis
        }
    }
    
    // Now, map (x, y, z) into the grid index
    int grid_size = 2 * n + 1;
    int index = (x + n) * grid_size * grid_size + (y + n) * grid_size + (z + n);

    // Increment the count for the particle at this final location
    grid[index]++;
}

//TODO
//Implement the following function
//This function returns the fraction of particles that lie within the distance
//r*n from the origin (including particles exactly r*n away)
//The distance used here is Euclidean distance
//Note: you will not have access to math.h when submitting on Mimir
double density(int *grid, int n, double r){
    int count = 0;
    int total_particles = 0;
    double r_squared = (r * n) * (r * n);

       for (int x = -n; x <= n; x++) {
        for (int y = -n; y <= n; y++) {
            for (int z = -n; z <= n; z++) {
                // Convert (x, y, z) into grid index
                int grid_size = 2 * n + 1;
                int index = (x + n) * grid_size * grid_size + (y + n) * grid_size + (z + n);
                int num_particles = grid[index];
                
              
                total_particles += num_particles;
                
              
                int dist_squared = x*x + y*y + z*z;
                
               
                if (dist_squared <= r_squared) {
                    count += num_particles;
                }
            }
        }
    }
    

    return (double)count / total_particles;  
}

//use this function to print results
void print_result(int *grid, int n)
{
    printf("radius density\n");
    for(int k = 1; k <= 20; k++)
    {
        printf("%.2lf   %lf\n", 0.05*k, density(grid, n, 0.05*k));
    }
}


void diffusion(int n, int m) {
    int grid_size = (2 * n + 1) * (2 * n + 1) * (2 * n + 1);
    int *grid = (int*) calloc(grid_size, sizeof(int));  // Allocate and initialize the grid


    for (int i = 0; i < m; i++) {
        one_particle(grid, n); 
    }

    print_result(grid, n);  // Print the final results

    free(grid);  // Free the allocated memory
}

int main(int argc, char *argv[])
{
	
	if(argc != 3)
	{
		printf("Usage: %s n m\n", argv[0]);
		return 0; 
	}
	int n = atoi(argv[1]);
	int m = atoi(argv[2]);

	assert(n >= 1 && n <=50);
	assert(m >= 1 && m <= 1000000);
	srand(12345);
	diffusion(n, m);
	return 0;
}