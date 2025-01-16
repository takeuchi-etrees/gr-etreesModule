find_package(PkgConfig)

PKG_CHECK_MODULES(PC_GR_ETREESMODULE gnuradio-etreesModule)

FIND_PATH(
    GR_ETREESMODULE_INCLUDE_DIRS
    NAMES gnuradio/etreesModule/api.h
    HINTS $ENV{ETREESMODULE_DIR}/include
        ${PC_ETREESMODULE_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    GR_ETREESMODULE_LIBRARIES
    NAMES gnuradio-etreesModule
    HINTS $ENV{ETREESMODULE_DIR}/lib
        ${PC_ETREESMODULE_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
          )

include("${CMAKE_CURRENT_LIST_DIR}/gnuradio-etreesModuleTarget.cmake")

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(GR_ETREESMODULE DEFAULT_MSG GR_ETREESMODULE_LIBRARIES GR_ETREESMODULE_INCLUDE_DIRS)
MARK_AS_ADVANCED(GR_ETREESMODULE_LIBRARIES GR_ETREESMODULE_INCLUDE_DIRS)
