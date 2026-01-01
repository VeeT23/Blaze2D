cmake_minimum_required(VERSION 3.8)

project(Blaze2D LANGUAGES C CXX)

include(FetchContent)

# ================= Catch 2 =================

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.5.2
)

FetchContent_MakeAvailable(Catch2)

enable_testing()
add_subdirectory(tests)


# ================= SDL3 =================
FetchContent_Declare(
  SDL3
  GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
  GIT_TAG main
)

FetchContent_MakeAvailable(SDL3)

# ================= SDL3_image =================
FetchContent_Declare(
  SDL3_image
  GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
  GIT_TAG main
)

set(SDL3IMAGE_AVIF OFF CACHE BOOL "" FORCE)
set(SDL3IMAGE_WEBP OFF CACHE BOOL "" FORCE)
set(SDL3IMAGE_TIF OFF CACHE BOOL "" FORCE)
set(SDL3IMAGE_JXL OFF CACHE BOOL "" FORCE)

set(DAV1D_ASM OFF CACHE BOOL "" FORCE)
set(DAV1D_ENABLE_TOOLS OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(SDL3_image)

# ================= Blaze2D =================
add_library(Blaze2D STATIC
  src/Core.cpp
  src/internal/SDLManager.cpp
)

# Public headers
target_include_directories(Blaze2D
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Internal headers
target_include_directories(Blaze2D
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(Blaze2D
  PUBLIC
    SDL3::SDL3
    SDL3_image::SDL3_image
)

target_compile_features(Blaze2D PUBLIC cxx_std_20)
