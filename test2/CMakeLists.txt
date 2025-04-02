cmake_minimum_required(VERSION 3.10)
project(AllocatorTests)

# Укажите путь к основному проекту
add_subdirectory(../Allocator)

# Добавьте исполняемый файл для тестов
add_executable(test_allocator test_allocator.cpp)

# Свяжите с основной библиотекой Allocator
target_link_libraries(test_allocator Allocator)
