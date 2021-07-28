cmake_minimum_required(VERSION 3.5)

project(unienet LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Wt REQUIRED)

SET (WT_CONNECTOR "wthttp" CACHE STRING "Connector used (wthttp(YES) or wtfcgi(NO))")

add_executable(unienet
  app.h
  app.cpp
  session.h
  session.cpp
  user.h
  user.cpp
  style.css
)

TARGET_LINK_LIBRARIES(unienet
  ${WT_CONNECTOR}
  wt
  Wt::Dbo
  Wt::DboMySQL
)

include_directories(/usr/local/include/Wt)
