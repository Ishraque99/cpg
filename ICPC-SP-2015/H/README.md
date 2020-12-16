# H. Hiking

Alice likes to hike. She likes some bits of track and dislikes others. A cost function will model her distaste
for (or liking of) all available track sections. Given a map with the costs of going from one location to
the next, find the average cost for a hike in that area.
The map is a rectangular grid of cells. Each cell has information about the cost of going from it to each
of its northern, western, southern and eastern neighbours. A hike is a finite sequence of steps each of
which goes from a cell to one of its neighbours. The cost of a hike is the sum of the costs of its steps.
When Alice hikes from a given start point to a given end point, she always chooses a minimal cost hike.
Determine the average cost of such minimal-cost hikes taken over all possible start and end cells. The
start and end cells of a hike must be different. Each pair of start and end cells counts just once towards
the average even if there are several minimal-cost hikes between the two cells.

## Input

The input will contain a single test case.
The first line contains two integers w and h specifying the width and the height of the map (2 ≤ w, h ≤
50). Each of the following h lines contains w integers n_ij (1 ≤ i ≤ h and 1 ≤ j ≤ w and −107 ≤ n_ij ≤ 107
)
specifying the cost of going from cell (i, j) one step to its northern neighbour (i − 1, j). Then follow
three blocks of h lines each, similarly specifying costs for the western, southern and eastern neighbours
in this order.
It is not permitted to walk off the map; the corresponding costs will be 0. A minimal-cost hike will exist
between any two cells.

## Output

Display the smallest integer that is greater than or equal to the average cost of minimal-cost hikes among
all pairs of distinct start and end cells.
