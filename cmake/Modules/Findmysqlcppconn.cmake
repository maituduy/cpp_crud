set( DEFAULT_PATH "${CMAKE_PREFIX_PATH}")
find_path(MYSQLCPPCONN_INCLUDE_DIR NAMES mysql_connection.h PATHS ${DEFAULT_PATH} PATH_SUFFIXES "include")
find_library(MYSQLCPPCONN_LIBRARY NAMES mysqlcppconn PATHS ${DEFAULT_PATH} PATH_SUFFIXES "lib")

message("MYSQLCPPCONN include dir = ${MYSQLCPPCONN_INCLUDE_DIR}")
message("MYSQLCPPCONN lib = ${MYSQLCPPCONN_LIBRARY}")

set(MYSQLCPPCONN_LIBRARIES ${MYSQLCPPCONN_LIBRARY})
set(MYSQLCPPCONN_INCLUDE_DIRS ${MYSQLCPPCONN_INCLUDE_DIR})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(MYSQLCPPCONN DEFAULT_MSG
        MYSQLCPPCONN_LIBRARY MYSQLCPPCONN_INCLUDE_DIR)

mark_as_advanced(MYSQLCPPCONN_INCLUDE_DIR MYSQLCPPCONN_LIBRARY)