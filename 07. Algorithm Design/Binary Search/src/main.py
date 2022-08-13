import math

def find_possible_f(f):
    j = 0 # counter
    f = f # guessed f

    # l_temp store's  f + [f/m] + [f/m^2] + ...
    l_temp1 = 0

    # untill the f/m^j is not 0 this means that the guessed f 
    # -has this chance to be minimum f.
    while((f/(m**j)) >= 1):
        # Sum f + [f/m] + [f/m^2] + ...
        l_temp1 += math.floor((f/(m**j)))
        j += 1
        
    return l_temp1

def find_minimum_f(l, m, start, end):
    
    # in cases like l = 1 or l=2 in which l is less than m (2 <= m <= 10) 
    # devinetly minimum f is l.
    if l <= m:
        return(l)

    else:
    
     while start <= end:

         # Find middle
         mid = (end + start) // 2

         # l_temp store's  f + [f/m] + [f/m^2] + ...
         l_temp = find_possible_f(mid)
         
         # if temporary l is equal to main l so congratulations:) the minimum f is founded.
         if (l_temp == l):
                 return(mid)

        # temporary l is smaller than l so ignore left-hand and go to other side.
         if l_temp < l:
            start = mid+1

        # temporary l is greater than l so ignore right-hand and go to other side.
         if l_temp > l:

             # whenever its possible to f be greater than l, we must ensure that
             # we are choosing smallest f among those which are greater than l.
             if find_possible_f(mid-1) > l:
                end = mid-1
             else:
                 return mid
            
# Get inputs from the user
user_input= input().split()
l = int(user_input[0])
m = int(user_input[1])


print(find_minimum_f(l=l, m=m, start=m, end=l))



