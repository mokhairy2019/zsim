//
// Created by Mokhairy on 8/16/2020.
//

#ifndef ZSIM_ZSTIMESTEP_H
#define ZSIM_ZSTIMESTEP_H
#include <string>

#include "zsCore/zsExport.h"
#include "zsStateCounterType.h"
#include "zsTimeDiscretizationType.h"
#include "zsInputRecord.h"



namespace zsim{
     class zsEngngModel;
     class zsDataStream;
     /**
 * Class representing solution step. The timeStep instance may represent either
 * time step, load increment, or load case depending on used Engineering model.
 * See corresponding EngngModel reference for details. TimeStep maintains a reference to corresponding
 * Engineering model class instance.
 *
 * The class hold target time, which may represent the end of time interval. In addition, there is
 * intrinsic time, which is normally set the same as target time. Intrinsic (assembly) time is used
 * especially in constitutive laws, where the material law is not meant to be evaluated at target time. Also,
 * imposing boundary conditions occurs at intrinsic time by default. This reflects changes of static system and proper
 * equation numbering during each timeStep.
 *
 * Some components (typically integration points real stresses or integration points nonlocal values)
 * are computationally very demanding. Because in typical code, there are number of requests for same value
 * during the computation process, it may be efficient to store these values and compute them only once.
 * The principal problem is to recognize, when is necessary to re-compute these stored values to reflect
 * newly reached state. This cannot be determined form solution step "time", because solution step may
 * represent for example load increment, inside which typically many iterations are needed to reach
 * convergence. For this purpose, a concept of solution state counters is provided.
 * Whenever the solution state changes, the engineering model updates the solution state counter.
 * The solution state counter is guaranteed to grow up smoothly (it newer decreases) during solution process.
 * Other components of program (integration points) can then store their computationally expensive values
 * but have to store also corresponding solution state counter value valid when these were computed.
 * Then, easy check is done for finding differences between frozen solution state counter and their value with
 * current solution state requested from solution step and recompute the values if necessary.
 */
     class ZSIM_EXPORT zsTimeStep {
     protected:
         /// Engineering model reference.
         zsEngngModel *eModel;
         /// Current target time, which represents time at the end of a time step.
         real_t targetTime;
         /// Current intrinsic time, which may represents imposing time of boundary condition or time entering constitutive laws.
         real_t intrinsicTime;
         /// Current intrinsic time increment.
         real_t deltaT;
         /// Solution state counter.
         zsStateCounterType solutionStateCounter;
         /// Receiver's number.
         index_t number;
         /**
          * Receiver's version, used for special applications; default set to 0.
          * Typically, new version of same step is generated after adaptive restart, when
          * the restarted step is equilibrated on new domain.
          */
         index_t version;
         /**
          * Receiver's substep (iteration) number.
          */
         index_t subStepNumber;
         /// Corresponding meta step number.
         index_t mStepNumber;
         /// Time discretization.
         zsTimeDiscretizationType timeDiscretization;

     public:
         /**
          * Creates a new solution step.
          * @param n Solution step number.
          * @param e Reference to corresponding engng model.
          * @param mn Meta step number.
          * @param tt Intrinsic time.
          * @param dt Intrinsic time increment.
          * @param counter Solution state counter.
          * @param td Time discretization.
          */
         zsTimeStep(index_t n, zsEngngModel * e, index_t mn, real_t tt, real_t dt, zsStateCounterType counter, zsTimeDiscretizationType td = TD_Unspecified);
         zsTimeStep(const zsTimeStep &);
         /// Convenience ctor for constructing the next timestep based on the previous one.
         zsTimeStep(const zsTimeStep &previous, real_t dt);
         zsTimeStep(zsEngngModel * e);
         zsTimeStep &operator = ( const zsTimeStep & );

         /// Returns receiver's number.
         index_t giveNumber() { return number; }
         /// Set receiver's number.
         void setNumber(index_t i) { number = i; }
         /// Returns receiver's version.
         index_t giveVersion() { return version; }
         /// Returns receiver's meta step number.
         index_t giveMetaStepNumber() { return mStepNumber; }
         /// Returns receiver's substep number.
         index_t giveSubStepNumber() { return subStepNumber; }
         /**
          * Returns class name of receiver.
          * @return Pointer to s parameter filled with name.
          */
         const char *giveClassName() const { return "TimeStep"; }
         /// Returns pointer to previous solution step.
         zsTimeStep *givePreviousStep();
         /// Returns target time.
         real_t giveTargetTime() { return targetTime; }
         /// Returns intrinsic time, e.g. time in which constitutive model is evaluated.
         real_t giveIntrinsicTime() { return intrinsicTime; }
         /// Returns solution step associated time increment.
         real_t giveTimeIncrement() { return deltaT; }
         /// Sets solution step time increment.
         void setTimeIncrement(real_t newDt) { deltaT = newDt; }
         /// Sets target and intrinsic time to be equal.
         void setTime(real_t newt) {
             targetTime = newt;
             intrinsicTime = newt;
         }
         /// Sets only target time.
         void setTargetTime(real_t newt) { targetTime = newt; }
         /// Sets only intrinsic time.
         void setIntrinsicTime(real_t newt) { intrinsicTime = newt; }
         /// Sets time discretization.
         void setTimeDiscretization(zsTimeDiscretizationType td) { timeDiscretization = td; }

         /**
          * Check if solution step is not the last step.
          * @return True if not last step, false otherwise.
          */
         bool isNotTheLastStep();
         /**
          * Check if receiver is first step.
          * @return True if receiver is the first step, false otherwise.
          */
         bool isTheFirstStep();
         /**
          * Check if receiver is current solution step.
          * @returns True if receiver is current step, false otherwise.
          */
         bool isTheCurrentTimeStep();
         /**
          * Check if receiver is solution step when initial conditions should apply.
          * @return True if ic apply, false otherwise.
          */
         bool isIcApply();
         /**
          * Returns current solution state counter.
          */
         zsStateCounterType giveSolutionStateCounter() { return solutionStateCounter; }
         /// Updates solution state counter.
         void incrementStateCounter() { solutionStateCounter++; }
         /// Increments receiver's version.
         void incrementVersion() { version++; }
         /// Increments receiver's substep number.
         void incrementSubStepNumber() { subStepNumber++; }
         /// Returns time discretization.
         zsTimeDiscretizationType giveTimeDiscretization() { return timeDiscretization; }

         void initializeFrom(zsInputRecord &ir) { }
         /**
          * Stores receiver state to output stream.
          * @param stream Output stream.
          * @exception ContextIOERR If error encountered.
          */
         void saveContext(zsDataStream &stream);
         /**
          * Restores the receiver state previously written in stream.
          * @see saveContext member function.
          */
         void restoreContext(zsDataStream &stream);

         std :: string errorInfo(const char *func) { return std :: string("TimeStep::") + func; }


     };

 }


#endif //ZSIM_ZSTIMESTEP_H
