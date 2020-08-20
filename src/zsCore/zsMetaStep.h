#ifndef ZSMETASTEP_H
#define ZSMETASTEP_H

#include "zsInputRecord.h"
#include "zsCore/zsExport.h"
#include <memory>

namespace zsim {
    class zsEngngModel;
    /**
 * Class representing meta step. The meta step instance represent sequence of
 * solution steps (timeSteps). The meta step role is to describe the common
 * attributes related to solution steps it represent from the point of view of engineering model.
 * For example, meta step may represent series of solution steps, for which particular
 * solution control is used. The common attributes it represent depend on engineering model
 * representation. To store these dependent attributes, the metaStep record (currently string)
 * is read from input and is provided to engineering model upon request.
 *
 * The meta step maintains its number, the total number of steps it represent, time increment and
 * its e-model attributes.
 */

class ZSIM_EXPORT zsMetaStep {
protected:
    /// Engineering model of receiver.
    zsEngngModel *eModel;
    /// Number of subsequent steps the receiver represent
    index_t numberOfSteps;
    /// Intrinsic time increment.
    real_t deltaT;
    /// Engineering model attributes.
    std::unique_ptr<zsInputRecord> attributes;
    /// Start solution step number for which receiver is responsible.
    index_t sindex;
    /// Receiver number.
    index_t number;
public:
    /**
     * Constructor. Creates a new meta step.
     * @param n Meta step number.
     * @param e Reference to corresponding engineering model.
     */
    zsMetaStep(index_t n, zsEngngModel * e);
    zsMetaStep(index_t n, zsEngngModel * e, index_t nsteps, zsInputRecord & attrib);
    zsMetaStep(zsMetaStep &&ms) = default;

    /// Returns receiver's number.
    index_t giveNumber() { return number; }
    /// Returns number of Steps it represent.
    index_t giveNumberOfSteps() { return this->numberOfSteps; }
    /// Returns time increment.
    real_t giveTimeIncrement() { return this->deltaT; }
    /// Returns e-model attributes.
    zsInputRecord &giveAttributesRecord() { return *this->attributes; }
    /**
     * Instanciates the receiver from input record.
     */
    void initializeFrom(zsInputRecord &ir);
    /// Sets the receiver bounds according to given solution step number, returns end index.
    index_t setStepBounds(index_t startStepNumber);
    /// Sets the number of steps within the metastep.
    void setNumberOfSteps(index_t newNumberOfSteps);
    /// Tests if step number is maintained by receiver.
    index_t isStepValid(index_t solStepNumber);
    /// Returns the step relative number  to receiver.
    index_t giveStepRelativeNumber(index_t stepNumber) { return ( stepNumber - sindex + 1 ); }
    /// Returns first step number.
    index_t giveFirstStepNumber() { return sindex; }
    /// Returns last step number.
    index_t giveLastStepNumber() { return ( sindex + numberOfSteps - 1 ); }
    /// Returns class name of receiver.
    const char *giveClassName() const { return "MetaStep"; }

};
}

#endif