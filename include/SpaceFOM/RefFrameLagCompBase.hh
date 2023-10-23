/*!
@file SpaceFOM/RefFrameLagCompBase.hh
@ingroup SpaceFOM
@brief Definition of the TrickHLA SpaceFOM physical entity latency/lag
compensation class.

This is the base implementation for the Space Reference FOM (SpaceFOM) interface
to the RefFrame latency compensation object.

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
@trick_link_dependency{../../source/TrickHLA/LagCompensation.cpp}
@trick_link_dependency{../../source/SpaceFOM/RefFrameLagCompBase.cpp}
@trick_link_dependency{QuaternionData.c}

@revs_title
@revs_begin
@rev_entry{Edwin Z. Crues, NASA ER7, TrickHLA, October 2023, --, Initial version.}
@revs_end

*/

#ifndef SPACEFOM_REF_FRAME_LAG_COMP_BASE_HH
#define SPACEFOM_REF_FRAME_LAG_COMP_BASE_HH

// System include files.

// Trick includes.

// TrickHLA include files.
#include "TrickHLA/LagCompensation.hh"

// SpaceFOM include files.
#include "SpaceFOM/QuaternionData.hh"
#include "SpaceFOM/SpaceTimeCoordinateData.hh"
#include "SpaceFOM/RefFrameBase.hh"

namespace SpaceFOM
{

class RefFrameLagCompBase : public TrickHLA::LagCompensation
{
   // Let the Trick input processor access protected and private data.
   // InputProcessor is really just a marker class (does not really
   // exist - at least yet). This friend statement just tells Trick
   // to go ahead and process the protected and private data as well
   // as the usual public data.
   friend class InputProcessor;
   // IMPORTANT Note: you must have the following line too.
   // Syntax: friend void init_attr<namespace>__<class name>();
   friend void init_attrSpaceFOM__RefFrameLagCompBase();

  public:
   // Public constructors and destructors.
   RefFrameLagCompBase( RefFrameBase & ref_frame_ref ); // Initialization constructor.
   virtual ~RefFrameLagCompBase(); // Destructor.

   /*! @brief Entity instance initialization routine. */
   virtual void initialize();

   /*! @brief Initialize the callback object to the supplied Object pointer.
    *  @param obj Associated object for this class. */
   virtual void initialize_callback( TrickHLA::Object *obj );

   /*! @brief Initialization integration states. */
   virtual void initialize_states();

   /*! @brief Sending side latency compensation callback interface from the
    *  TrickHLALagCompensation class. */
   virtual void send_lag_compensation() = 0;

   /*! @brief Receive side latency compensation callback interface from the
    *  TrickHLALagCompensation class. */
   virtual void receive_lag_compensation() = 0;

  public:
   bool debug; ///< @trick_units{--} Debug output flag.

  protected:

   RefFrameBase & ref_frame; ///< @trick_units{--} @trick_io{**}  RefFrame to compensate.

   // Setup Object Attribute references. These are set in initialize_callback
   // routine and used for efficiency and ownership transfer in unpack routines.
   TrickHLA::Attribute *state_attr; ///< @trick_io{**} Reference frame state Attribute.

   double compensate_dt; ///< @trick_units{s} Time difference between publish time and receive time.

   SpaceTimeCoordinateData lag_comp_data; ///< @trick_units{--} Compensated reference frame data.
   QuaternionData          Q_dot;         ///< @trick_units{--} Computed attitude quaternion rate.

   /*! @brief Compensate the state data from the data time to the current scenario time.
    *  @param t_begin Scenario time at the start of the compensation step.
    *  @param t_end   Scenario time at the end of the compensation step. */
   virtual int compensate(
      const double t_begin,
      const double t_end   ) = 0;

   /*! @brief Copy the lag compensation state into the reference frame state. */
   virtual void copy_state_to_frame();

   /*! @brief Copy the reference frame state into the lag compensation state. */
   virtual void copy_state_from_frame();

   /*! @brief Print out the lag compensation data values. */
   virtual void print_lag_comp_data();

  private:
   // This object is not copyable
   /*! @brief Copy constructor for RefFrameLagCompBase class.
    *  @details This constructor is private to prevent inadvertent copies. */
   RefFrameLagCompBase( RefFrameLagCompBase const &rhs );
   /*! @brief Assignment operator for RefFrameLagCompBase class.
    *  @details This assignment operator is private to prevent inadvertent copies. */
   RefFrameLagCompBase &operator=( RefFrameLagCompBase const &rhs );
};

} // namespace SpaceFOM

#endif // SPACEFOM_REF_FRAME_LAG_COMP_BASE_HH: Do NOT put anything after this line!
