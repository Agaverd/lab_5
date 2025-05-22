cmake_minimum_required(VERSION 3.14)
project(lab_5)

# 1) Найти OpenCV
find_package(OpenCV REQUIRED)

# 2) Подключить include-директории
include_directories(${OpenCV_INCLUDE_DIRS})

# 3) Добавить ваш исполняемый файл
add_executable(sequential src/main.cpp)
add_executable(parallel src/parallel.cpp)
add_executable(atomic src/parallel.cpp)

# 4) Линковать библиотеки OpenCV
target_link_libraries(sequential ${OpenCV_LIBS})
target_link_libraries(parallel ${OpenCV_LIBS})
target_link_libraries(atomic ${OpenCV_LIBS})