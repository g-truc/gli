function(glmCreateTestGTC NAME)
	if(GLI_TEST_ENABLE)
		set(SAMPLE_NAME test-${NAME})
		add_executable(${SAMPLE_NAME} ${NAME}.cpp)

		add_test(
			NAME ${SAMPLE_NAME}
			COMMAND $<TARGET_FILE:${SAMPLE_NAME}> )
	endif(GLI_TEST_ENABLE)
endfunction()

add_subdirectory(bug)
add_subdirectory(core)
