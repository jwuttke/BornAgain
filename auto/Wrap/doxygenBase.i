
// File: index.xml

// File: classBasicVector3D.xml
%feature("docstring") BasicVector3D "

Forked from CLHEP/Geometry by E. Chernyaev Evgueni.Tcherniaev@cern.ch, then reworked beyond recognition. Removed split of point and vector semantics. Transforms are relegated to a separate class  Transform3D. Three-dimensional vector template, for use with integer, double, or complex components.

C++ includes: BasicVector3D.h
";

%feature("docstring")  BasicVector3D::BasicVector3D "BasicVector3D< T >::BasicVector3D()

Default constructor. 
";

%feature("docstring")  BasicVector3D::BasicVector3D "BasicVector3D< T >::BasicVector3D(const T x1, const T y1, const T z1)

Constructor from cartesian components. 
";

%feature("docstring")  BasicVector3D::x "T BasicVector3D< T >::x() const

Returns x-component in cartesian coordinate system. 
";

%feature("docstring")  BasicVector3D::y "T BasicVector3D< T >::y() const

Returns y-component in cartesian coordinate system. 
";

%feature("docstring")  BasicVector3D::z "T BasicVector3D< T >::z() const

Returns z-component in cartesian coordinate system. 
";

%feature("docstring")  BasicVector3D::setX "void BasicVector3D< T >::setX(const T &a)

Sets x-component in cartesian coordinate system. 
";

%feature("docstring")  BasicVector3D::setY "void BasicVector3D< T >::setY(const T &a)

Sets y-component in cartesian coordinate system. 
";

%feature("docstring")  BasicVector3D::setZ "void BasicVector3D< T >::setZ(const T &a)

Sets z-component in cartesian coordinate system. 
";

%feature("docstring")  BasicVector3D::conj "BasicVector3D<T> BasicVector3D< T >::conj() const

Returns complex conjugate vector. 
";

%feature("docstring")  BasicVector3D::mag2 "double BasicVector3D< T >::mag2() const

Returns magnitude squared of the vector. 
";

%feature("docstring")  BasicVector3D::mag "double BasicVector3D< T >::mag() const

Returns magnitude of the vector. 
";

%feature("docstring")  BasicVector3D::magxy2 "double BasicVector3D< T >::magxy2() const

Returns squared distance from z axis. 
";

%feature("docstring")  BasicVector3D::magxy "double BasicVector3D< T >::magxy() const

Returns distance from z axis. 
";

%feature("docstring")  BasicVector3D::phi "double BasicVector3D< T >::phi() const

Returns azimuth angle. 
";

%feature("docstring")  BasicVector3D::theta "double BasicVector3D< T >::theta() const

Returns polar angle. 
";

%feature("docstring")  BasicVector3D::cosTheta "double BasicVector3D< T >::cosTheta() const

Returns cosine of polar angle. 
";

%feature("docstring")  BasicVector3D::sin2Theta "double BasicVector3D< T >::sin2Theta() const

Returns squared sine of polar angle. 
";

%feature("docstring")  BasicVector3D::unit "BasicVector3D<T> BasicVector3D< T >::unit() const

Returns unit vector in direction of this. Throws for null vector. 
";

%feature("docstring")  BasicVector3D::complex "BasicVector3D<std::complex<double> > BasicVector3D< T >::complex() const

Returns this, trivially converted to complex type. 
";

%feature("docstring")  BasicVector3D::real "BasicVector3D<double> BasicVector3D< T >::real() const

Returns real parts. 
";

%feature("docstring")  BasicVector3D::dot "auto BasicVector3D< T >::dot(const BasicVector3D< U > &v) const

Returns dot product of vectors (antilinear in the first [=self] argument).

Returns dot product of (complex) vectors (antilinear in the first [=self] argument). 
";

%feature("docstring")  BasicVector3D::cross "auto BasicVector3D< T >::cross(const BasicVector3D< U > &v) const

Returns cross product of vectors (linear in both arguments).

Returns cross product of (complex) vectors. 
";

%feature("docstring")  BasicVector3D::angle "double BasicVector3D< T >::angle(const BasicVector3D< T > &v) const

Returns angle with respect to another vector. 
";

%feature("docstring")  BasicVector3D::project "BasicVector3D<T> BasicVector3D< T >::project(const BasicVector3D< T > &v) const

Returns projection of this onto other vector: (this*v)*v/|v|^2. 
";

%feature("docstring")  BasicVector3D::rotatedX "BasicVector3D<T> BasicVector3D< T >::rotatedX(double a) const

Returns result of rotation around x-axis. 
";

%feature("docstring")  BasicVector3D::rotatedY "BasicVector3D<T> BasicVector3D< T >::rotatedY(double a) const

Returns result of rotation around y-axis. 
";

%feature("docstring")  BasicVector3D::rotatedZ "BasicVector3D<T> BasicVector3D< T >::rotatedZ(double a) const

Returns result of rotation around z-axis. 
";

%feature("docstring")  BasicVector3D::rotated "BasicVector3D<T> BasicVector3D< T >::rotated(double a, const BasicVector3D< T > &v) const

Returns result of rotation around the axis specified by another vector. 
";

%feature("docstring")  BasicVector3D::conj "BasicVector3D< double > BasicVector3D< double >::conj() const

Returns complex conjugate vector. 
";

%feature("docstring")  BasicVector3D::conj "BasicVector3D< complex_t > BasicVector3D< complex_t >::conj() const
";

%feature("docstring")  BasicVector3D::phi "double BasicVector3D< double >::phi() const

Returns azimuth angle. 
";

%feature("docstring")  BasicVector3D::theta "double BasicVector3D< double >::theta() const

Returns polar angle. 
";

%feature("docstring")  BasicVector3D::cosTheta "double BasicVector3D< double >::cosTheta() const

Returns cosine of polar angle. 
";

%feature("docstring")  BasicVector3D::sin2Theta "double BasicVector3D< double >::sin2Theta() const

Returns squared sine of polar angle. 
";

%feature("docstring")  BasicVector3D::complex "BasicVector3D< complex_t > BasicVector3D< double >::complex() const

Returns this, trivially converted to complex type. 
";

%feature("docstring")  BasicVector3D::real "BasicVector3D< double > BasicVector3D< double >::real() const

Returns real parts. 
";

%feature("docstring")  BasicVector3D::real "BasicVector3D< double > BasicVector3D< complex_t >::real() const
";

%feature("docstring")  BasicVector3D::unit "BasicVector3D< double > BasicVector3D< double >::unit() const

Returns unit vector in direction of this. Throws for null vector. 
";

%feature("docstring")  BasicVector3D::unit "BasicVector3D< complex_t > BasicVector3D< complex_t >::unit() const
";

%feature("docstring")  BasicVector3D::angle "double BasicVector3D< double >::angle(const BasicVector3D< double > &v) const

Returns angle with respect to another vector. 
";

%feature("docstring")  BasicVector3D::conj "BasicVector3D< double > BasicVector3D< double >::conj() const
";

%feature("docstring")  BasicVector3D::conj "BasicVector3D< std::complex< double > > BasicVector3D< std::complex< double > >::conj() const
";

%feature("docstring")  BasicVector3D::phi "double BasicVector3D< double >::phi() const
";

%feature("docstring")  BasicVector3D::theta "double BasicVector3D< double >::theta() const
";

%feature("docstring")  BasicVector3D::cosTheta "double BasicVector3D< double >::cosTheta() const
";

%feature("docstring")  BasicVector3D::sin2Theta "double BasicVector3D< double >::sin2Theta() const
";

%feature("docstring")  BasicVector3D::complex "BasicVector3D< std::complex< double > > BasicVector3D< double >::complex() const
";

%feature("docstring")  BasicVector3D::real "BasicVector3D< double > BasicVector3D< double >::real() const
";

%feature("docstring")  BasicVector3D::real "BasicVector3D< double > BasicVector3D< std::complex< double > >::real() const
";

%feature("docstring")  BasicVector3D::unit "BasicVector3D< double > BasicVector3D< double >::unit() const
";

%feature("docstring")  BasicVector3D::unit "BasicVector3D< std::complex< double > > BasicVector3D< std::complex< double > >::unit() const
";

%feature("docstring")  BasicVector3D::angle "double BasicVector3D< double >::angle(const BasicVector3D< double > &v) const
";


// File: structIntegratorMCMiser_1_1CallBackHolder.xml
%feature("docstring") IntegratorMCMiser::CallBackHolder "

structure holding the object and possible extra parameters

C++ includes: IntegratorMCMiser.h
";


// File: classExceptions_1_1ClassInitializationException.xml
%feature("docstring") Exceptions::ClassInitializationException "";

%feature("docstring")  Exceptions::ClassInitializationException::ClassInitializationException "Exceptions::ClassInitializationException::ClassInitializationException(const std::string &message)
";


// File: classCloneableVector.xml
%feature("docstring") CloneableVector "

The objects pointed to must posses a clone() function.

A vector of unique pointers to objects that are cloneable.

Equips vector<unique_ptr<T>> with copy constructor. For use with polymorphic objects, or in pimpl idiom.

C++ includes: CloneableVector.h
";

%feature("docstring")  CloneableVector::CloneableVector "CloneableVector< T >::CloneableVector()
";

%feature("docstring")  CloneableVector::CloneableVector "CloneableVector< T >::CloneableVector(const CloneableVector &other)
";

%feature("docstring")  CloneableVector::push_back "void CloneableVector< T >::push_back(T *t)
";

%feature("docstring")  CloneableVector::emplace_back "void CloneableVector< T >::emplace_back(std::unique_ptr< T > &&t)
";


// File: classComplexIntegrator.xml
%feature("docstring") ComplexIntegrator "

To integrate a complex function of a real variable.

C++ includes: Integrator.h
";

%feature("docstring")  ComplexIntegrator::integrate "complex_t ComplexIntegrator::integrate(const std::function< complex_t(double)> &f, double lmin, double lmax)
";


// File: classExceptions_1_1DivisionByZeroException.xml
%feature("docstring") Exceptions::DivisionByZeroException "";

%feature("docstring")  Exceptions::DivisionByZeroException::DivisionByZeroException "Exceptions::DivisionByZeroException::DivisionByZeroException(const std::string &message)
";


// File: classExceptions_1_1DomainErrorException.xml
%feature("docstring") Exceptions::DomainErrorException "";

%feature("docstring")  Exceptions::DomainErrorException::DomainErrorException "Exceptions::DomainErrorException::DomainErrorException(const std::string &message)
";


// File: classExceptions_1_1ExistingClassRegistrationException.xml
%feature("docstring") Exceptions::ExistingClassRegistrationException "";

%feature("docstring")  Exceptions::ExistingClassRegistrationException::ExistingClassRegistrationException "Exceptions::ExistingClassRegistrationException::ExistingClassRegistrationException(const std::string &message)
";


// File: classExceptions_1_1FileIsBadException.xml
%feature("docstring") Exceptions::FileIsBadException "";

%feature("docstring")  Exceptions::FileIsBadException::FileIsBadException "Exceptions::FileIsBadException::FileIsBadException(const std::string &message)
";


// File: classExceptions_1_1FileNotIsOpenException.xml
%feature("docstring") Exceptions::FileNotIsOpenException "";

%feature("docstring")  Exceptions::FileNotIsOpenException::FileNotIsOpenException "Exceptions::FileNotIsOpenException::FileNotIsOpenException(const std::string &message)
";


// File: classExceptions_1_1FormatErrorException.xml
%feature("docstring") Exceptions::FormatErrorException "";

%feature("docstring")  Exceptions::FormatErrorException::FormatErrorException "Exceptions::FormatErrorException::FormatErrorException(const std::string &message)
";


// File: classICloneable.xml
%feature("docstring") ICloneable "

Interface for polymorphic classes that should not be copied, except by explicit cloning.

Child classes of  ICloneable must provide clone().

C++ includes: ICloneable.h
";

%feature("docstring")  ICloneable::ICloneable "ICloneable::ICloneable()=default
";

%feature("docstring")  ICloneable::~ICloneable "virtual ICloneable::~ICloneable()=default
";

%feature("docstring")  ICloneable::ICloneable "ICloneable::ICloneable(const ICloneable &)=delete
";

%feature("docstring")  ICloneable::ICloneable "ICloneable::ICloneable(ICloneable &&)=default
";

%feature("docstring")  ICloneable::clone "virtual ICloneable* ICloneable::clone() const =0
";

%feature("docstring")  ICloneable::transferToCPP "virtual void ICloneable::transferToCPP()

Used for Python overriding of clone (see swig/tweaks.py) 
";


// File: classIntegratorMCMiser.xml
%feature("docstring") IntegratorMCMiser "

Template class to use Monte Carlo MISER integration of class member functions.

Wraps an integrator from GNU Scientific Library. Since this class holds a persistent workspace, we need at least one instance per thread. Standard usage for integration inside a class T:
Create a handle to an integrator: 'auto integrator = make_integrator_miser(this, mem_function, dimension)'

Call: 'integrator.integrate(lmin, lmax, data, nbr_points)'

C++ includes: IntegratorMCMiser.h
";

%feature("docstring")  IntegratorMCMiser::IntegratorMCMiser "IntegratorMCMiser< T >::IntegratorMCMiser(const T *p_object, miser_integrand< T > p_member_function, size_t dim)

to integrate p_member_function, which must belong to p_object 
";

%feature("docstring")  IntegratorMCMiser::~IntegratorMCMiser "IntegratorMCMiser< T >::~IntegratorMCMiser()
";

%feature("docstring")  IntegratorMCMiser::integrate "double IntegratorMCMiser< T >::integrate(double *min_array, double *max_array, void *params, size_t nbr_points)

perform the actual integration over the ranges [min_array, max_array] 
";


// File: classExceptions_1_1LogicErrorException.xml
%feature("docstring") Exceptions::LogicErrorException "";

%feature("docstring")  Exceptions::LogicErrorException::LogicErrorException "Exceptions::LogicErrorException::LogicErrorException(const std::string &message)
";


// File: classExceptions_1_1NotImplementedException.xml
%feature("docstring") Exceptions::NotImplementedException "";

%feature("docstring")  Exceptions::NotImplementedException::NotImplementedException "Exceptions::NotImplementedException::NotImplementedException(const std::string &message)
";


// File: classExceptions_1_1NullPointerException.xml
%feature("docstring") Exceptions::NullPointerException "";

%feature("docstring")  Exceptions::NullPointerException::NullPointerException "Exceptions::NullPointerException::NullPointerException(const std::string &message)
";


// File: classExceptions_1_1OutOfBoundsException.xml
%feature("docstring") Exceptions::OutOfBoundsException "";

%feature("docstring")  Exceptions::OutOfBoundsException::OutOfBoundsException "Exceptions::OutOfBoundsException::OutOfBoundsException(const std::string &message)
";


// File: classRealIntegrator.xml
%feature("docstring") RealIntegrator "

To integrate a real function of a real variable.

C++ includes: Integrator.h
";

%feature("docstring")  RealIntegrator::RealIntegrator "RealIntegrator::RealIntegrator()
";

%feature("docstring")  RealIntegrator::~RealIntegrator "RealIntegrator::~RealIntegrator()
";

%feature("docstring")  RealIntegrator::integrate "double RealIntegrator::integrate(const std::function< double(double)> &f, double lmin, double lmax)
";


// File: structPrecomputed_1_1ReciprocalFactorial.xml
%feature("docstring") Precomputed::ReciprocalFactorial "";


// File: structPrecomputed_1_1ReciprocalFactorial_3_010_01_4.xml
%feature("docstring") Precomputed::ReciprocalFactorial< 0 > "
";


// File: classExceptions_1_1RuntimeErrorException.xml
%feature("docstring") Exceptions::RuntimeErrorException "";

%feature("docstring")  Exceptions::RuntimeErrorException::RuntimeErrorException "Exceptions::RuntimeErrorException::RuntimeErrorException(const std::string &message)
";


// File: classSafePointerVector.xml
%feature("docstring") SafePointerVector "

The objects pointed to must support the  ICloneable interface.

A vector of pointers, owned by *this, with methods to handle them safely.

C++ includes: SafePointerVector.h
";

%feature("docstring")  SafePointerVector::SafePointerVector "SafePointerVector< T >::SafePointerVector()
";

%feature("docstring")  SafePointerVector::SafePointerVector "SafePointerVector< T >::SafePointerVector(const SafePointerVector &other)
";

%feature("docstring")  SafePointerVector::SafePointerVector "SafePointerVector< T >::SafePointerVector(SafePointerVector &&other)
";

%feature("docstring")  SafePointerVector::~SafePointerVector "SafePointerVector< T >::~SafePointerVector()
";

%feature("docstring")  SafePointerVector::size "size_t SafePointerVector< T >::size() const
";

%feature("docstring")  SafePointerVector::empty "bool SafePointerVector< T >::empty() const
";

%feature("docstring")  SafePointerVector::push_back "void SafePointerVector< T >::push_back(T *pointer)
";

%feature("docstring")  SafePointerVector::begin "iterator SafePointerVector< T >::begin()
";

%feature("docstring")  SafePointerVector::begin "const_iterator SafePointerVector< T >::begin() const
";

%feature("docstring")  SafePointerVector::end "iterator SafePointerVector< T >::end()
";

%feature("docstring")  SafePointerVector::end "const_iterator SafePointerVector< T >::end() const
";

%feature("docstring")  SafePointerVector::deleteElement "bool SafePointerVector< T >::deleteElement(T *pointer)
";

%feature("docstring")  SafePointerVector::back "T* SafePointerVector< T >::back()
";

%feature("docstring")  SafePointerVector::back "const T* SafePointerVector< T >::back() const
";

%feature("docstring")  SafePointerVector::clear "void SafePointerVector< T >::clear()
";


// File: classTransform3D.xml
%feature("docstring") Transform3D "

Vector transformations in three dimensions.

C++ includes: Transform3D.h
";

%feature("docstring")  Transform3D::Transform3D "Transform3D::Transform3D()

Constructs unit transformation. 
";

%feature("docstring")  Transform3D::Transform3D "Transform3D::Transform3D(const Eigen::Matrix3d &matrix)

Constructor from matrix (no checks if this is an element of SO(3)!) 
";

%feature("docstring")  Transform3D::~Transform3D "Transform3D::~Transform3D()

Destructor. 
";

%feature("docstring")  Transform3D::clone "Transform3D * Transform3D::clone() const

Clones the transformation. 
";

%feature("docstring")  Transform3D::calculateEulerAngles "void Transform3D::calculateEulerAngles(double *p_alpha, double *p_beta, double *p_gamma) const

Calculates the Euler angles corresponding to the rotation. 
";

%feature("docstring")  Transform3D::calculateRotateXAngle "double Transform3D::calculateRotateXAngle() const

Calculates the rotation angle for a rotation around the x-axis alone Only meaningfull if the actual rotation is around the x-axis 
";

%feature("docstring")  Transform3D::calculateRotateYAngle "double Transform3D::calculateRotateYAngle() const

Calculates the rotation angle for a rotation around the y-axis alone Only meaningfull if the actual rotation is around the y-axis 
";

%feature("docstring")  Transform3D::calculateRotateZAngle "double Transform3D::calculateRotateZAngle() const

Calculates the rotation angle for a rotation around the z-axis alone Only meaningfull if the actual rotation is around the z-axis 
";

%feature("docstring")  Transform3D::getInverse "Transform3D Transform3D::getInverse() const

Returns the inverse transformation. 
";

%feature("docstring")  Transform3D::transformed "template cvector_t Transform3D::transformed< cvector_t >(const ivector_t &v) const

Return transformed vector  v. 
";

%feature("docstring")  Transform3D::transformedInverse "template cvector_t Transform3D::transformedInverse< cvector_t >(const ivector_t &v) const

Return transformed vector  v. 
";

%feature("docstring")  Transform3D::getRotationType "Transform3D::ERotationType Transform3D::getRotationType() const

Retrieve the rotation type (general, around x, y or z-axis) 
";

%feature("docstring")  Transform3D::isIdentity "bool Transform3D::isIdentity() const

Determine if the transformation is trivial (identity) 
";

%feature("docstring")  Transform3D::print "void Transform3D::print(std::ostream &ostr) const
";

%feature("docstring")  Transform3D::isXRotation "bool Transform3D::isXRotation() const
";

%feature("docstring")  Transform3D::isYRotation "bool Transform3D::isYRotation() const
";

%feature("docstring")  Transform3D::isZRotation "bool Transform3D::isZRotation() const
";


// File: classExceptions_1_1UnknownClassRegistrationException.xml
%feature("docstring") Exceptions::UnknownClassRegistrationException "";

%feature("docstring")  Exceptions::UnknownClassRegistrationException::UnknownClassRegistrationException "Exceptions::UnknownClassRegistrationException::UnknownClassRegistrationException(const std::string &message)
";


// File: namespacealgo.xml
%feature("docstring")  algo::almostEqual "bool algo::almostEqual(double a, double b)

Returns true if two doubles agree within machine epsilon. 
";

%feature("docstring")  algo::min_value "double algo::min_value(const Iterator &begin, const Iterator &end, const Evaluator &evaluate)

Returns the minimum value of function evaluate as applied to the elements of an iterator range. 
";

%feature("docstring")  algo::max_value "double algo::max_value(const Iterator &begin, const Iterator &end, const Evaluator &evaluate)

Returns the maximum value of function evaluate as applied to the elements of an iterator range. 
";

%feature("docstring")  algo::concat "std::vector< T > algo::concat(const std::vector< T > &v1, const std::vector< T > &v2)

Returns the concatenation of two std::vectors. 
";


// File: namespaceExceptions.xml
%feature("docstring")  Exceptions::LogExceptionMessage "void Exceptions::LogExceptionMessage(const std::string &)
";


// File: namespaceFileSystemUtils.xml
%feature("docstring")  FileSystemUtils::extension "std::string FileSystemUtils::extension(const std::string &path)

Returns extension of given filename. \"/home/user/filename.int\" -> \".int\", \"/home/user/filename.int.gz\" -> \".gz\" 
";

%feature("docstring")  FileSystemUtils::extensions "std::string FileSystemUtils::extensions(const std::string &path)

Returns extension(s) of given filename. \"/home/user/filename.int\" -> \".int\", \"/home/user/filename.int.gz\" -> \".int.gz\" 
";

%feature("docstring")  FileSystemUtils::createDirectory "bool FileSystemUtils::createDirectory(const std::string &dir_name)

Creates directory in current directory. 
";

%feature("docstring")  FileSystemUtils::createDirectories "bool FileSystemUtils::createDirectories(const std::string &dir_name)

Creates directories in current directory for any element of dir_name which doesn't exist. 
";

%feature("docstring")  FileSystemUtils::filesInDirectory "std::vector< std::string > FileSystemUtils::filesInDirectory(const std::string &dir_name)

Returns filenames of files in directory. 
";

%feature("docstring")  FileSystemUtils::jointPath "std::string FileSystemUtils::jointPath(const std::string &spath1, const std::string &spath2)

Returns joint path name. 
";

%feature("docstring")  FileSystemUtils::filename "std::string FileSystemUtils::filename(const std::string &path)

Returns path without directory part (\"Foo/Bar/Doz.int.gz\" -> \"Doz.int.gz\") 
";

%feature("docstring")  FileSystemUtils::stem "std::string FileSystemUtils::stem(const std::string &path)

Returns filename without extension. \"/home/user/filename.int\" -> \"filename\", \"/home/user/filename.int.gz\" -> \"filename.int\" 
";

%feature("docstring")  FileSystemUtils::stem_ext "std::string FileSystemUtils::stem_ext(const std::string &path)

Returns filename without extension(s). \"/home/user/filename.int\" -> \"filename\", \"/home/user/filename.int.gz\" -> \"filename\" 
";

%feature("docstring")  FileSystemUtils::glob "std::vector< std::string > FileSystemUtils::glob(const std::string &dir, const std::string &pattern)

Returns file names that agree with a regex glob pattern. 
";

%feature("docstring")  FileSystemUtils::convert_utf8_to_utf16 "std::wstring FileSystemUtils::convert_utf8_to_utf16(const std::string &str)

Converts utf8 string represented by std::string to utf16 string represented by std::wstring. 
";

%feature("docstring")  FileSystemUtils::IsFileExists "bool FileSystemUtils::IsFileExists(const std::string &str)

Returns true if file with given name exists on disk. 
";


// File: namespaceMathFunctions.xml
%feature("docstring")  MathFunctions::Bessel_J0_PowSer "complex_t MathFunctions::Bessel_J0_PowSer(const complex_t z)

Computes complex Bessel function J0(z), using power series and asymptotic expansion.

Computes the complex Bessel function J0(z), using power series and asymptotic expansion.

Forked from unoptimized code at http://www.crbond.com/math.htm, who refers to \"Computation of Special Functions\", Zhang and Jin, John Wiley and Sons, 1996. 
";

%feature("docstring")  MathFunctions::Bessel_J1_PowSer "complex_t MathFunctions::Bessel_J1_PowSer(const complex_t z)

Computes complex Bessel function J0(z), using power series and asymptotic expansion.

Computes the complex Bessel function J1(z), using power series and asymptotic expansion.

Forked from same source as for Bessel_J0_PowSer 
";

%feature("docstring")  MathFunctions::StandardNormal "double MathFunctions::StandardNormal(double x)
";

%feature("docstring")  MathFunctions::Gaussian "double MathFunctions::Gaussian(double x, double average, double std_dev)
";

%feature("docstring")  MathFunctions::IntegratedGaussian "double MathFunctions::IntegratedGaussian(double x, double average, double std_dev)
";

%feature("docstring")  MathFunctions::cot "double MathFunctions::cot(double x)

cotangent function:  $cot(x)\\\\equiv1/tan(x)$
";

%feature("docstring")  MathFunctions::Si "double MathFunctions::Si(double x)

Sine integral function:  $Si(x)\\\\equiv\\\\int_0^x du \\\\sin(u)/u$. 
";

%feature("docstring")  MathFunctions::sinc "double MathFunctions::sinc(double x)

sinc function:  $sinc(x)\\\\equiv\\\\sin(x)/x$
";

%feature("docstring")  MathFunctions::sinc "complex_t MathFunctions::sinc(const complex_t z)

Complex sinc function:  $sinc(x)\\\\equiv\\\\sin(x)/x$. 
";

%feature("docstring")  MathFunctions::tanhc "complex_t MathFunctions::tanhc(const complex_t z)

Complex tanhc function:  $tanhc(x)\\\\equiv\\\\tanh(x)/x$. 
";

%feature("docstring")  MathFunctions::Laue "double MathFunctions::Laue(const double x, size_t N)

Real Laue function:  $Laue(x,N)\\\\equiv\\\\sin(Nx)/sin(x)$. 
";

%feature("docstring")  MathFunctions::erf "double MathFunctions::erf(double arg)

Error function of real-valued argument. 
";

%feature("docstring")  MathFunctions::Bessel_J0 "double MathFunctions::Bessel_J0(double x)

Bessel function of the first kind and order 0. 
";

%feature("docstring")  MathFunctions::Bessel_J1 "double MathFunctions::Bessel_J1(double x)

Bessel function of the first kind and order 1. 
";

%feature("docstring")  MathFunctions::Bessel_J1c "double MathFunctions::Bessel_J1c(double x)

Bessel function Bessel_J1(x)/x. 
";

%feature("docstring")  MathFunctions::Bessel_I0 "double MathFunctions::Bessel_I0(double x)

Modified Bessel function of the first kind and order 0. 
";

%feature("docstring")  MathFunctions::Bessel_J0 "complex_t MathFunctions::Bessel_J0(const complex_t z)

Complex Bessel function of the first kind and order 0. 
";

%feature("docstring")  MathFunctions::Bessel_J1 "complex_t MathFunctions::Bessel_J1(const complex_t z)

Complex Bessel function of the first kind and order 1. 
";

%feature("docstring")  MathFunctions::Bessel_J1c "complex_t MathFunctions::Bessel_J1c(const complex_t z)

Complex Bessel function Bessel_J1(x)/x. 
";

%feature("docstring")  MathFunctions::FastFourierTransform "std::vector< complex_t > MathFunctions::FastFourierTransform(const std::vector< complex_t > &data, EFFTDirection tcase)

simple (and unoptimized) wrapper function for the discrete fast Fourier transformation library (fftw3) 
";

%feature("docstring")  MathFunctions::FastFourierTransform "std::vector< complex_t > MathFunctions::FastFourierTransform(const std::vector< double > &data, EFFTDirection tcase)

simple (and unoptimized) wrapper function for the discrete fast Fourier transformation library (fftw3); transforms real to complex 
";

%feature("docstring")  MathFunctions::ConvolveFFT "std::vector< complex_t > MathFunctions::ConvolveFFT(const std::vector< double > &signal, const std::vector< double > &resfunc)

convolution of two real vectors of equal size 
";

%feature("docstring")  MathFunctions::GenerateUniformRandom "double MathFunctions::GenerateUniformRandom()
";

%feature("docstring")  MathFunctions::GenerateStandardNormalRandom "double MathFunctions::GenerateStandardNormalRandom()
";

%feature("docstring")  MathFunctions::GenerateNormalRandom "double MathFunctions::GenerateNormalRandom(double average, double std_dev)
";

%feature("docstring")  MathFunctions::GeneratePoissonRandom "double MathFunctions::GeneratePoissonRandom(double average)
";


// File: namespacePhysConsts.xml


// File: namespacePrecomputed.xml
%feature("docstring")  Precomputed::GenerateArrayHelper "constexpr std::array<double, sizeof...(I)> Precomputed::GenerateArrayHelper(std::index_sequence< I... >)
";

%feature("docstring")  Precomputed::GenerateReciprocalFactorialArray "constexpr std::array<double, N> Precomputed::GenerateReciprocalFactorialArray()
";


// File: namespacePyEmbeddedUtils.xml
%feature("docstring")  PyEmbeddedUtils::toString "std::string PyEmbeddedUtils::toString(PyObject *obj)

Converts PyObject into string, if possible, or throws exception. 
";

%feature("docstring")  PyEmbeddedUtils::toVectorString "std::vector< std::string > PyEmbeddedUtils::toVectorString(PyObject *obj)

Converts PyObject into vector of strings, if possible, or throws exception. 
";

%feature("docstring")  PyEmbeddedUtils::toString "std::string PyEmbeddedUtils::toString(char *c)

Converts char to string. In the case of nullptr will return an empty string. 
";

%feature("docstring")  PyEmbeddedUtils::toString "std::string PyEmbeddedUtils::toString(wchar_t *c)
";

%feature("docstring")  PyEmbeddedUtils::import_bornagain "void PyEmbeddedUtils::import_bornagain(const std::string &path=\"\")

Imports BornAgain from given location. If path is empty, tries to rely on PYTHONPATH. 
";

%feature("docstring")  PyEmbeddedUtils::pythonRuntimeInfo "std::string PyEmbeddedUtils::pythonRuntimeInfo()

Returns multi-line string representing PATH, PYTHONPATH, sys.path and other info. 
";

%feature("docstring")  PyEmbeddedUtils::pythonStackTrace "std::string PyEmbeddedUtils::pythonStackTrace()

Returns string representing python stack trace. 
";


// File: namespacepyfmt.xml
%feature("docstring")  pyfmt::scriptPreamble "std::string pyfmt::scriptPreamble()
";

%feature("docstring")  pyfmt::getSampleFunctionName "std::string pyfmt::getSampleFunctionName()
";

%feature("docstring")  pyfmt::printBool "std::string pyfmt::printBool(double value)
";

%feature("docstring")  pyfmt::printDouble "std::string pyfmt::printDouble(double input)
";

%feature("docstring")  pyfmt::printNm "std::string pyfmt::printNm(double input)
";

%feature("docstring")  pyfmt::printNm2 "std::string pyfmt::printNm2(double input)
";

%feature("docstring")  pyfmt::printScientificDouble "std::string pyfmt::printScientificDouble(double input)
";

%feature("docstring")  pyfmt::printDegrees "std::string pyfmt::printDegrees(double input)
";

%feature("docstring")  pyfmt::printValue "std::string pyfmt::printValue(double value, const std::string &units)
";

%feature("docstring")  pyfmt::printString "std::string pyfmt::printString(const std::string &value)
";

%feature("docstring")  pyfmt::isSquare "bool pyfmt::isSquare(double length1, double length2, double angle)
";

%feature("docstring")  pyfmt::isHexagonal "bool pyfmt::isHexagonal(double length1, double length2, double angle)
";

%feature("docstring")  pyfmt::printKvector "std::string pyfmt::printKvector(const kvector_t value)
";

%feature("docstring")  pyfmt::indent "std::string pyfmt::indent(size_t width)

Returns a string of blanks with given width. By default the width equals standard offset in python files. 
";

%feature("docstring")  pyfmt::printInt "std::string pyfmt::printInt(int value)
";


// File: namespacepyfmt2.xml
%feature("docstring")  pyfmt2::representShape2D "std::string pyfmt2::representShape2D(const std::string &indent, const IShape2D *ishape, bool mask_value, std::function< std::string(double)> printValueFunc)

Returns fixed Python code snippet that defines the function \"runSimulation\". 
";

%feature("docstring")  pyfmt2::valueTimesUnit "std::string pyfmt2::valueTimesUnit(const RealParameter *par)

Returns parameter value, followed by its unit multiplicator (like \"* nm\"). 
";

%feature("docstring")  pyfmt2::argumentList "std::string pyfmt2::argumentList(const IParameterized *ip)

Returns comma-separated list of parameter values, including unit multiplicator (like \"* nm\"). 
";

%feature("docstring")  pyfmt2::printDistribution "std::string pyfmt2::printDistribution(const IDistribution1D &par_distr, const std::string &units)

Prints distribution with constructor parameters in given units. ba.DistributionGaussian(2.0*deg, 0.02*deg) 
";

%feature("docstring")  pyfmt2::printParameterDistribution "std::string pyfmt2::printParameterDistribution(const ParameterDistribution &par_distr, const std::string &distVarName, const std::string &units)
";

%feature("docstring")  pyfmt2::printAxis "std::string pyfmt2::printAxis(const IAxis &axis, const std::string &units, size_t offset)

Prints python-script definition for given axis. offset is used for alignment and indentation in multiple-line definitions 
";


// File: namespaceSysUtils.xml
%feature("docstring")  SysUtils::getCurrentDateAndTime "std::string SysUtils::getCurrentDateAndTime()
";

%feature("docstring")  SysUtils::enableFloatingPointExceptions "void SysUtils::enableFloatingPointExceptions()

Enables exception throw in the case of NaN, Inf.

enables exception throw in the case of NaN, Inf 
";

%feature("docstring")  SysUtils::getenv "std::string SysUtils::getenv(const std::string &name)

Returns environment variable. 
";

%feature("docstring")  SysUtils::isWindowsHost "bool SysUtils::isWindowsHost()

Returns true if operation system is Windows. 
";


// File: namespaceUnits.xml
%feature("docstring")  Units::rad2deg "double Units::rad2deg(double angle)
";

%feature("docstring")  Units::deg2rad "double Units::deg2rad(double angle)
";


// File: MathConstants_8h.xml


// File: PhysicalConstants_8h.xml


// File: Units_8h.xml


// File: CloneableVector_8h.xml


// File: Complex_8h.xml
%feature("docstring")  mul_I "complex_t mul_I(complex_t z)

Returns product I*z, where I is the imaginary unit. 
";

%feature("docstring")  exp_I "complex_t exp_I(complex_t z)

Returns exp(I*z), where I is the imaginary unit. 
";


// File: Exceptions_8cpp.xml


// File: Exceptions_8h.xml


// File: ICloneable_8h.xml


// File: SafePointerVector_8h.xml


// File: Algorithms_8h.xml


// File: Assert_8h.xml


// File: FileSystemUtils_8cpp.xml


// File: FileSystemUtils_8h.xml


// File: Integrator_8cpp.xml


// File: Integrator_8h.xml


// File: IntegratorMCMiser_8h.xml
%feature("docstring")  make_integrator_miser "P_integrator_miser<T> make_integrator_miser(const T *object, miser_integrand< T > mem_function, size_t dim)

Template function to create an integrator object 
";


// File: MathFunctions_8cpp.xml


// File: MathFunctions_8h.xml


// File: Precomputed_8h.xml


// File: PyEmbeddedUtils_8cpp.xml


// File: PyEmbeddedUtils_8h.xml


// File: PyFmt_8cpp.xml


// File: PyFmt_8h.xml


// File: PyFmt2_8cpp.xml


// File: PyFmt2_8h.xml


// File: PyObject_8h.xml


// File: PythonCore_8h.xml


// File: SysUtils_8cpp.xml


// File: SysUtils_8h.xml


// File: BasicVector3D_8cpp.xml
%feature("docstring")  vecOfLambdaAlphaPhi "BasicVector3D<double> vecOfLambdaAlphaPhi(double _lambda, double _alpha, double _phi)

Creates a vector<double> as a wavevector with given wavelength and angles. Specifically needed for grazing-incidence scattering. 
";


// File: BasicVector3D_8h.xml
%feature("docstring")  vecOfLambdaAlphaPhi "BasicVector3D<double> vecOfLambdaAlphaPhi(double _lambda, double _alpha, double _phi)

Creates a vector<double> as a wavevector with given wavelength and angles. Specifically needed for grazing-incidence scattering. 
";


// File: EigenCore_8h.xml


// File: Transform3D_8cpp.xml


// File: Transform3D_8h.xml


// File: Vectors3D_8h.xml


// File: dir_628593db0cdce5a76fb85526ae5aa762.xml


// File: dir_53458346a71374f205070d8bd3d865f1.xml


// File: dir_38a5ec4dd9a60e867dacdb92549a13e0.xml


// File: dir_ddfc3031126aa7182b75ced37b3eee2b.xml


// File: dir_3d1c6f3819a4cd7ba7fe36c1c1e379fe.xml

