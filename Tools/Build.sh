#!/usr/bin/env bash

root=$(dirname $0)

cd $root

make $1

cd -
