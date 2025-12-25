cmake_minimum_required(VERSION 3.15)
project(SkvozShifr VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# OpenSSL не требуется - все алгоритмы реализованы самостоятельно
# Можно использовать только для тестирования, но не обязательно

# Директории исходников
set(SOURCES_DIR src)
set(INCLUDES_DIR include)

# Исходные файлы
file(GLOB_RECURSE SOURCES "${SOURCES_DIR}/*.cpp")

# Заголовочные файлы
file(GLOB_RECURSE HEADERS "${INCLUDES_DIR}/*.h" "${INCLUDES_DIR}/*.hpp")

# Исполняемый файл
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Включаемые директории
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDES_DIR})

# Все криптографические алгоритмы реализованы самостоятельно
# Не требуется подключение внешних библиотек

# Флаги компиляции
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic)
endif()

