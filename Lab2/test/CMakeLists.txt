function(OPTION_TURN_ON_TESTING 
    CONDITION TEST_NAME TEST_SOURCE EXEC_TARGET_NAME)
    if (NOT ${CONDITION})
        message("Тестирование класса OctalDigit отключено!\n")
    else()
        add_executable(${TEST_NAME} ${TEST_SOURCE})
        target_link_libraries(${TEST_NAME} 
            PRIVATE 
                Lab3::source
                GTest::GTest)
        add_custom_target(${EXEC_TARGET_NAME} ALL COMMAND ${TEST_NAME})
    endif()    

endfunction()

include(${PROJECT_SOURCE_DIR}/cmake/gtest.cmake)

option(GTEST_DISABLE_PTHREADS "" OFF)
