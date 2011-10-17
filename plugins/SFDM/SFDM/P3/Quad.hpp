// Copyright (C) 2010-2011 von Karman Institute for Fluid Dynamics, Belgium
//
// This software is distributed under the terms of the
// GNU Lesser General Public License version 3 (LGPLv3).
// See doc/lgpl.txt and doc/gpl.txt for the license text.

#ifndef CF_SFDM_P3_Quad_hpp
#define CF_SFDM_P3_Quad_hpp

#include "SFDM/ShapeFunction.hpp"

namespace CF {
namespace SFDM {
namespace P3 {

//////////////////////////////////////////////////////////////////////////////

class SFDM_API Quad  : public ShapeFunction {
public:

  typedef boost::shared_ptr<Quad>       Ptr;
  typedef boost::shared_ptr<Quad const> ConstPtr;

  static const Mesh::GeoShape::Type shape          = Mesh::GeoShape::QUAD;
  static const Uint                 nb_nodes       = 16;
  static const Uint                 dimensionality = 2;
  static const Uint                 order          = 3;

  enum FaceNumbering { ETA_NEG = 0 , KSI_POS = 1 , ETA_POS = 2 , KSI_NEG = 3 };

public:

  /// Constructor
  Quad(const std::string& name = type_name());

  /// Type name
  static std::string type_name() { return "Quad"; }

  virtual const ShapeFunction& line() const;
  virtual const ShapeFunction& flux_line() const;

  virtual const RealMatrix& local_coordinates() const;

  virtual void compute_value(const RealVector& local_coordinate, RealRowVector& value) const;
  virtual void compute_gradient(const RealVector& local_coordinate, RealMatrix& gradient) const;

};

//////////////////////////////////////////////////////////////////////////////

} // P3
} // SFDM
} // CF

#endif // CF_Mesh_P3_Quad
