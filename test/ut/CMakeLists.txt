cmake_minimum_required(VERSION 3.15)

include(GoogleTest)
include(CTest)
include(FetchContent)

enable_testing()

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.10.0
)

FetchContent_GetProperties(googletest)
if(NOT googletest_POPULATED)
  FetchContent_Populate(googletest)
  if(MSVC)
    add_compile_options(/MD$<$<CONFIG:Debug>:d>)
  endif()   # MSVC
  add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
endif()     # NOT googletest_POPULATED

mark_as_advanced(
    BUILD_GMOCK BUILD_GTEST BUILD_SHARED_LIBS
    gmock_build_tests gtest_build_samples gtest_build_tests
    gtest_disable_pthreads gtest_force_shared_crt gtest_hide_internal_symbols
)

set_target_properties(gtest PROPERTIES FOLDER extern)
set_target_properties(gtest_main PROPERTIES FOLDER extern)
set_target_properties(gmock PROPERTIES FOLDER extern)
set_target_properties(gmock_main PROPERTIES FOLDER extern)

macro(package_add_test_with_libraries TESTNAME FILES LIBRARIES TEST_WORKING_DIRECTORY)
    add_executable(${TESTNAME} ${FILES})
    target_link_libraries(${TESTNAME} gtest gmock gtest_main ${LIBRARIES})
    gtest_discover_tests(${TESTNAME}
        WORKING_DIRECTORY ${TEST_WORKING_DIRECTORY}
        PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${TEST_WORKING_DIRECTORY}"
    )
    set_target_properties(${TESTNAME} PROPERTIES FOLDER tests)
endmacro()

message("${PROJECT_DIR}")

# package_add_test_with_libraries(
#     runUnitTests
#     tests/TicketVendingMachine/VendingMachineTests.cpp
#     TicketVendingMachine
#     "${PROJECT_DIR}")

package_add_test_with_libraries(
    VendingMachineTests
    tests/TicketVendingMachine/VendingMachineTests.cpp
    TicketVendingMachine
    "${CMAKE_SOURCE_DIR}"
)



# # Find GTest
# find_package(GTest REQUIRED)
# include_directories(${GTEST_INCLUDE_DIR})

# # Add test sources
# add_executable(runUnitTests
#     tests/TicketVendingMachine/VendingMachineTests.cpp
#     tests/TicketVendingMachine/Currencies/CurrencyPlnTests.cpp
#     tests/TicketVendingMachine/Ticket/TicketTests.cpp
#     tests/TicketVendingMachine/Zone/ZoneTests.cpp
#     tests/User/UserTests.cpp
#     tests/Utilities/UtilitiesTests.cpp
# )

# target_link_libraries(runUnitTests ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} pthread TicketVendingMachine)

# # Enable testing
# enable_testing()

# # Add tests
# add_test(NAME VendingMachineTests COMMAND runUnitTests --gtest_filter=VendingMachineTest.*)
# add_test(NAME CurrencyPlnTests COMMAND runUnitTests --gtest_filter=CurrencyPlnTest.*)
# add_test(NAME TicketTests COMMAND runUnitTests --gtest_filter=TicketTest.*)
# add_test(NAME ZoneTests COMMAND runUnitTests --gtest_filter=ZoneTest.*)
# add_test(NAME UserTests COMMAND runUnitTests --gtest_filter=UserTest.*)
# add_test(NAME UtilitiesTests COMMAND runUnitTests --gtest_filter=UtilitiesTest.*)

# # Coverage target
# add_custom_target(
#     coverage
#     COMMAND ${CMAKE_COMMAND} -E make_directory coverage
#     COMMAND ${CMAKE_COMMAND} -E chdir coverage gcovr -r .. --html --html-details -o index.html
#     WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
# )
