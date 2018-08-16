len 20

input o
tape o

state read {
    o: o, R, read
    .: ., L, minus
}

state minus {
    o: ., L, accept
    .: ., L, reject
}

state accept = accept
state reject = reject

start read