/*-------------------------------------------------------------------
* Purpose:
*         system library
* Time:
*         2012年3月2日 12:24:11
* Author:
*         张彦升
--------------------------------------------------------------------*/

#ifndef _SYSLIB_H_2012_3_2_lisency
#define _SYSLIB_H_2012_3_2_lisency

#include "Util.h"
#include "object.h"

#include <iostream>
#include <string>

EF_NAMESPACE_BEGIN

static CoutObject* cout_handler = new CoutObject();

/**
 * 这是一个C函数，根据关键字，查看该关键字是否是系统保留关键字
 */
inline Object* reserver(std::string name)
{
    if (name == "cout")
    {
        return cout_handler;
    }
    else
    {
        return NULL;
    }
}

EF_NAMESPACE_END

#endif // _SYSLIB_H_2012_3_2_lisency

