#add one to input tape

len 100

input 1
tape 1

state one {
    1: 1, R, one
    .: 1, R, zero
}

state zero = accept

start one

#program end.
