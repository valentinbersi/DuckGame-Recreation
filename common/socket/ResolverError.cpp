#include "ResolverError.h"

#include <netdb.h>

ResolverError::ResolverError(const int gai_errno): gai_errno(gai_errno) {}

cppstring ResolverError::what() const noexcept { return gai_strerror(gai_errno); }
