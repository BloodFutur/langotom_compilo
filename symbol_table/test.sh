#!/bin/bash

TMP=`mktemp`

trap "exit 1" TERM
export SPID=$$ # Script PID

function err() {
  echo $1
  make clean
  kill -s TERM $SPID
  #exit 1
}

make all || (err "step invalid: make")

for f in ../samples/*.c; do
    echo "Testing $f" 
    ./c < $f
done

