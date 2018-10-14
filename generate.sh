#!/usr/bin/bash

COUNT=$1
FILE=$2

base64 /dev/urandom | tr -dc 'ACGT' | head -c $COUNT > $FILE
