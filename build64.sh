rm -r -f build64
rm -r -f thrift
rm -r -f api

git clone https://github.com/pvl1175/thrift-interface-definitions
mkdir api
thrift -r -gen cpp:no_skeleton,pure_enums,moveable_types -out ./api ./thrift-interface-definitions/api.thrift

git clone https://github.com/pvl1175/thrift
cd thrift

cd ..
mkdir build64
cd build64

cmake ..
cmake  --build . --config Debug
cmake  --build . --config Release




