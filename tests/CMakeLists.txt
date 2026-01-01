
add_executable(blaze2d_tests
  test_core.cpp
)

target_link_libraries(blaze2d_tests
  PRIVATE
    Blaze2D    
    Catch2::Catch2WithMain
)

add_test(NAME Blaze2DTests COMMAND blaze2d_tests)

