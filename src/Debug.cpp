/*-------------------------------------------------------------------
 * Purpose:
 *         Lise Debug class cpp
 * Time:
 *         2011年12月8日 22:06:34
 * Author:
 *         张彦升
--------------------------------------------------------------------*/

#include "Debug.h"
#include "Util.h"
#include "Config.h"

#include <fstream>
#include <iostream>

EF_NAMESPACE_BEGIN

//#ifdef lise_DEBUG
//const bool D::b_lock;
//#else
//const bool D::b_lock;
//#endif

static const std::string log_file_name("log.txt");
static const std::string debug_file_name("debug.txt");

std::string log_file_path = LOG_PATH + log_file_name;
std::string debug_file_path = TEMP_PATH + debug_file_name;

//std::fstream D::log_file(log_file_path.c_str(),std::ios_base::app);

extern std::fstream log_stream(log_file_path.c_str(),std::ios_base::app);
extern std::fstream debug_stream(debug_file_path.c_str(),std::ios_base::out);

extern EfDebug d(debug_stream,std::cout);
extern EfDebug l(log_stream);
extern EfDebug e(log_stream,std::cout);
extern EfDebug i(std::cout);

EF_NAMESPACE_END
