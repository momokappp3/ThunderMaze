/*****************************************************************//**
 * \file   TextureAtlas.h
 * \brief  binÉtÉ@ÉCÉãÇÃì«Ç›çûÇ›
 * \author momoka
 * \date   2021 7/12
 *********************************************************************/
#pragma once
#include <tuple>
#include <stdio.h>
#include <stdlib.h>
#include "../libtexpack.h"
#include <string>

class TextureAtlas{
public:
    TextureAtlas();
    virtual ~TextureAtlas();

    static bool Init();

    static LIBTEXPACK_DATA* _texPack;

    static int GetHandle(std::string string);
};