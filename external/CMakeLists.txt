

include(FetchContent)


##
##  doctest
##
FetchContent_Declare(
  doctest
  GIT_REPOSITORY https://github.com/onqtam/doctest.git
  GIT_TAG master
)


FetchContent_MakeAvailable(doctest)
