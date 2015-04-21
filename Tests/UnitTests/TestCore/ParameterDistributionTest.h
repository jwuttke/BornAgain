#ifndef PARAMETERDISTRIBUTIONTEST_H
#define PARAMETERDISTRIBUTIONTEST_H

#include "ParameterDistribution.h"
#include "Distributions.h"
#include "ParameterSample.h"
#include "IParameterized.h"
#include <cmath>

class ParameterDistributionTest : public ::testing::Test
{

protected:
   ParameterDistributionTest(){}
    virtual ~ParameterDistributionTest(){}
};

TEST_F(ParameterDistributionTest, ParameterDistributionConstructor)
{
    std::string name = "MainParameterName";
    DistributionGate distribution(1.0, 2.0);
    EXPECT_THROW(ParameterDistribution(name, distribution, 1, -1.0), RuntimeErrorException);
    EXPECT_THROW(ParameterDistribution(name, distribution, 0), RuntimeErrorException);

    // Sigma constructor
    ParameterDistribution pardistr(name, distribution, 1);
    EXPECT_EQ("ParameterDistribution", pardistr.getName());
    EXPECT_EQ(1.5, pardistr.getDistribution()->getMean());
    EXPECT_EQ("DistributionGate", pardistr.getDistribution()->getName());
    EXPECT_EQ(1.0, pardistr.getDistribution()->probabilityDensity(1));
    EXPECT_EQ(name, pardistr.getMainParameterName());
    EXPECT_EQ(1, pardistr.getNbrSamples());
    EXPECT_EQ(0.0, pardistr.getSigmaFactor());
    EXPECT_EQ(AttLimits(), pardistr.getLimits());
    EXPECT_EQ(pardistr.getLinkedParameterNames().size(), size_t(0));
    EXPECT_EQ(1.0, pardistr.getMinValue());
    EXPECT_EQ(-1.0, pardistr.getMaxValue());

    ParameterDistribution pardistr2(name, distribution, 5, 2.0, AttLimits::limited(1.0, 2.0));
    EXPECT_EQ(5, pardistr2.getNbrSamples());
    EXPECT_EQ(2.0, pardistr2.getSigmaFactor());
    EXPECT_EQ(AttLimits::limited(1.0, 2.0), pardistr2.getLimits());

    // xmin, xmax constructor
    ParameterDistribution pardistr3(name, distribution, 5, 1.0, 2.0);
    EXPECT_EQ("ParameterDistribution", pardistr3.getName());
    EXPECT_EQ(1.5, pardistr3.getDistribution()->getMean());
    EXPECT_EQ("DistributionGate", pardistr3.getDistribution()->getName());
    EXPECT_EQ(1.0, pardistr3.getDistribution()->probabilityDensity(1));
    EXPECT_EQ(name, pardistr3.getMainParameterName());
    EXPECT_EQ(5, pardistr3.getNbrSamples());
    EXPECT_EQ(0.0, pardistr3.getSigmaFactor());
    EXPECT_EQ(AttLimits(), pardistr3.getLimits());
    EXPECT_EQ(pardistr3.getLinkedParameterNames().size(), size_t(0));


//    ParameterDistribution pd1D1(name, distribution, 0, 1.0);
//    EXPECT_THROW(pd1D1.generateSamples(),OutOfBoundsException);
//    std::vector<ParameterSample> list = pd1D.generateSamples();
//    ParameterSample parameterSample = list[0];
//    EXPECT_EQ(pd1D.getDistribution()->getMean(), parameterSample.value);
//    EXPECT_EQ(pd1D.getDistribution()->probabilityDensity(pd1D.getDistribution()->getMean()), parameterSample.weight);
//    pd1D.linkParameter("parameter");

//    std::vector<std::string> linked_par_names = pd1D.getLinkedParameterNames();
//    EXPECT_EQ("parameter", linked_par_names[0]);


//    std::string nameOther = "ParameterDistribution2";
//    DistributionGate distributionOther(1.0,2.0);
//    ParameterDistribution pd1DOther(nameOther,distributionOther,1,0.0);
//    pd1D.operator =(pd1DOther);
//    EXPECT_EQ(pd1DOther.getDistribution()->getName(), pd1D.getDistribution()->getName());
//    EXPECT_EQ(pd1DOther.getLinkedParameterNames(), pd1D.getLinkedParameterNames());
//    EXPECT_EQ(pd1DOther.getNbrSamples(), pd1D.getNbrSamples());
//    EXPECT_EQ(pd1DOther.getName(), pd1D.getName());
//    EXPECT_EQ(pd1DOther.getMainParameterName(), pd1D.getMainParameterName());
//    EXPECT_EQ(pd1DOther.getSigmaFactor(), pd1D.getSigmaFactor());

}

TEST_F(ParameterDistributionTest, ParameterDistributionCopyConstructor)
{
    DistributionGate distribution(1.0, 2.0);
    std::string name = "MainParameterName";
    ParameterDistribution pardistr(name, distribution, 5, 2.0, AttLimits::limited(1.0, 2.0));
    pardistr.linkParameter("link1").linkParameter("link2");

    ParameterDistribution pcopy(pardistr);
    EXPECT_EQ(pardistr.getName(), pcopy.getName());
    EXPECT_EQ(1.5, pcopy.getDistribution()->getMean());
    EXPECT_EQ(pardistr.getDistribution()->getName(), pcopy.getDistribution()->getName());

    EXPECT_EQ(pardistr.getDistribution()->probabilityDensity(1), pcopy.getDistribution()->probabilityDensity(1));
    EXPECT_EQ(pardistr.getMainParameterName(), pcopy.getMainParameterName());
    EXPECT_EQ(pardistr.getNbrSamples(), pcopy.getNbrSamples());
    EXPECT_EQ(pardistr.getSigmaFactor(), pcopy.getSigmaFactor());
    EXPECT_EQ(pardistr.getLimits(), pcopy.getLimits());
    EXPECT_EQ(pardistr.getLinkedParameterNames().size(), pcopy.getLinkedParameterNames().size());
    EXPECT_EQ("link1", pcopy.getLinkedParameterNames()[0]);
    EXPECT_EQ("link2", pcopy.getLinkedParameterNames()[1]);
    EXPECT_EQ(pardistr.getMinValue(), pcopy.getMinValue());
    EXPECT_EQ(pardistr.getMaxValue(), pcopy.getMaxValue());
}

TEST_F(ParameterDistributionTest, ParameterDistributionAssignment)
{
    DistributionGate distribution(1.0, 2.0);
    std::string name = "MainParameterName";
    ParameterDistribution pardistr(name, distribution, 5, 2.0, AttLimits::limited(1.0, 2.0));
    pardistr.linkParameter("link1").linkParameter("link2");

    ParameterDistribution pcopy = pardistr;
    EXPECT_EQ(pardistr.getName(), pcopy.getName());
    EXPECT_EQ(1.5, pcopy.getDistribution()->getMean());
    EXPECT_EQ(pardistr.getDistribution()->getName(), pcopy.getDistribution()->getName());

    EXPECT_EQ(pardistr.getDistribution()->probabilityDensity(1), pcopy.getDistribution()->probabilityDensity(1));
    EXPECT_EQ(pardistr.getMainParameterName(), pcopy.getMainParameterName());
    EXPECT_EQ(pardistr.getNbrSamples(), pcopy.getNbrSamples());
    EXPECT_EQ(pardistr.getSigmaFactor(), pcopy.getSigmaFactor());
    EXPECT_EQ(pardistr.getLimits(), pcopy.getLimits());
    EXPECT_EQ(pardistr.getLinkedParameterNames().size(), pcopy.getLinkedParameterNames().size());
    EXPECT_EQ("link1", pcopy.getLinkedParameterNames()[0]);
    EXPECT_EQ("link2", pcopy.getLinkedParameterNames()[1]);
    EXPECT_EQ(pardistr.getMinValue(), pcopy.getMinValue());
    EXPECT_EQ(pardistr.getMaxValue(), pcopy.getMaxValue());
}

TEST_F(ParameterDistributionTest, GenerateSamples)
{
    const double mean(1.0);
    const double sigma(0.8);
    DistributionGaussian distribution(mean, sigma);

    std::string name = "MainParameterName";
    const int nbr_samples(3);
    const double sigma_factor(2.0);

    // without AttLimits
    ParameterDistribution pardistr(name, distribution, nbr_samples, sigma_factor);
    std::vector<ParameterSample> sample_values = pardistr.generateSamples();
    EXPECT_EQ(sample_values.size(), size_t(3));
    EXPECT_EQ(sample_values[0].value, mean-sigma_factor*sigma);
    EXPECT_EQ(sample_values[1].value, mean);
    EXPECT_EQ(sample_values[2].value, mean+sigma_factor*sigma);

    // with AttLimits
    ParameterDistribution pardistr2(name, distribution, nbr_samples, sigma_factor, AttLimits::lowerLimited(mean));
    sample_values = pardistr2.generateSamples();
    EXPECT_EQ(sample_values.size(), size_t(3));
    EXPECT_EQ(sample_values[0].value, mean);
    EXPECT_EQ(sample_values[1].value, mean+sigma_factor*sigma/2.0);
    EXPECT_EQ(sample_values[2].value, mean+sigma_factor*sigma);

    // with xmin, xmax defined
    double xmin(-1.0);
    double xmax(2.0);
    ParameterDistribution pardistr3(name, distribution, nbr_samples, xmin, xmax);
    sample_values = pardistr3.generateSamples();
    EXPECT_EQ(sample_values.size(), size_t(3));
    EXPECT_EQ(sample_values[0].value, xmin);
    EXPECT_EQ(sample_values[1].value, xmin + (xmax-xmin)/2.0);
    EXPECT_EQ(sample_values[2].value, xmax);

}


#endif
