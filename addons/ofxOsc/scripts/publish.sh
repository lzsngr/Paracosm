#!/bin/bash

if [ ! $# -eq 1 ]; then
	echo usage: $0 \<version tag eg 0.4\>
	exit
fi

echo removing old at http://damian.dreamhosters.com/svn/public/ofxOsc/v$1
svn rm http://damian.dreamhosters.com/svn/public/ofxOsc/v$1 http://damian.dreamhosters.com/svn/public/ofxOsc/latest -m"removed old"
echo mkdir http://damian.dreamhosters.com/svn/public/ofxOsc/v$1
svn mkdir http://damian.dreamhosters.com/svn/public/ofxOsc/v$1 -m"preparing for new"
echo copy http://damian.dreamhosters.com/svn/projects/ofxOsc to http://damian.dreamhosters.com/svn/public/ofxOsc/v$1
svn cp http://damian.dreamhosters.com/svn/projects/ofxOsc http://damian.dreamhosters.com/svn/public/ofxOsc/v$1 -m"publishing at v$1"
echo copy http://damian.dreamhosters.com/svn/projects/ofxOsc to http://damian.dreamhosters.com/svn/public/ofxOsc/latest
svn cp http://damian.dreamhosters.com/svn/projects/ofxOsc http://damian.dreamhosters.com/svn/public/ofxOsc/latest -m"publishing v$1 as latest"



