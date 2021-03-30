#!/bin/bash
##
#    Copyright 2021 ENEGENO
# 
#   Licensed under the Apache License, Version 2.0 (the "License");
#   you may not use this file except in compliance with the License.
#   You may obtain a copy of the License at
# 
#       http://www.apache.org/licenses/LICENSE-2.0
# 
#   Unless required by applicable law or agreed to in writing, software
#   distributed under the License is distributed on an "AS IS" BASIS,
#   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#   See the License for the specific language governing permissions and
#   limitations under the License.
# 
##

echo "/*"                     >  license.h
cat license.x | sed 's/^/ */' >> license.h
echo " */"                    >> license.h

LICENSE_LINE_NB=`wc -l license.h | awk -F' ' '{print $1}'`

find templates -name "*.[chs]" | while read FILE; do
    X=`head -n $LICENSE_LINE_NB $FILE | diff - license.h`
    if [ ! -z "$X" ]; then
        Y=`grep -i STMicro $FILE`
        if [ ! -z "$Y" ]; then
            echo "$FILE copyrighted by STMicro ?"
        else
            echo "license missing in file $FILE"
        fi
    fi
done

rm license.h

###############################################################################

echo "##"                     >  license.mk
cat license.x | sed 's/^/# /' >> license.mk
echo "##"                     >> license.mk

LICENSE_LINE_NB=`wc -l license.mk | awk -F' ' '{print $1}'`

find templates -name "*.mk" | while read FILE; do
    Y=`head -n $LICENSE_LINE_NB $FILE | diff - license.mk`
    if [ ! -z "$Y" ]; then
        echo "license missing in file $FILE"
    fi
done

###############################################################################

LICENSE_LINE_NB=`wc -l license.mk | awk -F' ' '{print $1}'`

find . -maxdepth 1 -name "*.sh" | while read FILE; do
    Y=`tail -n +2 $FILE | head -n $LICENSE_LINE_NB | diff - license.mk`
    if [ ! -z "$Y" ]; then
        echo "license missing in file $FILE"
    fi
done

rm license.mk

