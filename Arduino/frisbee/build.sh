#!/bin/bash
arduino-cli compile -b esp8266:esp8266:d1 -v

while getopts "u" option ; do
case ${option} in
  u )
  arduino-cli upload -b esp8266:esp8266:d1 -v -p 10.10.10.2
  ;;
esac
done
#screen -h 1000 /dev/ttyUSB0 9600
