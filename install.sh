#!/bin/bash

echo 'Recommended to run this script as root.'
./build.sh
cp build/lightfetch /usr/bin/
echo 'Installed lightfetch successfully!'
