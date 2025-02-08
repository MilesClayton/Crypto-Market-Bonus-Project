cmake_minimum_required(VERSION 3.10)
project(Bonus_Project)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Bonus_Project
        main.cpp
        exchange.cpp
        useraccount.cpp  # Ensure this is included
        utility.cpp
)
