#!/bin/sh

scons $* test && (cd test && ./CoronaTest)
