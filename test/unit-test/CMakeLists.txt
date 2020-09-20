# Include filepaths for Device Defender library.
include( ${MODULE_ROOT_DIR}/defenderFilePaths.cmake )

# ====================  Define your project name (edit) ========================
set( project_name "defender" )

# =====================  Create your mock here  (edit)  ========================
# No mocks are needed for device defender library.

# ================= Create the library under test here (edit) ==================

# List the files you would like to test here.
list( APPEND real_source_files
      ${DEFENDER_SOURCES} )

# List the directories the module under test includes.
list( APPEND real_include_directories
      ${DEFENDER_INCLUDE_PUBLIC_DIRS} )

# Build Device Defender library without requiring config file.
add_compile_definitions( DEFENDER_DO_NOT_USE_CUSTOM_CONFIG )

# =====================  Create UnitTest Code here (edit)  =====================

# List the directories your test needs to include.
list( APPEND test_include_directories
     ${DEFENDER_INCLUDE_PUBLIC_DIRS} )

# =============================  (end edit)  ===================================

set( real_name "${project_name}_real" )

create_real_library( ${real_name}
                     "${real_source_files}"
                     "${real_include_directories}"
                     "${mock_name}"
                   )

list( APPEND utest_link_list
      lib${real_name}.a )

list( APPEND utest_dep_list
     ${real_name} )

set( utest_name "${project_name}_utest" )
set( utest_source "${project_name}_utest.c" )
create_test( ${utest_name}
             ${utest_source}
             "${utest_link_list}"
             "${utest_dep_list}"
             "${test_include_directories}" )
