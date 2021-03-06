ADD_DEFINITIONS(-D_GNU_SOURCE)

INCLUDE(TestBigEndian)
TEST_BIG_ENDIAN(BIGENDIAN)
IF(${BIGENDIAN})
  ADD_DEFINITIONS(-DWORDS_BIGENDIAN)
ENDIF(${BIGENDIAN})

list(APPEND CMAKE_REQUIRED_DEFINITIONS '-D_GNU_SOURCE')

INCLUDE(CheckPrototypeDefinition)
check_prototype_definition(qsort_r
 "void qsort_r(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *, void *), void *arg)"
 ""
 "stdlib.h"
 LINUX_QSORT_R)

IF(${LINUX_QSORT_R})
  ADD_DEFINITIONS(-DLINUX_QSORT_R)
ENDIF(${LINUX_QSORT_R})


check_prototype_definition(qsort_r
 "void qsort_r(void *base, size_t nel, size_t width, void *thunk, int (*compar)(void *, const void *, const void *))"
 ""
 "stdlib.h"
 BSD_QSORT_R)

IF(${BSD_QSORT_R})
  ADD_DEFINITIONS(-DBSD_QSORT_R)
ENDIF(${BSD_QSORT_R})


include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${ECDSAUTIL_BINARY_DIR}
  ${CMAKE_CURRENT_BINARY_DIR} ${UECC_INCLUDE_DIRS})
link_directories(${UECC_LIBRARY_DIRS})

add_executable(ecdsautil ecdsautil.c keygen.c sign.c verify.c hexutil.c random.c ecdsa.c version.c hmac_sha256.c sha256_file.c sha256sum.c array.c)

set_target_properties(ecdsautil PROPERTIES COMPILE_FLAGS "-std=c99 -Wall" ${UECC_CFLAGS_OTHER} LINK_FLAGS "" ${UECC_LDFLAGS_OTHER})
target_link_libraries(ecdsautil ${UECC_LIBRARIES})

install(TARGETS ecdsautil RUNTIME DESTINATION bin)
