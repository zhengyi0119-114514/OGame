target_include_directories(abs_game PRIVATE include)
target_sources(
    abs_game PUBLIC FILE_SET HEADERS TYPE HEADERS FILES
    include/empty.hpp
)
target_sources(
    abs_game
    PRIVATE
    main.cpp
)
