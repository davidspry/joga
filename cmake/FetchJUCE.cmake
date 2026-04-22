include(FetchContent)

FetchContent_Declare(juce
  GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
  GIT_BRANCH master
  GIT_SHALLOW TRUE)

FetchContent_MakeAvailable(juce)
