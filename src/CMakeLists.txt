SET(QT_USE_QTSQL 1)
INCLUDE(${QT_USE_FILE})

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR}
                    ${CMAKE_SOURCE_DIR}/src/utils
                   )

ADD_SUBDIRECTORY(tests)

SET(QtPersistence_SRCS

    utils/inflection.cpp

    core/qtpersistence.cpp
    core/qpersistantobject.cpp
    core/introspection.cpp
    core/newobjectsavestate.cpp
    core/existingobjectsavestate.cpp
    core/databaseconfiguration.cpp
#   core/objectloader.cpp
    )

SET(QtPersistence_MOC_HDRS
    core/qpersistantobject.h
    )

QT_WRAP_CPP(QtPersistence QtPersistence_SRCS ${QtPersistence_MOC_HDRS})
ADD_LIBRARY(QtPersistence SHARED ${QtPersistence_SRCS})
SET_TARGET_PROPERTIES(QtPersistence 
                      PROPERTIES SKIP_BUILD_RPATH TRUE
                                 BUILD_WITH_INSTALL_RPATH TRUE
                                 VERSION 0.1.1
                                 SOVERSION 0)
TARGET_LINK_LIBRARIES(QtPersistence ${QT_LIBRARIES})
INSTALL(TARGETS QtPersistence DESTINATION lib${LIB_SUFFIX})
INSTALL(FILES core/qpersistantobject.h DESTINATION include)


# vim: set et sts=4 sw=4 ts=16 tw=78 :
# kate: replace-tabs on; indent-width 4;
