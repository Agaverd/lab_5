cmake_minimum_required(VERSION 3.14)
project(lab_5)

# 1) Найти OpenCV
find_package(OpenCV REQUIRED)

# 2) Подключить include-директории
include_directories(${OpenCV_INCLUDE_DIRS})

# 3) Добавить ваш исполняемый файл
add_executable(${PROJECT_NAME} src/main.cpp)

# 4) Линковать библиотеки OpenCV
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})