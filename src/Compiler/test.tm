#this is a test program
#add one to input tape

len 100

input 10
tape 10

state one {
    1: 1, R, one
    0: 1, R, zero
}

state zero = accept

start one

#program end.
