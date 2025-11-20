#!/bin/bash

sudo apt-get update
sudo apt-get install -y \
    g++ \
    make \
    libpapi-dev \
    libjemalloc-dev \
    bear \
    ccache \
    libboost-system-dev \
    libboost-thread-dev 