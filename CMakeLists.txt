cmake_minimum_required(VERSION 2.8.7 FATAL_ERROR)
project(HELLO_CPP)

include(ExternalProject)

add_custom_target(third)

ExternalProject_Add(
    google_gtest
    URL https://github.com/google/googletest/archive/release-1.8.0.zip
    PREFIX ${HELLO_CPP_SOURCE_DIR}/third/gtest
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=${HELLO_CPP_SOURCE_DIR}/third/gtest/build -DBUILD_SHARED_LIBS=OFF
)
add_dependencies(third google_gtest)

ExternalProject_Add(
    google_protobuf
    URL https://github.com/google/protobuf/archive/v3.5.2.zip
    PREFIX ${HELLO_CPP_SOURCE_DIR}/third/protobuf
    BUILD_IN_SOURCE true
    CONFIGURE_COMMAND ""
    BUILD_COMMAND sh autogen.sh && ./configure --prefix=${HELLO_CPP_SOURCE_DIR}/third/protobuf/build --disable-shared && make -j8
    INSTALL_COMMAND make install
)
add_dependencies(third google_protobuf)

ExternalProject_Add(
    boostorg_boost
    URL https://dl.bintray.com/boostorg/release/1.67.0/source/boost_1_67_0.tar.gz
    PREFIX ${HELLO_CPP_SOURCE_DIR}/third/boost
    BUILD_IN_SOURCE true
    CONFIGURE_COMMAND ""
    BUILD_COMMAND sh bootstrap.sh && ./b2 link=static -j8
    INSTALL_COMMAND ./b2 install --prefix=${HELLO_CPP_SOURCE_DIR}/third/boost/build
)
add_dependencies(third boostorg_boost)

ExternalProject_Add(
    peterscott_murmur3
    URL https://github.com/PeterScott/murmur3/archive/master.zip
    PREFIX ${HELLO_CPP_SOURCE_DIR}/third/murmur3
    BUILD_IN_SOURCE true
    CONFIGURE_COMMAND ""
    BUILD_COMMAND gcc -c murmur3.c && ar rcs libmurmur3.a murmur3.o
    INSTALL_COMMAND mkdir -p ../../build/{include,lib} && cp murmur3.h ../../build/include && cp libmurmur3.a ../../build/lib
)
add_dependencies(third peterscott_murmur3)

ExternalProject_Add(
    vipshop_hiredis_vip
    URL https://github.com/vipshop/hiredis-vip/archive/0.3.0.zip
    PREFIX ${HELLO_CPP_SOURCE_DIR}/third/hiredis-vip
    BUILD_IN_SOURCE true
    CONFIGURE_COMMAND ""
    BUILD_COMMAND make
    INSTALL_COMMAND PREFIX=${HELLO_CPP_SOURCE_DIR}/third/hiredis-vip/build make install
    COMMAND rm -rf ${HELLO_CPP_SOURCE_DIR}/third/hiredis-vip/build/lib/*.dylib
)
add_dependencies(third vipshop_hiredis_vip)

ExternalProject_Add(
    aerospike_aerospike_client_c
    GIT_REPOSITORY https://github.com/aerospike/aerospike-client-c.git
    PREFIX ${HELLO_CPP_SOURCE_DIR}/third/aerospike-client-c
    BUILD_IN_SOURCE true
    CONFIGURE_COMMAND ""
    BUILD_COMMAND make
    INSTALL_COMMAND ls target | xargs -I {} cp -r target/{}/ ${HELLO_CPP_SOURCE_DIR}/third/aerospike-client-c/build
    COMMAND rm -rf ${HELLO_CPP_SOURCE_DIR}/third/aerospike-client-c/build/lib/libaerospike.dylib
)
add_dependencies(third aerospike_aerospike_client_c)

# ExternalProject_Add(
#     nlohmann_json
#     URL https://github.com/nlohmann/json/archive/v3.1.2.zip
#     PREFIX ${HELLO_CPP_SOURCE_DIR}/third/json
#     CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=${HELLO_CPP_SOURCE_DIR}/third/json/build -DBUILD_SHARED_LIBS=OFF
# )
# add_dependencies(third nlohmann_json)

ExternalProject_Add(
    open_source_parses_jsoncpp
    URL https://github.com/open-source-parsers/jsoncpp/archive/1.8.4.zip
    PREFIX ${HELLO_CPP_SOURCE_DIR}/third/jsoncpp
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=${HELLO_CPP_SOURCE_DIR}/third/jsoncpp/build -DBUILD_SHARED_LIBS=OFF
)
add_dependencies(third open_source_parses_jsoncpp)

# ExternalProject_Add(
#     openssl_openssl
#     URL https://github.com/openssl/openssl/archive/OpenSSL_1_0_2.zip
#     PREFIX ${HELLO_CPP_SOURCE_DIR}/third/openssl
#     BUILD_IN_SOURCE true
#     CONFIGURE_COMMAND ./Configure darwin64-x86_64-cc --prefix=${HELLO_CPP_SOURCE_DIR}/third/openssl/build
# )
# add_dependencies(aerospike_aerospike_client_c openssl_openssl)

ExternalProject_Add(
    sparsehash_sparsehash
    URL https://github.com/sparsehash/sparsehash/archive/sparsehash-2.0.3.zip
    PREFIX ${HELLO_CPP_SOURCE_DIR}/third/sparsehash
    BUILD_IN_SOURCE true
    CONFIGURE_COMMAND ./configure --prefix=${HELLO_CPP_SOURCE_DIR}/third/sparsehash/build
    BUILD_COMMAND make
)
add_dependencies(third sparsehash_sparsehash)

ExternalProject_Add(
    google_double_conversion
    URL https://github.com/google/double-conversion/archive/v3.0.0.zip
    PREFIX ${HELLO_CPP_SOURCE_DIR}/third/double_conversion
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=${HELLO_CPP_SOURCE_DIR}/third/double_conversion/build
)
add_dependencies(third google_double_conversion)

ExternalProject_Add(
    google_gperftools
    URL https://github.com/gperftools/gperftools/archive/gperftools-2.7.zip
    PREFIX ${HELLO_CPP_SOURCE_DIR}/third/gperftools
    BUILD_IN_SOURCE true
    CONFIGURE_COMMAND ""
    BUILD_COMMAND sh autogen.sh && ./configure --prefix=${HELLO_CPP_SOURCE_DIR}/third/gperftools/build && make -j8
)
add_dependencies(third google_gperftools)

ExternalProject_Add(
    tessil_hopscotch_map
    URL https://github.com/Tessil/hopscotch-map/archive/v2.0.0.zip
    PREFIX ${HELLO_CPP_SOURCE_DIR}/third/hopscotch_map
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=${HELLO_CPP_SOURCE_DIR}/third/hopscotch_map/build
    INSTALL_COMMAND mkdir -p ${HELLO_CPP_SOURCE_DIR}/third/hopscotch_map/build/ && cp -r ${HELLO_CPP_SOURCE_DIR}/third/hopscotch_map/src/tessil_hopscotch_map/include ${HELLO_CPP_SOURCE_DIR}/third/hopscotch_map/build/
)
add_dependencies(third tessil_hopscotch_map)

# ExternalProject_Add(
#     facebook_folly
#     GIT_REPOSITORY https://github.com/facebook/folly.git
#     PREFIX ${HELLO_CPP_SOURCE_DIR}/third/folly
#     CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=${HELLO_CPP_SOURCE_DIR}/third/folly/build
# )
# add_dependencies(third facebook_folly)

set(CMAKE_CXX_FLAGS "-w -g -std=c++11")
set(CMAKE_CXX_FLAGS_RELEASE "-w -g -O2 -std=c++11")

include_directories(
    "${HELLO_CPP_SOURCE_DIR}/include"
    "${HELLO_CPP_SOURCE_DIR}/proto"
    "${HELLO_CPP_SOURCE_DIR}/third/boost/build/include"
    "${HELLO_CPP_SOURCE_DIR}/third/murmur3/build/include"
    "${HELLO_CPP_SOURCE_DIR}/third/gtest/build/include"
    "${HELLO_CPP_SOURCE_DIR}/third/protobuf/build/include"
    "${HELLO_CPP_SOURCE_DIR}/third/hiredis-vip/build/include"
    "${HELLO_CPP_SOURCE_DIR}/third/aerospike-client-c/build/include"
    "${HELLO_CPP_SOURCE_DIR}/third/jsoncpp/build/include"
    "${HELLO_CPP_SOURCE_DIR}/third/sparsehash/build/include"
    "${HELLO_CPP_SOURCE_DIR}/third/double_conversion/build/include"
    "${HELLO_CPP_SOURCE_DIR}/third/gperftools/build/include"
    "${HELLO_CPP_SOURCE_DIR}/third/hopscotch_map/build/include"
)

link_directories(
    "${HELLO_CPP_SOURCE_DIR}/third/gtest/build/lib"
    "${HELLO_CPP_SOURCE_DIR}/third/protobuf/build/lib"
    "${HELLO_CPP_SOURCE_DIR}/third/murmur3/build/lib"
    "${HELLO_CPP_SOURCE_DIR}/third/hiredis-vip/build/lib"
    "${HELLO_CPP_SOURCE_DIR}/third/aerospike-client-c/build/lib"
    "${HELLO_CPP_SOURCE_DIR}/third/jsoncpp/build/lib"
    "${HELLO_CPP_SOURCE_DIR}/third/sparsehash/build/lib"
    "${HELLO_CPP_SOURCE_DIR}/third/double_conversion/build/lib"
    "${HELLO_CPP_SOURCE_DIR}/third/gperftools/build/lib"
    "${HELLO_CPP_SOURCE_DIR}/third/hopscotch_map/build/lib"
)

aux_source_directory(src/unordered_map unordered_map_source)

add_executable(test_unordered_map ${unordered_map_source})
add_dependencies(test_unordered_map third)
target_link_libraries(
    test_unordered_map
    profiler
)

add_custom_command(
    OUTPUT ${HELLO_CPP_BINARY_DIR}/test_unordered_map.svg
    DEPENDS test_unordered_map
    COMMAND CPUPROFILE=test_unordered_map.pprof ./test_unordered_map && ${HELLO_CPP_SOURCE_DIR}/third/gperftools/build/bin/pprof --svg test_unordered_map test_unordered_map.pprof > test_unordered_map.svg
    WORKING_DIRECTORY ${HELLO_CPP_BINARY_DIR}
)

add_custom_target(
    svg
    DEPENDS ${HELLO_CPP_BINARY_DIR}/test_unordered_map.svg
)

enable_testing()
add_test(NAME test_unordered_map COMMAND test_unordered_map)
