#ifndef __LIBERO_H__
#define __LIBERO_H__

#include "httpserver.h"
#include "htmlrender.h"
#define Insert(x) Put(#x, x)
namespace libero
{
	using Libero = HttpServer;
}
#endif // !__LIBERO_H__
