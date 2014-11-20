#include <nan.h>
#include <fftw3.h>
#include "executor.h"
#include "complex.h"
#include "plan.h"

using namespace v8;

Executor::Executor(
    NanCallback *callback, 
    fftw_complex* in, 
    fftw_complex* out, 
    fftw_plan plan,
    int size) 
: NanAsyncWorker(callback), 
  plan(plan), 
  in(in), 
  out(out), 
  size(size)
{ }

Executor::~Executor() {
}

void Executor::Execute() {
  fftw_execute(this->plan);
}
  
void Executor::HandleOKCallback () {
  NanScope();

  Local<Array> result = NanNew<Array>(this->size);

  for(int i = 0; i< size; i++) {
    result->Set(i, Complex::NewInstance(
          NanNew<Number>(out[i][0]),
          NanNew<Number>(out[i][1])
        )
    );
  }

  Handle<Value> arguments [3] = { Null(), result, Plan::NewInstance(
      this->in, 
      this->out, 
      this->plan,
      this->size) };
  callback->Call(3, arguments);
}
