// Copyright (C) 2010 von Karman Institute for Fluid Dynamics, Belgium
//
// This software is distributed under the terms of the
// GNU Lesser General Public License version 3 (LGPLv3).
// See doc/lgpl.txt and doc/gpl.txt for the license text.

#include "Common/OptionT.hpp"
#include "Common/OptionURI.hpp"

#include "Solver/CSolver.hpp"

namespace CF {
namespace Solver {

using namespace Common;

////////////////////////////////////////////////////////////////////////////////

CSolver::CSolver ( const std::string& name  ) :
  CMethod ( name )
{
  mark_basic();

  // properties

  properties()["brief"] = std::string("Solver");
  properties()["description"] = std::string("");

  // options

  m_properties.add_option< OptionURI > ("Domain",
                                        "Domain to solve",
                                        URI("cpath:../Domain"));

  // signals

  regist_signal ("solve" ,
                 "Solves",
                 "Solve" )
      ->connect ( boost::bind ( &CSolver::signal_solve, this, _1 ) );
}

////////////////////////////////////////////////////////////////////////////////

CSolver::~CSolver()
{
}

////////////////////////////////////////////////////////////////////////////////

void CSolver::signal_solve ( Common::Signal::arg_t& node )
{
  this->solve(); // dispatch to the virtual function
}

////////////////////////////////////////////////////////////////////////////////

} // Solver
} // CF