find_package(Catch2 2 REQUIRED)

add_executable(testing testing.cpp)

target_link_libraries(testing lab1 Catch2::Catch2)