all: Viterbi

Viterbi:
	gcc -I . -m32 -O2 mr*.o Comm.c Paillier.c IntOps.c FLOps.c Data.c Viterbi.c -lm

