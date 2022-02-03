#ifndef ROADT_CYRILLIC_SLAVIC
#define ROADT_CYRILLIC_SLAVIC

#include "charset.h"

/* 
 *  Basic Latin characters + Cyrillic characters used in Russian, Ukrainian,
 *  Belorussian, Rusyn, Serbian, Bulgarian and Macedonian languages
*/

class CyrillicSlavicCharset : public Charset
{
  public:
    const word chars[192] =
    {
    // 0x00:
      0x0000, 0x0540, 0x0060, 0x156B, 0xB5CB, 0xBC5B, 0xD345, 0x0040, //  !"#$%&'
      0x0014, 0x4800, 0x5C5C, 0x1448, 0x0800, 0x1008, 0x0100, 0x0810, // ()*+,-./
    // 0x10:  
      0xABB3, 0x0032, 0x93A9, 0x81AB, 0x302A, 0xB18B, 0xB38B, 0x80A2, // 01234567
      0xB3AB, 0xB1AB, 0x0440, 0x0840, 0x1014, 0x1109, 0x4808, 0x84A8, // 89:;<=>?
    // 0x20:
      0xA3B9, 0xB2AA, 0x85EB, 0xA381, 0x85E3, 0xB381, 0xB280, 0xA38B, // @ABCDEFG
      0x322A, 0x85C1, 0x0323, 0x3214, 0x2301, 0x6232, 0x6226, 0xA3A3, // HIJKLMNO
    // 0x30:
      0xB2A8, 0xA3A7, 0xB2AC, 0xB18B, 0x84C0, 0x2323, 0x2A10, 0x2A26, // PQRSTUVW
      0x4814, 0x3428, 0x8991, 0x04C1, 0x4004, 0x8540, 0x0804, 0x0101, // XYZ[\]^_
    // 0x40:
      0x4000, 0x1704, 0x3700, 0x1300, 0x1740, 0x1B00, 0x14C8, 0xB540, // `abcdefg
      0x3600, 0x0480, 0x05C0, 0x0454, 0x0440, 0x160A, 0x1600, 0x1700, // hijklmno
    // 0x50:
      0xB240, 0xB440, 0x1200, 0x0D00, 0x1449, 0x0700, 0x0A00, 0x0A06, // pqrstuvw
      0x4814, 0x4810, 0x1900, 0x14C1, 0x0440, 0x8548, 0x4010, 0xFFFF, // xyz{|}~DEL
    // 0x60:
      0xB381, 0xB381, 0x84CB, 0xA280, 0xB389, 0xB18B, 0x85C1, 0x85C1, // ЀЁЂЃЄЅІЇ
      0x0323, 0xA64B, 0x364B, 0x84CA, 0x3294, 0xAA32, 0x31AB, 0x2323, // ЈЉЊЋЌЍЎЏ
    // 0x70:
      0xB2AA, 0xB38B, 0x85EB, 0xA280, 0x0933, 0xB381, 0x366A, 0x81AB, // АБВГДЕЖЗ
      0x2A32, 0x2AB2, 0x3214, 0x0832, 0x6232, 0x322A, 0xA3A3, 0xA2A2, // ИЙКЛМНОП
    // 0x80:
      0xB2A8, 0xA381, 0x84C0, 0x312B, 0xB4E8, 0x4814, 0x2741, 0x302A, // РСТУФХЦЧ
      0x2763, 0x2763, 0x844B, 0x3722, 0x330B, 0x81AB, 0x36E3, 0xB8AA, // ШЩЪЫЬЭЮЯ
    // 0x90
      0x1704, 0x041B, 0x7700, 0x1401, 0xB540, 0x1B00, 0x4C54, 0x009B, // абвгдежз
      0x0E00, 0x4E00, 0x0454, 0x0C00, 0x160A, 0x3640, 0x1700, 0x1600, // ийклмноп
    // 0xA0
      0xB240, 0x1300, 0x1408, 0x4810, 0x170B, 0x4814, 0x0700, 0x1400, // рстуфхцч
      0x0703, 0x0703, 0x1405, 0x0407, 0x044B, 0x000F, 0x0E0B, 0xBC40, // шщъыьэюя
    // 0xB0
      0x5B00, 0x9B00, 0x3A00, 0x0418, 0x1B00, 0x0D00, 0x0480, 0x8480, // ѐёђѓєѕії
      0x05C0, 0x0C45, 0x3645, 0x3600, 0x04D4, 0x4E00, 0x4890, 0x0700, // јљњћќѝўџ
    };
  
    inline word Char(word index)
    {
      return index < size() ? chars[index] : dummy();
    }

    inline word size() override { return 0xC0; }

    /*
     * remapUTF takes a pointer to char* array
     * and removes all the UTF-8 prefixes for
     * cyrillic characters, fixing even macOS 
     * 'wrong' Ë code (0xC38B)
     */
    String& remap(String& string) override
    { 
      word curLen = 0;
      byte prefix = 0;
    
      for (word i = 0; i < string.length(); i++)
      {
        byte ch = string[i];
    
        if (ch == 0xD0 || ch == 0xD1 || ch == 0xC3)
        {
          prefix = ch;
          continue;
        }

        // fix for macOS uppercase 'double umlaut E' – Ë
        if (prefix == 0xC3 && ch == 0x8B)
        {
          ch = 0x81;
        }
        else if (prefix == 0xD1)
        {
           // there's a weird gap between п (0xD0BF) and р (0xD180)
          ch += 0x40;
        }
         
        prefix = 0;
    
        string[curLen++] = ch;
      }

      string = string.substring(0, curLen);

      return string; 
    }
};

#endif
