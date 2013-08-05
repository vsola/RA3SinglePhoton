
#######CONFIGURATION######################
#'old' means signal scans from Summer 10 production (1/fb result)
#'new' means signal scans produced in early 2012 (used for paper)
#scan ranges
sqglpointsOld = ['160','240','320','400','480','560','640','720','800','880','960','1040','1120','1200','1280','1360','1440','1520','1600','1680','1760','1840','1920','2000']
neutrpointsOld = ['50','150','250','350','450','550','650','750','850','950','1050']
neutrpointsSqGlScanOld = ['375']

sqpointsNew = ['400','500','600','700','800','900','1000','1100','1200','1300','1400','1500','1600','1700','1800','1900','2000']
glpointsNew = ['420','520','620','720','820','920','1020','1120','1220','1320','1420','1520','1620','1720','1820','1920','2020']
neutrpointsNew = ['5','55','105','155','205','255','305','355','405','455','505','555','605','655','705','755','805','855','905','955','1005']
glpointsGlNeutrScanNew = ['315','365','415','465','515','565','615','665','715','765','815','865','915','965','1015']
neutrpointsSqGlScanNew = ['375']

decoupledMassOld = ['2500']
decoupledMassNew = ['2000']


#scan locations
oldFileLocBino='dcap:///pnfs/cms/WAX/11/store/user/lpcpjm/PrivateMC/FastSim/binolikegrid2/gen/'
oldFileLocWino='dcap:///pnfs/cms/WAX/11/store/user/lpcpjm/PrivateMC/FastSim/winolikegrid2/gen/'
oldFileLocBinoNeutr='dcap:///pnfs/cms/WAX/resilient/lpcpjm/PrivateMC/FastSim/binochigrids/gen/'
newFileLocBino='file:///eos/uscms/store/user/lpcpjm/PrivateMC/FastSim/428p7/Spectra_gsq_B/gen/'
newFileLocWino=''
newFileLocBinoNeutr='file:///eos/uscms/store/user/lpcpjm/PrivateMC/FastSim/428p7/Spectra_gB/gen/'
newFileLocWinoNeutr=''

#sampleFile parameters
sampleFileName='selectionanalyzer_MC_GMSBBino_1440_1520_375_cfg.py'
sampleFileScanLoc='dcap:///pnfs/cms/WAX/11/store/user/lpcpjm/PrivateMC/FastSim/binolikegrid2/gen/'
sampleFileNameCondor='scanSignalPointCondor_GGM_1440_1520_375'

##Fall11 PU scenario
PUDistributionMCWinter11Scan="cms.vdouble(0.003388501,0.010357558,0.024724258, 0.042348605, 0.058279812, 0.068851751,    0.072914824, 0.071579609, 0.066811668, 0.060672356,    0.054528356, 0.04919354, 0.044886042, 0.041341896,    0.0384679, 0.035871463, 0.03341952, 0.030915649,   0.028395374, 0.025798107, 0.023237445, 0.020602754,    0.0180688, 0.015559693, 0.013211063, 0.010964293,    0.008920993, 0.007080504, 0.005499239, 0.004187022,    0.003096474, 0.002237361, 0.001566428, 0.001074149,    0.000721755, 0.000470838, 0.00030268, 0.000184665,    0.000112883, 6.74043E-05, 3.82178E-05, 2.22847E-05,    1.20933E-05, 6.96173E-06, 3.4689E-06, 1.96172E-06,    8.49283E-07, 5.02393E-07, 2.15311E-07, 9.56938E-08)"
PUDistributionDataWinter11Scan="cms.vdouble(0,125539,1.96677e+06,2.48976e+07,9.625e+07,1.6262e+08,2.22979e+08,3.57969e+08,4.18238e+08,4.15993e+08,3.80825e+08,3.51564e+08,3.30735e+08,2.94181e+08,2.29225e+08,1.45499e+08,7.43711e+07,3.08969e+07,1.0913e+07,3.68176e+06,1.13003e+06,288668,64020.4,2350.83,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)"

#######END CONFIGURATION##################
