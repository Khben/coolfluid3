// Copyright (C) 2010 von Karman Institute for Fluid Dynamics, Belgium
//
// This software is distributed under the terms of the
// GNU Lesser General Public License version 3 (LGPLv3).
// See doc/lgpl.txt and doc/gpl.txt for the license text.

#include "Scalar2D.hpp"

namespace CF {
namespace Physics {
namespace Scalar {

using namespace Common;

////////////////////////////////////////////////////////////////////////////////

Scalar2D::Scalar2D( const std::string& name ) : Physics::PhysModel(name)
{
}

Scalar2D::~Scalar2D()
{
}

////////////////////////////////////////////////////////////////////////////////

} // Scalar
} // Physics
} // CF
