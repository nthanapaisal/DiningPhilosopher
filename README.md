# DiningPhilosophers

### Compile: 
    gcc file.c -o file.o -pthread
### Run: 
    ./file.o numThreads
### Run 100 times: 
    for i in {1...100}; do  ./file.o numThreads; done
### Make sure Order is correct for part 3: 
    ./file.o numThreads | grep "eating"

# Part 1:
  Create n threads
# Part 2:
  Use mutex locks to manage philophers eat order (non-order)
# Part 3:
  Use only 1 global mutex to manage philophers eat order (in-order)
# Part 4:
   Use mutex locks and conditional variables to manage philophers eat order (non-order)
