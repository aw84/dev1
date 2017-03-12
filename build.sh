#!/bin/sh

BIN=g++

INCLUDE=./

EXTRA_SWITCHES='-Wall -pedantic'

$BIN $EXTRA_SWITCHES -I$INCLUDE -c Server.cpp -o Server.o
$BIN $EXTRA_SWITCHES -I$INCLUDE -c Reply.cpp -o Reply.o
