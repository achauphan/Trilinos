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
#ifndef XPETRA_TPETRACRSGRAPH_HPP
#define XPETRA_TPETRACRSGRAPH_HPP

/* this file is automatically generated - do not edit (see script/tpetra.py) */

#include "Xpetra_TpetraConfigDefs.hpp"

#include "Xpetra_CrsGraph.hpp"

#include "Tpetra_CrsGraph.hpp"

#include "Xpetra_Utils.hpp"

#include "Xpetra_TpetraMap.hpp"

#include "Xpetra_TpetraImport.hpp"

#include "Xpetra_TpetraExport.hpp"

namespace Xpetra {

  // TODO: move that elsewhere
  template <class LocalOrdinal, class GlobalOrdinal, class Node>
  RCP<const CrsGraph<LocalOrdinal, GlobalOrdinal, Node> >
  toXpetra (RCP<const Tpetra::CrsGraph<LocalOrdinal, GlobalOrdinal, Node> > graph);

  template <class LocalOrdinal, class GlobalOrdinal, class Node>
  RCP< const Tpetra::CrsGraph< LocalOrdinal, GlobalOrdinal, Node > >
  toTpetra (const RCP<const CrsGraph< LocalOrdinal, GlobalOrdinal, Node> >& graph);

  template <class LocalOrdinal = CrsGraph<>::local_ordinal_type,
            class GlobalOrdinal = typename CrsGraph<LocalOrdinal>::global_ordinal_type,
            class Node = typename CrsGraph<LocalOrdinal, GlobalOrdinal>::node_type>
  class TpetraCrsGraph
    : public CrsGraph<LocalOrdinal,GlobalOrdinal,Node>
  {

    // The following typedef is used by the XPETRA_DYNAMIC_CAST() macro.
    typedef TpetraCrsGraph<LocalOrdinal,GlobalOrdinal,Node> TpetraCrsGraphClass;
    typedef Map<LocalOrdinal,GlobalOrdinal,Node> map_type;

  public:

    //! @name Constructor/Destructor Methods
    //@{

    //! Constructor specifying fixed number of entries for each row.
    TpetraCrsGraph(const RCP< const map_type > &rowMap, size_t maxNumEntriesPerRow, ProfileType pftype=DynamicProfile, const RCP< ParameterList > &params=null)
      : graph_(Teuchos::rcp(new Tpetra::CrsGraph< LocalOrdinal, GlobalOrdinal, Node >(toTpetra(rowMap), maxNumEntriesPerRow, toTpetra(pftype), params))) {  }

    //! Constructor specifying (possibly different) number of entries in each row.
    TpetraCrsGraph(const RCP< const Map< LocalOrdinal, GlobalOrdinal, Node > > &rowMap, const ArrayRCP< const size_t > &NumEntriesPerRowToAlloc, ProfileType pftype=DynamicProfile, const RCP< ParameterList > &params=null)
      : graph_(Teuchos::rcp(new Tpetra::CrsGraph< LocalOrdinal, GlobalOrdinal, Node >(toTpetra(rowMap), NumEntriesPerRowToAlloc, toTpetra(pftype), params))) {  }

    //! Constructor specifying column Map and fixed number of entries for each row.
    TpetraCrsGraph(const RCP< const Map< LocalOrdinal, GlobalOrdinal, Node > > &rowMap, const RCP< const Map< LocalOrdinal, GlobalOrdinal, Node > > &colMap, size_t maxNumEntriesPerRow, ProfileType pftype=DynamicProfile, const RCP< ParameterList > &params=null)
      : graph_(Teuchos::rcp(new Tpetra::CrsGraph< LocalOrdinal, GlobalOrdinal, Node >(toTpetra(rowMap), toTpetra(colMap), maxNumEntriesPerRow, toTpetra(pftype), params))) {  }

    //! Constructor specifying column Map and number of entries in each row.
    TpetraCrsGraph(const RCP< const Map< LocalOrdinal, GlobalOrdinal, Node > > &rowMap, const RCP< const Map< LocalOrdinal, GlobalOrdinal, Node > > &colMap, const ArrayRCP< const size_t > &NumEntriesPerRowToAlloc, ProfileType pftype=DynamicProfile, const RCP< ParameterList > &params=null)
      : graph_(Teuchos::rcp(new Tpetra::CrsGraph< LocalOrdinal, GlobalOrdinal, Node >(toTpetra(rowMap), toTpetra(colMap), NumEntriesPerRowToAlloc, toTpetra(pftype), params))) {  }

    //! Destructor.
    virtual ~TpetraCrsGraph() {  }

    //@}

    //! @name Insertion/Removal Methods
    //@{

    //! Insert global indices into the graph.
    void insertGlobalIndices(GlobalOrdinal globalRow, const ArrayView< const GlobalOrdinal > &indices) { XPETRA_MONITOR("TpetraCrsGraph::insertGlobalIndices"); graph_->insertGlobalIndices(globalRow, indices); }

    //! Insert local indices into the graph.
    void insertLocalIndices(const LocalOrdinal localRow, const ArrayView< const LocalOrdinal > &indices) { XPETRA_MONITOR("TpetraCrsGraph::insertLocalIndices"); graph_->insertLocalIndices(localRow, indices); }

    //! Remove all graph indices from the specified local row.
    void removeLocalIndices(LocalOrdinal localRow) { XPETRA_MONITOR("TpetraCrsGraph::removeLocalIndices"); graph_->removeLocalIndices(localRow); }

    //@}

    //! @name Transformational Methods
    //@{

    //! Signal that data entry is complete, specifying domain and range maps.
    void fillComplete(const RCP< const Map< LocalOrdinal, GlobalOrdinal, Node > > &domainMap, const RCP< const Map< LocalOrdinal, GlobalOrdinal, Node > > &rangeMap, const RCP< ParameterList > &params=null) { XPETRA_MONITOR("TpetraCrsGraph::fillComplete"); graph_->fillComplete(toTpetra(domainMap), toTpetra(rangeMap), params); }

    //! Signal that data entry is complete.
    void fillComplete(const RCP< ParameterList > &params=null) { XPETRA_MONITOR("TpetraCrsGraph::fillComplete"); graph_->fillComplete(params); }

    //@}

    //! @name Methods implementing RowGraph.
    //@{

    //! Returns the communicator.
    RCP< const Comm< int > > getComm() const { XPETRA_MONITOR("TpetraCrsGraph::getComm"); return graph_->getComm(); }

    //! Returns the Map that describes the row distribution in this graph.
    RCP< const Map< LocalOrdinal, GlobalOrdinal, Node > >  getRowMap() const { XPETRA_MONITOR("TpetraCrsGraph::getRowMap"); return toXpetra(graph_->getRowMap()); }

    //! Returns the Map that describes the column distribution in this graph.
    RCP< const Map< LocalOrdinal, GlobalOrdinal, Node > >  getColMap() const { XPETRA_MONITOR("TpetraCrsGraph::getColMap"); return toXpetra(graph_->getColMap()); }

    //! Returns the Map associated with the domain of this graph.
    RCP< const Map< LocalOrdinal, GlobalOrdinal, Node > >  getDomainMap() const { XPETRA_MONITOR("TpetraCrsGraph::getDomainMap"); return toXpetra(graph_->getDomainMap()); }

    //! Returns the Map associated with the domain of this graph.
    RCP< const Map< LocalOrdinal, GlobalOrdinal, Node > >  getRangeMap() const { XPETRA_MONITOR("TpetraCrsGraph::getRangeMap"); return toXpetra(graph_->getRangeMap()); }

    //! Returns the importer associated with this graph.
    RCP< const Import< LocalOrdinal, GlobalOrdinal, Node > > getImporter() const { XPETRA_MONITOR("TpetraCrsGraph::getImporter"); return toXpetra(graph_->getImporter()); }

    //! Returns the exporter associated with this graph.
    RCP< const Export< LocalOrdinal, GlobalOrdinal, Node > > getExporter() const { XPETRA_MONITOR("TpetraCrsGraph::getExporter"); return toXpetra(graph_->getExporter()); }

    //! Returns the number of global rows in the graph.
    global_size_t getGlobalNumRows() const { XPETRA_MONITOR("TpetraCrsGraph::getGlobalNumRows"); return graph_->getGlobalNumRows(); }

    //! Returns the number of global columns in the graph.
    global_size_t getGlobalNumCols() const { XPETRA_MONITOR("TpetraCrsGraph::getGlobalNumCols"); return graph_->getGlobalNumCols(); }

    //! Returns the number of graph rows owned on the calling node.
    size_t getNodeNumRows() const { XPETRA_MONITOR("TpetraCrsGraph::getNodeNumRows"); return graph_->getNodeNumRows(); }

    //! Returns the number of columns connected to the locally owned rows of this graph.
    size_t getNodeNumCols() const { XPETRA_MONITOR("TpetraCrsGraph::getNodeNumCols"); return graph_->getNodeNumCols(); }

    //! Returns the index base for global indices for this graph.
    GlobalOrdinal getIndexBase() const { XPETRA_MONITOR("TpetraCrsGraph::getIndexBase"); return graph_->getIndexBase(); }

    //! Returns the global number of entries in the graph.
    global_size_t getGlobalNumEntries() const { XPETRA_MONITOR("TpetraCrsGraph::getGlobalNumEntries"); return graph_->getGlobalNumEntries(); }

    //! Returns the local number of entries in the graph.
    size_t getNodeNumEntries() const { XPETRA_MONITOR("TpetraCrsGraph::getNodeNumEntries"); return graph_->getNodeNumEntries(); }

    //! Returns the current number of entries on this node in the specified global row.
    size_t getNumEntriesInGlobalRow(GlobalOrdinal globalRow) const { XPETRA_MONITOR("TpetraCrsGraph::getNumEntriesInGlobalRow"); return graph_->getNumEntriesInGlobalRow(globalRow); }

    //! Returns the current number of entries on this node in the specified local row.
    size_t getNumEntriesInLocalRow(LocalOrdinal localRow) const { XPETRA_MONITOR("TpetraCrsGraph::getNumEntriesInLocalRow"); return graph_->getNumEntriesInLocalRow(localRow); }

    //! Returns the current number of allocated entries for this node in the specified global row .
    size_t getNumAllocatedEntriesInGlobalRow(GlobalOrdinal globalRow) const { XPETRA_MONITOR("TpetraCrsGraph::getNumAllocatedEntriesInGlobalRow"); return graph_->getNumAllocatedEntriesInGlobalRow(globalRow); }

    //! Returns the current number of allocated entries on this node in the specified local row.
    size_t getNumAllocatedEntriesInLocalRow(LocalOrdinal localRow) const { XPETRA_MONITOR("TpetraCrsGraph::getNumAllocatedEntriesInLocalRow"); return graph_->getNumAllocatedEntriesInLocalRow(localRow); }

    //! Returns the number of global diagonal entries, based on global row/column index comparisons.
    global_size_t getGlobalNumDiags() const { XPETRA_MONITOR("TpetraCrsGraph::getGlobalNumDiags"); return graph_->getGlobalNumDiags(); }

    //! Returns the number of local diagonal entries, based on global row/column index comparisons.
    size_t getNodeNumDiags() const { XPETRA_MONITOR("TpetraCrsGraph::getNodeNumDiags"); return graph_->getNodeNumDiags(); }

    //! Maximum number of entries in all rows over all processes.
    size_t getGlobalMaxNumRowEntries() const { XPETRA_MONITOR("TpetraCrsGraph::getGlobalMaxNumRowEntries"); return graph_->getGlobalMaxNumRowEntries(); }

    //! Maximum number of entries in all rows owned by the calling process.
    size_t getNodeMaxNumRowEntries() const { XPETRA_MONITOR("TpetraCrsGraph::getNodeMaxNumRowEntries"); return graph_->getNodeMaxNumRowEntries(); }

    //! Whether the graph has a column Map.
    bool hasColMap() const { XPETRA_MONITOR("TpetraCrsGraph::hasColMap"); return graph_->hasColMap(); }

    //! Whether the graph is locally lower triangular.
    bool isLowerTriangular() const { XPETRA_MONITOR("TpetraCrsGraph::isLowerTriangular"); return graph_->isLowerTriangular(); }

    //! Whether the graph is locally upper triangular.
    bool isUpperTriangular() const { XPETRA_MONITOR("TpetraCrsGraph::isUpperTriangular"); return graph_->isUpperTriangular(); }

    //! Whether column indices are stored using local indices on the calling process.
    bool isLocallyIndexed() const { XPETRA_MONITOR("TpetraCrsGraph::isLocallyIndexed"); return graph_->isLocallyIndexed(); }

    //! Whether column indices are stored using global indices on the calling process.
    bool isGloballyIndexed() const { XPETRA_MONITOR("TpetraCrsGraph::isGloballyIndexed"); return graph_->isGloballyIndexed(); }

    //! Whether fillComplete() has been called and the graph is in compute mode.
    bool isFillComplete() const { XPETRA_MONITOR("TpetraCrsGraph::isFillComplete"); return graph_->isFillComplete(); }

    //! Returns true if storage has been optimized.
    bool isStorageOptimized() const { XPETRA_MONITOR("TpetraCrsGraph::isStorageOptimized"); return graph_->isStorageOptimized(); }

    //! Return a const, nonpersisting view of global indices in the given row.
    void getGlobalRowView(GlobalOrdinal GlobalRow, ArrayView< const GlobalOrdinal > &Indices) const { XPETRA_MONITOR("TpetraCrsGraph::getGlobalRowView"); graph_->getGlobalRowView(GlobalRow, Indices); }

    //! Return a const, nonpersisting view of local indices in the given row.
    void getLocalRowView(LocalOrdinal LocalRow, ArrayView< const LocalOrdinal > &indices) const { XPETRA_MONITOR("TpetraCrsGraph::getLocalRowView"); graph_->getLocalRowView(LocalRow, indices); }

    //@}

    //! @name Overridden from Teuchos::Describable
    //@{

    //! Return a simple one-line description of this object.
    std::string description() const { XPETRA_MONITOR("TpetraCrsGraph::description"); return graph_->description(); }

    //! Print the object with some verbosity level to an FancyOStream object.
    void describe(Teuchos::FancyOStream &out, const Teuchos::EVerbosityLevel verbLevel=Teuchos::Describable::verbLevel_default) const { XPETRA_MONITOR("TpetraCrsGraph::describe"); graph_->describe(out, verbLevel); }

    //@}

    //! @name Advanced methods, at increased risk of deprecation.
    //@{

    //! Get an ArrayRCP of the row-offsets.
    ArrayRCP< const size_t > getNodeRowPtrs() const { XPETRA_MONITOR("TpetraCrsGraph::getNodeRowPtrs"); return graph_->getNodeRowPtrs(); }

    //@}

    //! Implements DistObject interface
    //{@

    //! Access function for the Tpetra::Map this DistObject was constructed with.
    Teuchos::RCP< const Map< LocalOrdinal, GlobalOrdinal, Node > > getMap() const { XPETRA_MONITOR("TpetraCrsGraph::getMap"); return rcp( new TpetraMap< LocalOrdinal, GlobalOrdinal, Node >(graph_->getMap()) ); }

    //! Import.
    void doImport(const DistObject<GlobalOrdinal, LocalOrdinal, GlobalOrdinal, Node> &source,
                  const Import< LocalOrdinal, GlobalOrdinal, Node > &importer, CombineMode CM) {
      XPETRA_MONITOR("TpetraCrsGraph::doImport");

      XPETRA_DYNAMIC_CAST(const TpetraCrsGraphClass, source, tSource, "Xpetra::TpetraCrsGraph::doImport only accept Xpetra::TpetraCrsGraph as input arguments.");//TODO: remove and use toTpetra()
      RCP< const Tpetra::CrsGraph<LocalOrdinal, GlobalOrdinal, Node> > v = tSource.getTpetra_CrsGraph();
      //graph_->doImport(toTpetraCrsGraph(source), *tImporter.getTpetra_Import(), toTpetra(CM));

      graph_->doImport(*v, toTpetra(importer), toTpetra(CM));
    }

    //! Export.
    void doExport(const DistObject<GlobalOrdinal, LocalOrdinal, GlobalOrdinal, Node> &dest,
                  const Import< LocalOrdinal, GlobalOrdinal, Node >& importer, CombineMode CM) {
      XPETRA_MONITOR("TpetraCrsGraph::doExport");

      XPETRA_DYNAMIC_CAST(const TpetraCrsGraphClass, dest, tDest, "Xpetra::TpetraCrsGraph::doImport only accept Xpetra::TpetraCrsGraph as input arguments.");//TODO: remove and use toTpetra()
      RCP< const Tpetra::CrsGraph<LocalOrdinal, GlobalOrdinal, Node> > v = tDest.getTpetra_CrsGraph();
      graph_->doExport(*v, toTpetra(importer), toTpetra(CM));

    }

    //! Import (using an Exporter).
    void doImport(const DistObject<GlobalOrdinal, LocalOrdinal, GlobalOrdinal, Node> &source,
                  const Export< LocalOrdinal, GlobalOrdinal, Node >& exporter, CombineMode CM) {
      XPETRA_MONITOR("TpetraCrsGraph::doImport");

      XPETRA_DYNAMIC_CAST(const TpetraCrsGraphClass, source, tSource, "Xpetra::TpetraCrsGraph::doImport only accept Xpetra::TpetraCrsGraph as input arguments.");//TODO: remove and use toTpetra()
      RCP< const Tpetra::CrsGraph<LocalOrdinal, GlobalOrdinal, Node> > v = tSource.getTpetra_CrsGraph();

      graph_->doImport(*v, toTpetra(exporter), toTpetra(CM));

    }

    //! Export (using an Importer).
    void doExport(const DistObject<GlobalOrdinal, LocalOrdinal, GlobalOrdinal, Node> &dest,
                  const Export< LocalOrdinal, GlobalOrdinal, Node >& exporter, CombineMode CM) {
      XPETRA_MONITOR("TpetraCrsGraph::doExport");

      XPETRA_DYNAMIC_CAST(const TpetraCrsGraphClass, dest, tDest, "Xpetra::TpetraCrsGraph::doImport only accept Xpetra::TpetraCrsGraph as input arguments.");//TODO: remove and use toTpetra()
      RCP< const Tpetra::CrsGraph<LocalOrdinal, GlobalOrdinal, Node> > v = tDest.getTpetra_CrsGraph();

      graph_->doExport(*v, toTpetra(exporter), toTpetra(CM));

    }

    // @}

    //! @name Xpetra specific
    //@{

    //! TpetraCrsGraph constructor to wrap a Tpetra::CrsGraph object
    TpetraCrsGraph(const Teuchos::RCP<Tpetra::CrsGraph<LocalOrdinal, GlobalOrdinal, Node> > &graph) : graph_(graph) { }

    //! Get the underlying Tpetra graph
    RCP< const Tpetra::CrsGraph<LocalOrdinal, GlobalOrdinal, Node> > getTpetra_CrsGraph() const { return graph_; }

    //@}

  private:
    RCP< Tpetra::CrsGraph<LocalOrdinal, GlobalOrdinal, Node> > graph_;
  }; // TpetraCrsGraph class

  // TODO: move that elsewhere
  template <class LocalOrdinal, class GlobalOrdinal, class Node>
  RCP<const CrsGraph<LocalOrdinal, GlobalOrdinal, Node> >
  toXpetra (RCP<const Tpetra::CrsGraph<LocalOrdinal, GlobalOrdinal, Node> > graph)
  { //TODO: return TpetraCrsGraph instead of CrsGraph
    // typedef TpetraCrsGraph<LocalOrdinal, GlobalOrdinal, Node> TpetraCrsGraphClass;
    // XPETRA_RCP_DYNAMIC_CAST(const TpetraCrsGraphClass, graph, tGraph, "toTpetra");
    if (graph.is_null ()) {
      return Teuchos::null;
    }
    RCP<Tpetra::CrsGraph<LocalOrdinal, GlobalOrdinal, Node> > tGraph =
      Teuchos::rcp_const_cast<Tpetra::CrsGraph<LocalOrdinal, GlobalOrdinal, Node> > (graph);
    return rcp (new Xpetra::TpetraCrsGraph<LocalOrdinal, GlobalOrdinal, Node> (tGraph));
  }

  template <class LocalOrdinal, class GlobalOrdinal, class Node>
  RCP< const Tpetra::CrsGraph< LocalOrdinal, GlobalOrdinal, Node > >
  toTpetra (const RCP<const CrsGraph<LocalOrdinal, GlobalOrdinal, Node> > &graph)
  {
    typedef TpetraCrsGraph<LocalOrdinal, GlobalOrdinal, Node> TpetraCrsGraphClass;
    XPETRA_RCP_DYNAMIC_CAST(const TpetraCrsGraphClass, graph, tpetraCrsGraph, "toTpetra");
    return tpetraCrsGraph->getTpetra_CrsGraph ();
  }


#ifndef HAVE_XPETRA_TPETRA_INST_INT_INT
  // specialization of TpetraCrsGraph for GO=LO=int
  template <class Node>
  class TpetraCrsGraph<int,int,Node>
    : public CrsGraph<int,int,Node>
  {
    typedef int LocalOrdinal;
    typedef int GlobalOrdinal;

    // The following typedef is used by the XPETRA_DYNAMIC_CAST() macro.
    typedef TpetraCrsGraph<LocalOrdinal,GlobalOrdinal,Node> TpetraCrsGraphClass;
    typedef Map<LocalOrdinal,GlobalOrdinal,Node> map_type;

  public:

    //! @name Constructor/Destructor Methods
    //@{

    //! Constructor specifying fixed number of entries for each row.
    TpetraCrsGraph(const RCP< const map_type > &rowMap, size_t maxNumEntriesPerRow, ProfileType pftype=DynamicProfile, const RCP< ParameterList > &params=null) {
      XPETRA_TPETRA_ETI_EXCEPTION("TpetraCrsGraph<int,int>", "TpetraCrsGraph<int,int>", "int");
    }

    //! Constructor specifying (possibly different) number of entries in each row.
    TpetraCrsGraph(const RCP< const Map< LocalOrdinal, GlobalOrdinal, Node > > &rowMap, const ArrayRCP< const size_t > &NumEntriesPerRowToAlloc, ProfileType pftype=DynamicProfile, const RCP< ParameterList > &params=null) {
      XPETRA_TPETRA_ETI_EXCEPTION("TpetraCrsGraph<int,int>", "TpetraCrsGraph<int,int>", "int");
    }

    //! Constructor specifying column Map and fixed number of entries for each row.
    TpetraCrsGraph(const RCP< const Map< LocalOrdinal, GlobalOrdinal, Node > > &rowMap, const RCP< const Map< LocalOrdinal, GlobalOrdinal, Node > > &colMap, size_t maxNumEntriesPerRow, ProfileType pftype=DynamicProfile, const RCP< ParameterList > &params=null) {
      XPETRA_TPETRA_ETI_EXCEPTION("TpetraCrsGraph<int,int>", "TpetraCrsGraph<int,int>", "int");
    }

    //! Constructor specifying column Map and number of entries in each row.
    TpetraCrsGraph(const RCP< const Map< LocalOrdinal, GlobalOrdinal, Node > > &rowMap, const RCP< const Map< LocalOrdinal, GlobalOrdinal, Node > > &colMap, const ArrayRCP< const size_t > &NumEntriesPerRowToAlloc, ProfileType pftype=DynamicProfile, const RCP< ParameterList > &params=null) {
      XPETRA_TPETRA_ETI_EXCEPTION("TpetraCrsGraph<int,int>", "TpetraCrsGraph<int,int>", "int");
    }

    //! Destructor.
    virtual ~TpetraCrsGraph() {  }

    //@}

    //! @name Insertion/Removal Methods
    //@{

    //! Insert global indices into the graph.
    void insertGlobalIndices(GlobalOrdinal globalRow, const ArrayView< const GlobalOrdinal > &indices) { }

    //! Insert local indices into the graph.
    void insertLocalIndices(const LocalOrdinal localRow, const ArrayView< const LocalOrdinal > &indices) { }

    //! Remove all graph indices from the specified local row.
    void removeLocalIndices(LocalOrdinal localRow) { }

    //@}

    //! @name Transformational Methods
    //@{

    //! Signal that data entry is complete, specifying domain and range maps.
    void fillComplete(const RCP< const Map< LocalOrdinal, GlobalOrdinal, Node > > &domainMap, const RCP< const Map< LocalOrdinal, GlobalOrdinal, Node > > &rangeMap, const RCP< ParameterList > &params=null) { }

    //! Signal that data entry is complete.
    void fillComplete(const RCP< ParameterList > &params=null) { }

    //@}

    //! @name Methods implementing RowGraph.
    //@{

    //! Returns the communicator.
    RCP< const Comm< int > > getComm() const { return Teuchos::null; }

    //! Returns the Map that describes the row distribution in this graph.
    RCP< const Map< LocalOrdinal, GlobalOrdinal, Node > >  getRowMap() const { return Teuchos::null; }

    //! Returns the Map that describes the column distribution in this graph.
    RCP< const Map< LocalOrdinal, GlobalOrdinal, Node > >  getColMap() const { return Teuchos::null; }

    //! Returns the Map associated with the domain of this graph.
    RCP< const Map< LocalOrdinal, GlobalOrdinal, Node > >  getDomainMap() const { return Teuchos::null; }

    //! Returns the Map associated with the domain of this graph.
    RCP< const Map< LocalOrdinal, GlobalOrdinal, Node > >  getRangeMap() const { return Teuchos::null; }

    //! Returns the importer associated with this graph.
    RCP< const Import< LocalOrdinal, GlobalOrdinal, Node > > getImporter() const { return Teuchos::null; }

    //! Returns the exporter associated with this graph.
    RCP< const Export< LocalOrdinal, GlobalOrdinal, Node > > getExporter() const { return Teuchos::null; }

    //! Returns the number of global rows in the graph.
    global_size_t getGlobalNumRows() const { return 0; }

    //! Returns the number of global columns in the graph.
    global_size_t getGlobalNumCols() const { return 0; }

    //! Returns the number of graph rows owned on the calling node.
    size_t getNodeNumRows() const { return 0; }

    //! Returns the number of columns connected to the locally owned rows of this graph.
    size_t getNodeNumCols() const { return 0; }

    //! Returns the index base for global indices for this graph.
    GlobalOrdinal getIndexBase() const { return 0; }

    //! Returns the global number of entries in the graph.
    global_size_t getGlobalNumEntries() const { return 0; }

    //! Returns the local number of entries in the graph.
    size_t getNodeNumEntries() const { return 0; }

    //! Returns the current number of entries on this node in the specified global row.
    size_t getNumEntriesInGlobalRow(GlobalOrdinal globalRow) const { return 0; }

    //! Returns the current number of entries on this node in the specified local row.
    size_t getNumEntriesInLocalRow(LocalOrdinal localRow) const { return 0; }

    //! Returns the current number of allocated entries for this node in the specified global row .
    size_t getNumAllocatedEntriesInGlobalRow(GlobalOrdinal globalRow) const { return 0; }

    //! Returns the current number of allocated entries on this node in the specified local row.
    size_t getNumAllocatedEntriesInLocalRow(LocalOrdinal localRow) const { return 0; }

    //! Returns the number of global diagonal entries, based on global row/column index comparisons.
    global_size_t getGlobalNumDiags() const { return 0; }

    //! Returns the number of local diagonal entries, based on global row/column index comparisons.
    size_t getNodeNumDiags() const { return 0; }

    //! Maximum number of entries in all rows over all processes.
    size_t getGlobalMaxNumRowEntries() const { return 0; }

    //! Maximum number of entries in all rows owned by the calling process.
    size_t getNodeMaxNumRowEntries() const { return 0; }

    //! Whether the graph has a column Map.
    bool hasColMap() const { return false; }

    //! Whether the graph is locally lower triangular.
    bool isLowerTriangular() const { return false; }

    //! Whether the graph is locally upper triangular.
    bool isUpperTriangular() const { return false; }

    //! Whether column indices are stored using local indices on the calling process.
    bool isLocallyIndexed() const { return false; }

    //! Whether column indices are stored using global indices on the calling process.
    bool isGloballyIndexed() const { return false; }

    //! Whether fillComplete() has been called and the graph is in compute mode.
    bool isFillComplete() const { return false; }

    //! Returns true if storage has been optimized.
    bool isStorageOptimized() const { return false; }

    //! Return a const, nonpersisting view of global indices in the given row.
    void getGlobalRowView(GlobalOrdinal GlobalRow, ArrayView< const GlobalOrdinal > &Indices) const {  }

    //! Return a const, nonpersisting view of local indices in the given row.
    void getLocalRowView(LocalOrdinal LocalRow, ArrayView< const LocalOrdinal > &indices) const {  }

    //@}

    //! @name Overridden from Teuchos::Describable
    //@{

    //! Return a simple one-line description of this object.
    std::string description() const { return std::string(""); }

    //! Print the object with some verbosity level to an FancyOStream object.
    void describe(Teuchos::FancyOStream &out, const Teuchos::EVerbosityLevel verbLevel=Teuchos::Describable::verbLevel_default) const {  }

    //@}

    //! @name Advanced methods, at increased risk of deprecation.
    //@{

    //! Get an ArrayRCP of the row-offsets.
    ArrayRCP< const size_t > getNodeRowPtrs() const { return Teuchos::ArrayRCP< const size_t>(); }

    //@}

    //! Implements DistObject interface
    //{@

    //! Access function for the Tpetra::Map this DistObject was constructed with.
    Teuchos::RCP< const Map< LocalOrdinal, GlobalOrdinal, Node > > getMap() const { return Teuchos::null; }

    //! Import.
    void doImport(const DistObject<GlobalOrdinal, LocalOrdinal, GlobalOrdinal, Node> &source,
                  const Import< LocalOrdinal, GlobalOrdinal, Node > &importer, CombineMode CM) { }

    //! Export.
    void doExport(const DistObject<GlobalOrdinal, LocalOrdinal, GlobalOrdinal, Node> &dest,
                  const Import< LocalOrdinal, GlobalOrdinal, Node >& importer, CombineMode CM) { }

    //! Import (using an Exporter).
    void doImport(const DistObject<GlobalOrdinal, LocalOrdinal, GlobalOrdinal, Node> &source,
                  const Export< LocalOrdinal, GlobalOrdinal, Node >& exporter, CombineMode CM) { }

    //! Export (using an Importer).
    void doExport(const DistObject<GlobalOrdinal, LocalOrdinal, GlobalOrdinal, Node> &dest,
                  const Export< LocalOrdinal, GlobalOrdinal, Node >& exporter, CombineMode CM) { }

    // @}

    //! @name Xpetra specific
    //@{

    //! TpetraCrsGraph constructor to wrap a Tpetra::CrsGraph object
    TpetraCrsGraph(const Teuchos::RCP<Tpetra::CrsGraph<LocalOrdinal, GlobalOrdinal, Node> > &graph)  { }

    //! Get the underlying Tpetra graph
    RCP< const Tpetra::CrsGraph<LocalOrdinal, GlobalOrdinal, Node> > getTpetra_CrsGraph() const { return Teuchos::null; }

    //@}
  }; // TpetraCrsGraph class (specialization for LO=GO=int)
#endif // #ifndef HAVE_XPETRA_TPETRA_INST_INT_INT
} // Xpetra namespace

#define XPETRA_TPETRACRSGRAPH_SHORT
#endif // XPETRA_TPETRACRSGRAPH_HPP
