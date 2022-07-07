if (NOT EXISTS "C:/Users/Duy Thanh/Downloads/Compressed/Pinball-on-Android/app/.cxx/RelWithDebInfo/2b3p5t06/x86_64/install_manifest.txt")
    message(FATAL_ERROR "Cannot find install manifest: \"C:/Users/Duy Thanh/Downloads/Compressed/Pinball-on-Android/app/.cxx/RelWithDebInfo/2b3p5t06/x86_64/install_manifest.txt\"")
endif(NOT EXISTS "C:/Users/Duy Thanh/Downloads/Compressed/Pinball-on-Android/app/.cxx/RelWithDebInfo/2b3p5t06/x86_64/install_manifest.txt")

file(READ "C:/Users/Duy Thanh/Downloads/Compressed/Pinball-on-Android/app/.cxx/RelWithDebInfo/2b3p5t06/x86_64/install_manifest.txt" files)
string(REGEX REPLACE "\n" ";" files "${files}")
foreach (file ${files})
    message(STATUS "Uninstalling \"$ENV{DESTDIR}${file}\"")
    execute_process(
        COMMAND C:/Users/Duy Thanh/AppData/Local/Android/Sdk/cmake/3.18.1/bin/cmake.exe -E remove "$ENV{DESTDIR}${file}"
        OUTPUT_VARIABLE rm_out
        RESULT_VARIABLE rm_retval
    )
    if(NOT ${rm_retval} EQUAL 0)
        message(FATAL_ERROR "Problem when removing \"$ENV{DESTDIR}${file}\"")
    endif (NOT ${rm_retval} EQUAL 0)
endforeach(file)

