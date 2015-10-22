# MeVisLab-Hausdorff-distance

MeVisLab module for computing the Hausdorff distance.

Installation:

1. Download these sources and place them in your existing MeVisLab packages or create a new ISI package
2. Add the following to YourPackage/ThirdParty/Configuration/YourPackage_ThirdParty.pri
    
    ```
    flann {
      CONFIG_FOUND += flann
      INCLUDEPATH += $${PACKAGE_SOURCES}/flann/flann-master/src/cpp
    }
    ```
    
    If you do not keep the ISI/ThirdParty folder, but put the sources somewhere else, you have to update the MLAB_PACKAGES in ISIHausdorffDistance.pro.

3. (Optional, compile the FLANN sources, this is not needed for the Hausdorff distance module.)
4. Compile the ISI\General\Sources\ML\ISIHausdorffDistance sources