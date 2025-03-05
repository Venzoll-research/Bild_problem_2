# cmake_minimum_required(VERSION 3.14)
# project(signal_processor)

# # ============================================================
# # Настройка компилятора и стандарта C++
# # ============================================================
# set(CMAKE_CXX_COMPILER "C:/msys64/ucrt64/bin/g++.exe")  # Путь к GCC из MSYS2
# set(CMAKE_CXX_STANDARD 17)                              # Требуется C++17
# set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_EXTENSIONS OFF)

# # ============================================================
# # Флаги компиляции
# # ============================================================
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -pthread")  # Для MinGW и потоков
# add_definitions(-D_GLIBCXX_HAS_GTHREADS)                  # Включение поддержки потоков

# # ============================================================
# # Пути к Python и pybind11 (замените на свои!)
# # ============================================================
# set(Python_ROOT_DIR "C:/Users/37111/AppData/Local/Programs/Python/Python313")  # Путь к Python
# set(pybind11_DIR "${Python_ROOT_DIR}/Lib/site-packages/pybind11/share/cmake/pybind11")

# # ============================================================
# # Поиск зависимостей
# # ============================================================
# find_package(Python REQUIRED COMPONENTS Interpreter Development)
# find_package(pybind11 REQUIRED)
# find_package(Threads REQUIRED)  # Для многопоточности

# # ============================================================
# # Подключение заголовочных файлов
# # ============================================================
# include_directories(
#     ${PROJECT_SOURCE_DIR}/include  # Ваши .h файлы
#     ${Python_INCLUDE_DIRS}         # Заголовки Python
#     ${pybind11_INCLUDE_DIRS}       # Заголовки pybind11
# )

# # ============================================================
# # Список исходных файлов
# # ============================================================
# set(SOURCES
#     src/signal.cpp
#     src/FIR.cpp
#     src/IIR.cpp
#     src/Summator.cpp
#     src/SignalProcessor.cpp
#     pybind_wrapper.cpp  # Файл-обёртка для pybind11
# )

# # ============================================================
# # Создание Python-модуля
# # ============================================================
# pybind11_add_module(signal_processor ${SOURCES})

# # ============================================================
# # Линковка библиотек
# # ============================================================
# target_link_libraries(signal_processor PRIVATE
#     pybind11::module      # pybind11
#     Python::Python        # Python
#     Threads::Threads      # Потоки (обязательно!)
# )

# # ============================================================
# # Для Windows: переименование в .pyd
# # ============================================================
# set_target_properties(signal_processor PROPERTIES SUFFIX ".pyd")






cmake_minimum_required(VERSION 3.12)
project(signal_processor)

# # ============================================================
# # Настройка компилятора и стандарта C++
# # ============================================================
# set(CMAKE_CXX_COMPILER "C:/msys64/ucrt64/bin/g++.exe")  # Путь к GCC из MSYS2
# set(CMAKE_CXX_STANDARD 17)                              # Требуется C++17
# set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_EXTENSIONS OFF)

# ============================================================
# Флаги компиляции
# ============================================================
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -pthread")  # Для MinGW и потоков
# add_definitions(-D_GLIBCXX_HAS_GTHREADS)                  # Включение поддержки потоков

# ============================================================
# Пути к Python и pybind11 (замените на свои!)
# ============================================================
set(Python_ROOT_DIR "C:/Users/37111/AppData/Local/Programs/Python/Python313")  # Путь к Python
set(pybind11_DIR "C:/Users/37111/AppData/Local/Programs/Python/Python313/Lib/site-packages/pybind11/share/cmake/pybind11")

# ============================================================
# Поиск зависимостей
# ============================================================
find_package(Python REQUIRED COMPONENTS Interpreter Development)
find_package(pybind11 REQUIRED)
# find_package(Threads REQUIRED)  # Для многопоточности

# ============================================================
# Подключение заголовочных файлов
# ============================================================
# ============================================================
# Список исходных файлов
# ============================================================
set(SOURCES
${CMAKE_CURRENT_SOURCE_DIR}/src/signal.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/FIR.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/IIR.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/Summator.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/SignalProcessor.cpp
${CMAKE_CURRENT_SOURCE_DIR}/pybind_wrapper.cpp  # Файл-обёртка для pybind11
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static -fPIC")
pybind11_add_module(signal_processor ${SOURCES})


target_include_directories(signal_processor PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include  # Ваши .h файлы
    ${Python_INCLUDE_DIRS}         # Заголовки Python
    ${pybind11_INCLUDE_DIRS}       # Заголовки pybind11
)

# ============================================================
# Создание Python-модуля
# ============================================================

# ============================================================
# Линковка библиотек
# ============================================================
target_link_libraries(signal_processor PRIVATE
    pybind11::module      # pybind11
    Python::Python        # Python
)

# ============================================================
# Для Windows: переименование в .pyd
# ============================================================
set_target_properties(signal_processor PROPERTIES SUFFIX ".pyd")