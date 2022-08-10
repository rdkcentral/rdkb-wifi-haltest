#!/usr/bin/env bash

# Clone the HTS Requirements
TEST_REPO=git@github.com:comcast-sky/rdk-components-haltest-core.git

# This will look up the last tag in the git repo, depending on the project this may require modification
PROJECT_VERSION=feature/RDKB-43403_v4_hal_creation

# Check if the common document configuration is present, if not clone it
if [ -d "./hts-core" ]; then
    make -C . -f Makefile $@
else
    echo "Cloning Hal Core Test System"
    git clone ${TEST_REPO} hts-core
    cd ./hts-core
    git flow init -d
    git checkout ${PROJECT_VERSION}
    ./hts.sh
    cd ..
    ./${0}
fi