# CMSC 701 Homework 1 Report

## Part (a): constructing the suffix array and an auxiliary index

### (1) Challenges

One of the most challenging parts of implementing `buildsa` is coming up with a proper way to store the prefix table. I ended up using `unordered_map<string, pair<int, int>>`. The keys of the map are prefixes, and the values are pairs of `int`'s representing left and right bounds respectively. In addition, I also had some difficulties dealing with serialization using cereal, specifically with how to serialize `unique_ptr`. 

### (2) Performance Analysis

For performance analysis, I chose four reference strings with various size (9 KB - 30.8 MB). I built the SA for each reference string five times, and recorded the average build time.

|                     | NC_001802.1 | NC_007795.1 | U00096.2 | NC_003070.9 |
| ------------------- | ----------- | ----------- | -------- | ----------- |
| Reference file size | 9 KB        | 2.9 MB      | 4.7 MB   | 30.8 MB     |
| Build time of SA    | 0.001s      | 0.13s       | 0.20s    | 1.39s       |
| Output file size    | 83 KB       | 25.4 MB     | 41.8 MB  | 273.8 MB    |

- **Build time**:  from the chart we can see that build time and reference string size have a near-linear relationship. 

- **Resulting serialized file size**: the output file size is roughly $9$ times the size of the reference string. 

- **Test with** $k$ :

  - Build time

  | k    | NC_001802.1 | NC_007795.1 | U00096.2 | NC_003070.9 |
  | ---- | ----------- | ----------- | -------- | ----------- |
  | 2    | 0.007 s     | 0.97 s      | 1.64 s   | 11.64 s     |
  | 4    | 0.007 s     | 1.06 s      | 1.75 s   | 12.42 s     |
  | 6    | 0.008 s     | 1.07 s      | 1.81 s   | 13.16 s     |
  | 8    | 0.013 s     | 1.21 s      | 2.06 s   | 13.61 s     |

  - Resulting serialized file size

  | k    | NC_001802.1 | NC_007795.1 | U00096.2 | NC_003070.9 |
  | :--- | ----------- | ----------- | -------- | ----------- |
  | 2    | 83 KB       | 25.4 MB     | 41.8 MB  | 273.9 MB    |
  | 4    | 88 KB       | 25.4 MB     | 41.8 MB  | 273.9 MB    |
  | 6    | 146 KB      | 25.5 MB     | 41.8 MB  | 275 MB      |
  | 8    | 268 KB      | 26.9 MB     | 43.3 MB  | 292 MB      |

  From my results, we can see that it takes a lot longer to build prefix table than to build suffix array. With the increase of k, we can barely see any increase in output file size, and the increase in build time is also marginal. 

- On machine with 32 GB RAM:

  - 


- Given the scaling above, how large of a genome do you think you could construct the suffix array for on a machine with 32GB of RAM, why?

## Part (b): querying the suffix array

### (1) Challenges

The most challenging part to me was to find a way to record multiple hits. When I first started implementing the naive solution, I followed the algorithm on the lecture slides, but it always stoped after hitting the first match. Since hits are always consecutive in the suffix array, I just need to find the left and right bound of the indexes of the hits in the suffix array. To get the left bound, instead of using the query string, I used a string that has one more character appended to the end of the query string, and that appended character is "smaller" than (i.e., has a smaller ASCII code than) any characters that could appear in the reference string, which in this case is '`$`'. In this way, by querying this new string, I will always get the match with the smallest index. Similarly, to get the right bound, this character can be any character that is larger than '`z`'. After getting the left and right bound of the indexes, the positions of the hits in the original text would be `suffix_array[index]` for each `index` in the range of `[left_bound, right_bound)`. 

### (2) Performance Analysis

For references of various size:

- How long does query take on references of different size, and on queries of different length?
- How does the speed of the `naive` lookup algorithm compare to the speed of the `simpleaccel` lookup algorithm?
- How does the speed further compare when not using a prefix lookup table versus using a prefix lookup table with different values of `k`?
- Given the scaling above, and the memory requirements of each type of index, what kind of tradeoff do you personally think makes sense in terms of using more memory in exchange for faster search.



