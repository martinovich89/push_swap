LANCER PUSH_SWAP AVEC NOMBRES ALEATOIRES :
./push_swap $(shuf -i 1-500 -n 100 | tr '\n' ' ')
ou
ARG=$(shuf -i 1-500 -n 100 | tr '\n' ' ') && ./push_swap $ARG