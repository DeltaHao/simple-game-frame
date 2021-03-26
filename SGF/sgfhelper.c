#include "sgfhelper.h"
#include "SDL.h"

/*********************************************************************************
 *									编码转换
 *********************************************************************************/


/**
 * GBK 转 UTF8
 * 参数：
 *		gbk 需要转换的 GBK 编码字符串指针
 *		gbklen 字符串长度（需要计算结束字符 strlen(gbk) + 1)，推荐填写 -1，自动计算长度
 *		utf8 转换的结果指针
 *		utf8len 转换结果的空间大小
 *
 * 返回：
 *		返回转换后字符串的长度 （> 0)
 */

int GBKToUTF8(const char* gbk, int gbklen, char* utf8, int utf8len)
{
	if (!(gbk && utf8)) {
		return 0;
	}

	//转换为宽字符
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

	//转换为 UTF8
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

	//空间不够，不截取...
	if (bufMLen > utf8len) {
		free(bufW);
		free(bufM);
		return -7;
	}

	//复制
	memset(utf8, 0, utf8len);
	memcpy(utf8, bufM, bufMLen);

	free(bufW);
	free(bufM);

	return bufMLen;
}


/*********************************************************************************
 *								    资源加载
 *********************************************************************************/
 //获取资源数据
SDL_RWops* getResourceData(HINSTANCE hinst, LPCWSTR lpName, LPCWSTR lpType)
{
	//查找资源
	HRSRC hr = FindResource(hinst, lpName, lpType);
	if (hr == NULL) {
		return NULL;
	}

	//获取资源大小
	DWORD size = SizeofResource(hinst, hr);
	if (size == 0) {
		return NULL;
	}

	//加载资源
	HGLOBAL hResData = LoadResource(hinst, hr);
	if (hResData == NULL) {
		return NULL;
	}

	//获取资源指针
	LPVOID pData = LockResource(hResData);
	if (pData == NULL) {
		return NULL;
	}

	//读写操作指针
	SDL_RWops* rwOps = SDL_RWFromConstMem(pData, size);
	if (rwOps == NULL) {
		return NULL;
	}

	return rwOps;
}


/*********************************************************************************
 *									简单声音播放
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