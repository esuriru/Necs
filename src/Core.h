#pragma once

// TODO - No use of STL
// TODO - Probably use PCH

#ifdef _DEBUG
#   define NECS_ENABLE_ASSERTS
#endif

#ifdef NECS_ENABLE_ASSERTS
#   define NECS_ASSERT(x) if (!(x)) { __debugbreak(); }
#else
#   define NECS_ASSERT(x) do {} while false;
#endif