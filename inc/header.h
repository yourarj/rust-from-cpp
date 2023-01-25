#pragma once
#include <memory>
#include <cinttypes>

namespace perf
{
    class Package
    {
    private:
        uint64_t u_sixty_four;
        int64_t s_sixty_four;
        uint32_t u_thirty_two;
        int32_t s_thirty_two;
        uint16_t u_sixteen;
        int16_t s_sixteen;
        uint8_t u_eight;
        int8_t s_eight;
        int8_t (*arr_ptr)[2];

    public:
        Package(int8_t (*arr_ptr_a)[2]) : u_eight(8), u_sixteen(16), u_thirty_two(32), u_sixty_four(64), s_eight(-8), s_sixteen(-16), s_thirty_two(-32), s_sixty_four(-64), arr_ptr(arr_ptr_a)
        {
        }
        void inline mutate_c();
        void printPackage();

        int8_t *get_a_mutable_pointer() { return arr_ptr[0]; }
    };

    std::unique_ptr<Package>
    new_package();

}