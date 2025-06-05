#pragma once
#define __IDENT_ALIGNMENT_AT__(ident, line) struct SCS_CONCAT(__alignment_at_, line) { char a; int b;}; static constexpr const size_t ident = sizeof(SCS_CONCAT(__alignment_at_, line)) - sizeof(int)
#define IDENT_ALIGNMENT(ident) __IDENT_ALIGNMENT_AT__(ident, __LINE__)
