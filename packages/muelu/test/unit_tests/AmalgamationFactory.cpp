// @HEADER
//
// ***********************************************************************
//
//        MueLu: A package for multigrid based preconditioning
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
// // Questions? Contact
//                    Jonathan Hu       (jhu@sandia.gov)
//                    Andrey Prokopenko (aprokop@sandia.gov)
//                    Ray Tuminaro      (rstumin@sandia.gov)
//
// ***********************************************************************
//
// @HEADER
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_ScalarTraits.hpp>

#include <MueLu_config.hpp>

#include <MueLu_TestHelpers.hpp>
#include <MueLu_Version.hpp>

#include <MueLu_AmalgamationFactory.hpp>

namespace MueLuTests {

TEUCHOS_UNIT_TEST_TEMPLATE_4_DECL(AmalgamationFactory, Constructor, Scalar, LocalOrdinal, GlobalOrdinal, Node) {
#include <MueLu_UseShortNames.hpp>
  MUELU_TESTING_SET_OSTREAM;
  MUELU_TESTING_LIMIT_SCOPE(Scalar, GlobalOrdinal, Node);
  out << "version: " << MueLu::Version() << std::endl;

  RCP<AmalgamationFactory> amalgamationFactory = rcp(new AmalgamationFactory());

  TEST_INEQUALITY(amalgamationFactory, Teuchos::null);
}  // Constructor

TEUCHOS_UNIT_TEST_TEMPLATE_4_DECL(AmalgamationFactory, DOFGid2NodeId, Scalar, LocalOrdinal, GlobalOrdinal, Node) {
#include <MueLu_UseShortNames.hpp>
  MUELU_TESTING_SET_OSTREAM;
  MUELU_TESTING_LIMIT_SCOPE(Scalar, GlobalOrdinal, Node);
  out << "version: " << MueLu::Version() << std::endl;

  RCP<const Teuchos::Comm<int> > comm = TestHelpers::Parameters::getDefaultComm();
  Xpetra::UnderlyingLib lib           = MueLuTests::TestHelpers::Parameters::getLib();

  // Test layout: 1D mesh w/ 3 DOFs per node
  const GlobalOrdinal numGlobalNodes = 12;
  const LocalOrdinal numDofsPerNode  = 3;
  const GlobalOrdinal indexBase      = 3;
  RCP<const Map> nodeMap             = MapFactory::Build(lib, numGlobalNodes, indexBase, comm);
  RCP<const Map> dofMap              = MapFactory::Build(lib, numGlobalNodes * numDofsPerNode, indexBase, comm);

  // Probe all nodes in the mesh
  const LocalOrdinal numLocalDofs = dofMap->getLocalNumElements();
  LocalOrdinal localNodeID        = Teuchos::ScalarTraits<LocalOrdinal>::zero();
  for (LocalOrdinal localDofID = 0; localDofID < numLocalDofs; ++localDofID) {
    // Ask AmalgamationFactory for global node ID of this DOF and check w/ expected result
    GlobalOrdinal nodeID = AmalgamationFactory::DOFGid2NodeId(dofMap->getGlobalElement(localDofID), numDofsPerNode, 0, indexBase);
    TEST_EQUALITY(nodeID, nodeMap->getGlobalElement(localNodeID));

    // Increment localNodeId, if this is the first DOF of a node
    if (localDofID % numDofsPerNode == numDofsPerNode - Teuchos::ScalarTraits<LocalOrdinal>::one())
      ++localNodeID;
  }
}  // DOFGid2NodeId

TEUCHOS_UNIT_TEST_TEMPLATE_4_DECL(AmalgamationFactory, AmalgamateMap, Scalar, LocalOrdinal, GlobalOrdinal, Node) {
  // Test static method AmalgamationFactory::AmalgamateMap().
#include <MueLu_UseShortNames.hpp>
  MUELU_TESTING_SET_OSTREAM;
  MUELU_TESTING_LIMIT_SCOPE(Scalar, GlobalOrdinal, Node);
  out << "Test static method AmalgamationFactory::AmalgamateMap()." << std::endl;

  RCP<const Teuchos::Comm<int> > comm = TestHelpers::Parameters::getDefaultComm();

  const GlobalOrdinal nx = 32;
  Teuchos::ParameterList matrixList;
  matrixList.set("nx", nx);
  matrixList.set("matrixType", "Laplace1D");
  RCP<Matrix> Op = TestHelpers::TestFactory<Scalar, LO, GO, NO>::BuildMatrix(matrixList, TestHelpers::Parameters::getLib());
  LO blkSize     = 2;
  Op->SetFixedBlockSize(blkSize);

  RCP<Array<LO> > theRowTranslation = rcp(new Array<LO>);
  RCP<const Map> uniqueMap;
  AmalgamationFactory::AmalgamateMap(*(Op->getRowMap()), *Op, uniqueMap, *theRowTranslation);

  Teuchos::ArrayView<const GO> localEltList = uniqueMap->getLocalElementList();
  for (size_t j = 0; j < uniqueMap->getLocalNumElements(); j++) {
    TEST_EQUALITY(uniqueMap->getLocalElement(localEltList[j]), static_cast<LO>(j));
  }

  RCP<Array<LO> > theColTranslation = rcp(new Array<LO>);
  RCP<const Map> nonUniqueMap;
  AmalgamationFactory::AmalgamateMap(*(Op->getColMap()), *Op, nonUniqueMap, *theColTranslation);

  localEltList = nonUniqueMap->getLocalElementList();
  for (size_t j = 0; j < nonUniqueMap->getLocalNumElements(); j++) {
    TEST_EQUALITY(nonUniqueMap->getLocalElement(localEltList[j]), static_cast<LO>(j));
  }

}  // AmalgamateMap

TEUCHOS_UNIT_TEST_TEMPLATE_4_DECL(AmalgamationFactory, GidOffset, Scalar, LocalOrdinal, GlobalOrdinal, Node) {
  // Test static method AmalgamationFactory::GidOffset().
#include <MueLu_UseShortNames.hpp>
  MUELU_TESTING_SET_OSTREAM;
  MUELU_TESTING_LIMIT_SCOPE(Scalar, GlobalOrdinal, Node);
  out << "Test static method AmalgamationFactory::GidOffset()." << std::endl;

  RCP<const Teuchos::Comm<int> > comm = TestHelpers::Parameters::getDefaultComm();
  Xpetra::UnderlyingLib lib           = MueLuTests::TestHelpers::Parameters::getLib();

  const GO n         = 32;
  const LO blkSize   = 2;
  const GO indexBase = 3;
  const GO offset    = 101;

  std::vector<size_t> stridedInfo;
  stridedInfo.push_back(blkSize);

  // Case 1: Zero starting GIDs with offset set
  RCP<StridedMap> correct_strided_map = RCP(new StridedMap(lib, n, indexBase, stridedInfo, comm, 0, offset));
  TEST_EQUALITY(offset, AmalgamationFactory::GidOffset(correct_strided_map)); // -> offset = 101
  TEST_EQUALITY(offset, correct_strided_map->getOffset());                    // -> offset = 101

  // Case 2: Non-zero starting GIDs shifted by offset and variable correctly set
  RCP<StridedMap> still_correct_strided_map = RCP(new StridedMap(correct_strided_map->getMap(), stridedInfo, indexBase, 0, offset));
  TEST_EQUALITY(offset, AmalgamationFactory::GidOffset(still_correct_strided_map)); // -> offset = 101
  TEST_EQUALITY(offset, still_correct_strided_map->getOffset());                    // -> offset = 101

  // Case 3: Non-zero starting GIDs shifted by offset, but offset variable information not correctly available
  // (this can happen if a Xpetra::BlockedCrsMatrix with offset is converted to Thyra -> offset information is lost, but GIDs preserved)
  RCP<StridedMap> faulty_strided_map = RCP(new StridedMap(correct_strided_map->getMap(), stridedInfo, indexBase));
  TEST_EQUALITY(offset, AmalgamationFactory::GidOffset(faulty_strided_map)); // -> offset = 101
  TEST_INEQUALITY(offset, faulty_strided_map->getOffset());                  // -> offset = 0

}  // AmalgamateMap

#define MUELU_ETI_GROUP(Scalar, LO, GO, Node)                                                    \
  TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT(AmalgamationFactory, Constructor, Scalar, LO, GO, Node)   \
  TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT(AmalgamationFactory, DOFGid2NodeId, Scalar, LO, GO, Node) \
  TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT(AmalgamationFactory, AmalgamateMap, Scalar, LO, GO, Node) \
  TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT(AmalgamationFactory, GidOffset, Scalar, LO, GO, Node)

#include <MueLu_ETI_4arg.hpp>

}  // namespace MueLuTests
