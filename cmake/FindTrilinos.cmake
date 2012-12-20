# this module looks for the Trilinos library
# it will define the following values
#
# Needs environmental variables
#   TRILINOS_HOME
# Sets
#   TRILINOS_INCLUDE_DIRS
#   TRILINOS_LIBRARIES
#   CF3_HAVE_TRILINOS
#
option( CF3_SKIP_TRILINOS "Skip search for Trilinos library" OFF )

if( NOT CF3_HAVE_TRILINOS ) # skip if already have

set(CF3_TRILINOS_EXTRA_LIBS "" CACHE  STRING "Extra libraries needed to link with Trilinos")

# Try to find Trilinos using Trilinos recommendations

if( DEFINED TRILINOS_HOME )
    find_package(Trilinos PATHS ${TRILINOS_HOME}/lib/cmake/Trilinos ${TRILINOS_HOME}/include )
endif()

if( DEFINED DEPS_ROOT )
    find_package(Trilinos PATHS ${DEPS_ROOT}/lib/cmake/Trilinos ${DEPS_ROOT}/include )
endif()

if( Trilinos_FOUND )

    set( TRILINOS_INCLUDE_DIRS "" )
    list( APPEND TRILINOS_INCLUDE_DIRS ${Trilinos_INCLUDE_DIRS})
    list( APPEND TRILINOS_INCLUDE_DIRS ${Trilinos_TPL_INCLUDE_DIRS})

    foreach( test_lib ${Trilinos_LIBRARIES})
      find_library( ${test_lib}_lib ${test_lib} PATHS  ${Trilinos_LIBRARY_DIRS}  NO_DEFAULT_PATH)
      find_library( ${test_lib}_lib ${test_lib})
      mark_as_advanced( ${test_lib}_lib )
      list( APPEND TRILINOS_LIBRARIES ${${test_lib}_lib} )
    endforeach()

    list( APPEND TRILINOS_LIBRARIES ${Trilinos_TPL_LIBRARIES} )

else()

  # Try to find Trilinos the hard way

  coolfluid_set_trial_include_path("") # clear include search path
  coolfluid_set_trial_library_path("") # clear library search path

  coolfluid_add_trial_include_path( ${TRILINOS_HOME}/include )
  coolfluid_add_trial_include_path( $ENV{TRILINOS_HOME}/include )

  coolfluid_add_trial_library_path(${TRILINOS_HOME}/lib )
  coolfluid_add_trial_library_path($ENV{TRILINOS_HOME}/lib)

  find_path( TRILINOS_INCLUDE_DIRS Epetra_SerialComm.h PATHS ${TRIAL_INCLUDE_PATHS}  NO_DEFAULT_PATH )
  find_path( TRILINOS_INCLUDE_DIRS Epetra_SerialComm.h )

  list( APPEND trilinos_req_libs
      epetra
      teuchos
      stratimikosamesos
      stratimikosaztecoo
      stratimikosbelos
      stratimikosifpack
      stratimikosml
      stratimikos
      aztecoo
      ml
      belos
      ifpack
      thyra
      thyracore
      thyraepetra
  )

  foreach( test_lib ${trilinos_req_libs} )
    find_library( ${test_lib}_lib ${test_lib} PATHS  ${TRIAL_LIBRARY_PATHS}  NO_DEFAULT_PATH)
    find_library( ${test_lib}_lib ${test_lib})
    mark_as_advanced( ${test_lib}_lib )
    list( APPEND TRILINOS_LIBRARIES ${${test_lib}_lib} )
  endforeach()

  if( CF3_HAVE_PARMETIS )
    list( APPEND TRILINOS_LIBRARIES ${PARMETIS_LIBRARIES} )
    list( APPEND TRILINOS_INCLUDE_DIRS ${PARMETIS_INCLUDE_DIRS} )
  endif()

  if( CF3_HAVE_PTSCOTCH )
    list( APPEND TRILINOS_LIBRARIES ${PTSCOTCH_LIBRARIES} )
    list( APPEND TRILINOS_INCLUDE_DIRS ${PTSCOTCH_INCLUDE_DIRS} )
  endif()

endif()

list(APPEND TRILINOS_LIBRARIES ${CF3_TRILINOS_EXTRA_LIBS})

coolfluid_log("TRILINOS_INCLUDE_DIRS = ${TRILINOS_INCLUDE_DIRS}" )
coolfluid_log("TRILINOS_LIBRARIES = ${TRILINOS_LIBRARIES}" )

coolfluid_set_package( PACKAGE Trilinos
                       DESCRIPTION "parallel linear system solver and other libraries"
                       URL "http://trilinos.sandia.gov"
                       VARS
                       TRILINOS_INCLUDE_DIRS
                       TRILINOS_LIBRARIES  )

if( Trilinos_FOUND )
    set( CF3_HAVE_TRILINOS 1 )
else()
    set( CF3_HAVE_TRILINOS 0 )
endif()

endif( NOT CF3_HAVE_TRILINOS )
