#include "StdAfx.h"
#include "mlodfile.h"

#pragma pack(1)
typedef struct s_p3d_headerr {
  char signature[4];
  int version;
  int lodcount;
} p3d_header;

typedef struct s_lod_header {
  char signature[4];
  int lod_minor;
  int lod_major;
  int vertices;
  int normals;
  int polygons;
  int flags;
} lod_header;

typedef struct s_poly {
  char texture[32];
  int vertices;
  int vertexdata[16];
  int flags;
} poly_data;

typedef struct s_tag_header {
  char name[64];
  int size;
} tag_header;
#pragma pack(8)

CMLODFile::CMLODFile(void)
{
	data = NULL;
	size = -1;
}

CMLODFile::~CMLODFile(void)
{
	if (data != NULL) delete[] data;
}

int CMLODFile::Read(CFile *in) {
	size = (int)in->SeekToEnd();
	in->SeekToBegin();

	if (size == 0) return 0;

	if (data != NULL) delete[] data;

	data = new unsigned char[size];

	UINT bytes_read = in->Read(data, size);

	CMemFile memf(data, size, 0);

	p3d_header header;
	memf.Read(&header, sizeof(p3d_header));

	textureList.RemoveAll();

	for (int l = 0; l < header.lodcount; l++) {
		lod_header lodheader;

		memf.Read(&lodheader, sizeof(lod_header));
			// skip vertex & normal data
			memf.Seek(lodheader.vertices * 16 + lodheader.normals * 12, CMemFile::current);

			for (int f = 0; f < lodheader.polygons; f++) {
				poly_data poly;

				int pos = (int)memf.GetPosition();

				unsigned char *strpos  = data + pos;

				textureList.AddTail(strpos);

				memf.Read(&poly, sizeof(poly_data));

			}

			// skip "TAGG" marker
			memf.Seek(4, CMemFile::current);

			tag_header tag;
			do {
				memf.Read(&tag, sizeof(tag_header));
				memf.Seek(tag.size, CMemFile::current);
			} while (strncmp(tag.name, "#EndOfFile#", 63) != 0);

			// skip lod resolution
			memf.Seek(4, CMemFile::current);
	}

	memf.Close();

	return size;
}


int CMLODFile::Write(CFile *out)
{
	if (size < 1) return 0;
	if (data == NULL) return 0;

	out->Write(data, size);

	return size;
}
