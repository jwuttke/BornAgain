// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/IDetector2D.h
//! @brief     Defines interface IDetector2D.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef IDETECTOR2D_H
#define IDETECTOR2D_H

#include "IParameterized.h"
#include "Beam.h"
#include "DetectorMask.h"
#include "SafePointerVector.h"
#include "Rectangle.h"
#include "DetectionProperties.h"
#include <memory>

template<class T> class OutputData;
class Beam;
class IAxis;
class IDetectorResolution;
class IPixelMap;
class SimulationElement;
class DetectionProperties;
namespace Geometry {
    class IShape2D;
}

//! @class IDetector
//! @ingroup simulation
//! @brief The detector interface.

class BA_CORE_API_ IDetector2D : public ICloneable, public IParameterized
{
public:
    enum EAxesUnits {DEFAULT, NBINS, RADIANS, DEGREES, MM, QYQZ};

    IDetector2D();

    virtual IDetector2D* clone() const=0;

    virtual ~IDetector2D();

    //! Inits detector with the beam settings
    virtual void init(const Beam&) {}

    void addAxis(const IAxis& axis);

    const IAxis& getAxis(size_t index) const;

    size_t getDimension() const;

    void clear();

    //! Sets detector parameters using axes of output data
    void matchDetectorAxes(const OutputData<double>& output_data);

    //! Sets detector parameters using angle ranges
    void setDetectorParameters(size_t n_x, double x_min, double x_max,
                               size_t n_y, double y_min, double y_max);

    //! Sets detector parameters using axes
    void setDetectorAxes(const IAxis& axis0, const IAxis& axis1);

    //! Sets the detector resolution
    void setDetectorResolution(IDetectorResolution* p_detector_resolution);

    //! Applies the detector resolution to the given intensity maps
    void applyDetectorResolution(OutputData<double>* p_intensity_map) const;

    const IDetectorResolution* getDetectorResolutionFunction() const;

    //! Sets the polarization analyzer characteristics of the detector
    void setAnalyzerProperties(const kvector_t direction, double efficiency,
                               double total_transmission=1.0);

    //! removes all masks from the detector
    void removeMasks();

    //! Adds mask of given shape to the stack of detector masks. The mask value 'true' means
    //! that the channel will be excluded from the simulation. The mask which is added last
    //! has priority.
    //! @param shape The shape of mask (Rectangle, Polygon, Line, Ellipse)
    //! @param mask_value The value of mask
    void addMask(const Geometry::IShape2D& shape, bool mask_value = true);

    //! Put the mask for all detector channels (i.e. exclude whole detector from the analysis)
    void maskAll();

    const DetectorMask* getDetectorMask() const;

    int getNumberOfMaskedChannels() const;


    bool isMasked(size_t index) const;

    //! return true if has masks
    bool hasMasks() const;

#ifndef SWIG
    //! Create a vector of SimulationElement objects according to the detector and its mask
    std::vector<SimulationElement> createSimulationElements(const Beam& beam);

    //! Creates single simulation element.
    SimulationElement getSimulationElement(size_t index, const Beam& beam) const;

    void transferResultsToIntensityMap(OutputData<double> &data,
                                       const std::vector<SimulationElement> &elements) const;
#endif

    //! Adds parameters from local pool to external pool and recursively calls its direct children.
    virtual std::string addParametersToExternalPool(
        const std::string& path, ParameterPool* external_pool, int copy_number = -1) const;

    //! Returns clone of the intensity map with detector resolution applied,
    //! axes of map will be in requested units
    OutputData<double>* getDetectorIntensity(
        const OutputData<double>& data, const Beam& beam,
        IDetector2D::EAxesUnits units_type=IDetector2D::DEFAULT) const;

    //! Returns detector map in given axes units
    virtual OutputData<double>* createDetectorMap(const Beam& beam, EAxesUnits units) const;

    //! Inits axes of OutputData to match the detector and sets values to zero.
    virtual void initOutputData(OutputData<double> &data) const;

    //! returns vector of valid axes units
    virtual std::vector<EAxesUnits> getValidAxesUnits() const;

    //! return default axes units
    virtual EAxesUnits getDefaultAxesUnits() const { return DEFAULT; }

    //! Returns region of  interest if exists.
    const Geometry::Rectangle* regionOfInterest() const;

    //! Sets rectangular region of interest with lower left and upper right corners defined.
    void setRegionOfInterest(double xlow, double ylow, double xup, double yup);

    //! Resets region of interest making whole detector plane available for the simulation.
    void resetRegionOfInterest();

    //! Returns total number of pixels
    size_t getTotalSize() const;

    //! Calculate axis index for given global index
    size_t getAxisBinIndex(size_t index, size_t selected_axis) const;

    //! Returns number of simulation elements.
    size_t numberOfSimulationElements() const;

protected:
    IDetector2D(const IDetector2D& other);

    //! Create an IPixelMap for the given OutputData object and index
    virtual IPixelMap* createPixelMap(size_t index) const=0;

    //! Registers some class members for later access via parameter pool.
    virtual void init_parameters() {}

    //! Generates an axis with correct name and default binning for given index
    virtual IAxis* createAxis(size_t index, size_t n_bins, double min, double max) const=0;

    //! Constructs axis with min,max corresponding to selected units
    std::unique_ptr<IAxis> constructAxis(size_t axis_index, const Beam& beam,
                                         EAxesUnits units) const;

    std::unique_ptr<IAxis> clipAxisToRoi(size_t axis_index, const IAxis &axis) const;

    //! Calculates axis range from original detector axes in given units (mm, rad, etc)
    virtual void calculateAxisRange(size_t axis_index, const Beam& beam, EAxesUnits units,
                                    double &amin, double &amax) const;

    //! Returns the name for the axis with given index
    virtual std::string getAxisName(size_t index) const=0;

    bool isCorrectAxisIndex(size_t index) const;

    //! Returns true if data has a compatible format with the detector.
    bool dataShapeMatches(const OutputData<double>* p_data) const;

    //! Calculate global index from two axis indices
    size_t getGlobalIndex(size_t x, size_t y) const;

    //! Returns index of pixel that contains the specular wavevector.
    //! If no pixel contains this specular wavevector, the number of pixels is
    //! returned. This corresponds to an overflow index.
    virtual size_t getIndexOfSpecular(const Beam& beam) const=0;

    SafePointerVector<IAxis> m_axes;
    std::unique_ptr<IDetectorResolution> mP_detector_resolution;
    DetectorMask m_detector_mask;

private:
    void setDataToDetectorMap(OutputData<double> &detectorMap,
                              const OutputData<double> &data) const;
    std::unique_ptr<Geometry::Rectangle> m_region_of_interest;
    DetectionProperties m_detection_properties;
};

#endif // IDETECTOR2D_H
