#!/bin/sh

set -e

./kdmf --build-index dataset dataset_tr_index
./kdmf --build-index dataset dataset_te_index
./kdmf --train --tr-rmse --obj -k 40 -s 4 -p 0.05 -q 0.05 -g 0.003 -v dataset_te_index dataset_tr_index model
./kdmf --predict dataset_te_index model output
