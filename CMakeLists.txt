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

ExternalProject_Add(
    google_protobuf
    URL https://github.com/google/protobuf/archive/v3.5.2.zip
    PREFIX ${HELLO_CPP_SOURCE_DIR}/third/protobuf
    BUILD_IN_SOURCE true
    CONFIGURE_COMMAND ""
    BUILD_COMMAND sh autogen.sh && ./configure --prefix=${HELLO_CPP_SOURCE_DIR}/third/protobuf/build --disable-shared && make -j8
    INSTALL_COMMAND make install
)

# ExternalProject_Add(
#     boostorg_boost
#     URL https://jaist.dl.sourceforge.net/project/boost/boost/1.72.0/boost_1_72_0.7z
#     PREFIX ${HELLO_CPP_SOURCE_DIR}/third/boost
#     BUILD_IN_SOURCE true
#     CONFIGURE_COMMAND ""
#     BUILD_COMMAND  export PATH=${HELLO_CPP_SOURCE_DIR}/third/openmpi/build/bin:$ENV{PATH} &&
#         export LD_LIBRARY_PATH=${HELLO_CPP_SOURCE_DIR}/third/openmpi/build/lib:$ENV{LD_LIBRARY_PATH} &&
#         export DYLD_LIBRARY_PATH=${HELLO_CPP_SOURCE_DIR}/third/openmpi/build/lib:$ENV{DYLD_LIBRARY_PATH} &&
#         export CPLUS_INCLUDE_PATH=${HELLO_CPP_SOURCE_DIR}/third/openmpi/build/include:$ENV{CPLUS_INCLUDE_PATH} && 
#         sh bootstrap.sh && echo "using mpi $<SEMICOLON>" >> project-config.jam  && ./b2 link=static  -j8
#     INSTALL_COMMAND export PATH=${HELLO_CPP_SOURCE_DIR}/third/openmpi/build/bin:$ENV{PATH} &&
#         export LD_LIBRARY_PATH=${HELLO_CPP_SOURCE_DIR}/third/openmpi/build/lib:$ENV{LD_LIBRARY_PATH} &&
#         export DYLD_LIBRARY_PATH=${HELLO_CPP_SOURCE_DIR}/third/openmpi/build/lib:$ENV{DYLD_LIBRARY_PATH} &&
#         export CPLUS_INCLUDE_PATH=${HELLO_CPP_SOURCE_DIR}/third/openmpi/build/include:$ENV{CPLUS_INCLUDE_PATH} &&
#         ./b2 install --prefix=${HELLO_CPP_SOURCE_DIR}/third/boost/build
# )

ExternalProject_Add(
    boostorg_boost
    URL https://jaist.dl.sourceforge.net/project/boost/boost/1.72.0/boost_1_72_0.7z
    PREFIX ${HELLO_CPP_SOURCE_DIR}/third/boost
    BUILD_IN_SOURCE true
    CONFIGURE_COMMAND ""
    BUILD_COMMAND sh bootstrap.sh && echo "using mpi $<SEMICOLON>" >> project-config.jam  && ./b2 link=static  -j8
    INSTALL_COMMAND ./b2 install --prefix=${HELLO_CPP_SOURCE_DIR}/third/boost/build
)
add_dependencies(boostorg_boost openmpi)

ExternalProject_Add(
    peterscott_murmur3
    URL https://github.com/PeterScott/murmur3/archive/master.zip
    PREFIX ${HELLO_CPP_SOURCE_DIR}/third/murmur3
    BUILD_IN_SOURCE true
    CONFIGURE_COMMAND ""
    BUILD_COMMAND gcc -c murmur3.c && ar rcs libmurmur3.a murmur3.o
    INSTALL_COMMAND mkdir -p ../../build/{include,lib} && cp murmur3.h ../../build/include && cp libmurmur3.a ../../build/lib
)

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

# ExternalProject_Add(
#     aerospike_aerospike_client_c
#     GIT_REPOSITORY https://github.com/aerospike/aerospike-client-c.git
#     PREFIX ${HELLO_CPP_SOURCE_DIR}/third/aerospike-client-c
#     BUILD_IN_SOURCE true
#     CONFIGURE_COMMAND ""
#     BUILD_COMMAND make
#     INSTALL_COMMAND ls target | xargs -I {} cp -r target/{}/ ${HELLO_CPP_SOURCE_DIR}/third/aerospike-client-c/build
#     COMMAND rm -rf ${HELLO_CPP_SOURCE_DIR}/third/aerospike-client-c/build/lib/libaerospike.dylib
# )
# add_dependencies(third aerospike_aerospike_client_c)

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

ExternalProject_Add(
    openssl_openssl
    URL https://github.com/openssl/openssl/archive/OpenSSL_1_0_2o.zip
    PREFIX ${HELLO_CPP_SOURCE_DIR}/third/openssl
    BUILD_IN_SOURCE true
    CONFIGURE_COMMAND KERNEL_BITS=64 ./config -fPIC --prefix=${HELLO_CPP_SOURCE_DIR}/third/openssl/build
)

ExternalProject_Add(
    sparsehash_sparsehash
    URL https://github.com/sparsehash/sparsehash/archive/sparsehash-2.0.3.zip
    PREFIX ${HELLO_CPP_SOURCE_DIR}/third/sparsehash
    BUILD_IN_SOURCE true
    CONFIGURE_COMMAND ./configure --prefix=${HELLO_CPP_SOURCE_DIR}/third/sparsehash/build
    BUILD_COMMAND make
)

ExternalProject_Add(
    google_double_conversion
    URL https://github.com/google/double-conversion/archive/v3.0.0.zip
    PREFIX ${HELLO_CPP_SOURCE_DIR}/third/double_conversion
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=${HELLO_CPP_SOURCE_DIR}/third/double_conversion/build
)

ExternalProject_Add(
    google_gperftools
    URL https://github.com/gperftools/gperftools/archive/gperftools-2.7.zip
    PREFIX ${HELLO_CPP_SOURCE_DIR}/third/gperftools
    BUILD_IN_SOURCE true
    CONFIGURE_COMMAND ""
    BUILD_COMMAND sh autogen.sh && ./configure --prefix=${HELLO_CPP_SOURCE_DIR}/third/gperftools/build && make -j8
)

ExternalProject_Add(
    tessil_hopscotch_map
    URL https://github.com/Tessil/hopscotch-map/archive/v2.0.0.zip
    PREFIX ${HELLO_CPP_SOURCE_DIR}/third/hopscotch_map
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=${HELLO_CPP_SOURCE_DIR}/third/hopscotch_map/build
    INSTALL_COMMAND mkdir -p ${HELLO_CPP_SOURCE_DIR}/third/hopscotch_map/build/ && cp -r ${HELLO_CPP_SOURCE_DIR}/third/hopscotch_map/src/tessil_hopscotch_map/include ${HELLO_CPP_SOURCE_DIR}/third/hopscotch_map/build/
)

ExternalProject_Add(
    tessil_robin_map
    URL https://github.com/Tessil/robin-map/archive/v0.3.0.zip
    PREFIX ${HELLO_CPP_SOURCE_DIR}/third/robin_map
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND mkdir -p ${HELLO_CPP_SOURCE_DIR}/third/robin_map/build/include && cp -r ${HELLO_CPP_SOURCE_DIR}/third/robin_map/src/tessil_robin_map/tsl ${HELLO_CPP_SOURCE_DIR}/third/robin_map/build/include
)

ExternalProject_Add(
    gflags_gflags
    URL https://github.com/gflags/gflags/archive/v2.2.1.zip
    PREFIX ${HELLO_CPP_SOURCE_DIR}/third/gflags
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=${HELLO_CPP_SOURCE_DIR}/third/gflags/build
)

ExternalProject_Add(
    libevent
    URL https://github.com/nmathewson/Libevent/archive/release-2.1.7-rc.zip
    PREFIX ${HELLO_CPP_SOURCE_DIR}/third/libevent
    BUILD_IN_SOURCE true
    CONFIGURE_COMMAND sh autogen.sh && ./configure
        --prefix=${HELLO_CPP_SOURCE_DIR}/third/libevent/build
    BUILD_COMMAND
        export C_INCLUDE_PATH=${HELLO_CPP_SOURCE_DIR}/third/openssl/build/include &&
        export LD_LIBRARY_PATH=${HELLO_CPP_SOURCE_DIR}/third/openssl/build/lib &&
        make
)
add_dependencies(libevent openssl_openssl)

ExternalProject_Add(
    bison
    URL http://mirrors.nju.edu.cn/gnu/bison/bison-3.0.5.tar.gz
    PREFIX ${HELLO_CPP_SOURCE_DIR}/third/bison
    BUILD_IN_SOURCE true
    CONFIGURE_COMMAND ./configure --prefix=${HELLO_CPP_SOURCE_DIR}/third/bison/build
    BUILD_COMMAND make -j8
)

# 这个版本 --with-openssl 有点问题 https://github.com/tuna/issues/issues/326
ExternalProject_Add(
    apache_thrift_0_9_3
    URL https://github.com/apache/thrift/archive/0.9.3.zip
    PREFIX ${HELLO_CPP_SOURCE_DIR}/third/thrift_0_9_3
    BUILD_IN_SOURCE true
    CONFIGURE_COMMAND
        export PATH=${HELLO_CPP_SOURCE_DIR}/third/bison/build/bin:$ENV{PATH} &&
        sh bootstrap.sh &&
        CPPFLAGS=-I${HELLO_CPP_SOURCE_DIR}/third/openssl/build/include LDFLAGS=-L${HELLO_CPP_SOURCE_DIR}/third/openssl/build/lib ./configure
        --prefix=${HELLO_CPP_SOURCE_DIR}/third/thrift_0_9_3/build
        --with-boost=${HELLO_CPP_SOURCE_DIR}/third/boost/build
        --with-libevent=${HELLO_CPP_SOURCE_DIR}/third/libevent/build
        --with-openssl=${HELLO_CPP_SOURCE_DIR}/third/openssl/build
        --with-qt4=no
        --with-qt5=no
        --with-c_glib=no
        --with-csharp=no
        --with-java=no
        --with-erlang=no
        --with-nodejs=no
        --with-lua=no
        --with-python=no
        --with-perl=no
        --with-php=no
        --with-php_extension=no
        --with-dart=no
        --with-ruby=no
        --with-haskell=no
        --with-go=no
        --with-rs=no
        --with-haxe=no
        --with-dotnetcore=no
        --with-d=no
        --disable-shared
        --disable-tests
        --disable-tutorial
    BUILD_COMMAND
        export PATH=${HELLO_CPP_SOURCE_DIR}/third/bison/build/bin:$ENV{PATH} &&
        export CPLUS_INCLUDE_PATH=${HELLO_CPP_SOURCE_DIR}/third/openssl/build/include &&
        export LD_LIBRARY_PATH=${HELLO_CPP_SOURCE_DIR}/third/openssl/build/lib &&
        make -j8
)
add_dependencies(apache_thrift_0_9_3 openssl_openssl)
add_dependencies(apache_thrift_0_9_3 boostorg_boost)
add_dependencies(apache_thrift_0_9_3 libevent)
add_dependencies(apache_thrift_0_9_3 bison)

ExternalProject_Add(
    apache_thrift_0_11_0
    URL https://github.com/apache/thrift/archive/0.11.0.zip
    PREFIX ${HELLO_CPP_SOURCE_DIR}/third/thrift_0_11_0
    BUILD_IN_SOURCE true
    CONFIGURE_COMMAND
        export PATH=${HELLO_CPP_SOURCE_DIR}/third/bison/build/bin:$ENV{PATH} &&
        sh bootstrap.sh && ./configure
        --prefix=${HELLO_CPP_SOURCE_DIR}/third/thrift_0_11_0/build
        --with-boost=${HELLO_CPP_SOURCE_DIR}/third/boost/build
        --with-openssl=${HELLO_CPP_SOURCE_DIR}/third/openssl/build
        --with-libevent=${HELLO_CPP_SOURCE_DIR}/third/libevent/build
        --with-qt4=no
        --with-qt5=no
        --with-c_glib=no
        --with-csharp=no
        --with-java=no
        --with-erlang=no
        --with-nodejs=no
        --with-lua=no
        --with-python=no
        --with-perl=no
        --with-php=no
        --with-php_extension=no
        --with-dart=no
        --with-ruby=no
        --with-haskell=no
        --with-go=no
        --with-rs=no
        --with-haxe=no
        --with-dotnetcore=no
        --with-d=no
        --disable-shared
    BUILD_COMMAND
        export PATH=${HELLO_CPP_SOURCE_DIR}/third/bison/build/bin:$ENV{PATH} &&
        make -j8
)
add_dependencies(apache_thrift_0_11_0 openssl_openssl)
add_dependencies(apache_thrift_0_11_0 boostorg_boost)
add_dependencies(apache_thrift_0_11_0 libevent)
add_dependencies(apache_thrift_0_11_0 bison)

# ExternalProject_Add(
#     facebook_folly
#     URL https://github.com/facebook/folly/archive/v2018.04.09.00.zip
#     PREFIX ${HELLO_CPP_SOURCE_DIR}/third/folly
#     CMAKE_ARGS
#         -DCMAKE_INSTALL_PREFIX:PATH=${HELLO_CPP_SOURCE_DIR}/third/folly/build
#         -DBOOST_ROOT=${HELLO_CPP_SOURCE_DIR}/third/boost/build
#         -DOPENSSL_INCLUDE_DIR=${HELLO_CPP_SOURCE_DIR}/third/openssl/build/include
#         -DOPENSSL_LIBRARIES=${HELLO_CPP_SOURCE_DIR}/third/openssl/build/lib
#         -DOPENSSL_ROOT_DIR=${HELLO_CPP_SOURCE_DIR}/third/openssl/build/
#         -DDOUBLE_CONVERSION_INCLUDE_DIR=${HELLO_CPP_SOURCE_DIR}/third/double_conversion/build/include
#         -DDOUBLE_CONVERSION_LIBRARY=${HELLO_CPP_SOURCE_DIR}/third/double_conversion/build/lib/libdouble-conversion.a
# )
# add_dependencies(facebook_folly openssl_openssl)
# add_dependencies(facebook_folly boostorg_boost)
# add_dependencies(facebook_folly google_double_conversion)
# add_dependencies(third facebook_folly)

ExternalProject_Add(
    openmpi
    URL https://download.open-mpi.org/release/open-mpi/v3.1/openmpi-3.1.5.tar.gz
    PREFIX ${HELLO_CPP_SOURCE_DIR}/third/openmpi
    BUILD_IN_SOURCE true
    CONFIGURE_COMMAND ./configure --prefix=${HELLO_CPP_SOURCE_DIR}/third/openmpi/build --enable-static=yes --enable-shared=no
    BUILD_COMMAND make -j8
)

add_dependencies(third google_gtest)
add_dependencies(third google_protobuf)
add_dependencies(third boostorg_boost)
add_dependencies(third peterscott_murmur3)
add_dependencies(third vipshop_hiredis_vip)
add_dependencies(third open_source_parses_jsoncpp)
add_dependencies(third openssl_openssl)
add_dependencies(third sparsehash_sparsehash)
add_dependencies(third google_double_conversion)
add_dependencies(third google_gperftools)
add_dependencies(third tessil_hopscotch_map)
add_dependencies(third tessil_robin_map)
add_dependencies(third gflags_gflags)
add_dependencies(third libevent)
add_dependencies(third bison)
add_dependencies(third apache_thrift_0_9_3)
add_dependencies(third apache_thrift_0_11_0)
add_dependencies(third openmpi)

set(CMAKE_CXX_FLAGS "-w -g -std=c++2a -lpthread")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

include_directories(
    "${HELLO_CPP_SOURCE_DIR}/include"
    "${HELLO_CPP_SOURCE_DIR}/proto"
    "${HELLO_CPP_SOURCE_DIR}/third/boost/build/include"
    "${HELLO_CPP_SOURCE_DIR}/third/libevent/build/include"
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
    "${HELLO_CPP_SOURCE_DIR}/third/robin_map/build/include"
    "${HELLO_CPP_SOURCE_DIR}/third/gflags/build/include"
    "${HELLO_CPP_SOURCE_DIR}/third/openmpi/build/include"
)

link_directories(
    "${HELLO_CPP_SOURCE_DIR}/third/gtest/build/lib"
    "${HELLO_CPP_SOURCE_DIR}/third/boost/build/lib"
    "${HELLO_CPP_SOURCE_DIR}/third/libevent/build/lib"
    "${HELLO_CPP_SOURCE_DIR}/third/protobuf/build/lib"
    "${HELLO_CPP_SOURCE_DIR}/third/murmur3/build/lib"
    "${HELLO_CPP_SOURCE_DIR}/third/hiredis-vip/build/lib"
    "${HELLO_CPP_SOURCE_DIR}/third/aerospike-client-c/build/lib"
    "${HELLO_CPP_SOURCE_DIR}/third/jsoncpp/build/lib"
    "${HELLO_CPP_SOURCE_DIR}/third/sparsehash/build/lib"
    "${HELLO_CPP_SOURCE_DIR}/third/double_conversion/build/lib"
    "${HELLO_CPP_SOURCE_DIR}/third/gperftools/build/lib"
    "${HELLO_CPP_SOURCE_DIR}/third/gflags/build/lib"
    "${HELLO_CPP_SOURCE_DIR}/third/openmpi/build/lib"
)

# api
set(thrift_version thrift_0_11_0 CACHE STRING "thrift version")
add_custom_command(
    OUTPUT ${HELLO_CPP_SOURCE_DIR}/api/echo/${thrift_version}
    DEPENDS ${HELLO_CPP_SOURCE_DIR}/api/echo/echo.thrift
    COMMAND mkdir -p ${HELLO_CPP_SOURCE_DIR}/api/echo/${thrift_version}
    COMMAND ${HELLO_CPP_SOURCE_DIR}/third/${thrift_version}/build/bin/thrift -r --gen cpp -o ${HELLO_CPP_SOURCE_DIR}/api/echo/${thrift_version} ${HELLO_CPP_SOURCE_DIR}/api/echo/echo.thrift
    COMMAND rm ${HELLO_CPP_SOURCE_DIR}/api/echo/${thrift_version}/gen-cpp/Service_server.skeleton.cpp
    WORKING_DIRECTORY ${HELLO_CPP_SOURCE_DIR}/api/echo
)
add_custom_target(
    thrift_out
    DEPENDS ${HELLO_CPP_SOURCE_DIR}/api/echo/${thrift_version}
)
add_dependencies(thrift_out third)

include_directories(
    "${HELLO_CPP_SOURCE_DIR}/api/echo/${thrift_version}/gen-cpp"
    "${HELLO_CPP_SOURCE_DIR}/third/${thrift_version}/build/include"
)
link_directories(
    "${HELLO_CPP_SOURCE_DIR}/third/${thrift_version}/build/lib"
)
aux_source_directory(${HELLO_CPP_SOURCE_DIR}/api/echo/${thrift_version}/gen-cpp thrift_source)

add_executable(simple_server_${thrift_version} src/${thrift_version}_echo/simple_server/main.cpp ${thrift_source})
target_link_libraries(simple_server_${thrift_version} thrift gflags)
add_dependencies(simple_server_${thrift_version} thrift_out)

add_executable(threaded_server_${thrift_version} src/${thrift_version}_echo/threaded_server/main.cpp ${thrift_source})
target_link_libraries(threaded_server_${thrift_version} thrift gflags)
add_dependencies(threaded_server_${thrift_version} thrift_out)

add_executable(thread_pool_server_${thrift_version} src/${thrift_version}_echo/thread_pool_server/main.cpp ${thrift_source})
target_link_libraries(thread_pool_server_${thrift_version} thrift gflags)
add_dependencies(thread_pool_server_${thrift_version} thrift_out)

add_executable(noblocking_server_${thrift_version} src/${thrift_version}_echo/noblocking_server/main.cpp ${thrift_source})
target_link_libraries(noblocking_server_${thrift_version} thriftnb thrift event gflags)
add_dependencies(noblocking_server_${thrift_version} thrift_out)

add_executable(client_${thrift_version} src/${thrift_version}_echo/client/main.cpp ${thrift_source})
target_link_libraries(client_${thrift_version} thrift gflags)
add_dependencies(client_${thrift_version} thrift_out)

# test_unordered_map
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

# test_random
aux_source_directory(src/random random_source)
add_executable(test_random ${random_source})
target_link_libraries(
    test_random
    boost_system
    boost_thread
)

# test std
aux_source_directory(src/std std_source)
add_executable(test_std ${std_source})
add_dependencies(test_std third)
target_link_libraries(
    test_std
    gtest
)

# test boost
aux_source_directory(src/boost boost_source)
add_executable(test_boost ${boost_source})
add_dependencies(test_boost third)
target_link_libraries(
    test_boost
    boost_date_time
    boost_system
    gtest
)

enable_testing()
add_test(NAME test_unordered_map COMMAND test_unordered_map)
add_test(NAME test_random COMMAND test_random)
add_test(NAME test_std COMMAND test_std)
add_test(NAME test_boost COMMAND test_boost)
