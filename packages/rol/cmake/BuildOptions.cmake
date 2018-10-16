INCLUDE(BuildOptionFunctions)
INCLUDE(Deprecated)

IF( ROL_ENABLE_TIMERS )
  MESSAGE("Build ROL with Teuchos TimeMonitors enabled.")
  OPTION( ROL_TIMERS ON )
  CONFIGURE_FILE("${PACKAGE_SOURCE_DIR}/cmake/ROL_config.h.in" ROL_config.h  @ONLY)
ENDIF( ROL_ENABLE_TIMERS )

SET_PROPERTY( GLOBAL PROPERTY TEUCHOS_PARAMETERLIST "Teuchos::ParameterList" )
SET_PROPERTY( GLOBAL PROPERTY TEUCHOS_STACKTRACE    "Teuchos::stacktrace"    )
SET_PROPERTY( GLOBAL PROPERTY TEUCHOS_RCP           "Teuchos::RCP"           )

SET_PROPERTY( GLOBAL PROPERTY BACKWARD_CPP          "backward-cpp"           )

SET_PROPERTY( GLOBAL PROPERTY SIMPLE_STACKTRACE     "simple"                 )

SET_PROPERTY( GLOBAL PROPERTY BOOST_PROPERTY_TREE   "boost::property_tree"   )
SET_PROPERTY( GLOBAL PROPERTY BOOST_STACKTRACE      "boost::stacktrace"      )
SET_PROPERTY( GLOBAL PROPERTY STD_SHARED_PTR        "std::shared_ptr"        )


SET_DEFAULT( ROL_Ptr           "Teuchos::RCP"           )
SET_DEFAULT( ROL_ParameterList "Teuchos::ParameterList" )
SET_DEFAULT( ROL_stacktrace    "Teuchos::stacktrace"    )
SET_DEFAULT( ROL_LinearAlgebra "Teuchos::SerialDense"   )
SET_DEFAULT( ROL_LAPACK        "Teuchos::LAPACK"        )

SET( USING_TEUCHOS_ALL ON )
SET( USING_TEUCHOS_ALL ON PARENT_SCOPE )

# Compatibility Directory 
SET( DIR ${${PACKAGE_NAME}_SOURCE_DIR}/src/compatibility )



# Set smart pointer type
IF( ROL_Ptr STREQUAL "std::shared_ptr")
  SET_PROPERTY( GLOBAL PROPERTY PTR_IMPL "std::shared_ptr"       )
  SET_PROPERTY( GLOBAL PROPERTY PTR_DIR  "${DIR}/std/shared_ptr" )
  SET( USING_TEUCHOS_ALL OFF )
  SET( USING_TEUCHOS_ALL OFF PARENT_SCOPE )
ELSE()
  SET_PROPERTY( GLOBAL PROPERTY PTR_IMPL "Teuchos::RCP"       )
  SET_PROPERTY( GLOBAL PROPERTY PTR_DIR "${DIR}/teuchos/rcp" )
ENDIF()



# Set parameter list type
IF( ROL_ParameterList STREQUAL "boost::property_tree")
  SET_PROPERTY( GLOBAL PROPERTY PARAMETERLIST_IMPL "boost::property_tree"       )
  SET_PROPERTY( GLOBAL PROPERTY PARAMETERLIST_DIR  "${DIR}/boost/property_tree" )
  SET( USING_TEUCHOS_ALL OFF )
  SET( USING_TEUCHOS_ALL OFF PARENT_SCOPE )
ELSE()
  SET_PROPERTY( GLOBAL PROPERTY PARAMETERLIST_IMPL "Teuchos::ParameterList"       )
  SET_PROPERTY( GLOBAL PROPERTY PARAMETERLIST_DIR  "${DIR}/teuchos/parameterlist" )
ENDIF()


# set stacktrace type
IF( ROL_stacktrace STREQUAL "backward-cpp" )
  INCLUDE(BackwardConfig)
  SET_PROPERTY( GLOBAL PROPERTY STACKTRACE_IMPL "backward-cpp"               )
  SET_PROPERTY( GLOBAL PROPERTY STACKTRACE_DIR  "${DIR}/backward_cpp"        )
  SET( USING_TEUCHOS_ALL OFF )
  SET( USING_TEUCHOS_ALL OFF PARENT_SCOPE )
ELSEIF( ROL_stacktrace STREQUAL "simple" )
  SET_PROPERTY( GLOBAL PROPERTY STACKTRACE_IMPL "simple"                       )
  SET_PROPERTY( GLOBAL PROPERTY STACKTRACE_DIR  "${DIR}/simple/stacktrace"     )
  SET( USING_TEUCHOS_ALL OFF )
  SET( USING_TEUCHOS_ALL OFF PARENT_SCOPE )
ELSEIF( ROL_stacktrace STREQUAL "boost::stacktrace")
  SET_PROPERTY( GLOBAL PROPERTY STACKTRACE_IMPL "boost::stacktrace"          )
  SET_PROPERTY( GLOBAL PROPERTY STACKTRACE_DIR  "${DIR}/boost/stacktrace"    )
  SET( USING_TEUCHOS_ALL OFF )
  SET( USING_TEUCHOS_ALL OFF PARENT_SCOPE )
ELSE()
  SET_PROPERTY( GLOBAL PROPERTY STACKTRACE_IMPL "Teuchos::stacktrace"       )
  SET_PROPERTY( GLOBAL PROPERTY STACKTRACE_DIR  "${DIR}/teuchos/stacktrace" )
ENDIF()


# Set linear algebra
IF( ROL_LinearAlgebra STREQUAL "Eigen")
  SET_PROPERTY( GLOBAL PROPERTY LA_IMPL "Eigen"        )
  SET_PROPERTY( GLOBAL PROPERTY LA_DIR  "${DIR}/eigen" )
  find_package(Eigen3 REQUIRED)
  INCLUDE_DIRECTORIES(${EIGEN3_INCLUDE_DIR})
  SET( USING_TEUCHOS_ALL OFF )
  SET( USING_TEUCHOS_ALL OFF PARENT_SCOPE )
ELSE()
  SET_PROPERTY( GLOBAL PROPERTY LA_IMPL "Teuchos::SerialDense"           )
  SET_PROPERTY( GLOBAL PROPERTY LA_DIR  "${DIR}/teuchos/la"              )
ENDIF()

# Set lapack
IF( ROL_LAPACK STREQUAL "simple")
  SET_PROPERTY( GLOBAL PROPERTY LAPACK_IMPL "simple"       )
  SET_PROPERTY( GLOBAL PROPERTY LAPACK_DIR  "${DIR}/simple/lapack" )
  SET( USING_TEUCHOS_ALL OFF )
  SET( USING_TEUCHOS_ALL OFF PARENT_SCOPE )
ELSE()
  SET_PROPERTY( GLOBAL PROPERTY LAPACK_IMPL "Teuchos::LAPACK"       )
  SET_PROPERTY( GLOBAL PROPERTY LAPACK_DIR  "${DIR}/teuchos/lapack" )
ENDIF()
