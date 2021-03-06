
#ifndef SYS_SHARED_H
#define SYS_SHARED_H
#include "Mutex.h"
namespace util
{
class SimpleShared
{
public:

SimpleShared();
SimpleShared(const SimpleShared&);

virtual ~SimpleShared()
{
}

SimpleShared& operator=(const SimpleShared&)
{
return *this;
}

void __incRef()
{
assert(_ref >= 0);
++_ref;
}

void __decRef()
{
assert(_ref > 0);
if(--_ref == 0)
{
if(!_noDelete)
{
_noDelete = true;
delete this;
}
}
}

int __getRef() const
{
return _ref;
}

void __setNoDelete(bool b)
{
_noDelete = b;
}

private:

int _ref;
bool _noDelete;
};

class Shared
{
public:

Shared();
Shared(const Shared&);

virtual ~Shared()
{
}

Shared& operator=(const Shared&)
{
return *this;
}

virtual void __incRef();
virtual void __decRef();
virtual int __getRef() const;
virtual void __setNoDelete(bool);

protected:
int _ref;
bool _noDelete;
Mutex _mutex;
};
}//end namespace
#endif