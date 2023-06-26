#PUSH_SWAP  

Sort a given stack with the following constraints :
- There are 2 stacks A and B
-

-> To compile :  
$> make

-> Run the program with random numbers :
$> ./push_swap $(shuf -i 1-500 -n 100 | tr '\n' ' ')
ou
$> ARG=$(shuf -i 1-500 -n 100 | tr '\n' ' ') && ./push_swap $ARG
