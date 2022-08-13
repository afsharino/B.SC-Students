import sys
sys.setrecursionlimit(10000)
def isSubSequence(string1, string2, m, n):
	# Base Cases
	if m == 0:
		return True
	if n == 0:
		return False

	# If last characters of two
	# strings are matching
	if string1[m-1] == string2[n-1]:
		return isSubSequence(string1, string2, m-1, n-1)

	# If last characters are not matching
	return isSubSequence(string1, string2, m, n-1)


# Find all subsequences in a string and store in a dictionary
dictionary = {}
def find_all_subsequences(s, f):
    if(len(s) == 0):
        if f not in dictionary.keys():
            if len(f) < 8:
                dictionary[f] = 1
        else:
            if len(((int(dictionary[f])+1) * str(f))) < 8:
                dictionary[f] += 1

        return
    
    find_all_subsequences(s[1:], f+s[0])

    find_all_subsequences(s[1:], f)


# main 
s = input()
f = ""
k = int(input())
find_all_subsequences(s, f)

dictionary2 = {}
for i in dictionary.keys():
    string1 = int(dictionary[i]) * str(i)
    string2 = s
    if isSubSequence(string1, string2, len(string1), len(string2)):
        dictionary2[i] = dictionary[i]

result = []
# select those with value k
for seq in dictionary2.keys():
    if dictionary2[seq] == k:
        result.append(seq)

if len(result) == 0:
    print("Not Exist")
else:
    #sort them and choose the longest one
    final_result = []
    for i in range(len(result)):
        if len(result[i]) == len(result[0]):
            final_result.append(result[i])

    if len(final_result) == 1:
        print(final_result[0])
    else:
        final_result.sort()
        print(final_result[-1])