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

set(CLIENT_HEADERS
    include/view/client/clientdesktop.h
)

set(CLIENT_SOURCES
    src/view/clientdesktop.cc
    src/model/client.cc
    src/model/room.cc
    src/model/user.cc
    src/model/database/database.cc
    src/model/database/tables/clienttable.cc
    src/model/database/tables/roomtable.cc
    src/model/database/tables/usertable.cc
    src/presenter/client/clientpresenter.cc
)

add_executable(ClientGUI ${CLIENT_SOURCES} ${CLIENT_HEADERS})

target_link_libraries(ClientGUI ${SQLite3_LIBRARIES})
target_link_libraries(ClientGUI Qt5::Widgets)

set(User_HEADERS
    include/view/user/userdesktop.h
)

set(User_SOURCES
    src/view/userdesktop.cc
    src/model/client.cc
    src/model/room.cc
    src/model/user.cc
    src/model/database/database.cc
    src/model/database/tables/clienttable.cc
    src/model/database/tables/roomtable.cc
    src/model/database/tables/usertable.cc
    src/presenter/client/clientpresenter.cc
    src/presenter/user/userpresenter.cc
)

add_executable(UserGUI ${User_SOURCES} ${User_HEADERS})

target_link_libraries(UserGUI ${SQLite3_LIBRARIES})
target_link_libraries(UserGUI Qt5::Widgets)