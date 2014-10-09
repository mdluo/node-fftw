#ifndef COMPLEX_H
#define COMPLEX_H

#include <nan.h>
#include <node.h>

class Complex : public node::ObjectWrap {
 public:
  static void Init();
  static v8::Handle<v8::Value> NewInstance(
      v8::Handle<v8::Number> real,
      v8::Handle<v8::Number> imag
  );

  Complex(double real, double imag);
  ~Complex();

 private:
  static NAN_METHOD(New);
  static NAN_METHOD(Real);
  static NAN_METHOD(Imag);

  double real;
  double imag;
};

#endif