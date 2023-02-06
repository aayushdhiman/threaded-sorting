# Concurrent Sorting

Compares threaded merge sorts (tmsort.c) to a standard single threaded merge sort (msort.c). Written for a systems class. 

Completed 11/16/2022.

The [Makefile](Makefile) contains the following targets:

- `make all` - compile `msort` and `tmsort`
- `make msort` and `make tmsort` - compile the individual programs
- `make diff-N` - compile and run a diff test, comparing the results of `msort` and `tmsort` on a random input. `N` needs to be replaced by a positive integer. E.g., `make diff-100`.
- `make clean` - perform a minimal clean-up of the source tree

Note: This Makefile asks gcc to convert warnings into errors to help draw your attention to them.
