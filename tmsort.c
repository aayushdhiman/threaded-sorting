/** 
 * Threaded Merge Sort
 *
 * Modify this file to implement your multi-threaded version of merge sort. 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#include <unistd.h>

#include <assert.h>

#include <pthread.h>

#define tty_printf(...) (isatty(1) && isatty(0) ? printf(__VA_ARGS__) : 0)

#ifndef SHUSH
#define log(...) (fprintf(stderr, __VA_ARGS__))
#else 
#define log(...)
#endif

typedef struct total_arr{
  long *arr;
}total_t;

typedef struct mergeData {
  total_t nums_t;
  int from_t;
  int to_t;
  long* target_t;
}mergeData_t;


/** The number of threads to be used for sorting. Default: 1 */
int thread_count = 1;

/**
 * Compute the delta between the given timevals in seconds.
 */
double time_in_secs(const struct timeval *begin, const struct timeval *end) {
  long s = end->tv_sec - begin->tv_sec;
  long ms = end->tv_usec - begin->tv_usec;
  return s + ms * 1e-6;
}

/**
 * Print the given array of longs, an element per line.
 */
void print_long_array(const long *array, int count) {
  for (int i = 0; i < count; ++i) {
    printf("%ld\n", array[i]);
  }
}

/**
 * Merge two slices of nums into the corresponding portion of target.
 */
void merge(long nums[], int from, int mid, int to, long target[]) {
  int left = from;
  int right = mid;

  int i = from;
  for (; i < to && left < mid && right < to; i++) {
    if (nums[left] <= nums[right]) {
      target[i] = nums[left];
      left++;
    }
    else {
      target[i] = nums[right];
      right++;
    }
  }
  if (left < mid) {
    memmove(&target[i], &nums[left], (mid - left) * sizeof(long));
  }
  else if (right < to) {
    memmove(&target[i], &nums[right], (to - right) * sizeof(long));
  }

}


/**
 * Sort the given slice of nums into target.
 *
 * Warning: nums gets overwritten.
 */
void* merge_sort_aux(void* arg){
  //printf("\nmege_sort_aux arrived::::::::::::::::::::::");
  mergeData_t *data = (mergeData_t *) malloc(sizeof(mergeData_t));
  *data = *((mergeData_t*)arg);
  //printf("\n from to in data is %d %d", data->from_t, data->to_t);
  //mergeData_t data = (mergeData_t*) arg;
  total_t fullArr = data->nums_t;
  //total_t fullArr = data.nums_t

  long* nums = fullArr.arr;
  int from = data->from_t;
  //int from = data.from_t;
  int to = data->to_t;
  //int to = data.to_t;
  long* target = data->target_t;
  //long* target = data.target_t;
  //printf("\n checking condition %d %d", to, from);
  if(to - from > 1) {
    int mid = (from + to) / 2;
    //printf("\nMID IS %d", mid);
    //printf("\nFROM IS %d", from);
    //printf("\nTO IS %d", to);

    //while(1) {
    //  if(pthread_mutex_trylock(*thread_count))
    //    break;
    //  sched_yield();
    //}
    total_t targetArr = {target};
    mergeData_t leftData = {targetArr, from, mid, nums};
    mergeData_t rightData = {targetArr, mid, to, nums};
    if(thread_count > 0){
      thread_count--;
      printf("\n THREAD CREATED \n");
      pthread_t leftThread;
      if(thread_count > 0) {
        printf("\n THREAD CREATED \n");
        thread_count --;
        //pthread_mutex_unlock(*thread_count);
        pthread_t rightThread;
        pthread_create(&leftThread, NULL, merge_sort_aux, &leftData);
        pthread_create(&rightThread, NULL, merge_sort_aux, &rightData);
        pthread_join(leftThread, 0);
        pthread_join(rightThread, 0);
      } else {
        //pthread_mutex_unlock(*thread_count);
        pthread_create(&leftThread, NULL, merge_sort_aux, &leftData);
        merge_sort_aux(&rightData);
        pthread_join(leftThread,0);
      }
    }else {
      //pthread_mutex_unlock(*thread_count);
      merge_sort_aux(&leftData);
      merge_sort_aux(&rightData);
    }

    
    //pthread_create(&leftThread, NULL, merge_sort_aux, &leftData);
    //pthread_create(&rightThread, NULL, merge_sort_aux, &rightData);
    
    //pthread_join(leftThread,0);
    //pthread_join(rightThread,0);
    merge(nums, from, mid, to, target);
    free(data);
  }
}
  
/*void merge_sort_aux(long nums[], int from, int to, long target[]) {
  if (to - from <= 1) {
    return;
  }

  int mid = (from + to) / 2;
  merge_sort_aux(target, from, mid, nums);
  merge_sort_aux(target, mid, to, nums);
  merge(nums, from, mid, to, target);
}
*/

/**
 * Sort the given array and return the sorted version.
 *
 * The result is malloc'd so it is the caller's responsibility to free it.
 *
 * Warning: The source array gets overwritten.
 */
long *merge_sort(long nums[], int count) {
  long *result = calloc(count, sizeof(long));
  assert(result != NULL);

  memmove(result, nums, count * sizeof(long));

  total_t firstNums = {nums};
  mergeData_t firstMerge = {firstNums, 0, count, result};
  thread_count--;
  pthread_t thread;

  pthread_create(&thread, NULL, merge_sort_aux, &firstMerge);
  pthread_join(thread, NULL);
  //  merge_sort_aux((void *) &firstMerge);
    
  // this needs to be set up with a struct 
  // merge_sort_aux(nums, 0, count, result);

  return result;
}

/**
 * Based on command line arguments, allocate and populate an input and a 
 * helper array.
 *
 * Returns the number of elements in the array.
 */
int allocate_load_array(int argc, char **argv, long **array) {
  assert(argc > 1);
  int count = atoi(argv[1]);

  *array = calloc(count, sizeof(long));
  assert(*array != NULL);

  long element;
  tty_printf("Enter %d elements, separated by whitespace\n", count);
  int i = 0;
  while (i < count && scanf("%ld", &element) != EOF)  {
    (*array)[i++] = element;
  }

  return count;
}

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <n>\n", argv[0]);
    return 1;
  }

  struct timeval begin, end;

  // get the number of threads from the environment variable SORT_THREADS
  if (getenv("MSORT_THREADS") != NULL)
    thread_count = atoi(getenv("MSORT_THREADS"));

  log("Running with %d thread(s). Reading input.\n", thread_count);

  // Read the input
  gettimeofday(&begin, 0);
  long *array = NULL;
  int count = allocate_load_array(argc, argv, &array);
  gettimeofday(&end, 0);

  log("Array read in %f seconds, beginning sort.\n", 
      time_in_secs(&begin, &end));
 
  // Sort the array
  gettimeofday(&begin, 0);
  long *result = merge_sort(array, count);
  gettimeofday(&end, 0);
  
  log("Sorting completed in %f seconds.\n", time_in_secs(&begin, &end));

  // Print the result
  gettimeofday(&begin, 0);
  print_long_array(result, count);
  gettimeofday(&end, 0);
  
  log("Array printed in %f seconds.\n", time_in_secs(&begin, &end));

  free(array);
  free(result);

  return 0;
}
