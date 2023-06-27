#PUSH_SWAP  

Sort a given stack with the following constraints :  
  There are 2 stacks : A and B  
  Only these operations can be performed :  
  - swap the 2 first elements of a stack  
  - rotate the first element to the end of a stack  
  - push the first element of a stack to the first position in the other stack

My approach has been to take 5 days to think and test (with speculative standard cases) about solutions before deciding which one to use.
I chose to use something relatively close to the merge sort. Didn't know at that time what it was called, but figured out once it was done.
Overall, this was a very fun project to me, and I'm quite proud having succeeded with my own solution, passing 4/5 performance tests.

-> To compile :  
$> make

-> Run the program with random numbers :
$> ./push_swap $(shuf -i 1-500 -n 100 | tr '\n' ' ')
ou
$> ARG=$(shuf -i 1-500 -n 100 | tr '\n' ' ') && ./push_swap $ARG
