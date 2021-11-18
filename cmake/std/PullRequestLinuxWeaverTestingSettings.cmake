# This file contains the options needed to both run the pull request testing
# for Trilinos for the CUDA 10.2.2 pull request testing builds, and to reproduce
# the errors reported by those builds. Prior to using this this file, the
# appropriate set of modules must be loaded and path must be augmented.
# (See the sems/PullRequestCuda10.2.2TestingEnv.sh files.)

# Usage: cmake -C PullRequestLinuxCUDA10.2.2TestingSettings.cmake

set (CMAKE_CXX_STANDARD "14" CACHE STRING "Set C++ standard to C++14")

# Misc options typically added by CI testing mode in TriBITS

# Use the below option only when submitting to the dashboard
set (CTEST_USE_LAUNCHERS ON CACHE BOOL "Set by default for PR testing")

# Options necessary for CUDA build
set (TPL_ENABLE_MPI ON CACHE BOOL "Set by default for CUDA PR testing")
set (Kokkos_ENABLE_CUDA ON CACHE BOOL "Set by default for CUDA PR testing")
set (Kokkos_ENABLE_CUDA_UVM ON CACHE BOOL "Set by default for CUDA PR testing")
set (Tpetra_ENABLE_CUDA_UVM ON CACHE BOOL "Set by default for CUDA PR testing")
set (Kokkos_ARCH_POWER9 ON CACHE BOOL "Set by default for CUDA PR testing")
set (Kokkos_ARCH_VOLTA70 ON CACHE BOOL "Set by default for CUDA PR testing")
set (Kokkos_ENABLE_CUDA_RELOCATABLE_DEVICE_CODE OFF CACHE BOOL "Set by default for CUDA PR testing")
set (Sacado_ENABLE_HIERARCHICAL_DFAD ON CACHE BOOL "Set by default for CUDA PR testing")
set (Kokkos_ENABLE_CXX11_DISPATCH_LAMBDA ON CACHE BOOL "Set by default for CUDA PR testing")
set (Kokkos_ENABLE_CUDA_LAMBDA ON CACHE BOOL "Set by default for CUDA PR testing")
set (Phalanx_KOKKOS_DEVICE_TYPE CUDA CACHE STRING "Set by default for CUDA PR testing")
set (MPI_EXEC_POST_NUMPROCS_FLAGS "-map-by;socket:PE=10" CACHE STRING "Set by default for CUDA PR testing")


# Do not use ninja on weaver because it is broken somehow
set(CTEST_CMAKE_GENERATOR "Unix Makefiles" CACHE STRING FORCE "Set by default for CUDA PR testing on weaver")

# Options set to match the ATDM build
set (Trilinos_ENABLE_DEBUG OFF CACHE BOOL "Set by default for CUDA PR testing")
set (Trilinos_ENABLE_DEBUG_SYMBOLS OFF CACHE BOOL "Set by default for CUDA PR testing")
set (BUILD_SHARED_LIBS OFF CACHE BOOL "Set by default for CUDA PR testing")
set (Tpetra_INST_SERIAL ON CACHE BOOL "Set by default for CUDA PR testing")
set (Trilinos_ENABLE_SECONDARY_TESTED_CODE OFF CACHE BOOL "Set by default for CUDA PR testing")
set (EpetraExt_ENABLE_HDF5 OFF CACHE BOOL "Set by default for CUDA PR testing")
set (Panzer_FADTYPE "Sacado::Fad::DFad<RealType>" CACHE STRING "Set by default for CUDA PR testing")
set (Kokkos_ENABLE_Debug_Bounds_Check ON CACHE BOOL "Set by default for CUDA PR testing")
set (KOKKOS_ENABLE_DEBUG ON CACHE BOOL "Set by default for CUDA PR testing")

# TPL settings specific to CUDA build
set (TPL_ENABLE_CUDA ON CACHE BOOL "Set by default for CUDA PR testing")
set (TPL_ENABLE_CUSPARSE ON CACHE BOOL "Set by default for CUDA PR testing")
set (TPL_ENABLE_Pthread OFF CACHE BOOL "Set by default for CUDA PR testing")
set (TPL_ENABLE_BinUtils OFF CACHE BOOL "Set by default for CUDA PR testing")
set (TPL_ENABLE_BLAS ON CACHE BOOL "Set by default for CUDA PR testing")
set (TPL_BLAS_LIBRARIES "-L$ENV{BLAS_ROOT}/lib64;-lblas;-lgfortran;-lgomp;-lm" CACHE STRING "Set by default for CUDA PR testing")
set (TPL_ENABLE_Boost ON CACHE BOOL "Set by default for CUDA PR testing")
set (Boost_INCLUDE_DIRS "$ENV{BOOST_ROOT}/include" CACHE FILEPATH "Set by default for CUDA PR testing")
set (TPL_Boost_LIBRARIES "$ENV{BOOST_ROOT}/lib/libboost_program_options.a;$ENV{BOOST_ROOT}/lib/libboost_system.a" CACHE FILEPATH  "Set by default for CUDA PR testing")
set (TPL_ENABLE_BoostLib ON CACHE BOOL "Set by default for CUDA PR testing")
set (BoostLib_INCLUDE_DIRS "$ENV{BOOST_ROOT}/include" CACHE FILEPATH "Set by default for CUDA PR testing")
set (TPL_BoostLib_LIBRARIES "$ENV{BOOST_ROOT}/lib/libboost_program_options.a;$ENV{BOOST_ROOT}/lib/libboost_system.a" CACHE FILEPATH "Set by default for CUDA PR testing")
set (TPL_ENABLE_METIS OFF CACHE BOOL "Set by default for CUDA PR testing")
set (TPL_ENABLE_ParMETIS OFF CACHE BOOL "Set by default for CUDA PR testing")
set (TPL_ENABLE_Scotch OFF CACHE BOOL "Set by default for CUDA PR testing")
set (TPL_ENABLE_HWLOC OFF CACHE BOOL "Set by default for CUDA PR testing")
set (TPL_ENABLE_LAPACK ON CACHE BOOL "Set by default for CUDA PR testing")
set (TPL_LAPACK_LIBRARIES "-L$ENV{LAPACK_ROOT}/lib64;-llapack;-lgfortran;-lgomp" CACHE STRING "Set by default for CUDA PR testing")
set (TPL_ENABLE_Zlib OFF CACHE BOOL "Set by default for CUDA PR testing")
set (TPL_ENABLE_CGNS OFF CACHE BOOL "Set by default for CUDA PR testing")
set (TPL_ENABLE_HDF5 ON CACHE BOOL "Set by default for CUDA PR testing")
set (HDF5_INCLUDE_DIRS "$ENV{HDF5_ROOT}/include" CACHE FILEPATH "Set by default for CUDA PR testing")
set (TPL_HDF5_LIBRARIES "-L$ENV{HDF5_ROOT}/lib;$ENV{HDF5_ROOT}/lib/libhdf5_hl.a;$ENV{HDF5_ROOT}/lib/libhdf5.a;-lz;-ldl" CACHE FILEPATH "Set by default for CUDA PR testing")
set (TPL_ENABLE_Netcdf ON CACHE BOOL "Set by default for CUDA PR testing")
set (Netcdf_INCLUDE_DIRS "$ENV{NETCDF_ROOT}/include" CACHE FILEPATH "Set by default for CUDA PR testing")
IF ("$ENV{PNETCDF_ROOT}" STREQUAL "")
  SET(PNETCDF_ROOT "$ENV{NETCDF_ROOT}")
ELSE()
  SET(PNETCDF_ROOT "$ENV{PNETCDF_ROOT}")
ENDIF()
set (TPL_Netcdf_LIBRARIES "-L$ENV{NETCDF_ROOT}/lib;$ENV{NETCDF_ROOT}/lib64/libnetcdf.a;${PNETCDF_ROOT}/lib/libpnetcdf.a;${TPL_HDF5_LIBRARIES}" CACHE STRING "Set by default for CUDA PR testing")
# SuperLU and SuperLUDist is available on ride and could be enabled for the CUDA PR build
set (TPL_ENABLE_SuperLU OFF CACHE BOOL "Set by default for CUDA PR testing")
set (TPL_ENABLE_SuperLUDist OFF CACHE BOOL "Set by default for CUDA PR testing")
set (TPL_ENABLE_BoostLib OFF CACHE BOOL "Set by default for CUDA PR testing")
set (TPL_ENABLE_Matio OFF CACHE BOOL "Set by default for CUDA PR testing")
set (TPL_DLlib_LIBRARIES "-ldl" CACHE FILEPATH "Set by default for CUDA PR testing")

set (Trilinos_ENABLE_Stokhos OFF CACHE BOOL "Set by default for CUDA PR testing")

# The compile times for two Panzer files went up to over 6 hours. This
# turns off one feature that allows these in about 24 minutes. Please remove
# when issue #7532 is resolved.
set (Sacado_NEW_FAD_DESIGN_IS_DEFAULT OFF CACHE BOOL "Temporary fix for issue #7532" )

# Disable some packages that can't be tested with this PR build
set (Trilinos_ENABLE_ShyLU_NodeTacho OFF CACHE BOOL
  "Can't test Tacho with CUDA without RDC" FORCE)

# Force some tests to run in serial in this PR build (usually to resolve random timeouts that can occur under contention)
set (Intrepid2_unit-test_Discretization_Basis_HierarchicalBases_Hierarchical_Basis_Tests_MPI_1_SET_RUN_SERIAL ON CACHE BOOL "Run serial for CUDA PR testing")

# Options used to clean up build
set (MueLu_ParameterListInterpreterTpetra_MPI_1_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (MueLu_ParameterListInterpreterTpetraHeavy_MPI_1_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (STKUnit_tests_stk_ngp_test_utest_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (ROL_example_PDE-OPT_0ld_adv-diff-react_example_01_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (ROL_example_PDE-OPT_0ld_adv-diff-react_example_02_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (ROL_example_PDE-OPT_0ld_poisson_example_01_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (ROL_example_PDE-OPT_0ld_stefan-boltzmann_example_03_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (ROL_example_PDE-OPT_navier-stokes_example_01_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (ROL_example_PDE-OPT_navier-stokes_example_02_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (ROL_example_PDE-OPT_nonlinear-elliptic_example_01_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (ROL_example_PDE-OPT_nonlinear-elliptic_example_02_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (ROL_example_PDE-OPT_obstacle_example_01_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (ROL_example_PDE-OPT_topo-opt_poisson_example_01_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (ROL_test_elementwise_TpetraMultiVector_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (ROL_NonlinearProblemTest_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (PanzerAdaptersSTK_CurlLaplacianExample-ConvTest-Quad-Order-4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (PanzerAdaptersSTK_MixedPoissonExample-ConvTest-Hex-Order-3_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (TrilinosCouplings_Example_Maxwell_MueLu_MPI_1_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (TrilinosCouplings_Example_Maxwell_MueLu_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")

# Disable some tests that should not need to be disabled but do because the
# Trilinos PR tester is using too high a parallel level for ctest. (If the
# ctest parallel test level is dropped from 29 to 8, all of these will pass.)
set (MueLu_UnitTestsIntrepid2Tpetra_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (PanzerAdaptersSTK_main_driver_energy-ss-blocked-tp_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (PanzerAdaptersSTK_MixedCurlLaplacianExample-ConvTest-Tri-Order-1_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (PanzerAdaptersSTK_PoissonInterfaceExample_3d_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (PanzerMiniEM_MiniEM-BlockPrec_Augmentation_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (PanzerMiniEM_MiniEM-BlockPrec_RefMaxwell_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (ROL_example_PDE-OPT_poisson-boltzmann_example_01_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")

# Disable a couple of unit tests in test KokkosCore_UnitTest_Cuda_MPI_1 that
# are randomly failing in PR test iterations (#6799)
set (KokkosCore_UnitTest_Cuda_MPI_1_EXTRA_ARGS
  "--gtest_filter=-cuda.debug_pin_um_to_host:cuda.debug_serial_execution"
  CACHE STRING "Temporary disable for CUDA PR testing")

# Disable a few failing tests for initial release of Cuda 10.2.2 PR build
set (EpetraExt_inout_test_LL_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (EpetraExt_inout_test_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Teko_testdriver_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Zoltan2_fix4785_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Intrepid2_unit-test_Discretization_Basis_HierarchicalBases_Hierarchical_Basis_Tests_MPI_1_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")

set (Trilinos_ENABLE_COMPLEX ON CACHE BOOL "Testing for #9025")
set (Teuchos_ENABLE_COMPLEX ON CACHE BOOL "Testing for #9025")
set (Tpetra_INST_COMPLEX_DOUBLE ON CACHE BOOL "Testing for #9025")

include("${CMAKE_CURRENT_LIST_DIR}/PullRequestLinuxCommonTestingSettings.cmake")


#Tests turned off to be able to move the cuda pr build to weaver
set (_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Anasazi_BlockDavidson_complex_test_0_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Anasazi_BlockDavidson_complex_test_2_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Anasazi_BlockDavidsonThyra_test_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Anasazi_BlockKrylovSchur_complex_test_0_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Anasazi_BlockKrylovSchur_complex_test_1_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Anasazi_BlockKrylovSchur_complex_test_2_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Anasazi_BlockKrylovSchur_complex_test_3_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Anasazi_BlockKrylovSchurThyra_test_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Anasazi_Epetra_BKS_nh_test_0_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Anasazi_Epetra_BKS_nh_test_1_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Anasazi_Epetra_BKS_norestart_test_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Anasazi_Epetra_BKS_solvertest_0_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Anasazi_Epetra_BKS_solvertest_1_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Anasazi_Epetra_BKS_sym_test_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Anasazi_Epetra_BKS_test_0_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Anasazi_Epetra_BKS_test_1_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Anasazi_Epetra_BlockDavidson_auxtest_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Anasazi_Epetra_BlockDavidson_solvertest_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Anasazi_Epetra_BlockDavidson_test_0_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Anasazi_Epetra_BlockDavidson_test_1_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Anasazi_Epetra_BlockDavidson_test_2_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Anasazi_Epetra_BlockDavidson_test_3_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Anasazi_Epetra_BlockDavidson_test_4_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Anasazi_Epetra_BlockDavidson_test_5_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Anasazi_Epetra_BlockDavidson_test_6_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Anasazi_Epetra_BlockDavidson_test_7_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Anasazi_Epetra_BlockDavidson_test_8_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Anasazi_Epetra_GeneralizedDavidson_nh_test_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Anasazi_Epetra_GeneralizedDavidson_solvertest_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Anasazi_Epetra_IRTR_auxtest_0_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Anasazi_Epetra_IRTR_auxtest_1_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Anasazi_Epetra_IRTR_auxtest_2_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Anasazi_Epetra_IRTR_auxtest_3_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Anasazi_Epetra_IRTR_auxtest_4_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Anasazi_Epetra_IRTR_test_0_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Anasazi_Epetra_IRTR_test_1_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Anasazi_Epetra_IRTR_test_2_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Anasazi_Epetra_IRTR_test_3_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Anasazi_Epetra_LOBPCG_auxtest_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Anasazi_Epetra_LOBPCG_simpletest_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Anasazi_Epetra_LOBPCG_solvertest_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Anasazi_Epetra_LOBPCG_test_0_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Anasazi_Epetra_LOBPCG_test_1_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Anasazi_Epetra_OrthoManagerGenTester_1_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Anasazi_Epetra_OrthoManagerMatTester_0_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Anasazi_Epetra_OrthoManagerMatTester_1_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Anasazi_Epetra_OrthoManagerMatTester_2_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Anasazi_Epetra_OrthoManagerMatTester_3_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Anasazi_Epetra_OrthoManagerMatTester_4_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Anasazi_Epetra_OrthoManagerMatTester_5_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Anasazi_Epetra_OrthoManagerTester_0_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Anasazi_Epetra_OrthoManagerTester_1_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Anasazi_Epetra_OrthoManagerTester_2_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Anasazi_Epetra_OrthoManagerTester_3_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Anasazi_Epetra_OrthoManagerTester_4_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Anasazi_Epetra_OrthoManagerTester_5_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Anasazi_IRTRThyra_test_0_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Anasazi_IRTRThyra_test_1_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Anasazi_IRTRThyra_test_2_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Anasazi_IRTRThyra_test_3_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Anasazi_LOBPCG_complex_test_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Anasazi_LOBPCGThyra_test_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Anasazi_Tpetra_BlockDavidson_Complex_test_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Anasazi_Tpetra_BlockKrylovSchur_Complex_test_0_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Anasazi_Tpetra_BlockKrylovSchur_Complex_test_1_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Anasazi_Tpetra_BlockKrylovSchur_Lap_test_0_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Anasazi_Tpetra_BlockKrylovSchur_Lap_test_1_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Anasazi_Tpetra_LOBPCG_Complex_test_0_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Anasazi_Tpetra_LOBPCG_Complex_test_1_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Belos_bl_fgmres_hb_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Belos_bl_pgmres_hb_0_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Belos_bl_pgmres_hb_1_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Belos_bl_pgmres_hb_2_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Belos_bl_pgmres_hb_3_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Belos_bl_pgmres_hb_4_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Belos_bl_pgmres_hb_5_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Belos_BlockGmres_Galeri_Ex_0_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Belos_BlockGmresPoly_Epetra_File_Ex_0_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Belos_BlockPrecGmres_Galeri_Ex_0_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Belos_Epetra_OrthoManager_test_0_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Belos_Epetra_OrthoManager_test_1_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Belos_gcrodr_complex_hb_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Belos_gcrodr_hb_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Belos_prec_gcrodr_hb_0_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Belos_prec_gcrodr_hb_1_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Belos_pseudo_gmres_hb_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Belos_pseudo_gmres_multi_hb_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Belos_pseudo_pcg_hb_0_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Belos_pseudo_pcg_hb_1_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Belos_pseudo_pcg_hb_2_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Belos_pseudo_pgmres_hb_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Belos_pseudo_stochastic_pcg_hb_0_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Belos_pseudo_stochastic_pcg_hb_1_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Belos_resolve_gmres_hb_0_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Belos_resolve_gmres_hb_1_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Belos_SolverFactory_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Belos_Tpetra_gcrodr_complex_hb_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Belos_Tpetra_gcrodr_hb_test_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Ifpack2_Diagonal_gcrodr_belos_MPI_1_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Ifpack2_Jacobi_gcrodr_hb_belos_MPI_1_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Intrepid2_unit-test_Discretization_Basis_DeRHAM_TET_FEM_Serial_Test_01_MPI_1_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Intrepid2_unit-test_Discretization_Basis_DeRHAM_TRI_FEM_Serial_Test_01_MPI_1_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Intrepid2_unit-test_Discretization_Basis_HGRAD_TET_Cn_FEM_Cuda_Test_02_MPI_1_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Intrepid2_unit-test_Discretization_Basis_HGRAD_TET_Cn_FEM_Serial_Test_02_MPI_1_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Intrepid2_unit-test_Discretization_Basis_HGRAD_TRI_Cn_FEM_Cuda_Test_02_MPI_1_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Intrepid2_unit-test_Discretization_Basis_HGRAD_TRI_Cn_FEM_Serial_Test_02_MPI_1_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Intrepid2_unit-test_MonolithicExecutable_Intrepid2_Tests_MPI_1_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Intrepid2_unit-test_Orientation_Serial_Test_Orientation_TET_MPI_1_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Intrepid2_unit-test_Projection_Cuda_Test_Convergence_TET_MPI_1_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Intrepid2_unit-test_Projection_Cuda_Test_InterpolationProjection_TRI_MPI_1_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Intrepid2_unit-test_Projection_Serial_Test_Convergence_TET_MPI_1_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Intrepid2_unit-test_Projection_Serial_Test_DeRhamCommutativity_TET_MPI_1_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Intrepid2_unit-test_Projection_Serial_Test_InterpolationProjection_TRI_MPI_1_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Intrepid_test_Discretization_Basis_HCURL_HEX_In_FEM_Test_02_MPI_1_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Intrepid_test_Discretization_Basis_HCURL_TET_In_FEM_Test_02_MPI_1_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Intrepid_test_Discretization_Basis_HDIV_HEX_In_FEM_Test_02_MPI_1_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Intrepid_test_Discretization_Basis_HDIV_QUAD_In_FEM_Test_02_MPI_1_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Intrepid_test_Discretization_Basis_HDIV_TET_In_FEM_Test_02_MPI_1_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Intrepid_test_Discretization_Basis_HDIV_TRI_In_FEM_Test_02_MPI_1_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Intrepid_test_Discretization_Basis_HGRAD_HEX_C1_FEM_Test_02_MPI_1_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Intrepid_test_Discretization_Basis_HGRAD_HEX_C2_FEM_Test_02_MPI_1_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Intrepid_test_Discretization_Basis_HGRAD_HEX_Cn_FEM_Test_02_MPI_1_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Intrepid_test_Discretization_Basis_HGRAD_HEX_I2_FEM_Test_02_MPI_1_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Intrepid_test_Discretization_Basis_HGRAD_PYR_C1_FEM_Test_02_MPI_1_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Intrepid_test_Discretization_Basis_HGRAD_PYR_I2_FEM_Test_02_MPI_1_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Intrepid_test_Discretization_Basis_HGRAD_QUAD_C2_FEM_Test_02_MPI_1_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Intrepid_test_Discretization_Basis_HGRAD_QUAD_Cn_FEM_Test_02_MPI_1_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Intrepid_test_Discretization_Basis_HGRAD_TET_C2_FEM_Test_02_MPI_1_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Intrepid_test_Discretization_Basis_HGRAD_TET_Cn_FEM_Test_02_MPI_1_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Intrepid_test_Discretization_Basis_HGRAD_TRI_Cn_FEM_ORTH_Test_02_MPI_1_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Intrepid_test_Discretization_Basis_HGRAD_TRI_Cn_FEM_Test_02_MPI_1_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Intrepid_test_Discretization_Basis_HGRAD_WEDGE_C1_FEM_Test_02_MPI_1_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Intrepid_test_Discretization_Basis_HGRAD_WEDGE_I2_FEM_Test_02_MPI_1_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (KokkosCore_UnitTest_CudaTimingBased_MPI_1_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (MueLu_UnitTestsTpetra_MPI_1_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (MueLu_UnitTestsTpetra_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (NOX_LOCA_AnasaziJacobianInverse_MPI_1_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (NOX_LOCA_AnasaziNotConverged_MPI_1_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (NOX_LOCA_Brusselator_Cayley2Matrix_MPI_2_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (NOX_LOCA_Brusselator_MPI_2_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (NOX_LOCA_Brusselator_ShiftInvert2Matrix_MPI_2_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (NOX_LOCA_MultiPointTcubed_MPI_2_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (NOX_LOCA_Pitchfork_MPI_2_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (NOX_LOCA_Tcubed_Continuation_Example_MPI_1_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (NOX_LOCA_Tcubed_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (NOX_Thyra_1DFEM_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (PanzerAdaptersSTK_main_driver_energy-ss-loca-eigenvalue_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (ROL_test_algorithm_TypeU_TrustRegion_MPI_1_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (ROL_test_step_TrustRegion_MPI_1_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (ShyLU_DDBDDC_bddc_simple_interface_test_MPI_2_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (ShyLU_DDBDDC_bddc_standard_interface_test_MPI_2_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (STKUnit_tests_stk_util_unit_tests_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Stokhos_DivisionOperatorUnitTest_MPI_1_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Stokhos_Linear2D_Diffusion_GMRES_KLR_MPI_2_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Stokhos_QuadraturePseudoSpectralExpansionUnitTest_MPI_1_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Stokhos_SacadoUQPCEUnitTest_MPI_1_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Stokhos_SDMUtilsUnitTest_MPI_1_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Stokhos_SmolyakPseudoSpectralExpansionUnitTest_MPI_1_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Stokhos_TensorProductPseudoSpectralOperatorUnitTest_MPI_1_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Stokhos_TpetraCrsMatrixUQPCEUnitTest_Serial_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Stratimikos_Belos_GCRODR_strattest_MPI_4_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Stratimikos_test_amesos_thyra_driver_MPI_1_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (Stratimikos_Thyra_Belos_StatusTest_UnitTests_MPI_1_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (ThyraCore_MultiVector_RowStatScaledOp_UnitTests_MPI_2_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")
set (TrilinosCouplings_Example_Maxwell_Tpetra_MueLu_MPI_1_DISABLE ON CACHE BOOL "Temporary disable for CUDA PR testing")