#ifndef __LIBERO_H__
#define __LIBERO_H__

#include "HttpServer.h"
#include "HTMLRender.h"
#define Insert(x) Put(#x, x)
namespace libero
{
	using Libero = HttpServer;
}
#endif // !__LIBERO_H__
