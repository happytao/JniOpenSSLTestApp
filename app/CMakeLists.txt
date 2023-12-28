cmake_minimum_required(VERSION 3.18.1)

#对应System.loadLibrary()
project("my-jni-test")

include_directories(./src/main/jni/include)

add_library(my-jni-test

            SHARED

        src/main/jni/my-jni-test.c)

add_library(openssl

            SHARED

            IMPORTED)

add_library(ssl

            SHARED

            IMPORTED)

set_target_properties(openssl

                    PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/libs/${ANDROID_ABI}/libcrypto.so)

set_target_properties(ssl

                    PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/libs/${ANDROID_ABI}/libssl.so)

target_link_libraries(my-jni-test

                        android

                        log

                        openssl

                        ssl)


