/*-------------------------------------------------------------------
 * Purpose:
 *         this is the super father object
 * Time:
 *         2011年11月13日 13:35:45
 * Author:
 *         张彦升
--------------------------------------------------------------------*/

#ifndef _BASE_H_2011_11_13_lisency
#define _BASE_H_2011_11_13_lisency

#include "Util.h"

EF_NAMESPACE_BEGIN

/**
 * abstract class,not for initialize
 * 
 **/
class Base
{
public:
protected:
    Base();
    virtual ~Base() = 0;
private:
};

EF_NAMESPACE_END

#endif // _BASE_H_2011_11_13_lisency

