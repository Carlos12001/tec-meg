set(BINARY ${CMAKE_PROJECT_NAME}_tst)
find_package(GTest REQUIRED)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(nlohmann_json 3.2.0 REQUIRED)

enable_testing()


file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.h *.cpp)

set(SOURCES ${TEST_SOURCES})

add_executable(${BINARY} ${TEST_SOURCES} main_tester.cpp)

add_test(NAME ${BINARY} COMMAND ${BINARY})

target_link_libraries(${BINARY} PUBLIC GTest::gtest GTest::gtest_main PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
PRIVATE nlohmann_json::nlohmann_json)