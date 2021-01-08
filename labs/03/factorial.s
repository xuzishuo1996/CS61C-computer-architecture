.data
n: .word 8

.text
main:
    la t0, n
    lw a0, 0(t0)  # a0 = n;  (input argument)
    jal ra, factorial   # invoke factorial

    addi a1, a0, 0
    addi a0, x0, 1  #sequence of these 2 lines matters
    ecall # Print Result(print a0)

    addi a0, x0, 10
    ecall # Exit

factorial:  #a0---result after every step  t1---number(j)
    # YOUR CODE HERE
    addi t2, x0, 1  #for a0 == 1 and t1 == 1
    beq a0, t2, result
    addi t1, a0, -1     # t1 = a0 - 1
loop:
    beq t1, t2, result # if (j == 1)
    mul a0, a0, t1    # result *= j;
    addi t1, t1, -1   # j--
    j loop  #
result:
    jr ra # back to main(the place where invokation of fac took place)
