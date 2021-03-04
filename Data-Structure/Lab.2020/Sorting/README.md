## 排序题目 Sorting

**Holiday Hotel**

**Description**

Mr. and Mrs. Smith are going to the seaside for their holiday. Before they start off, they need to choose a hotel. They got a list of hotels from the Internet, and want to choose some candidate hotels which are cheap and close to the seashore. A candidate hotel M meets two requirements: 

1. Any hotel which is closer to the seashore than M will be more expensive than M. 
2. Any hotel which is cheaper than M will be farther away from the seashore than M.

**Input**

There are several test cases. The first line of each test case is an integer N (1 <= N <= 10000), which is the number of hotels. Each of the following N lines describes a hotel, containing two integers D and C (1 <= D, C <= 10000). D means the distance from the hotel to the seashore, and C means the cost of staying in the hotel. You can assume that there are no two hotels with the same D and C. A test case with N = 0 ends the input, and should not be processed.

**Output**

For each test case, you should output one line containing an integer, which is the number of all the candidate hotels.

**Sample Input**

```
5
300 100
100 300
400 200
200 400
100 500
0
```

**Sample Output**

```
2
```
