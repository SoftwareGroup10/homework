#include <iostream>
using namespace std;
#include "./gdal/gdal_priv.h"
#pragma comment(lib, "gdal_i.lib")

int main()
{

	//����ͼ��
	GDALDataset* poSrcDS1;
	GDALDataset* poSrcDS2;
	//���ͼ��
	GDALDataset* poDstDS;
	//����ͼ��·��
	char* srcPath1 = "superman.jpg";
	char* srcPath2 = "space.jpg";
	//���ͼ��·��
	char* dstPath = "res.tif";
	//ͼ���ڴ�洢
	GByte* buffTmp1R;
	GByte* buffTmp1G;
	GByte* buffTmp1B;
	GByte* buffTmp2R;
	GByte* buffTmp2G;
	GByte* buffTmp2B;
	//ͼ�񲨶���
	int i,j, bandNum;
	//ע������
	GDALAllRegister();
	//��ͼ��
	poSrcDS1 = (GDALDataset*)GDALOpenShared(srcPath1,GA_ReadOnly);
	poSrcDS2 = (GDALDataset*)GDALOpenShared(srcPath2,GA_ReadOnly);
	//��ȡͼ��1��������
	bandNum = poSrcDS1->GetRasterCount();
	//�����ȡ�Ľ��
	cout << "Image X Length: " << "640" << endl;
	cout << "Image Y Length: " << "480" << endl;
	cout << "Band number: " << bandNum << endl;
	//����ͼ��Ŀ�Ⱥ͸߶ȷ����ڴ�
	buffTmp1R = (GByte*)CPLMalloc(640*480*sizeof(GByte));
	buffTmp1G = (GByte*)CPLMalloc(640*480*sizeof(GByte));
	buffTmp1B = (GByte*)CPLMalloc(640*480*sizeof(GByte));
	buffTmp2R = (GByte*)CPLMalloc(640*480*sizeof(GByte));
	buffTmp2G = (GByte*)CPLMalloc(640*480*sizeof(GByte));
	buffTmp2B = (GByte*)CPLMalloc(640*480*sizeof(GByte));
	//�������ͼ��
	poDstDS = (GetGDALDriverManager()->GetDriverByName("GTiff")->Create(dstPath, 640, 480, bandNum, GDT_Byte, NULL));
	
	//buffTmp1�洢����superman.jpg
	//buffTmp2�洢����space.jpg
	poSrcDS1->GetRasterBand(1)->RasterIO(GF_Read,0, 0, 640,480, buffTmp1R, 640,480, GDT_Byte, 0, 0);
	poSrcDS1->GetRasterBand(2)->RasterIO(GF_Read,0, 0, 640,480, buffTmp1G, 640,480, GDT_Byte, 0, 0);
	poSrcDS1->GetRasterBand(3)->RasterIO(GF_Read,0, 0, 640,480, buffTmp1B, 640,480, GDT_Byte, 0, 0);
	poSrcDS2->GetRasterBand(1)->RasterIO(GF_Read,0, 0, 640,480, buffTmp2R, 640,480, GDT_Byte, 0, 0);
	poSrcDS2->GetRasterBand(2)->RasterIO(GF_Read,0, 0, 640,480, buffTmp2G, 640,480, GDT_Byte, 0, 0);
	poSrcDS2->GetRasterBand(3)->RasterIO(GF_Read,0, 0, 640,480, buffTmp2B, 640,480, GDT_Byte, 0, 0);
	for(j=0;j<480;j++)
	{
		for(i=0;i<640;i++)
		{
			int k=j*640+i;
			if((buffTmp1R[k]>10)&&(buffTmp1R[k]<160)&&
				(buffTmp1G[k]>100)&&(buffTmp1G[k]<220)&&
				(buffTmp1B[k]>10)&&(buffTmp1B[k]<110)){
					buffTmp1R[k]=buffTmp2R[k];
					buffTmp1G[k]=buffTmp2G[k];
					buffTmp1B[k]=buffTmp2B[k];
			}
		}
	}
	
	poDstDS->GetRasterBand(1)->RasterIO(GF_Write, 0, 0, 640, 480, buffTmp1R, 640, 480, GDT_Byte, 0,0);
	poDstDS->GetRasterBand(2)->RasterIO(GF_Write, 0, 0, 640, 480, buffTmp1G, 640, 480, GDT_Byte, 0,0);
	poDstDS->GetRasterBand(3)->RasterIO(GF_Write, 0, 0, 640, 480, buffTmp1B, 640, 480, GDT_Byte, 0,0);
	printf("... ... band %d processing ... ...\n", i);
	//����ڴ�
	CPLFree(buffTmp1R);
	CPLFree(buffTmp1G);
	CPLFree(buffTmp1B);
	CPLFree(buffTmp2R);
	CPLFree(buffTmp2G);
	CPLFree(buffTmp2B);
	//�ر�dataset
	GDALClose(poSrcDS1);
	GDALClose(poSrcDS2);
	GDALClose(poDstDS);
	system("PAUSE");
	return 0;
	}
	
	
	



	
	//˼·��superman.jpgͼ���е�����ֵ�ã�r,g,b����ʾ������1��10<r<160; ����2��100<g<220; ����3��10<b<110��ͬʱ��������������������Ϊ�������ء��ѷǱ������أ�� space.jpg �м��ɡ�