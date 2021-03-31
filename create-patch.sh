#!/bin/sh
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

# Environment #################################################################
. ./template.env

_template_check_env

# Inputs ######################################################################
if [ -z $2 ]; then
    TEMPLATE=$DEFAULT_TEMPLATE
else
    TEMPLATE=$2
fi
if [ -z $1 ]; then
    PROJECT=$TEMPLATE
else
    PROJECT=$1
fi

if [ ! -d "$WORKSPACE/$PROJECT" ]; then
    echo "\"$WORKSPACE/$PROJECT\" does not exist, exiting"
    exit
fi
if [ ! -d "templates/$TEMPLATE" ]; then
    echo "template \"$TEMPLATE\" does not exist, exiting"
    exit
fi

###############################################################################
THERE=`pwd`
cd $WORKSPACE/$PROJECT && make erase
cd $THERE

# DANGEROUS, we need to create a project with the same name, so copy the
# project we want to create the patch for.
X=`date +%Y%m%d-%H%M%S`
mv $WORKSPACE/$PROJECT "$WORKSPACE/$PROJECT""-$X"

./create-project.sh $PROJECT $TEMPLATE

# thus pathes are clearer in patch files
cd "$WORKSPACE"

CREATE_PATCH_REVIEW=1
if [ ! -z $CREATE_PATCH_REVIEW ]; then
    meld "$PROJECT" "$PROJECT""-$X"
fi

# Whole project patch
#diff -Naur $PROJECT "$PROJECT""-$X" > "$THERE/$PROJECT"_complete.patch

# Main patch to apply to the template
diff -Naur "$PROJECT"/Core "$PROJECT""-$X"/Core \
           > "$THERE/$PROJECT"_Core.patch

# patches to keep around if not empty !
diff -Naur "$PROJECT"/Drivers "$PROJECT""-$X"/Drivers \
           > "$THERE/$PROJECT"_Drivers.patch
diff -Naur "$PROJECT"/Utilities "$PROJECT""-$X"/Utilities \
           > "$THERE/$PROJECT"_Utilities.patch
if [ -d "$PROJECT""-$X"/Middlewares ]; then
    diff -Naur "$PROJECT"/Middlewares "$PROJECT""-$X"/Middlewares \
               > "$THERE/$PROJECT"_Middlewares.patch
fi

# makefiles, gdbinit, ld files ...
diff -Naur -x Core -x Drivers -x Utilities -x Middlewares \
           -x .settings -x .project -x .cproject -x *.launch \
         "$PROJECT" "$PROJECT""-$X" > "$THERE/$PROJECT"_make.patch

diff -Naur -x Core -x Drivers -x Utilities -x Middlewares \
           -x *.mk -x Makefile -x gdbinit -x *.ld \
         "$PROJECT" "$PROJECT""-$X" > "$THERE/$PROJECT"_cube.patch

cd $THERE
rm -rf "$WORKSPACE/$PROJECT"
mv "$WORKSPACE/$PROJECT""-$X" "$WORKSPACE/$PROJECT"
find . -size 0 -name "*.patch" -exec rm -v '{}' \;

# how to detect file/symbol named as the project ?
#grep -Hn $PROJECT *.patch | grep -v "diff -Naur $PROJECT"


ls -l "$PROJECT"_*.patch

