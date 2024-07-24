// @HEADER
//
// ***********************************************************************
//
//             Xpetra: A linear algebra interface package
//                  Copyright 2012 Sandia Corporation
//
// Under the terms of Contract DE-AC04-94AL85000 with Sandia Corporation,
// the U.S. Government retains certain rights in this software.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
// 1. Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the distribution.
//
// 3. Neither the name of the Corporation nor the names of the
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY SANDIA CORPORATION "AS IS" AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL SANDIA CORPORATION OR THE
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Questions? Contact
//                    Jonathan Hu       (jhu@sandia.gov)
//                    Andrey Prokopenko (aprokop@sandia.gov)
//                    Ray Tuminaro      (rstumin@sandia.gov)
//
// ***********************************************************************
//
// @HEADER
#ifndef XPETRA_EPETRAIMPORT_HPP
#define XPETRA_EPETRAIMPORT_HPP

/* this file is automatically generated - do not edit (see script/epetra.py) */

#include "Xpetra_EpetraConfigDefs.hpp"

#include "Xpetra_Import.hpp"

#include "Xpetra_EpetraMap.hpp"  //TMP

#include "Epetra_Import.h"

#if defined(XPETRA_ENABLE_DEPRECATED_CODE)
#ifdef __GNUC__
#if defined(Xpetra_SHOW_DEPRECATED_WARNINGS)
#warning "The header file Trilinos/packages/xpetra/src/Import/Xpetra_EpetraImport.hpp is deprecated."
#endif
#endif
#else
#error "The header file Trilinos/packages/xpetra/src/Import/Xpetra_EpetraImport.hpp is deprecated."
#endif

namespace Xpetra {

template <class GlobalOrdinal, class Node>
XPETRA_DEPRECATED RCP<const Import<int, GlobalOrdinal, Node> > toXpetra(const Epetra_Import *import);
//

template <class EpetraGlobalOrdinal, class Node>
class XPETRA_DEPRECATED EpetraImportT
  : public Import<int, EpetraGlobalOrdinal, Node> {
  typedef int LocalOrdinal;
  typedef EpetraGlobalOrdinal GlobalOrdinal;
  //! The specialization of Map used by this class.
  typedef Map<LocalOrdinal, GlobalOrdinal, Node> map_type;

 public:
  //! @name Constructor/Destructor Methods
  //@{

  //! Construct an Import from the source and target Maps.
  EpetraImportT(const Teuchos::RCP<const map_type> &source, const Teuchos::RCP<const map_type> &target)
    : import_(rcp(new Epetra_Import(toEpetra<GlobalOrdinal, Node>(target), toEpetra<GlobalOrdinal, Node>(source)))) {}  // Warning: Epetra(Target, Source) vs. Tpetra(Source, Target)

  ////! Constructor (with list of parameters).
  // Definition not in cpp, so comment out
  // EpetraImportT(const Teuchos::RCP< const map_type > &source, const Teuchos::RCP< const map_type > &target, const Teuchos::RCP< Teuchos::ParameterList > &plist);

  ////! Copy constructor.
  // Definition commented out in cpp
  // EpetraImportT(const Import< LocalOrdinal, GlobalOrdinal, Node > &import);

  //! Destructor.
  ~EpetraImportT() {}

  //! Special "constructor"
  Teuchos::RCP<const Import<LocalOrdinal, GlobalOrdinal, Node> >
  createRemoteOnlyImport(const Teuchos::RCP<const map_type> &remoteTarget) const { TEUCHOS_TEST_FOR_EXCEPTION(1, Xpetra::Exceptions::NotImplemented, "TODO EpetraImportT<EpetraGlobalOrdinal>::createRemoteOnlyImport not implemented"); }

  //@}

  //! @name Import Attribute Methods
  //@{

  //! Number of initial identical IDs.
  size_t getNumSameIDs() const {
    XPETRA_MONITOR("EpetraImportT::getNumSameIDs");
    return import_->NumSameIDs();
  }

  //! Number of IDs to permute but not to communicate.
  size_t getNumPermuteIDs() const {
    XPETRA_MONITOR("EpetraImportT::getNumPermuteIDs");
    return import_->NumPermuteIDs();
  }

  //! List of local IDs in the source Map that are permuted.
  ArrayView<const LocalOrdinal> getPermuteFromLIDs() const {
    XPETRA_MONITOR("EpetraImportT::getPermuteFromLIDs");
    TEUCHOS_TEST_FOR_EXCEPTION(1, Xpetra::Exceptions::NotImplemented, "TODO EpetraImportT<EpetraGlobalOrdinal>::getExportImageIDs not implemented");
  }

  //! List of local IDs in the target Map that are permuted.
  ArrayView<const LocalOrdinal> getPermuteToLIDs() const {
    XPETRA_MONITOR("EpetraImportT::getPermuteToLIDs");
    TEUCHOS_TEST_FOR_EXCEPTION(1, Xpetra::Exceptions::NotImplemented, "TODO EpetraImportT<EpetraGlobalOrdinal>::getPermuteToLIDs not implemented");
  }

  //! Number of entries not on the calling process.
  size_t getNumRemoteIDs() const {
    XPETRA_MONITOR("EpetraImportT::getNumRemoteIDs");
    return import_->NumRemoteIDs();
  }

  //! List of entries in the target Map to receive from other processes.
  ArrayView<const LocalOrdinal> getRemoteLIDs() const {
    XPETRA_MONITOR("EpetraImportT::getRemoteLIDs");
    TEUCHOS_TEST_FOR_EXCEPTION(1, Xpetra::Exceptions::NotImplemented, "TODO EpetraImportT<EpetraGlobalOrdinal>::getRemoteLIDs not implemented");
  }

  //! List of entries in the target Map to receive from other processes.
  ArrayView<const LocalOrdinal> getRemotePIDs() const {
    XPETRA_MONITOR("EpetraImportT::getRemotePIDs");
    TEUCHOS_TEST_FOR_EXCEPTION(1, Xpetra::Exceptions::NotImplemented, "TODO EpetraImportT<EpetraGlobalOrdinal>::getRemotePIDs not implemented");
  }

  //! Number of entries that must be sent by the calling process to other processes.
  size_t getNumExportIDs() const {
    XPETRA_MONITOR("EpetraImportT::getNumExportIDs");
    return import_->NumExportIDs();
  }

  //! List of entries in the source Map that will be sent to other processes.
  ArrayView<const LocalOrdinal> getExportLIDs() const {
    XPETRA_MONITOR("EpetraImportT::getExportLIDs");
    TEUCHOS_TEST_FOR_EXCEPTION(1, Xpetra::Exceptions::NotImplemented, "TODO EpetraImportT<EpetraGlobalOrdinal>::getExportLIDs not implemented");
  }

  //! List of processes to which entries will be sent.
  ArrayView<const int> getExportPIDs() const {
    XPETRA_MONITOR("EpetraImportT::getExportImageIDs");
    return ArrayView<const int>(import_->ExportPIDs(), import_->NumExportIDs());
  }

  //! The Source Map used to construct this Import object.
  Teuchos::RCP<const Map<LocalOrdinal, GlobalOrdinal, Node> > getSourceMap() const {
    XPETRA_MONITOR("EpetraImportT::getSourceMap");
    return toXpetra<GlobalOrdinal, Node>(import_->SourceMap());
  }

  //! The Target Map used to construct this Import object.
  Teuchos::RCP<const Map<LocalOrdinal, GlobalOrdinal, Node> > getTargetMap() const {
    XPETRA_MONITOR("EpetraImportT::getTargetMap");
    return toXpetra<GlobalOrdinal, Node>(import_->TargetMap());
  }

  void setDistributorParameters(const Teuchos::RCP<Teuchos::ParameterList> params) const { XPETRA_MONITOR("EpetraImportT::setDistributorParameters"); }

  //@}

  //! @name I/O Methods
  //@{

  //! Print the Import's data to the given output stream.
  void print(std::ostream &os) const {
    XPETRA_MONITOR("EpetraImportT::print");
    import_->Print(os);
  }

  //@}

  //! @name Xpetra specific
  //@{

  //! EpetraImportT constructor to wrap a Epetra_Import object
  EpetraImportT(const RCP<const Epetra_Import> &import)
    : import_(import) {}

  //! Get the underlying Epetra import
  RCP<const Epetra_Import> getEpetra_Import() const { return import_; }

  //@}

 private:
  RCP<const Epetra_Import> import_;

};  // EpetraImportT class

}  // namespace Xpetra

#endif  // XPETRA_EPETRAIMPORT_HPP
