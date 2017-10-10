#include <node.h>
#include <node_buffer.h>
#include <v8.h>
#include <stdint.h>
#include <nan.h>

extern "C" {
    #include "phi.h"
}

#define THROW_ERROR_EXCEPTION(x) Nan::ThrowError(x)
#define THROW_ERROR_EXCEPTION_WITH_STATUS_CODE(x, y) Nan::ThrowError(x, y)

using namespace node;
using namespace v8;

Handle<Value> phi(const Nan::FunctionCallbackInfo<v8::Value>& args) {
    Nan::HandleScope scope;    
    if (args.Length() < 1)
        return THROW_ERROR_EXCEPTION("You must provide one argument.");

    Local<Object> target = args[0]->ToObject();

    if(!Buffer::HasInstance(target))
        return THROW_ERROR_EXCEPTION("Argument should be a buffer object.");

    char * input = Buffer::Data(target);
    char output[32];

    phi_hash(input, output);

    Nan::ReturnValue().Set(Nan::NewBuffer(output, 32));
}


void init(Handle<Object> exports) {
    exports->Set(Nan::New<String>("phi"), Nan::New<FunctionTemplate>(phi)->GetFunction());
}

NODE_MODULE(phi, init)
