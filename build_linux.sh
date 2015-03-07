#!/bin/bash      

premake4  gmake
make -C build config=debug verbose=false -j4
