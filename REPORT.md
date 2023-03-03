# CMSC 701 Homework 1 Report

[Link](https://github.com/DDXPP/CMSC701_HW1) to repo



Commit hash: d14266bc98e1c1d90a64518dd29c3a5c54f21aa4

https://github.com/DDXPP/CMSC701_HW1/commit/d14266bc98e1c1d90a64518dd29c3a5c54f21aa4

 

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

- Given the scaling above, how large of a genome do you think you could construct the suffix array for on a machine with 32GB of RAM

## Part (b): querying the suffix array

### (1) Challenges

The most challenging part to me was to find a way to record multiple hits. When I first started implementing the naive solution, I followed the algorithm on the lecture slides, but it always stoped after hitting the first match. Since hits are always consecutive in the suffix array, I just need to find the left and right bound of the indexes of the hits in the suffix array. To get the left bound, instead of using the query string, I used a string that has one more character appended to the end of the query string, and that appended character is "smaller" than (i.e., has a smaller ASCII code than) any characters that could appear in the reference string, which in this case is '`$`'. In this way, by querying this new string, I will always get the match with the smallest index. Similarly, to get the right bound, this character can be any character that is larger than '`z`'. After getting the left and right bound of the indexes, the positions of the hits in the original text would be `suffix_array[index]` for each `index` in the range of `[left_bound, right_bound)`. 

### (2) Performance Analysis

- Queries of different length &  `naive`  vs `simpleaccel` 

  - NC_001802.1 (9 kb)

  | Query length | naive        | simpaccel    |
  | ------------ | ------------ | ------------ |
  | 10           | 1.5875e-05 s | 0.0003915 s  |
  | 100          | 1.4583e-05 s | 9.6583e-05 s |
  | 1000         | 1.725e-05 s  | 2.9625e-05 s |
  | 5000         | 3.1e-05 s    | 2.4333e-05 s |

  - NC_007795.1 (2.9 MB)

  | Query length | naive        | simpaccel   |
  | ------------ | ------------ | ----------- |
  | 10           | 0.00447137 s | 0.0157744 s |
  | 100          | 0.00587504 s | 0.0199867 s |
  | 1000         | 0.00654696 s | 0.0247351 s |
  | 10000        | 0.00453758 s | 0.0155677 s |
  | 100000       | 0.00445667 s | 0.0233038 s |
  | 500000       | 0.00597654 s | 0.0468213 s |

  - NC_003070.9 (30.8 MB)

  | Query length | naive       | simpaccel  |
  | ------------ | ----------- | ---------- |
  | 10           | 0.0343952 s | 0.146011 s |
  | 100          | 0.0297995 s | 0.148972 s |
  | 1000         | 0.0294769 s | 0.141237 s |
  | 10000        | 0.0284526 s | 0.150314 s |
  | 100000       | 0.0331082 s | 0.153611 s |
  | 1000000      | 0.0309477 s | 0.198005 s |
  | 5000000      | 0.0334384 s | 0.467181 s |

- How does the speed further compare when not using a prefix lookup table versus using a prefix lookup table with different values of `k`?

  - Test on NC_003070.9 (30.8 MB)

  | Query length | naive (no preftab) | naive (k=2) | naive (k=4) | naive (k=6) | naive (k=8)  |
  | ------------ | ------------------ | ----------- | ----------- | ----------- | ------------ |
  | 10           | 0.0343952 s        | 0.0342457 s | 0.0302296 s | 0.0309253 s | 0.0261286 s  |
  | 100          | 0.0297995 s        | 0.033441 s  | 0.036452 s  | 0.0359773 s | 0.00842967 s |
  | 1000         | 0.0294769 s        | 0.0378476 s | 0.0353955 s | 0.023486 s  | 0.0178751 s  |
  | 10000        | 0.0284526 s        | 0.0468293 s | 0.0386028 s | 0.0298618 s | 0.0228138 s  |
  | 100000       | 0.0331082 s        | 0.0335216 s | 0.0338982 s | 0.0233689 s | 0.006043 s   |
  | 1000000      | 0.0309477 s        | 0.0393858 s | 0.0470415 s | 0.0367223 s | 0.0189974 s  |
  | 5000000      | 0.0334384 s        | 0.0301509 s | 0.0298986 s | 0.0232732 s | 0.0199204 s  |

  | Query length | simpaccel (no preftab) | simpaccel (k=2) | simpaccel (k=4) | simpaccel (k=6) | simpaccel (k=8) |
  | ------------ | ---------------------- | --------------- | --------------- | --------------- | --------------- |
  | 10           | 0.146011 s             | 0.1737 s        | 0.107652 s      | 0.0930255 s     | 0.101813 s      |
  | 100          | 0.148972 s             | 0.152657 s      | 0.13058 s       | 0.131504 s      | 0.0312648 s     |
  | 1000         | 0.141237 s             | 0.17904 s       | 0.10335 s       | 0.106558 s      | 0.070357 s      |
  | 10000        | 0.150314 s             | 0.193296 s      | 0.112921 s      | 0.112231 s      | 0.0962014 s     |
  | 100000       | 0.153611 s             | 0.183536 s      | 0.143058 s      | 0.100107 s      | 0.0572642 s     |
  | 1000000      | 0.198005 s             | 0.235825 s      | 0.194576 s      | 0.158821 s      | 0.130897 s      |
  | 5000000      | 0.467181 s             | 0.452442 s      | 0.407267 s      | 0.371217 s      | 0.358981 s      |

​	From the table we can see that using a prefix lookup table will increase the speed, for both `naive` and `simpaccel` query mode. With the increase of `k`, the query will be faster; however, the increase in speed is not drastic. 

- Given the scaling above, and the memory requirements of each type of index, what kind of tradeoff do you personally think makes sense in terms of using more memory in exchange for faster search.



