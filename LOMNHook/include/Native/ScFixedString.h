#pragma once
#include "_ScBaseString.h"

namespace LOMNHook {
    namespace Native {
        template <int Length>
        class ScFixedString {
        public:
            _ScBaseString Base;
            int MaxLength;
            char Buffer[Length];

            ScFixedString() : Base(), MaxLength(Length) {
                
            }

            ScFixedString(const char* data) : MaxLength(Length) {
                size_t length = strlen(data);
                if (length >= MaxLength) {
                    throw 1; // Too long!
                }
                memcpy(this->Buffer, data, length + 1);
                this->Base.Length = length;
                this->Base.Data = this->Buffer;
            }
        };
    }
}
