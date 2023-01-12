add_executable(earley_test)

file(GLOB_RECURSE EARLEY_TEST_INCLUDES *.hpp)
file(GLOB_RECURSE EARLEY_TEST_SOURCES *.cpp)

target_sources(earley_test
    PUBLIC
        ${EARLEY_TEST_INCLUDES}
    PRIVATE
        ${EARLEY_TEST_SOURCES}
    )

target_link_libraries(earley_test
    PUBLIC
        earley
        gtest
    )