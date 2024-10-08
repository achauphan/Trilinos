// @HEADER
// *****************************************************************************
//        MueLu: A package for multigrid based preconditioning
//
// Copyright 2012 NTESS and the MueLu contributors.
// SPDX-License-Identifier: BSD-3-Clause
// *****************************************************************************
// @HEADER

#ifndef MUELU_REGIONRFACTORY_DECL_HPP
#define MUELU_REGIONRFACTORY_DECL_HPP

#include "MueLu_ConfigDefs.hpp"

#include "MueLu_TwoLevelFactoryBase.hpp"
#include "MueLu_RegionRFactory_fwd.hpp"

namespace MueLu {

/*!
  @class RegionRFactory class
  @brief Factory that builds a restriction operator for region multigrid
*/

template <class Scalar        = DefaultScalar,
          class LocalOrdinal  = DefaultLocalOrdinal,
          class GlobalOrdinal = DefaultGlobalOrdinal,
          class Node          = DefaultNode>
class RegionRFactory : public TwoLevelFactoryBase {
#undef MUELU_REGIONRFACTORY_SHORT
#include "MueLu_UseShortNames.hpp"

 public:
  using real_type                  = typename Teuchos::ScalarTraits<SC>::coordinateType;
  using realvaluedmultivector_type = typename Xpetra::MultiVector<real_type, LO, GO, NO>;

  //! @name Constructors/Destructors.
  //@{

  //! Default Constructor
  RegionRFactory() = default;

  //! Destructor
  virtual ~RegionRFactory() = default;
  //@}

  //! Input
  //@{
  RCP<const ParameterList> GetValidParameterList() const;

  void DeclareInput(Level& fineLevel, Level& coarseLevel) const;

  //@}

  //! @name Build methods.
  //@{

  void Build(Level& fineLevel, Level& coarseLevel) const;

  void Build3D(const int numDimensions,
               Array<LO>& lFineNodesPerDim,
               const RCP<Matrix>& A,
               const RCP<realvaluedmultivector_type>& fineCoordinates,
               RCP<Matrix>& R,
               RCP<realvaluedmultivector_type>& coarseCoordinates,
               Array<LO>& lCoarseNodesPerDim) const;

  //@}

};  // class RegionRFactory

}  // namespace MueLu

#define MUELU_REGIONRFACTORY_SHORT
#endif  // MUELU_REGIONRFACTORY_DECL_HPP
