// Copyright (C) 2010 von Karman Institute for Fluid Dynamics, Belgium
//
// This software is distributed under the terms of the
// GNU Lesser General Public License version 3 (LGPLv3).
// See doc/lgpl.txt and doc/gpl.txt for the license text.

#ifndef CF_Mesh_CGNS_CReader_hpp
#define CF_Mesh_CGNS_CReader_hpp

////////////////////////////////////////////////////////////////////////////////

#include "Mesh/CMeshReader.hpp"
#include "Mesh/CGNS/LibCGNS.hpp"
#include "Mesh/CGNS/Shared.hpp"

////////////////////////////////////////////////////////////////////////////////
#include "Mesh/CElements.hpp"

namespace CF {
namespace Mesh {
  class CRegion;
namespace CGNS {

//////////////////////////////////////////////////////////////////////////////

/// This class defines CGNS mesh format reader
/// @author Willem Deconinck
  class CGNS_API CReader : public CMeshReader, public CGNS::Shared
{
public: // typedefs

  typedef boost::shared_ptr<CReader> Ptr;
  typedef boost::shared_ptr<CReader const> ConstPtr;

private: // typedefs

  typedef std::pair<boost::shared_ptr<CElements>,Uint> Region_TableIndex_pair;

public: // functions

  /// Contructor
  /// @param name of the component
  CReader ( const CName& name );

  /// Gets the Class name
  static std::string type_name() { return "CReader"; }

  virtual void read_from_to(boost::filesystem::path& fp, const boost::shared_ptr<CMesh>& mesh);

  virtual std::string get_format() { return "CGNS"; }

  virtual std::vector<std::string> get_extensions();

  static void define_config_properties ( CF::Common::PropertyList& options );

private: // functions

  void read_base(CMesh& parent_region);
  void read_zone(CRegion& parent_region);
  void read_coordinates_unstructured(CRegion& parent_region);
  void read_coordinates_structured(CRegion& parent_region);
  void read_section(CRegion& parent_region);
  void create_structured_elements(CRegion& parent_region);
  void read_boco_unstructured(CRegion& parent_region);
  void read_boco_structured(CRegion& parent_region);
  Uint get_total_nbElements();

  Uint structured_node_idx(Uint i, Uint j, Uint k)
  {
    return i + j*m_zone.nbVertices[XX] + k*m_zone.nbVertices[XX]*m_zone.nbVertices[YY];
  }
  Uint structured_elm_idx(Uint i, Uint j, Uint k)
  {
    return i + j*(m_zone.nbVertices[XX]-1) + k*(m_zone.nbVertices[XX]-1)*(m_zone.nbVertices[YY]-1);
  }

private: // helper functions

  /// regists all the signals declared in this class
  static void regist_signals ( Component* self ) {}

private: // data

  std::vector<Region_TableIndex_pair> m_global_to_region;
  boost::shared_ptr<CMesh> m_mesh;
  Uint m_coord_start_idx;

}; // end CReader


////////////////////////////////////////////////////////////////////////////////

} // CGNS
} // Mesh
} // CF

////////////////////////////////////////////////////////////////////////////////

#endif // CF_Mesh_CGNS_CReader_hpp
