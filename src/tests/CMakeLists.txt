INCLUDE(${QT_USE_FILE})

INCLUDE_DIRECTORIES( ${GTEST_INCLUDE_DIR}
                     ${GMOCK_INCLUDE_DIR}
                     ${CMAKE_SOURCE_DIR}/src/utils
                     ${CMAKE_SOURCE_DIR}/src/core )

SET(QtPersistence_test_SRCS
    inflectiontest.cpp 
    introspectiontest.cpp
    qtpersistencetest.cpp
    qpersistantobjectimpltest.cpp
    newobjectsavestatetest.cpp
    existingobjectsavestatetest.cpp
    qpersistantobjecttest.cpp
    databaseconfigurationtest.cpp
    objectloadertest.cpp
    testutils.cpp
    testmain.cpp
    )

SET(QtPersistence_test_HDRS
    inflectiontest.h
    qpersistantobjectimpltest.h
    qtpersistencetest.h
    mockobjectsavestate.h
    testutils.h
    newobjectsavestatetest.h
    existingobjectsavestatetest.h
    objectloadertest.h
    )

SET(QtPersistence_test_MOC_HDRS
    introspectiontest.h
    fakebook.h
   )

QT_WRAP_CPP(QtPersistenceTest QtPersistence_test_SRCS ${QtPersistence_test_MOC_HDRS})
ADD_EXECUTABLE(QtPersistenceTest ${QtPersistence_test_SRCS})
TARGET_LINK_LIBRARIES(QtPersistenceTest
                      ${QT_LIBRARIES}
                      ${GTEST_LIBRARY}
                      ${GMOCK_LIBRARY}
                      QtPersistence )
ADD_TEST(QtPersistenceTest ${CMAKE_CURRENT_BINARY_DIR}/QtPersistenceTest)

ADD_CUSTOM_TARGET(check COMMAND ${CMAKE_CURRENT_BINARY_DIR}/QtPersistenceTest
                  DEPENDS QtPersistenceTest VERBATIM)

# vim: set et sts=4 sw=4 ts=16 tw=78 :
# kate: replace-tabs on; indent-width 4;
