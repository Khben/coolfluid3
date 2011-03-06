// Copyright (C) 2010 von Karman Institute for Fluid Dynamics, Belgium
//
// This software is distributed under the terms of the
// GNU Lesser General Public License version 3 (LGPLv3).
// See doc/lgpl.txt and doc/gpl.txt for the license text.

#include "Common/URI.hpp"
#include "Common/CreateComponent.hpp"

#include "Common/OptionArray.hpp"
#include "Common/OptionComponent.hpp"

#include "Mesh/CRegion.hpp"
#include "Mesh/CMesh.hpp"

#include "RDM/Action.hpp"

/////////////////////////////////////////////////////////////////////////////////////

using namespace CF::Common;
using namespace CF::Mesh;

namespace CF {
namespace RDM {

/////////////////////////////////////////////////////////////////////////////////////

Action::Action ( const std::string& name ) :
  Common::CAction(name)
{
  mark_basic();

  // options

  m_properties.add_option( OptionComponent<CMesh>::create("Mesh",
                                                          "Mesh the Discretization Method will be applied to",
                                                          &m_mesh))
    ->mark_basic()
    ->add_tag("mesh");

//  m_properties["Mesh"].as_option().attach_trigger ( boost::bind ( & Action::config_mesh, this ) );

  std::vector< URI > dummy;
  m_properties.add_option< OptionArrayT < URI > > ("Regions", "Regions to loop over", dummy);

  m_properties["Regions"].as_option().attach_trigger ( boost::bind ( &Action::config_regions,   this ) );

}

Action::~Action() {}

/////////////////////////////////////////////////////////////////////////////////////

void Action::config_regions()
{
  std::vector<URI> vec; property("Regions").put_value(vec);

  boost_foreach(const URI region_path, vec)
  {
    Component& comp = access_component(region_path);

    if ( CRegion::Ptr region = comp.as_ptr<CRegion>() )
      m_loop_regions.push_back( region );
    else
      throw ValueNotFound ( FromHere(), "Could not find region with path [" + region_path.path() +"]" );
  }
}

/////////////////////////////////////////////////////////////////////////////////////

} // RDM
} // CF

/////////////////////////////////////////////////////////////////////////////////////
