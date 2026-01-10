#! /bin/bash -e
tar -cJf firmware_for_RP2xxx.tar.xz  RP2xxx/build/*

# create linux binaries
make release_linux

# create windows binaries
mkdir binaries_for_Windows || /bin/true
zip -9 -r binaries_for_Windows.zip binaries_for_Windows/
