#!/bin/sh

set -e

./kdmf --build-index smalldata smalldata.tr.bin
./kdmf --build-index smalldata smalldata.te.bin
./kdmf --train --tr-rmse --obj -k 40 -s 4 -p 0.05 -q 0.05 -g 0.003 -v smalldata.te.bin smalldata.tr.bin model
./kdmf --predict smalldata.te.bin model output
