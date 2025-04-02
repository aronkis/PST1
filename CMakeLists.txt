CMAKE_MINIMUM_REQUIRED(VERSION 3.31)
project(ClientServer)

cmake_policy(SET CMP0167 NEW)
set(CMAKE_CXX_STANDARD 20)

# Find required packages
find_package(SQLite3 REQUIRED)
find_package(Qt5 REQUIRED COMPONENTS Widgets)

# Include directories
include_directories(${SQLite3_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR}/include/)
include_directories(${PROJECT_SOURCE_DIR}/include/model)
include_directories(${PROJECT_SOURCE_DIR}/include/model/database)
include_directories(${PROJECT_SOURCE_DIR}/include/model/database/tables)
include_directories(${PROJECT_SOURCE_DIR}/include/presenter/client)
include_directories(${PROJECT_SOURCE_DIR}/include/presenter/user)
include_directories(${PROJECT_SOURCE_DIR}/include/view/client)
include_directories(${PROJECT_SOURCE_DIR}/include/view/user)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(HEADERS
    include/view/client/desktopgui.h
)

set(SOURCES
    src/view/desktopgui.cc
    src/model/client.cc
    src/model/room.cc
    src/model/user.cc
    src/model/database/database.cc
    src/model/database/tables/clienttable.cc
    src/model/database/tables/roomtable.cc
    src/model/database/tables/usertable.cc
    src/presenter/client/clientpresenter.cc
)

add_executable(DesktopGui ${SOURCES} ${HEADERS})

target_link_libraries(DesktopGui ${SQLite3_LIBRARIES})
target_link_libraries(DesktopGui Qt5::Widgets)