#!/bin/sh
test -d "src" && SRC='src/*.c,*.cpp' || SRC=""
test -d "include" && INCLUDE='include/*.h,*.hpp' || INCLUDE=""
test -d "test" && TEST='src/*.c,*.cpp' || TEST=""
test -d "laba3" && LABA3='laba3/*.c,*.cpp' || LABA3=""
test -d "laba4" && LABA4='laba4/*.c,*.cpp' || LABA4=""
test -d "laba5" && LABA5='laba5/*.c,*.cpp' || LABA5=""
astyle --project -r $SRC $INCLUDE $TEST $LABA3 $LABA4 $LABA5
