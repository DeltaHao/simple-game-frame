#include "sgfhelper.h"
#include "SDL.h"

/*********************************************************************************
 *									����ת��
 *********************************************************************************/


/**
 * GBK ת UTF8
 * ������
 *		gbk ��Ҫת���� GBK �����ַ���ָ��
 *		gbklen �ַ������ȣ���Ҫ��������ַ� strlen(gbk) + 1)���Ƽ���д -1���Զ����㳤��
 *		utf8 ת���Ľ��ָ��
 *		utf8len ת������Ŀռ��С
 *
 * ���أ�
 *		����ת�����ַ����ĳ��� ��> 0)
 */

int GBKToUTF8(const char* gbk, int gbklen, char* utf8, int utf8len)
{
	if (!(gbk && utf8)) {
		return 0;
	}

	//ת��Ϊ���ַ�
	int bufWLen = MultiByteToWideChar(CP_ACP, 0, gbk, gbklen, NULL, 0);
	if (bufWLen == 0) {
		return -1;
	}

	WCHAR* bufW = malloc(sizeof(WCHAR) * bufWLen);
	if (!bufW) {
		return -2;
	}

	int ret = MultiByteToWideChar(CP_ACP, 0, gbk, gbklen, bufW, bufWLen);
	if (ret == 0) {
		free(bufW);
		return -3;
	}

	//ת��Ϊ UTF8
	int bufMLen = WideCharToMultiByte(CP_UTF8, 0, bufW, -1, NULL, 0, NULL, NULL);
	if (bufMLen == 0) {
		free(bufW);
		return -4;
	}

	CHAR* bufM = malloc(bufMLen);
	if (!bufM) {
		free(bufW);
		return -5;
	}

	ret = WideCharToMultiByte(CP_UTF8, 0, bufW, -1, bufM, bufMLen, NULL, NULL);
	if (ret == 0) {
		free(bufW);
		free(bufM);
		return -6;
	}

	//�ռ䲻��������ȡ...
	if (bufMLen > utf8len) {
		free(bufW);
		free(bufM);
		return -7;
	}

	//����
	memset(utf8, 0, utf8len);
	memcpy(utf8, bufM, bufMLen);

	free(bufW);
	free(bufM);

	return bufMLen;
}


/*********************************************************************************
 *								    ��Դ����
 *********************************************************************************/
 //��ȡ��Դ����
SDL_RWops* getResourceData(HINSTANCE hinst, LPCWSTR lpName, LPCWSTR lpType)
{
	//������Դ
	HRSRC hr = FindResource(hinst, lpName, lpType);
	if (hr == NULL) {
		return NULL;
	}

	//��ȡ��Դ��С
	DWORD size = SizeofResource(hinst, hr);
	if (size == 0) {
		return NULL;
	}

	//������Դ
	HGLOBAL hResData = LoadResource(hinst, hr);
	if (hResData == NULL) {
		return NULL;
	}

	//��ȡ��Դָ��
	LPVOID pData = LockResource(hResData);
	if (pData == NULL) {
		return NULL;
	}

	//��д����ָ��
	SDL_RWops* rwOps = SDL_RWFromConstMem(pData, size);
	if (rwOps == NULL) {
		return NULL;
	}

	return rwOps;
}


/*********************************************************************************
 *									����������
 *********************************************************************************/
int playBackgroudMusic(const TCHAR* filename, int loop)
{
	TCHAR playCommand[513] = { 0 };
	MCIERROR merr = 0;

	if (loop)
	{
		_stprintf_s(playCommand, 512, TEXT("open %s type MPEGVideo"), filename);
		merr = mciSendString(playCommand, NULL, 0, NULL);
		if (merr != 0) {
			return -1;
		}

		_stprintf_s(playCommand, 512, TEXT("play %s repeat"), filename);
		merr = mciSendString(playCommand, NULL, 0, NULL);
		if (merr != 0) {
			mciSendString(TEXT("close all"), NULL, 0, NULL);
			return -2;
		}
	}
	else
	{
		_stprintf_s(playCommand, 512, TEXT("play %s"), filename);
		MCIERROR merr = mciSendString(playCommand, NULL, 0, NULL);
		if (merr != 0) {
			return -3;
		}
	}

	return 0;
}

void closeBackgroudMusic()
{
	mciSendString(TEXT("close all"), NULL, 0, NULL);
}

int playEffect(const TCHAR* filename, int block)
{
	BOOL ret = FALSE;

	if (block)
		ret = PlaySound(filename, NULL, SND_FILENAME);
	else
		ret = PlaySound(filename, NULL, SND_FILENAME | SND_ASYNC);

	return ret ? -1 : 0;
}