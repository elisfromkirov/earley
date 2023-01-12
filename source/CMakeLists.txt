add_library(earley)

file(GLOB_RECURSE EARLEY_INCLUDES *.hpp)
file(GLOB_RECURSE EARLEY_SOURCES *.cpp)

target_include_directories(earley
    PUBLIC
        .
    )

target_sources(earley
    PUBLIC
        ${EARLEY_INCLUDES}
    PRIVATE
        ${EARLEY_SOURCES}
    )