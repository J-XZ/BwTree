#!/bin/bash

make clean
make prepare 
bear -- ccache make -j