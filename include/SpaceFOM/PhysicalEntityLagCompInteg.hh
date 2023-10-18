/*!
@file SpaceFOM/PhysicalEntityLagCompInteg.hh
@ingroup SpaceFOM
@brief Definition of the TrickHLA SpaceFOM physical entity latency/lag
compensation class that uses integration to compensate the state.

This is the base implementation for the Space Reference FOM (SpaceFOM) interface
to the PhysicalEntity latency compensation object.

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

@tldh
@trick_link_dependency{../../source/SpaceFOM/PhysicalEntityLagCompBase.cpp}
@trick_link_dependency{../../source/SpaceFOM/PhysicalEntityLagCompInteg.cpp}

@revs_title
@revs_begin
@rev_entry{Edwin Z. Crues, NASA ER7, TrickHLA, October 2023, --, Initial version.}
@revs_end

*/

#ifndef SPACEFOM_PHYSICAL_ENTITY_LAG_COMP_INTEG_HH
#define SPACEFOM_PHYSICAL_ENTITY_LAG_COMP_INTEG_HH

// System include files.

// Trick includes.
#include "trick/Integrator.hh"

// TrickHLA include files.

// SpaceFOM include files.
#include "SpaceFOM/PhysicalEntityLagCompBase.hh"

namespace SpaceFOM
{

class PhysicalEntityLagCompInteg : public PhysicalEntityLagCompBase
{
   // Let the Trick input processor access protected and private data.
   // InputProcessor is really just a marker class (does not really
   // exist - at least yet). This friend statement just tells Trick
   // to go ahead and process the protected and private data as well
   // as the usual public data.
   friend class InputProcessor;
   // IMPORTANT Note: you must have the following line too.
   // Syntax: friend void init_attr<namespace>__<class name>();
   friend void init_attrSpaceFOM__PhysicalEntityLagCompInteg();

  public:
   // Public constructors and destructors.
   PhysicalEntityLagCompInteg( PhysicalEntityBase & entity_ref ); // Initialization constructor.
   virtual ~PhysicalEntityLagCompInteg(); // Destructor.

   /*! @brief Entity instance initialization routine. */
   virtual void initialize();

   /*! @brief Sending side latency compensation callback interface from the
    *  TrickHLALagCompensation class. */
   virtual void send_lag_compensation();

   /*! @brief Receive side latency compensation callback interface from the
    *  TrickHLALagCompensation class. */
   virtual void receive_lag_compensation();

   /*! @brief Set the lag compentation integration time step.
    *  @param dt Integration step time. */
   void set_integ_dt( double dt ){
      integ_dt = dt;
   }

   /*! @brief Set the lag compentation integration tolerance.
    *  @param dt Integration step time. */
   void set_integ_tolerance( double tol ){
      integ_tol = tol;
   }

  protected:
   double integ_t;   ///< @trick_units{s} Current compensation propagation time.
   double integ_dt;  ///< @trick_units{s} Default integration time steps.
   double integ_tol; ///< @trick_units{s} Tolerance for terminating a compensation step.

   /*! @brief Compensate the state data from the data time to the current scenario time.
    *  @param t_begin Scenario time at the start of the compensation step.
    *  @param t_end   Scenario time at the end of the compensation step. */
   int compensate(
      const double t_begin,
      const double t_end   ) = 0;

  private:
   // This object is not copyable
   /*! @brief Copy constructor for PhysicalEntityLagCompInteg class.
    *  @details This constructor is private to prevent inadvertent copies. */
   PhysicalEntityLagCompInteg( PhysicalEntityLagCompInteg const &rhs );
   /*! @brief Assignment operator for PhysicalEntityLagCompInteg class.
    *  @details This assignment operator is private to prevent inadvertent copies. */
   PhysicalEntityLagCompInteg &operator=( PhysicalEntityLagCompInteg const &rhs );
};

} // namespace SpaceFOM

#endif // SPACEFOM_PHYSICAL_ENTITY_LAG_COMP_INTEG_HH: Do NOT put anything after this line!
