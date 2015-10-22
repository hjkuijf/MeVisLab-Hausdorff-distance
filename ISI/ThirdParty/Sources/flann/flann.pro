# -----------------------------------------------------------------------------
# Flann project profile
#
# \file    flann.pro
# \author  Hugo
# \date    2010-03-10
# -----------------------------------------------------------------------------

TEMPLATE   = lib

TARGET     = flann

DESTDIR    = ../../lib
DLLDESTDIR = ../../lib

# set high warn level (warn 4 on MSCV)
WARN = HIGH

# add used projects here (see included pri files below for available projects)
CONFIG += dll OpenMP ML

MLAB_PACKAGES += 

# -- System -------------------------------------------------------------
include ($(MLAB_MeVis_Foundation)/Configuration/IncludePackages.pri)

DEFINES += ML_DISABLE_DEPRECATED \
           FLANN_EXPORTS

INCLUDEPATH += flann-master/src/cpp/

HEADERS += \
	FlannInit.h \
	FlannSystem.h \
    flann-master/src/cpp/flann/algorithms/all_indices.h \
    flann-master/src/cpp/flann/algorithms/autotuned_index.h \
	flann-master/src/cpp/flann/algorithms/center_chooser.h \
    flann-master/src/cpp/flann/algorithms/composite_index.h \
    flann-master/src/cpp/flann/algorithms/dist.h \
	flann-master/src/cpp/flann/algorithms/hierarchical_clustering_index.h \
    flann-master/src/cpp/flann/algorithms/kdtree_cuda_3d_index.h \
    flann-master/src/cpp/flann/algorithms/kdtree_cuda_builder.h \
    flann-master/src/cpp/flann/algorithms/kdtree_index.h \
    flann-master/src/cpp/flann/algorithms/kdtree_single_index.h \
    flann-master/src/cpp/flann/algorithms/kmeans_index.h \
    flann-master/src/cpp/flann/algorithms/linear_index.h \
    flann-master/src/cpp/flann/algorithms/lsh_index.h \
    flann-master/src/cpp/flann/algorithms/nn_index.h \
    flann-master/src/cpp/flann/io/hdf5.h \
    flann-master/src/cpp/flann/nn/ground_truth.h \
    flann-master/src/cpp/flann/nn/index_testing.h \
    flann-master/src/cpp/flann/nn/simplex_downhill.h \
    flann-master/src/cpp/flann/util/cuda/heap.h \
    flann-master/src/cpp/flann/util/cuda/result_set.h \
    flann-master/src/cpp/flann/util/allocator.h \
    flann-master/src/cpp/flann/util/any.h \
    flann-master/src/cpp/flann/util/cutil_math.h \
    flann-master/src/cpp/flann/util/dynamic_bitset.h \
    flann-master/src/cpp/flann/util/heap.h \
    flann-master/src/cpp/flann/util/logger.h \
    flann-master/src/cpp/flann/util/lsh_table.h \
    flann-master/src/cpp/flann/util/matrix.h \
    flann-master/src/cpp/flann/util/object_factory.h \
    flann-master/src/cpp/flann/util/params.h \
    flann-master/src/cpp/flann/util/random.h \
    flann-master/src/cpp/flann/util/result_set.h \
    flann-master/src/cpp/flann/util/sampling.h \
    flann-master/src/cpp/flann/util/saving.h \
    flann-master/src/cpp/flann/util/serialization.h \
    flann-master/src/cpp/flann/util/timer.h \
    flann-master/src/cpp/flann/config.h \
    flann-master/src/cpp/flann/defines.h \
    flann-master/src/cpp/flann/flann.h \
    flann-master/src/cpp/flann/flann.hpp \
    flann-master/src/cpp/flann/general.h 

SOURCES += \
	FlannInit.cpp \
    #flann-master/src/cpp/flann/flann.cpp \
    flann-master/src/cpp/flann/flann_cpp.cpp 

# additional files that are NOT compiled
RELATEDFILES += \
    flann-master/ChangeLog \
	flann-master/COPYING \
    flann-master/README.md

