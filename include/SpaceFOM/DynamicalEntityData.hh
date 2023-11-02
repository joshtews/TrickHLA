/**
@file SpaceFOM/DynamicalEntityData.hh
@ingroup SpaceFOM
@brief A simple structure that contains the date fields required to encode
and decode a SISO Space Reference FOM DynamicalEntity data type.  Note: this
does not include the PhysicalEntity data.

@copyright Copyright 2023 United States Government as represented by the
Administrator of the National Aeronautics and Space Administration.
No copyright is claimed in the United States under Title 17, U.S. Code.
All Other Rights Reserved.

\par<b>Responsible Organization</b>
Simulation and Graphics Branch, Mail Code ER7\n
Software, Robotics & Simulation Division\n
NASA, Johnson Space Center\n
2101 NASA Parkway, Houston, TX  77058

@trick_parse{everything}

@python_module{SpaceFOM}

@revs_begin
@rev_entry{ Edwin Z. Crues, NASA ER7, NExSyS, July 2023, --, Initial version }
@rev_entry{Edwin Z. Crues, NASA ER7, TrickHLA, October 2023, --, Made into full class.}
@revs_end

*/

#ifndef SPACEFOM_DYNAMICAL_ENTITY_FRAME_DATA_H
#define SPACEFOM_DYNAMICAL_ENTITY_FRAME_DATA_H

namespace SpaceFOM {

class DynamicalEntityData{

  public:
   double force[3];  ///< @trick_units{N} Entity force vector.
   double torque[3]; ///< @trick_units{N*m} Entity torque vector.
   double mass;      ///< @trick_units{kg} Entity mass.
   double mass_rate; ///< @trick_units{kg/s} Entity mass rate.

   double inertia[3][3];      ///< @trick_units{kg*m2} Entity inertia matrix.
   double inertia_rate[3][3]; ///< @trick_units{kg*m2/s} Entity inertia rate matrix.

};

} // namespace SpaceFOM

#endif // SPACEFOM_DYNAMICAL_ENTITY_FRAME_DATA_H: Do NOT put anything after this line!
