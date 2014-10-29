#include "FixedBinAxis.h"
#include "Exceptions.h"
#include <iomanip>


FixedBinAxis::FixedBinAxis(const std::string &name, size_t nbins, double start, double end)
    : IAxis(name)
    , m_nbins(nbins)
    , m_start(start)
    , m_end(end)
{

}


FixedBinAxis *FixedBinAxis::clone() const
{
    FixedBinAxis *result = new FixedBinAxis(getName(), m_nbins, m_start, m_end);
    return result;
}


size_t FixedBinAxis::getSize() const
{
    return m_nbins;
}


double FixedBinAxis::operator[](size_t index) const
{
    if(index >= m_nbins)
        throw Exceptions::OutOfBoundsException("FixedBinAxis::operator[] -> Error. Wrong index.");

    double step = (m_end - m_start)/m_nbins;
    return m_start + (index + 0.5)*step;
}


Bin1D FixedBinAxis::getBin(size_t index) const
{
    if(index >= m_nbins)
        throw Exceptions::OutOfBoundsException("FixedBinAxis::getBin() -> Error. Wrong index.");

    double step = (m_end - m_start)/m_nbins;
    Bin1D result( m_start + step*index, m_start + step*(index+1) );
    return result;
}


double FixedBinAxis::getMin() const
{
    return m_start;
}


double FixedBinAxis::getMax() const
{
    return m_end;
}


size_t FixedBinAxis::findClosestIndex(double value) const
{
    if (value < getMin() || value >= getMax()) {
        std::ostringstream ostr;
        ostr << "FixedBinAxis::findClosestIndex() -> Error! Given value not in any bin. ";
        ostr << "value:" << value << " name:" << getName() << " min:" << getMin() << " max:" << getMax();
        throw OutOfBoundsException(ostr.str());
    }

    double step = (m_end - m_start)/m_nbins;
    return int( (value-m_start)/step);
}

std::vector<double> FixedBinAxis::getBinCenters() const
{
    std::vector<double> result;
    result.resize(getSize(), 0.0);
    for(size_t i=0; i<getSize(); ++i) {
        result[i] = getBin(i).getMidPoint();
    }
    return result;
}

std::vector<double> FixedBinAxis::getBinBoundaries() const
{
    std::vector<double> result;
    result.resize(getSize()+1, 0.0);
    for(size_t i=0; i<getSize(); ++i) {
        result[i] = getBin(i).m_lower;
    }
    result[getSize()] = getBin(getSize()-1).m_upper;
    return result;
}

FixedBinAxis *FixedBinAxis::createClippedAxis(double left, double right) const
{
    if(left >= right)
        throw LogicErrorException("FixedBinAxis::createClippedAxis() -> Error. 'left'' should be smaller than 'right'");

    if(left < getMin()) left = getBin(0).getMidPoint();
    if(right >= getMax()) right = getBin(getSize()-1).getMidPoint();

    size_t nbin1 = findClosestIndex(left);
    size_t nbin2 = findClosestIndex(right);

    return new FixedBinAxis(getName(), nbin2-nbin1+1, getBin(nbin1).m_lower, getBin(nbin2).m_upper );
}


void FixedBinAxis::print(std::ostream& ostr) const
{
    ostr << "FixedBinAxis(\"" << m_name << "\", " << getSize() << ", " << std::setprecision(std::numeric_limits<double>::digits10+2) << getMin() << ", " << getMax() << ")";
}


bool FixedBinAxis::equals(const IAxis& other) const
{
    if (!IAxis::equals(other)) return false;
    if (const FixedBinAxis *otherAxis = dynamic_cast<const FixedBinAxis *>(&other)) {
        if (getSize() != otherAxis->getSize()) return false;
        if ( std::abs(getMin() - otherAxis->getMin()) > Numeric::double_epsilon) return false;
        if ( std::abs(getMax() - otherAxis->getMax()) > Numeric::double_epsilon) return false;
        return true;
    }
    return false;
}



