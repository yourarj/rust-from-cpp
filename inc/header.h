#pragma once
#include <memory>
#include <cinttypes>

namespace perf
{
    class Package
    {
    private:
        uint64_t usixtyfour;
        int64_t ssixtyfour;
        uint32_t uthirtytwo;
        int32_t sthirtytwo;
        uint16_t usixteen;
        int16_t ssixteen;
        uint8_t ueight;
        int8_t seight;
        int8_t (*arr_ptr)[2];

    public:
        Package(int8_t (*arr_ptra)[2]) : ueight(8), usixteen(16), uthirtytwo(32), usixtyfour(64), seight(-8), ssixteen(-16), sthirtytwo(-32), ssixtyfour(-64), arr_ptr(arr_ptra)
        {
        }
        void inline mutate_c();
        void printPackage();
    };

    std::shared_ptr<Package> make_package();

}