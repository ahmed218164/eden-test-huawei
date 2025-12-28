/*
* Copyright (c) Huawei Technologies Co., Ltd. 2021-2021. All rights reserved.
* Description: AIÄóÁ³PC¶Ë½ÇÉ«ÊÊÅä½Ó¿Ú
*/

#ifndef _CHARACTER_INTERFACE_H_
#define _CHARACTER_INTERFACE_H_

#include <vector>
#include <string>

#define EXPORT _declspec(dllexport)

struct CharacterData {
	std::string posPath;
	std::string negPath;
	std::string neutralPath;
	std::string texturePath;
	std::string markIdPath;
	std::string contourIdPath;
};

EXPORT int CharacterAdapter(const CharacterData data, std::string savePath);

#endif
