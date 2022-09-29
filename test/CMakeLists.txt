project(${project_name})

message("ok now testing begins")

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)

include(GoogleTest)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


file(GLOB test_files *.cpp *.hpp)

add_executable(${project_name}test ${test_files} )
target_include_directories(${project_name}test PRIVATE ../src)
target_link_libraries(${project_name}test PRIVATE GTest::gtest_main d_t_m)

#add commandline arguments to ctest
set(test_args d  6)
gtest_add_tests(${project_name}test "${test_args}" AUTO)

