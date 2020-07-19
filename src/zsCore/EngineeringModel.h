//
// Created by Mokhairy on 7/14/2020.
//
/**
 *
 */
#ifndef ZSIM_ENGINEERINGMODEL_H
#define ZSIM_ENGINEERINGMODEL_H

namespace zsim {
    class Domain;
    class TimeStep;
    class Dof;
    class DofManager;
    class DataReader;
    class DataStream;
    class ErrorEstimator;
    class MetaStep;
    class MaterialInterface;
    class SparseMtrx;
    class NumericalMethod;
    class InitModuleManager;
    class ExportModuleManager;
    class FloatMatrix;
    class FloatArray;
    class LoadBalancer;
    class LoadBalancerMonitor;
    class oofegGraphicContext;
    class ProblemCommunicator;
    class ProcessCommunicatorBuff;
    class CommunicatorBuff;
    class ProcessCommunicator;
    class UnknownNumberingScheme;

    /**
     * This is the main Engineering model class that will be inherited to all other Physics like structure mechanics,
     * fluid mechanics and thermal models.
     */

    class EngineeringModel {

    };
} //End of Namespace


#endif //ZSIM_ENGINEERINGMODEL_H
