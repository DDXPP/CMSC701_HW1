# CMSC 701 Homework 1

## Programming Language

This homework is written in C++.

## References

The resources I consulted when working on this assignment include: 

- Provided [C++ starter code](https://github.com/rob-p/cpp_sa_starter_proj)
- Lecture [slides](https://rob-p.github.io/CMSC701_S23/static_files/presentations/CMSC701_S23_3.pdf) on suffix arrays (for naive algorithms)
- Ben Langmead's original [slides](https://www.cs.jhu.edu/~langmea/resources/lecture_notes/suffix_arrays.pdf) on suffix arrays (for simpaccel algorithms)

- [Standard C++ library reference](https://cplusplus.com/reference/) 
- Cereal library [documentation](https://uscilab.github.io/cereal/quickstart.html) (for serialization)



## How to run

To build a suffix array with a given sequence in `FASTA` format , run the command below:

```
./buildsa reference output
```

Alternatively, to build a suffix array with a given sequence in `FASTA` format  and generate a prefix table of length `k`, run the command below:

```
./buildsa --preftab k reference output_buildsa
```

To perform queries against the generated suffix array, run the command below (Query mode can be either `naive` or `simpaccel`):

```
./querysa index queries query_mode output_querysa
```

