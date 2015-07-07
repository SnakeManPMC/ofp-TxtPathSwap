#pragma once

#include <afxtempl.h>

class CMLODFile
{
public:
	CMLODFile(void);
	~CMLODFile(void);

	int Read(CFile *in);

	unsigned char *data;
	int size;

	int textures;

	CList<unsigned char *, unsigned char *> textureList;
	int Write(CFile * out);
};
