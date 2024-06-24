// @HEADER
// *****************************************************************************
//           Amesos2: Templated Direct Sparse Solver Package
//
// Copyright 2011 NTESS and the Amesos2 contributors.
// SPDX-License-Identifier: BSD-3-Clause
// *****************************************************************************
// @HEADER

#include "Amesos2_MUMPS_decl.hpp"

#ifdef HAVE_AMESOS2_EXPLICIT_INSTANTIATION

#  include "Amesos2_MUMPS_def.hpp"
#  include "Amesos2_ExplicitInstantiationHelpers.hpp"

namespace Amesos2 {
#ifdef HAVE_AMESOS2_EPETRA
  AMESOS2_SOLVER_EPETRA_INST(MUMPS);
#endif
}

#include <Tpetra_KokkosCompat_DefaultNode.hpp>
#include "Tpetra_ETIHelperMacros.h"

#define AMESOS2_MUMPS_LOCAL_INSTANT(SC,LO,GO,N)                        \
  template class Amesos2::MUMPS<Tpetra::CrsMatrix<SC, LO, GO, N>,      \
                                  Tpetra::MultiVector<SC, LO, GO,  N> >;

TPETRA_ETI_MANGLING_TYPEDEFS()
TPETRA_INSTANTIATE_SLGN_NO_ORDINAL_SCALAR(AMESOS2_MUMPS_LOCAL_INSTANT)

#endif  // HAVE_AMESOS2_EXPLICIT_INSTANTIATION
