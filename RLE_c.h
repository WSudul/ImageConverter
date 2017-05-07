#ifndef RLE_C_H
#define RLE_C_H
#include <vector>
#include <stdint.h>


class RLE_c
{
    public:
        RLE_c();
        virtual ~RLE_c();
        static std::vector<uint8_t> compress_RLE(std::vector<uint8_t>&Vec);
		static std::vector<uint8_t> decompress_RLE(std::vector<uint8_t>&Vec);

    protected:

    private:
};

#endif // RLE_C_H
