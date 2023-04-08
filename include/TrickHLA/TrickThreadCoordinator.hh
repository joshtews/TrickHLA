/*!
@file TrickHLA/TrickThreadCoordinator.hh
@ingroup TrickHLA
@brief This class handles the coordination of Trick Child Threads with the
HLA asynchronous data exchanges and time management.

@copyright Copyright 2019 United States Government as represented by the
Administrator of the National Aeronautics and Space Administration.
No copyright is claimed in the United States under Title 17, U.S. Code.
All Other Rights Reserved.

\par<b>Responsible Organization</b>
Simulation and Graphics Branch, Mail Code ER7\n
Software, Robotics & Simulation Division\n
NASA, Johnson Space Center\n
2101 NASA Parkway, Houston, TX  77058

@trick_parse{everything}

@python_module{TrickHLA}

@tldh
@trick_link_dependency{../../source/TrickHLA/Federate.cpp}
@trick_link_dependency{../../source/TrickHLA/Manager.cpp}
@trick_link_dependency{../../source/TrickHLA/MutexLock.cpp}
@trick_link_dependency{../../source/TrickHLA/TrickThreadCoordinator.cpp}

@revs_title
@revs_begin
@rev_entry{Dan Dexter, NASA ER6, TrickHLA, March 2023, --, Initial implementation.}
@revs_end
*/

#ifndef TRICKHLA_TRICK_THREAD_COORDINATOR_HH
#define TRICKHLA_TRICK_THREAD_COORDINATOR_HH

// System includes
#include <cstdint>
#include <string>

// TrickHLA include files.
#include "TrickHLA/MutexLock.hh"

namespace TrickHLA
{

// Forward Declared Classes: Since these classes are only used as references
// through pointers, these classes are included as forward declarations. This
// helps to limit issues with recursive includes.
class Federate;
class Manager;

class TrickThreadCoordinator
{
   // Let the Trick input processor access protected and private data.
   // InputProcessor is really just a marker class (does not really
   // exists - at least yet). This friend statement just tells Trick
   // to go ahead and process the protected and private data as well
   // as the usual public data.
   friend class InputProcessor;
   // IMPORTANT Note: you must have the following line too.
   // Syntax: friend void init_attr<namespace>__<class name>();
   friend void init_attrTrickHLA__TrickThreadCoordinator();

  public:
   //-----------------------------------------------------------------
   // Constructors / destructors
   //-----------------------------------------------------------------
   /*! @brief Default constructor for the TrickHLA TrickThreadCoordinator class. */
   TrickThreadCoordinator();
   /*! @brief Destructor for the TrickHLA TrickThreadCoordinator class. */
   virtual ~TrickThreadCoordinator();

   /*! @brief Setup the required class instance associations.
    *  @param federate  Associated TrickHLA::Federate class instance.
    *  @param manager   Associated TrickHLA::Manager class instance. */
   void setup( Federate &federate,
               Manager  &manager );

   /*! @brief Initialize the thread memory associated with the Trick child threads. */
   void initialize_thread_state( double const main_thread_data_cycle_time );

   /*! @brief Associate a Trick child thread with TrickHLA. */
   void associate_to_trick_child_thread( unsigned int const thread_id,
                                         double const       data_cycle,
                                         std::string const &obj_isntance_names );

   /*! @brief Announce to all the child threads the main thread has data available. */
   void announce_data_available();

   /*! @brief Announce to all the child threads the main thread sent the data. */
   void announce_data_sent();

   /*! @brief Wait to send data until all Trick child threads are ready. */
   void wait_to_send_data();

   /*! @brief Wait to receive data when the Trick main thread is ready. */
   void wait_to_receive_data();

   /*! @brief On boundary if sim-time is an integer multiple of a valid cycle-time. */
   bool const on_data_cycle_boundary_for_thread( unsigned int const thread_id,
                                                 int64_t const      sim_time_micros ) const;

   /*! @brief On boundary if sim-time is an integer multiple of a valid cycle-time. */
   bool const on_data_cycle_boundary_for_obj( unsigned int const obj_index,
                                              int64_t const      sim_time_micros ) const;

   /*! @brief Get the data cycle time for the configured object index or return
    * the default data cycle time. */
   int64_t const get_data_cycle_time_micros_for_obj( unsigned int const obj_index,
                                                     int64_t const      default_data_cycle_micros ) const;

  protected:
   Federate *federate; ///< @trick_units{--} Associated TrickHLA::Federate.
   Manager  *manager;  ///< @trick_units{--} Associated TrickHLA::Manager.

   MutexLock mutex; ///< @trick_units{--} TrickHLA thread state mutex.

   unsigned int *thread_state;     ///< @trick_units{--} TrickHLA state of trick child threads being used.
   unsigned int  thread_state_cnt; ///< @trick_units{--} TrickHLA state of trick child threads being used count.

   long long *data_cycle_micros_per_thread; ///< @trick_units{--} Data cycle times per thread in microseconds.
   long long *data_cycle_micros_per_obj;    ///< @trick_units{--} Data cycle times per object instance in microseconds.

   bool any_thread_associated; ///< @trick_units{--} True if at least one Trick Child thread is associated to TrickHLA.

   long long main_thread_data_cycle_micros; ///< @trick_units{--} Trick main thread data cycle time in microseconds.
};

} // namespace TrickHLA

#endif // TRICKHLA_TRICK_THREAD_COORDINATOR_HH: Do NOT put anything after this line!