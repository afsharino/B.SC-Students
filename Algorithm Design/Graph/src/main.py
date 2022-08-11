import math

# Matrix to store given graph
matrix = []

# A list to store 0 and 1 which shows villages and cities.
is_city = []

def get_input():

    # Get n, A and B from the user.
    user_input = input().split()
    n = int(user_input[0])
    A = int(user_input[1])-1
    B = int(user_input[2])-1

    # Get elements of matrix from the user.
    for i in range(n):
        row = list(map(int, input().split()))
        matrix.append(row[:-1])
        is_city.append(row[-1])

    return n, A, B

# Function to find the node with minimum distance among all nodes not yet included in short path tree.
def minimum_distance(distance, set_of_short_path_tree):

    # Initialze min each time as a big int number.
    min = math.inf

    for v in range(n):
        if distance[v] < min and set_of_short_path_tree[v] == False:
            min = distance[v]
            min_index = v

    return min_index

# Implementaion of dijkstra for shortest path 
def dijkstra(source_node, n):

    # A list to hold shortest distance from source to other nodes.
    distance = [math.inf for i in range(n)]

    # Distance of source node to itself is 0
    distance[source_node] = 0

    # A list that determines if a node is in shortest path tree
    # (minimum dsitance from source node is evaluated) or not yet.
    set_of_short_path_tree = [False for i in range(n)]


    # Find shortest path to all nodes.
    for c in range(n):

        # u is a node which is not in set of shortest path tree and has minimum distance among others.
        u = minimum_distance(distance, set_of_short_path_tree)
        
        # Add node u to set of shortest path tree as its distance evaluated.
        set_of_short_path_tree[u] = True

        # Update distance value of all adjacent vertices of u.
        for v in range(n):
            if (matrix[u][v] > 0 and
            set_of_short_path_tree[v] == False and
            distance[v] > distance[u] + matrix[u][v]):
               distance[v] = distance[u] + matrix[u][v]

    return distance


# Let's Start
n, A, B = get_input()

# Run dijkstra on A and B to get shortest path to other nodes.
distance_A = dijkstra(A, n)
distance_B = dijkstra(B, n)

# Suppose distance between A and closet city be inf.
closest_A = math.inf
closest_B = math.inf

# Among all shortest paths from A to other nodes i,
# choose minimum one in which i is city.
for i, d in enumerate(distance_A):
    if is_city[i] == 1 and d < closest_A:
        closest_A = d

# Among all shortest paths from B to other nodes i,
# choose minimum one in which i is city.
for i, d in enumerate(distance_B):
    if is_city[i] == 1 and d < closest_B:
        closest_B = d

# if the closet city be  the same for both then we cant distinguish them.
if closest_A == closest_B:
    print("Indistinguishable")

else:
    print(min(closest_A, closest_B))