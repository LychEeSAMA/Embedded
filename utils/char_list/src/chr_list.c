#include <ft2build.h>
#include FT_FREETYPE_H
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>

/* 
    基本汉字（CJK Unified Ideographs）：从U+4E00到U+9FFF，这包含了20902个汉字，覆盖了日常使用的绝大部分汉字。
    扩展A区（CJK Unified Ideographs Extension A）：从U+3400到U+4DBF，这部分包含了6582个不那么常见的汉字，主要是一些古代文献中使用的字。
    扩展B区（CJK Unified Ideographs Extension B）：从U+20000到U+2A6DF，这部分包含了42711个非常罕见的汉字，主要用于古籍和专业领域。
    扩展C区（CJK Unified Ideographs Extension C）：从U+2A700到U+2B73F，这部分有4642个古代文献中出现的汉字。
    扩展D区（CJK Unified Ideographs Extension D）：从U+2B740到U+2B81F，这部分有1165个古代文献中出现的汉字。
    扩展E区（CJK Unified Ideographs Extension E）：从U+2B820到U+2CEAF，这部分有6173个古代文献中出现的汉字。
    扩展F区（CJK Unified Ideographs Extension F）：从U+2CEB0到U+2EBEF，这部分有1339个古代文献中出现的汉字。
    兼容汉字（CJK Compatibility Ideographs）：从U+F900到U+FAFF，这部分包含了为兼容某些旧编码而加入的汉字。 
*/

/* 
Unicode的0-255这一范围实际上对应的是ASCII和Latin-1（ISO 8859-1）标准中的字符。在Unicode中，这个范围被称为"BMP"（Basic Multilingual Plane）的一部分，但是通常我们称之为"C1控制字符"之外的ASCII和Latin-1兼容区域。以下是一些关键点：

ASCII兼容字符 (0-127):
这个范围内的字符是原始ASCII字符集的一部分，包含了英文字母（大写和小写）、数字、标点符号以及一些控制字符（如换行、回车等）。
Latin-1补充字符 (128-255):
这个部分包含了额外的西欧语言字符，比如带重音的字母（é, ñ, ü等），货币符号（€），度量单位（℃），以及其他常见的符号和标点。
下面是一些具体的例子：
ASCII字符 (0-127):

'A' 到 'Z' 对应 65 到 90
'a' 到 'z' 对应 97 到 122
'0' 到 '9' 对应 48 到 57
空格对应 32
换行符 \n 对应 10
回车符 \r 对应 13
Latin-1补充字符 (128-255):

Á 对应 193
É 对应 201
Í 对应 205
Ó 对应 211
Ú 对应 218
á 对应 225
é 对应 233
í 对应 237
ó 对应 243
ú 对应 250
ñ 对应 241
Ñ 对应 209
ü 对应 252
Ü 对应 220 
*/

char *unicode_to_wchar(unsigned int unicode)
{
    wchar_t wide_char = (wchar_t)unicode;
    static char wchar[4] = {0};
    memset(wchar, '\0', sizeof(wchar));

    /* 将宽字符转换为多字节字符 */
    int bytes_converted = wcstombs(wchar, &wide_char, 4);
    if (bytes_converted <= 0) {
        fprintf(stderr, "failed\n");
        return NULL;
    }    
    return wchar;
}

void get_all_exist_char_from_ttf(const char *font_path, const char *output_path)
{
    FT_Library library;
    FT_Face face;
    FT_UInt glyph_index;
    FILE *output_file;
    FT_Error error;
    int unicode;
    int index = 0;

    setlocale(LC_ALL, "");

    /* 初始化FreeType库 */
    if (FT_Init_FreeType(&library))
    {
        fprintf(stderr, "Failed to initialize FreeType library\n");
        return;
    }

    /* 打开输出文件 */
    output_file = fopen(output_path, "w");
    if (!output_file)
    {
        fprintf(stderr, "Failed to open output file\n");
        FT_Done_FreeType(library);
        return;
    }

    /* 加载字体文件 */
    if (FT_New_Face(library, font_path, 0, &face))
    {
        fprintf(stderr, "Failed to load font\n");
        fclose(output_file);
        FT_Done_FreeType(library);
        return;
    }

    /* 设置字体大小 */
    FT_Set_Pixel_Sizes(face, 0, 32); 

    fwprintf(output_file, L"中文字符:\n");
    /* 常用汉字unicode */
    for (unicode = 0x4E00, index = 1; unicode <= 0x9FFF; unicode++)
    {
        glyph_index = FT_Get_Char_Index(face, unicode);
        if (glyph_index != 0 && !FT_Load_Glyph(face, glyph_index, FT_LOAD_DEFAULT))
        {
            wchar_t wcahr_tmp = (wchar_t)unicode;
            // wprintf(L"%lc ", wcahr_tmp);
            fwprintf(output_file, L"%lc ", (wchar_t)wcahr_tmp);
        
            if (0 == (index % 50))
            {
                fwprintf(output_file, L"\n");
                // wprintf(L"\n");
            }
            index++;
        }        
    }

    fwprintf(output_file, L"\n\n");
    fwprintf(output_file, L"非中文字符:\n");

    for (unicode = 0x00, index = 1; unicode <= 0xFFFF; unicode++)
    {
        /* 跳过中文字符 */
        if (0x4E00 <= unicode && 0x9FFF >= unicode)
            continue;

        glyph_index = FT_Get_Char_Index(face, unicode);
        if (glyph_index != 0 && !FT_Load_Glyph(face, glyph_index, FT_LOAD_DEFAULT))
        {
            /* unicode 0-127 */
            if (0x7F >= unicode)
            {
                // printf("%d:%c\n", unicode, unicode);
                fprintf(output_file, "%c\n", unicode);
                if (0 == (index % 50))
                {
                    fprintf(output_file, "\n");
                    // printf("\n");
                }
            }
            else /* 处理宽体字符 */
            {
                wchar_t wcahr_tmp = (wchar_t)unicode;
                // wprintf(L"%lc ", wcahr_tmp);
                fwprintf(output_file, L"%lc ", (wchar_t)wcahr_tmp);

                if (0 == (index % 50))
                {
                    fwprintf(output_file, L"\n");
                    // wprintf(L"\n");
                }
            }
            index++;
        }        
    }

    fclose(output_file);
    FT_Done_Face(face);
    FT_Done_FreeType(library);
    
    printf("Generate char_list.txt in the end!\n");
}


int main(int argc, char const *argv[])
{
    if (2 == argc)
    {
        if (!strcmp("-h", argv[1]))
        {
            printf("eg:./chr_list /home/twei/code/Linux/font/ALIBABA_PUHUITI_R_0.ttf\n");
            printf("Notice: Absolute path must be used\n");
            return 0;
        }
        get_all_exist_char_from_ttf(argv[1], "char_list.txt");
    }
    else 
    {
        printf("chr_list:bad param!\n");
        printf("eg:./chr_list /home/twei/code/Linux/font/ALIBABA_PUHUITI_R_0.ttf\n");
        printf("Notice: Absolute path must be used\n");
        return -1;
    }

    return 0;
}
