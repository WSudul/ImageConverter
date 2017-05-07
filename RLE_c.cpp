#include "RLE_c.h"

RLE_c::RLE_c()
{
    //ctor
}

RLE_c::~RLE_c()
{
    //dtor
}

	/* kompresja RLE */
std::vector<uint8_t> RLE_c::compress_RLE(std::vector<uint8_t>&Vec)
{
    uint32_t rozmiar = Vec.size();
	std::vector<uint8_t> temp;
	std::vector<uint8_t> wyjscie;
    uint32_t licznik = 0;

	uint8_t cur, next;
    uint8_t cnt = 1;

    //cur = Vec[licznik];
    //next = Vec[licznik + 1];
    //licznik++;

    while (licznik < rozmiar-1)
	{
        cur=Vec[licznik];
        next=Vec[licznik+1];
		if (next != cur)
		{

				wyjscie.push_back(cnt);
				wyjscie.push_back(cur);

				cnt = 1;

		}
		else
		{
			cnt++;
            if(cnt==255)
            {
                wyjscie.push_back(cnt);
                wyjscie.push_back(cur);
                cnt=1;
            }
		}


        //if (licznik < rozmiar) cur = Vec[licznik];
        //if (licznik < rozmiar - 1)next = Vec[licznik + 1];

		licznik++;

	}


        wyjscie.push_back(cnt);
        wyjscie.push_back(next);


	return wyjscie;
}



	/* dekompresja RLE */
std:: vector<uint8_t> RLE_c::decompress_RLE(std::vector< uint8_t >&Vec)
{
    uint8_t cnt = 0;

    uint32_t rozmiar = Vec.size();
	std::vector<uint8_t> wyjscie;
    uint32_t licznik = 0;

	while (licznik < rozmiar)
	{
		cnt = Vec[licznik];
		licznik++;
		for (int i = 0; i < cnt; i++)
		{
			wyjscie.push_back(Vec[licznik]);
		}
		licznik++;
	}
	return wyjscie;
}

