#PUSH_SWAP  

Sort a given stack with the following constraints :  
  There are 2 stacks : A and B  
  Only these operations can be performed :  
  - swap the 2 first elements of a stack  
  - rotate the first element to the end of a stack  
  - push the first element of a stack to the first position in the other stack

-> To compile :  
$> make

-> Run the program with random numbers :
$> ./push_swap $(shuf -i 1-500 -n 100 | tr '\n' ' ')
ou
$> ARG=$(shuf -i 1-500 -n 100 | tr '\n' ' ') && ./push_swap $ARG
