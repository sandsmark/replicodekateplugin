#ifndef REPLICODESETTINGS_H
#define REPLICODESETTINGS_H

#include <QObject>

class QIODevice;

class ReplicodeSettings : public QObject
{
    Q_OBJECT
public:
    explicit ReplicodeSettings(QObject *parent = 0);
    void writeXml(QIODevice *output, QString sourceFile);
    void load();
    void save();
    void setDefaults();

    ///////
    // Load
    QString userOperatorPath;
    QString userClassPath;

    ///////
    // Init
    int basePeriod;
    int reductionCoreCount;
    int timeCoreCount;

    /////////
    // System
    int perfSamplingPeriod;
    float floatTolerance;
    int timeTolerance;
    int primaryTimeHorizon;
    int secondaryTimeHorizon;

    // Model
    float mdlInertiaSuccessRateThreshold;
    int mdlInertiaCountThreshold;

    // Targeted Pattern Extractor
    float tpxDeltaSuccessRateThreshold;
    int tpxTimehorizon;

    // Simulation
    int minimumSimulationTimeHorizon;
    int maximumSimulationTimeHorizon;
    float simulationTimeHorizon;

    ////////
    // Debug
    bool debug;
    int notificationMarkerResilience;
    int goalPredictionSuccessResilience;
    int debugWindows;
    int traceLevels;

    bool getObjects;
    bool decompileObjects;
    QString decompilationFilePath;
    bool ignoreNamedObjects;
    QString objectsPath;
    bool testObjects;

    //////
    // Run
    int runTime;
    int probeLevel;

    bool getModels;
    bool decompileModels;
    bool ignoreNamedModels;
    QString modelsPath;
    bool testModels;

};

#endif // REPLICODESETTINGS_H
