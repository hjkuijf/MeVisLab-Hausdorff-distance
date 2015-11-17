# -----------------------------------------------------------------------------
# ISIHausdorffDistance project profile
#
# \file    ISIHausdorffDistance.pro
# \author  Hugo Kuijf
# \date    2013-05-02
# -----------------------------------------------------------------------------


TEMPLATE   = lib

TARGET     = ISIHausdorffDistance

DESTDIR    = ../../../lib
DLLDESTDIR = ../../../lib

# Set high warn level (warn 4 on MSVC)
WARN = HIGH

# Add used projects here (see included pri files below for available projects)
CONFIG += dll ML MLBase flann OpenMP

MLAB_PACKAGES += ISI_General \
                 ISI_ThirdParty \
                 MeVisLab_Standard

# make sure that this file is included after CONFIG and MLAB_PACKAGES
include ($(MLAB_MeVis_Foundation)/Configuration/IncludePackages.pri)

DEFINES += ISIHAUSDORFFDISTANCE_EXPORTS

# Enable ML deprecated API warnings. To completely disable the deprecated API, change WARN to DISABLE.
DEFINES += ML_WARN_DEPRECATED

HEADERS += \
    ISIHausdorffDistanceInit.h \
    ISIHausdorffDistanceSystem.h \
    mlHausdorffDistance.h

SOURCES += \
    ISIHausdorffDistanceInit.cpp \
    mlHausdorffDistance.cpp

macx:QMAKE_CXXFLAGS += -fopenmp

# additional files that are NOT compiled
RELATEDFILES += \
    ../../../Modules/ML/ISIHausdorffDistance/ISIHausdorffDistance.def