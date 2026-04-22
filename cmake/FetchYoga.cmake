include(FetchContent)

FetchContent_Declare(yoga
  GIT_REPOSITORY https://github.com/facebook/yoga.git
  GIT_TAG v3.2.1
  GIT_SHALLOW TRUE)

FetchContent_MakeAvailable(yoga)
