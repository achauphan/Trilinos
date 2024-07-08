// @HEADER
// *****************************************************************************
//                 Anasazi: Block Eigensolvers Package
//
// Copyright 2004 NTESS and the Anasazi contributors.
// SPDX-License-Identifier: BSD-3-Clause
// *****************************************************************************
// @HEADER

// This software is a result of the research described in the report
//
//     "A comparison of algorithms for modal analysis in the absence
//     of a sparse direct method", P. Arbenz, R. Lehoucq, and U. Hetmaniuk,
//     Sandia National Laboratories, Technical report SAND2003-1028J.
//
// It is based on the Epetra, AztecOO, and ML packages defined in the Trilinos
// framework ( http://trilinos.org/ ).

#ifndef ARPACK_MODE1_H
#define ARPACK_MODE1_H

#include "Epetra_ConfigDefs.h"

#include "Epetra_Comm.h"
#include "Epetra_Operator.h"
#include "Epetra_Time.h"

#ifdef EPETRA_MPI
#include "Epetra_MpiComm.h"
#endif

#include "FortranRoutines.h"
#include "ModalAnalysisSolver.h"
#include "MyMemory.h"
#include "CheckingTools.h"

class ARPACKm1 : public ModalAnalysisSolver {

  private:

    const CheckingTools myVerify;
    const FortranRoutines callFortran;

    const Epetra_Comm &MyComm;
    const Epetra_Operator *K;
    const Epetra_Time MyWatch;

    double tolEigenSolve;
    int maxIterEigenSolve;

    char *which;

    int verbose;

    double memRequested;
    double highMem;

    int orthoOp;
    int outerIter;
    int stifOp;

    double timeOuterLoop;
    double timePostProce;
    double timeStifOp;

    // Don't define these functions
    ARPACKm1(const ARPACKm1 &ref);
    ARPACKm1& operator=(const ARPACKm1 &ref);

  public:

    ARPACKm1(const Epetra_Comm &_Comm, const Epetra_Operator *KK,
              double _tol = 1.0e-08, int _maxIter = 100, int _verb = 0);

    ARPACKm1(const Epetra_Comm &_Comm, const Epetra_Operator *KK, char *_which,
              double _tol = 1.0e-08, int _maxIter = 100, int _verb = 0);

    ~ARPACKm1() { }

    int solve(int numEigen, Epetra_MultiVector &Q, double *lambda);

    int reSolve(int numEigen, Epetra_MultiVector &Q, double *lambda, int startingEV = 0);

    int minimumSpaceDimension(int nev) const         { return nev+1; }

    void initializeCounters();

    void algorithmInfo() const;
    void memoryInfo() const;
    void operationInfo() const;
    void timeInfo() const;

};

#endif
