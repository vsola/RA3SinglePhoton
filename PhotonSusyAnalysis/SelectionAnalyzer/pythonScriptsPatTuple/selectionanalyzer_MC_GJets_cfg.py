####################################CONFIGURATION##################################
###################################################################################

###SAMPLE###
# MC
sampleConf = 9


#####################################################################################
#################################################
import FWCore.ParameterSet.Config as cms

process= cms.Process("PhotonJetSelectionFromPat")
process.TFileService = cms.Service("TFileService", fileName = cms.string("histo.root") )

test = False

import PhotonSusyAnalysis.SelectionAnalyzer.selectionanalyzer_multi_cfg as baseConfig
doSkimming        = False
doAnalysis        = True
noKinematicPresel = False

# PU Distribution S10
PUDistributionMC=cms.vdouble(
    2.560E-06,
    5.239E-06,
    1.420E-05,
    5.005E-05,
    1.001E-04,
    2.705E-04,
    1.999E-03,
    6.097E-03,
    1.046E-02,
    1.383E-02,
    1.685E-02,
    2.055E-02,
    2.572E-02,
    3.262E-02,
    4.121E-02,
    4.977E-02,
    5.539E-02,
    5.725E-02,
    5.607E-02,
    5.312E-02,
    5.008E-02,
    4.763E-02,
    4.558E-02,
    4.363E-02,
    4.159E-02,
    3.933E-02,
    3.681E-02,
    3.406E-02,
    3.116E-02,
    2.818E-02,
    2.519E-02,
    2.226E-02,
    1.946E-02,
    1.682E-02,
    1.437E-02,
    1.215E-02,
    1.016E-02,
    8.400E-03,
    6.873E-03,
    5.564E-03,
    4.457E-03,
    3.533E-03,
    2.772E-03,
    2.154E-03,
    1.656E-03,
    1.261E-03,
    9.513E-04,
    7.107E-04,
    5.259E-04,
    3.856E-04,
    2.801E-04,
    2.017E-04,
    1.439E-04,
    1.017E-04,
    7.126E-05,
    4.948E-05,
    3.405E-05,
    2.322E-05,
    1.570E-05,
    5.005E-06
)

PUDistributionDataTrue=cms.vdouble(
    0.,
    6.42782e-07,
    1.70699e-06,
    4.68205e-06,
    1.35817e-05,
    2.82826e-05,
    0.000154966,
    0.000897327,
    0.00265278,
    0.00627214,
    0.012708,
    0.0223683,
    0.0348397,
    0.0451651,
    0.0511594,
    0.0549409,
    0.0577943,
    0.0595269,
    0.0600457,
    0.0597266,
    0.0587794,
    0.0573398,
    0.0556098,
    0.0536771,
    0.0513109,
    0.048083,
    0.0437478,
    0.0384462,
    0.0325525,
    0.0264712,
    0.0206033,
    0.0153261,
    0.0108989,
    0.00740757,
    0.00480191,
    0.00295962,
    0.00173023,
    0.000959197,
    0.000505557,
    0.000254697,
    0.000123621,
    5.84035e-05,
    2.72049e-05,
    1.26907e-05,
    6.03366e-06,
    2.97347e-06,
    1.53712e-06,
    8.36387e-07,
    4.7668e-07,
    2.81805e-07,
    1.71017e-07,
    0.,
    0.,
    0.,
    0.,
    0.,
    0.,
    0.,
    0.,
    0.
)

baseConfig.getProcessFor(sampleConf,process,test,doSkimming,doAnalysis,"",noKinematicPresel,PUDistributionMC,PUDistributionDataTrue)

#QCD
process.weightProducer.Method     = cms.string("Constant")
process.weightProducer.XS         = cms.double(107.5)
#process.weightProducer.NumberEvts = cms.double(9539562)
process.weightProducer.NumberEvts = cms.double(42391678)
process.weightProducer.Lumi       = cms.double(100.)

process.source = cms.Source( "PoolSource",
                             fileNames = cms.untracked.vstring(
    '/store/user/gebbert/QCD_Pt-15to3000_TuneZ2_Flat_7TeV_pythia6/photonJetSelection_V17/9eb0e622dba8674e0363aeef4926baa1/photonJetSelection_76_1_NaT.root'
    )
)

