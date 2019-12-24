#ifndef PLATFORMMACROS_H_
#define PLATFORMMACROS_H_

#define Y_SAFEDELETE(p) \
if(p)\
{ \
    delete p;\
    p=nullptr;\
}

#define Y_CREATESAMPLE(T)\
static T* create()\
{\
   T* _t = new(std::nothrow)T;\
   if (_t&&_t->init())\
   {\
	   return _t;\
   }\
  else\
  {\
       delete _t;\
      _t=nullptr;\
      return nullptr;\
  } \
}

#endif // PLATFORMMACROS_H_
