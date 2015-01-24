cmake_minimum_required(VERSION 2.8.4)
project(DS_MP1)

set(CMAKE_CXX_FLAGS "-Wall -g")

set(TEST test_hash.c mp1_node.h)

set(mp1_node  mp1_node.c mp1_node.h emulnet.h params.h requests.h queue.h stdincludes.h log.h MPtemplate.h nodeaddr.h)
set(emulnet emulnet.c emulnet.h nodeaddr.h log.h params.h stdincludes.h)
set(app app.c app.h nodeaddr.h mp1_node.h MPtemplate.h stdincludes.h params.h queue.h requests.h emulnet.h log.h)
set(log log.c log.h nodeaddr.h stdincludes.h)
set(params params.c params.h stdincludes.h)
set(queue queue.c queue.h stdincludes.h)
set(APP ${mp1_node} ${emulnet} ${app} ${log} ${params} ${queue})

add_executable(DS_MP1 ${APP})