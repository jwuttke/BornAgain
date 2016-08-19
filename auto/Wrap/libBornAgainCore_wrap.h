/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.7
 *
 * This file is not intended to be easily readable and contains a number of
 * coding conventions designed to improve portability and efficiency. Do not make
 * changes to this file unless you know what you are doing--modify the SWIG
 * interface file instead.
 * ----------------------------------------------------------------------------- */

#ifndef SWIG_libBornAgainCore_WRAP_H_
#define SWIG_libBornAgainCore_WRAP_H_

#include <map>
#include <string>


class SwigDirector_INamed : public INamed, public Swig::Director {

public:
    SwigDirector_INamed(PyObject *self);
    SwigDirector_INamed(PyObject *self, std::string const &name);
    virtual ~SwigDirector_INamed();

/* Internal director utilities */
public:
    bool swig_get_inner(const char *swig_protected_method_name) const {
      std::map<std::string, bool>::const_iterator iv = swig_inner.find(swig_protected_method_name);
      return (iv != swig_inner.end() ? iv->second : false);
    }
    void swig_set_inner(const char *swig_protected_method_name, bool swig_val) const {
      swig_inner[swig_protected_method_name] = swig_val;
    }
private:
    mutable std::map<std::string, bool> swig_inner;
};


class SwigDirector_IParameterized : public IParameterized, public Swig::Director {

public:
    SwigDirector_IParameterized(PyObject *self, std::string const &name = "");
    SwigDirector_IParameterized(PyObject *self, IParameterized const &other);
    virtual ~SwigDirector_IParameterized();
    virtual std::string addParametersToExternalPool(std::string path, ParameterPool *external_pool, int copy_number = -1) const;
    virtual void onChange();
    virtual void onChangeSwigPublic() {
      IParameterized::onChange();
    }
    virtual void print(std::ostream &ostr) const;
    virtual void printSwigPublic(std::ostream &ostr) const {
      IParameterized::print(ostr);
    }

/* Internal director utilities */
public:
    bool swig_get_inner(const char *swig_protected_method_name) const {
      std::map<std::string, bool>::const_iterator iv = swig_inner.find(swig_protected_method_name);
      return (iv != swig_inner.end() ? iv->second : false);
    }
    void swig_set_inner(const char *swig_protected_method_name, bool swig_val) const {
      swig_inner[swig_protected_method_name] = swig_val;
    }
private:
    mutable std::map<std::string, bool> swig_inner;

#if defined(SWIG_PYTHON_DIRECTOR_VTABLE)
/* VTable implementation */
    PyObject *swig_get_method(size_t method_index, const char *method_name) const {
      PyObject *method = vtable[method_index];
      if (!method) {
        swig::SwigVar_PyObject name = SWIG_Python_str_FromChar(method_name);
        method = PyObject_GetAttr(swig_get_self(), name);
        if (!method) {
          std::string msg = "Method in class IParameterized doesn't exist, undefined ";
          msg += method_name;
          Swig::DirectorMethodException::raise(msg.c_str());
        }
        vtable[method_index] = method;
      }
      return method;
    }
private:
    mutable swig::SwigVar_PyObject vtable[2];
#endif

};


class SwigDirector_ISample : public ISample, public Swig::Director {

public:
    SwigDirector_ISample(PyObject *self);
    virtual ~SwigDirector_ISample();
    virtual ISample *clone() const;
    virtual void transferToCPP();
    virtual std::string addParametersToExternalPool(std::string path, ParameterPool *external_pool, int copy_number = -1) const;
    virtual void onChange();
    virtual void onChangeSwigPublic() {
      IParameterized::onChange();
    }
    virtual void print(std::ostream &ostr) const;
    virtual void printSwigPublic(std::ostream &ostr) const {
      IParameterized::print(ostr);
    }
    virtual ISample *cloneInvertB() const;
    virtual void accept(ISampleVisitor *p_visitor) const;
    virtual std::string to_str(int indent = 0) const;
    virtual IMaterial const *getMaterial() const;
    virtual IMaterial const *getAmbientMaterial() const;
    virtual std::vector< ISample const *,std::allocator< ISample const * > > getChildren() const;
    virtual size_t size() const;

/* Internal director utilities */
public:
    bool swig_get_inner(const char *swig_protected_method_name) const {
      std::map<std::string, bool>::const_iterator iv = swig_inner.find(swig_protected_method_name);
      return (iv != swig_inner.end() ? iv->second : false);
    }
    void swig_set_inner(const char *swig_protected_method_name, bool swig_val) const {
      swig_inner[swig_protected_method_name] = swig_val;
    }
private:
    mutable std::map<std::string, bool> swig_inner;

#if defined(SWIG_PYTHON_DIRECTOR_VTABLE)
/* VTable implementation */
    PyObject *swig_get_method(size_t method_index, const char *method_name) const {
      PyObject *method = vtable[method_index];
      if (!method) {
        swig::SwigVar_PyObject name = SWIG_Python_str_FromChar(method_name);
        method = PyObject_GetAttr(swig_get_self(), name);
        if (!method) {
          std::string msg = "Method in class ISample doesn't exist, undefined ";
          msg += method_name;
          Swig::DirectorMethodException::raise(msg.c_str());
        }
        vtable[method_index] = method;
      }
      return method;
    }
private:
    mutable swig::SwigVar_PyObject vtable[12];
#endif

};


class SwigDirector_IObservable : public IObservable, public Swig::Director {

public:
    SwigDirector_IObservable(PyObject *self);
    virtual ~SwigDirector_IObservable();
    virtual void attachObserver(IObservable::observer_t obj);
    virtual void notifyObservers();

/* Internal director utilities */
public:
    bool swig_get_inner(const char *swig_protected_method_name) const {
      std::map<std::string, bool>::const_iterator iv = swig_inner.find(swig_protected_method_name);
      return (iv != swig_inner.end() ? iv->second : false);
    }
    void swig_set_inner(const char *swig_protected_method_name, bool swig_val) const {
      swig_inner[swig_protected_method_name] = swig_val;
    }
private:
    mutable std::map<std::string, bool> swig_inner;

#if defined(SWIG_PYTHON_DIRECTOR_VTABLE)
/* VTable implementation */
    PyObject *swig_get_method(size_t method_index, const char *method_name) const {
      PyObject *method = vtable[method_index];
      if (!method) {
        swig::SwigVar_PyObject name = SWIG_Python_str_FromChar(method_name);
        method = PyObject_GetAttr(swig_get_self(), name);
        if (!method) {
          std::string msg = "Method in class IObservable doesn't exist, undefined ";
          msg += method_name;
          Swig::DirectorMethodException::raise(msg.c_str());
        }
        vtable[method_index] = method;
      }
      return method;
    }
private:
    mutable swig::SwigVar_PyObject vtable[2];
#endif

};


class SwigDirector_IFitObserver : public IFitObserver, public Swig::Director {

public:
    SwigDirector_IFitObserver(PyObject *self, int update_every_nth);
    virtual ~SwigDirector_IFitObserver();
    virtual void notify(IObservable *subject);
    virtual void update(FitSuite *fit_suite);

/* Internal director utilities */
public:
    bool swig_get_inner(const char *swig_protected_method_name) const {
      std::map<std::string, bool>::const_iterator iv = swig_inner.find(swig_protected_method_name);
      return (iv != swig_inner.end() ? iv->second : false);
    }
    void swig_set_inner(const char *swig_protected_method_name, bool swig_val) const {
      swig_inner[swig_protected_method_name] = swig_val;
    }
private:
    mutable std::map<std::string, bool> swig_inner;

#if defined(SWIG_PYTHON_DIRECTOR_VTABLE)
/* VTable implementation */
    PyObject *swig_get_method(size_t method_index, const char *method_name) const {
      PyObject *method = vtable[method_index];
      if (!method) {
        swig::SwigVar_PyObject name = SWIG_Python_str_FromChar(method_name);
        method = PyObject_GetAttr(swig_get_self(), name);
        if (!method) {
          std::string msg = "Method in class IFitObserver doesn't exist, undefined ";
          msg += method_name;
          Swig::DirectorMethodException::raise(msg.c_str());
        }
        vtable[method_index] = method;
      }
      return method;
    }
private:
    mutable swig::SwigVar_PyObject vtable[2];
#endif

};


class SwigDirector_IMultiLayerBuilder : public IMultiLayerBuilder, public Swig::Director {

public:
    SwigDirector_IMultiLayerBuilder(PyObject *self);
    virtual ~SwigDirector_IMultiLayerBuilder();
    virtual std::string addParametersToExternalPool(std::string path, ParameterPool *external_pool, int copy_number = -1) const;
    virtual void onChange();
    virtual void onChangeSwigPublic() {
      IParameterized::onChange();
    }
    virtual void print(std::ostream &ostr) const;
    virtual void printSwigPublic(std::ostream &ostr) const {
      IParameterized::print(ostr);
    }
    virtual MultiLayer *buildSample() const;

/* Internal director utilities */
public:
    bool swig_get_inner(const char *swig_protected_method_name) const {
      std::map<std::string, bool>::const_iterator iv = swig_inner.find(swig_protected_method_name);
      return (iv != swig_inner.end() ? iv->second : false);
    }
    void swig_set_inner(const char *swig_protected_method_name, bool swig_val) const {
      swig_inner[swig_protected_method_name] = swig_val;
    }
private:
    mutable std::map<std::string, bool> swig_inner;

#if defined(SWIG_PYTHON_DIRECTOR_VTABLE)
/* VTable implementation */
    PyObject *swig_get_method(size_t method_index, const char *method_name) const {
      PyObject *method = vtable[method_index];
      if (!method) {
        swig::SwigVar_PyObject name = SWIG_Python_str_FromChar(method_name);
        method = PyObject_GetAttr(swig_get_self(), name);
        if (!method) {
          std::string msg = "Method in class IMultiLayerBuilder doesn't exist, undefined ";
          msg += method_name;
          Swig::DirectorMethodException::raise(msg.c_str());
        }
        vtable[method_index] = method;
      }
      return method;
    }
private:
    mutable swig::SwigVar_PyObject vtable[3];
#endif

};


class SwigDirector_IFormFactor : public IFormFactor, public Swig::Director {

public:
    SwigDirector_IFormFactor(PyObject *self);
    virtual ~SwigDirector_IFormFactor();
    virtual IFormFactor *clone() const;
    virtual void transferToCPP();
    virtual std::string addParametersToExternalPool(std::string path, ParameterPool *external_pool, int copy_number = -1) const;
    virtual void onChange();
    virtual void onChangeSwigPublic() {
      IParameterized::onChange();
    }
    virtual void print(std::ostream &ostr) const;
    virtual void printSwigPublic(std::ostream &ostr) const {
      IParameterized::print(ostr);
    }
    virtual ISample *cloneInvertB() const;
    virtual void accept(ISampleVisitor *visitor) const;
    virtual std::string to_str(int indent = 0) const;
    virtual IMaterial const *getMaterial() const;
    virtual IMaterial const *getAmbientMaterial() const;
    virtual std::vector< ISample const *,std::allocator< ISample const * > > getChildren() const;
    virtual size_t size() const;
    virtual void setAmbientMaterial(IMaterial const &arg0);
    virtual complex_t evaluate(WavevectorInfo const &wavevectors) const;
    virtual double getVolume() const;
    virtual double getRadialExtension() const;
    virtual void setSpecularInfo(ILayerRTCoefficients const *arg0, ILayerRTCoefficients const *arg1);

/* Internal director utilities */
public:
    bool swig_get_inner(const char *swig_protected_method_name) const {
      std::map<std::string, bool>::const_iterator iv = swig_inner.find(swig_protected_method_name);
      return (iv != swig_inner.end() ? iv->second : false);
    }
    void swig_set_inner(const char *swig_protected_method_name, bool swig_val) const {
      swig_inner[swig_protected_method_name] = swig_val;
    }
private:
    mutable std::map<std::string, bool> swig_inner;

#if defined(SWIG_PYTHON_DIRECTOR_VTABLE)
/* VTable implementation */
    PyObject *swig_get_method(size_t method_index, const char *method_name) const {
      PyObject *method = vtable[method_index];
      if (!method) {
        swig::SwigVar_PyObject name = SWIG_Python_str_FromChar(method_name);
        method = PyObject_GetAttr(swig_get_self(), name);
        if (!method) {
          std::string msg = "Method in class IFormFactor doesn't exist, undefined ";
          msg += method_name;
          Swig::DirectorMethodException::raise(msg.c_str());
        }
        vtable[method_index] = method;
      }
      return method;
    }
private:
    mutable swig::SwigVar_PyObject vtable[17];
#endif

};


class SwigDirector_IFormFactorBorn : public IFormFactorBorn, public Swig::Director {

public:
    SwigDirector_IFormFactorBorn(PyObject *self);
    virtual ~SwigDirector_IFormFactorBorn();
    virtual IFormFactorBorn *clone() const;
    virtual void transferToCPP();
    virtual std::string addParametersToExternalPool(std::string path, ParameterPool *external_pool, int copy_number = -1) const;
    virtual void onChange();
    virtual void onChangeSwigPublic() {
      IParameterized::onChange();
    }
    virtual void print(std::ostream &ostr) const;
    virtual void printSwigPublic(std::ostream &ostr) const {
      IParameterized::print(ostr);
    }
    virtual ISample *cloneInvertB() const;
    virtual void accept(ISampleVisitor *visitor) const;
    virtual std::string to_str(int indent = 0) const;
    virtual IMaterial const *getMaterial() const;
    virtual IMaterial const *getAmbientMaterial() const;
    virtual std::vector< ISample const *,std::allocator< ISample const * > > getChildren() const;
    virtual size_t size() const;
    virtual void setAmbientMaterial(IMaterial const &arg0);
    virtual complex_t evaluate(WavevectorInfo const &wavevectors) const;
    virtual double getVolume() const;
    virtual double getRadialExtension() const;
    virtual void setSpecularInfo(ILayerRTCoefficients const *arg0, ILayerRTCoefficients const *arg1);
    virtual complex_t evaluate_for_q(cvector_t const q) const;
    virtual bool check_initialization() const;
    virtual bool check_initializationSwigPublic() const {
      return IFormFactorBorn::check_initialization();
    }

/* Internal director utilities */
public:
    bool swig_get_inner(const char *swig_protected_method_name) const {
      std::map<std::string, bool>::const_iterator iv = swig_inner.find(swig_protected_method_name);
      return (iv != swig_inner.end() ? iv->second : false);
    }
    void swig_set_inner(const char *swig_protected_method_name, bool swig_val) const {
      swig_inner[swig_protected_method_name] = swig_val;
    }
private:
    mutable std::map<std::string, bool> swig_inner;

#if defined(SWIG_PYTHON_DIRECTOR_VTABLE)
/* VTable implementation */
    PyObject *swig_get_method(size_t method_index, const char *method_name) const {
      PyObject *method = vtable[method_index];
      if (!method) {
        swig::SwigVar_PyObject name = SWIG_Python_str_FromChar(method_name);
        method = PyObject_GetAttr(swig_get_self(), name);
        if (!method) {
          std::string msg = "Method in class IFormFactorBorn doesn't exist, undefined ";
          msg += method_name;
          Swig::DirectorMethodException::raise(msg.c_str());
        }
        vtable[method_index] = method;
      }
      return method;
    }
private:
    mutable swig::SwigVar_PyObject vtable[19];
#endif

};


#endif
