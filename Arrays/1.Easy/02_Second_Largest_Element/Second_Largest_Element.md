# Second Smallest Element &  Second Largest Element 

## Brute Solution

### Approach

- Sort the array
- for 2nd smallest do ""arr[1]""
- for 2nd largest do ""arr[n-2]""
##
## Optimal 

### Approach

#### For second smallest

- initalize 
  ```cpp
  int small = INT_MAX;
  int second_small = INT_MAX;
  ```
- Swap the values of small and second_small accoringly while traversing the array
  ```cpp
  if (arr[i] < small) {
    second_small = small;
    small = arr[i];
  } 
  ```
  ```cpp
  else if (arr[i] < second_small && arr[i] != small) {
      second_small = arr[i];
  }
  ```
##

#### For second largest
- same as the second largest with `INIT_MIN` for both large and second_large

