In order to use this, please install everything, then

mkdir build && cd build

cmake ..

then use 

make

Launch sequence: server -> client

Exit sequence: client -> server

If exit sequence is broken, then 

killall -9 client/server and wait 1-2 min

Limitations: 1024 bytes for file content

0 to get file contents

1 to list files

2 to put file with its name (extension together with name)

3 to delete file (full name with extension)

4 to get file info (full name with extension)
