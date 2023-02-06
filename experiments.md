# Threaded Merge Sort Experiments


## Host 1: XOA VM

- CPU: Intel(R) Xeon(R) CPU E5-2690 v3 @ 2.60GHz
- Cores: 2
- Cache size (if known): 64 MB
- RAM: 4 GB
- Storage (if known): 40 GB
- OS: Ubuntu

### Input data

*Briefly describe how large your data set is and how you created it. Also include how long `msort` took to sort it.*
The input data was 100,000,000 digits long. It was generated using shuf -i1-100000000. msort took 22.811799 seconds to complete.

### Experiments

*Replace X, Y, Z with the number of threads used in each experiment set.*

#### 1 Thread

Command used to run experiment: `MSORT_THREADS=1 ./tmsort 100000000 < hundred-million.txt > /dev/null`

Sorting portion timings:

1. 74.551345 seconds
2. 69.121079 seconds
3. 68.777796 seconds
4. 70.591885 seconds

#### 2 Threads

Command used to run experiment: `MSORT_THREADS=2 ./tmsort 100000000 < hundred-million.txt > /dev/null`

Sorting portion timings:

1. 67.591953 seconds
2. 61.282131 seconds
3. 62.382901 seconds
4. 53.413844 seconds

#### 4 Threads

Command used to run experiment: `MSORT_THREADS=4 ./tmsort 100000000 < hundred-million.txt > /dev/null`

Sorting portion timings:

1. 51.552367 seconds
2. 62.946443 seconds
3. 61.087187 seconds
4. 53.975625 seconds

*repeat sections as needed*

## Host 2: Khoury Machine

*use Host 1 template to fill this section*

- CPU: Intel(R) Xeon(R) Silver 4214R CPU @ 2.40GHz
- Cores: 12
- Cache size (if known): 
- RAM: 383 GB
- Storage (if known): 
- OS: GNU/Linux

### Input data

*Briefly describe how large your data set is and how you created it. Also include how long `msort` took to sort it.*
The input data was 100,000,000 digits long. It was generated using shuf -i1-100000000. msort took 22.811799 seconds to complete.

### Experiments

*Replace X, Y, Z with the number of threads used in each experiment set.*

#### 1 Thread

Command used to run experiment: `MSORT_THREADS=1 ./tmsort 100000000 < hundred-million.txt > /dev/null`

Sorting portion timings:

1. 34.345346 seconds
2. 34.526343 seconds
3. 34.487307 seconds
4. 34.499425 seconds

#### 2 Threads

Command used to run experiment: `MSORT_THREADS=2 ./tmsort 100000000 < hundred-million.txt > /dev/null`

Sorting portion timings:

1. 18.285574 seconds
2. 18.377517 seconds
3. 18.289212 seconds
4. 18.080519 seconds

#### 12 Threads

Command used to run experiment: `MSORT_THREADS=12 ./tmsort 100000000 < hundred-million.txt > /dev/null`

Sorting portion timings:

1. 11.179919 seconds
2. 10.804876 seconds
3. 10.839081 seconds
4. 10.934420 seconds

## Observations and Conclusions

*Reflect on the experiment results and the optimal number of threads for your concurrent merge sort implementation on different hosts or platforms. Try to explain why the performance stops improving or even starts deteriorating at certain thread counts.*

From the experiment, it is clear to see that there are many factors that affect the performance of the merge sort. First, there is the number on threads. On the XOA VM, we can observe that the number of threads significantly improved the runtime of the program, from around 75 seconds to 50 seconds. The performance of the program relies heavily on the hardware of the machine that it is running on as well though, as we can see from the comparision between the XOA VM and the Khoury Machine. The increased number of cores made the program much quicker to run, and it also showed less improvement by increasing the threads. This shows that the runtime of the sort has an asymptotic limit where it approaches the best runtime possible. The performance of the sort actually decreases if there are too many threads, as these threads contest each other for actual memory, which in turn hurts the performance of the program.

