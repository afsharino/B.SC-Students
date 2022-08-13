matrix = []

def get_input():
    # Get n and k from the user.
    usr_input = input().split()
    n = int(usr_input[0])
    k = int(usr_input[1])

    # Get elements of matrix from the user.
    for i in range(n):
        row = list(map(int, input().split()))
        matrix.append(row)

    return n, k

def find_maximum_path(n, k):
    # matrix to store maximum sum of tangelos
    result_matrix = []
    result = 0

    #initialize the matrix with zero values
    for i in range(n):
        row = []
        for j in range(n+2):
            row .append(0)
        result_matrix.append(row)

    # append the first row of given matrix
    # to result matrix
    for i in range(n):
        result_matrix[0][i+1] = matrix[0][i]

    # Mail Algorithm
    for i in range(1, n):
        possible_k = []
        for j in range(1, n+1):

            if k > 0:
                result_matrix[i][j] = max(result_matrix[i-1][j-1],
                result_matrix[i-1][j], result_matrix[i-1][j+1]) \
                + matrix[i][j-1]

                if (max(result_matrix[i-1][j-1],
                result_matrix[i-1][j], result_matrix[i-1][j+1]) \
                == result_matrix[i-1][j]) and \
                (result_matrix[i-1][j-1] != result_matrix[i-1][j] and \
                result_matrix[i-1][j] != result_matrix[i-1][j+1]):
                    possible_k.append(result_matrix[i][j])
            else:
                result_matrix[i][j] = max(result_matrix[i-1][j-1],
                result_matrix[i-1][j+1]) + matrix[i][j-1]

        max_of_row = max(result_matrix[i])
        if max_of_row in possible_k:
            k -= 1


    # Find the result in last row
    for i in range(n+1):
        result = max(result, result_matrix[n-1][i])

    return(result)

n, k =get_input()
print(find_maximum_path(n, k))

