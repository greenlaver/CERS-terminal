#include "SJIS2UTF8.h"

bool convertSjis2UTF8(uint32_t max_len, char *str_sjis, char *str_utf8)
{
    for (int i = 0; i < max_len; i++)
    {
        switch (str_sjis[i])
        {
        case 0x00:
            *str_utf8 = 0x00;
            return true;
        case 0x20:
            *str_utf8++ = ' ';
            break;
        case 0xA6: // ヲ
            *str_utf8++ = 0xE3;
            *str_utf8++ = 0x83;
            *str_utf8++ = 0xB2;
            break;
        case 0xA7: // ァ
            *str_utf8++ = 0xE3;
            *str_utf8++ = 0x82;
            *str_utf8++ = 0xA1;
            break;
        case 0xA8: // ィ
            *str_utf8++ = 0xE3;
            *str_utf8++ = 0x82;
            *str_utf8++ = 0xA3;
            break;
        case 0xA9: // ゥ
            *str_utf8++ = 0xE3;
            *str_utf8++ = 0x82;
            *str_utf8++ = 0xA5;
            break;
        case 0xAA: // ェ
            *str_utf8++ = 0xE3;
            *str_utf8++ = 0x82;
            *str_utf8++ = 0xA7;
            break;
        case 0xAB: // ォ
            *str_utf8++ = 0xE3;
            *str_utf8++ = 0x82;
            *str_utf8++ = 0xA9;
            break;
        case 0xAC: // ャ
            *str_utf8++ = 0xE3;
            *str_utf8++ = 0x83;
            *str_utf8++ = 0xA3;
            break;
        case 0xAD: // ュ
            *str_utf8++ = 0xE3;
            *str_utf8++ = 0x83;
            *str_utf8++ = 0xA5;
            break;
        case 0xAE: // ョ
            *str_utf8++ = 0xE3;
            *str_utf8++ = 0x83;
            *str_utf8++ = 0xA7;
            break;
        case 0xAF: // ッ
            *str_utf8++ = 0xE3;
            *str_utf8++ = 0x83;
            *str_utf8++ = 0x83;
            break;
        case 0xB0: // -
            *str_utf8++ = 0xE3;
            *str_utf8++ = 0x83;
            *str_utf8++ = 0xBC;
            break;
        case 0xB1: // ア
            *str_utf8++ = 0xE3;
            *str_utf8++ = 0x82;
            *str_utf8++ = 0xA2;
            break;
        case 0xB2: // イ
            *str_utf8++ = 0xE3;
            *str_utf8++ = 0x82;
            *str_utf8++ = 0xA4;
            break;
        case 0xB3: // ウ
            *str_utf8++ = 0xE3;
            *str_utf8++ = 0x82;
            *str_utf8++ = 0xA6;
            break;
        case 0xB4: // エ
            *str_utf8++ = 0xE3;
            *str_utf8++ = 0x82;
            *str_utf8++ = 0xA8;
            break;
        case 0xB5: // オ
            *str_utf8++ = 0xE3;
            *str_utf8++ = 0x82;
            *str_utf8++ = 0xAA;
            break;
        case 0xB6: // カ
            *str_utf8++ = 0xE3;
            *str_utf8++ = 0x82;
            *str_utf8++ = 0xAB;
            break;
        case 0xB7: // キ
            *str_utf8++ = 0xE3;
            *str_utf8++ = 0x82;
            *str_utf8++ = 0xAD;
            break;
        case 0xB8: // ク
            *str_utf8++ = 0xE3;
            *str_utf8++ = 0x82;
            *str_utf8++ = 0xAF;
            break;
        case 0xB9: // ケ
            *str_utf8++ = 0xE3;
            *str_utf8++ = 0x82;
            *str_utf8++ = 0xB1;
            break;
        case 0xBA: // コ
            *str_utf8++ = 0xE3;
            *str_utf8++ = 0x82;
            *str_utf8++ = 0xB3;
            break;
        case 0xBB: // サ
            *str_utf8++ = 0xE3;
            *str_utf8++ = 0x82;
            *str_utf8++ = 0xB5;
            break;
        case 0xBC: // シ
            *str_utf8++ = 0xE3;
            *str_utf8++ = 0x82;
            *str_utf8++ = 0xB7;
            break;
        case 0xBD: // ス
            *str_utf8++ = 0xE3;
            *str_utf8++ = 0x82;
            *str_utf8++ = 0xB9;
            break;
        case 0xBE: // セ
            *str_utf8++ = 0xE3;
            *str_utf8++ = 0x82;
            *str_utf8++ = 0xBB;
            break;
        case 0xBF: // ソ
            *str_utf8++ = 0xE3;
            *str_utf8++ = 0x82;
            *str_utf8++ = 0xBD;
            break;
        case 0xC0: // タ
            *str_utf8++ = 0xE3;
            *str_utf8++ = 0x82;
            *str_utf8++ = 0xBF;
            break;
        case 0xC1: // チ
            *str_utf8++ = 0xE3;
            *str_utf8++ = 0x83;
            *str_utf8++ = 0x81;
            break;
        case 0xC2: // ツ
            *str_utf8++ = 0xE3;
            *str_utf8++ = 0x83;
            *str_utf8++ = 0x84;
            break;
        case 0xC3: // テ
            *str_utf8++ = 0xE3;
            *str_utf8++ = 0x83;
            *str_utf8++ = 0x86;
            break;
        case 0xC4: // ト
            *str_utf8++ = 0xE3;
            *str_utf8++ = 0x83;
            *str_utf8++ = 0x88;
            break;
        case 0xC5: // ナ
            *str_utf8++ = 0xE3;
            *str_utf8++ = 0x83;
            *str_utf8++ = 0x8A;
            break;
        case 0xC6: // ニ
            *str_utf8++ = 0xE3;
            *str_utf8++ = 0x83;
            *str_utf8++ = 0x8B;
            break;
        case 0xC7: // ヌ
            *str_utf8++ = 0xE3;
            *str_utf8++ = 0x83;
            *str_utf8++ = 0x8C;
            break;
        case 0xC8: // ネ
            *str_utf8++ = 0xE3;
            *str_utf8++ = 0x83;
            *str_utf8++ = 0x8D;
            break;
        case 0xC9: // ノ
            *str_utf8++ = 0xE3;
            *str_utf8++ = 0x83;
            *str_utf8++ = 0x8E;
            break;
        case 0xCA: // ハ
            *str_utf8++ = 0xE3;
            *str_utf8++ = 0x83;
            *str_utf8++ = 0x8F;
            break;
        case 0xCB: // ヒ
            *str_utf8++ = 0xE3;
            *str_utf8++ = 0x83;
            *str_utf8++ = 0x92;
            break;
        case 0xCC: // フ
            *str_utf8++ = 0xE3;
            *str_utf8++ = 0x83;
            *str_utf8++ = 0x95;
            break;
        case 0xCD: // ヘ
            *str_utf8++ = 0xE3;
            *str_utf8++ = 0x83;
            *str_utf8++ = 0x98;
            break;
        case 0xCE: // ホ
            *str_utf8++ = 0xE3;
            *str_utf8++ = 0x83;
            *str_utf8++ = 0x9B;
            break;
        case 0xCF: // マ
            *str_utf8++ = 0xE3;
            *str_utf8++ = 0x83;
            *str_utf8++ = 0x9E;
            break;
        case 0xD0: // ミ
            *str_utf8++ = 0xE3;
            *str_utf8++ = 0x83;
            *str_utf8++ = 0x9F;
            break;
        case 0xD1: // ム
            *str_utf8++ = 0xE3;
            *str_utf8++ = 0x83;
            *str_utf8++ = 0xA0;
            break;
        case 0xD2: // メ
            *str_utf8++ = 0xE3;
            *str_utf8++ = 0x83;
            *str_utf8++ = 0xA1;
            break;
        case 0xD3: // モ
            *str_utf8++ = 0xE3;
            *str_utf8++ = 0x83;
            *str_utf8++ = 0xA2;
            break;
        case 0xD4: // ヤ
            *str_utf8++ = 0xE3;
            *str_utf8++ = 0x83;
            *str_utf8++ = 0xA4;
            break;
        case 0xD5: // ユ
            *str_utf8++ = 0xE3;
            *str_utf8++ = 0x83;
            *str_utf8++ = 0xA6;
            break;
        case 0xD6: // ヨ
            *str_utf8++ = 0xE3;
            *str_utf8++ = 0x83;
            *str_utf8++ = 0xA8;
            break;
        case 0xD7: // ラ
            *str_utf8++ = 0xE3;
            *str_utf8++ = 0x83;
            *str_utf8++ = 0xA9;
            break;
        case 0xD8: // リ
            *str_utf8++ = 0xE3;
            *str_utf8++ = 0x83;
            *str_utf8++ = 0xAA;
            break;
        case 0xD9: // ル
            *str_utf8++ = 0xE3;
            *str_utf8++ = 0x83;
            *str_utf8++ = 0xAB;
            break;
        case 0xDA: // レ
            *str_utf8++ = 0xE3;
            *str_utf8++ = 0x83;
            *str_utf8++ = 0xAC;
            break;
        case 0xDB: // ロ
            *str_utf8++ = 0xE3;
            *str_utf8++ = 0x83;
            *str_utf8++ = 0xAD;
            break;
        case 0xDC: // ワ
            *str_utf8++ = 0xE3;
            *str_utf8++ = 0x83;
            *str_utf8++ = 0xAF;
            break;
        case 0xDD: // ン
            *str_utf8++ = 0xE3;
            *str_utf8++ = 0x83;
            *str_utf8++ = 0xB3;
            break;
        case 0xDE: // ゛
            *str_utf8++ = 0xE3;
            *str_utf8++ = 0x82;
            *str_utf8++ = 0x9B;
            break;
        case 0xDF: // ゜
            *str_utf8++ = 0xE3;
            *str_utf8++ = 0x82;
            *str_utf8++ = 0x9C;
            break;
        default:
//            *str_utf8++ = '?';
            *str_utf8++ = str_sjis[i];
            break;
        }
    }

    return false;
}
