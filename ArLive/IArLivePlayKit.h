/*
*  Copyright (c) 2021 The AnyRTC project authors. All Rights Reserved.
*
*  Please visit https://www.anyrtc.io for detail.
*
* The GNU General Public License is a free, copyleft license for
* software and other kinds of works.
*
* The licenses for most software and other practical works are designed
* to take away your freedom to share and change the works.  By contrast,
* the GNU General Public License is intended to guarantee your freedom to
* share and change all versions of a program--to make sure it remains free
* software for all its users.  We, the Free Software Foundation, use the
* GNU General Public License for most of our software; it applies also to
* any other work released this way by its authors.  You can apply it to
* your programs, too.
* See the GNU LICENSE file for more info.
*/
#ifndef __I_AR_LIVE_PLAY_KIT_H__
#define __I_AR_LIVE_PLAY_KIT_H__
#include "ArLiveBase.h"

namespace ar {
namespace live {

struct ArLivePlayConfig
{
	/* Ĭ��ֵ��true��
	true�������Զ������� SDK ����������״����һ����Χ�ڵ�������ʱ�䣻ͨ�� setMaxAutoAdjustCacheTime �� setMinAutoAdjustCacheTime �����ӿ����������á�
	false���ر��Զ������� SDK ��ʹ�ù̶�����ʱ����ͨ�� setCacheTime(float) ���������á�
	*/
	bool bAuto;	//�����Ƿ��Զ���������ʱ�䡣

	/*
	���ò���������ʱ�䣬��λΪ�룬Ĭ��ֵΪ5�롣
	���������ù��󣬻�Ӱ���뿪�Լ�ֱ�������ŵ�ʵʱ�ԡ�
	*/
	int nCacheTime;	//���ò���������ʱ�䡣

	
	/*
	Ĭ��ֵ��1����λΪ�롣
	���������Զ����û���ʱ��ӿ�ʱ����Ч��
	*/
	int nMinCacheTime;	//�������Ļ���ʱ�䡣

	/*
	Ĭ��ֵ��5����λΪ�롣
	���������Զ����û���ʱ��ӿ�ʱ����Ч��
	*/
	int nMaxCacheTime;	//������С�Ļ���ʱ�䡣

	/*
	Ĭ��ֵ��800����λΪ���롣
	����Ⱦ�����������ֵʱ�򣬱��������˿��٣���������ͨ�� IArLivePlayListener#onPlayEvent(int�� Event) �ص� PLAY_WARNING_VIDEO_PLAY_LAG �¼�֪ͨ��
	*/
	int nVideoBlockThreshold;	//���ò�������Ƶ���ٱ�����ֵ��

	/*
	Ĭ��ֵ��3��ȡֵ��Χ��1 - 10��
	�� SDK ��������쳣�Ͽ�����ʱ��SDK �᳢�������������������ͨ���˽ӿ���������������
	*/
	int nConnectRetryCount;		//���ò���������������

	/*
	Ĭ��ֵ��3����λΪ�룻ȡֵ��Χ��3 - 30��
	�� SDK ��������쳣�Ͽ�����ʱ�� SDK �᳢�������������������ͨ���˽ӿ�������������������ʱ������
	*/
	int nConnectRetryInterval;	//���ò��������������

	/*�˲�������Ƶ֡����Ϣ��Ҫ��ͬ�������ʹ�ã��磺ֱ�����ⳡ����
	�ӿ�˵����
	Ĭ��ֵ��false��
	�˽ӿ���Ҫ���� TXLivePusher#sendMessageEx(byte[]) ʹ�á�
	�˽ӿڴ���һ�������ܿ����Լ������Է��ա�
	*/
	bool bEnableMsg;

	/*�˲�������������ʹ��
	Ĭ��ֵΪ��false��
	����ʱ����˷�Ͳ����л��������Ա��뿪����������������������£����鲻������
	*/
	bool bEnableAEC;	//���û���������
};

class IArLivePlayListener
{
public:
	IArLivePlayListener(void) {};
	virtual ~IArLivePlayListener(void) {};

	virtual void onPlayEvent(int nEvent, const ArParams&param) {
		(void)nEvent;
		(void)param;
	};

	virtual void onNetStatus(const ArParams& status) {
		(void)status;
	};
};

class IArVideoRecordListener
{
public:
	IArVideoRecordListener(void) {};
	virtual ~IArVideoRecordListener(void) {};

	virtual void onRecordEvent(int nEvent, const ArParams&param) {
		(void)nEvent;
		(void)param;
	}

	virtual void onRecordProgress(long process) {
		(void)process;
	}

	virtual void onRecordComplete(int nCode, const char*strReason) {
		(void)nCode;
		(void)strReason;
	}
};

class IArSnapshotListener
{
public:
	IArSnapshotListener(void) {};
	virtual ~IArSnapshotListener(void) {};

	virtual void onSnapshot(const char*uid, const char* bmp, int nSize) {
		(void)uid;
		(void)bmp;
		(void)nSize;
	}
};

class IArLivePlayKit
{
public:
	IArLivePlayKit(void) {};
	virtual ~IArLivePlayKit(void) {};

	//### �ں� ��������
	/* ���ò��������
	������
		config	ArLivePlayConfig	�������������μ� ArLivePlayConfig��
	*/
	virtual void setConfig(ArLivePlayConfig &config) = 0;

	/* ���������ص��ӿڡ�
	������
		listener	IArLivePlayListener	�������ص�����μ� IArLivePlayListener��
	*/
	virtual void setPlayListener(IArLivePlayListener* listener) = 0;

	//### ���Ż����ӿ�
	/* ��������ʼ���š�
	������
		playUrl	String	���ŵ�����ַ��
		playType	int	�������͡�	0��ʹ��Rtmp��Դ�ں˲��� 1��ʹ��Player�ں˲���
	���أ�
		�Ƿ�ɹ��������ţ� 0���ɹ���-1��ʧ�ܣ�playUrl Ϊ�գ�-2��ʧ�ܣ�playUrl �Ƿ���-3��ʧ�ܣ�playType �Ƿ���
	*/
	virtual int startPlay(const char* playUrl, int playType) = 0;

	/* ֹͣ���š�
	������
		isNeedClearLastImg	boolean	true�������false���������
	*/
	virtual int stopPlay(bool isNeedClearLastImg) = 0;

	/* �Ƿ����ڲ��š�
	���أ�
		true�����ڲ��ţ�false��δ���š�
	*/
	virtual bool isPlaying() = 0;

	/* ��ͣ���š�
	���ܣ�
		ֹͣ��ȡ�����ݣ��������һ֡���档
	*/
	virtual void pause() = 0;

	/* �ָ����š�
	���ܣ�
		���»�ȡ���ݣ���ȡ��ǰֱ�����ݡ�
	*/
	virtual void resume() = 0;

	/* FLV ���������л���
	������
		playUrl	String	���ŵ�����ַ��
	*/
	virtual int switchStream(const char* playUrl) = 0;

	//### ����¼�ƺͽ�ͼ
	/* ����¼�ƻص��ӿڡ�
	������
		listener	IArVideoRecordListener	�ӿڡ�
	*/
	virtual void setVideoRecordListener(IArVideoRecordListener* listener) = 0;

	/* ������Ƶ¼�ơ�
	������
		recordType	int	Ĭ��0(��֧��¼��ֱ����)
	*/
	virtual int startRecord(int recordType) = 0;

	/* ֹͣ��Ƶ¼�ơ�
	������

	*/
	virtual int stopRecord() = 0;

	/* ���Ź����б��ؽ�ͼ��
	������
		listener	IArSnapshotListener	��ͼ�ص���
	*/
	virtual void snapshot(IArSnapshotListener* listener) = 0;

	//### �Զ������ݴ���
	/* ����������������� Buffer��
	������
		yuvBuffer	char*	-
	���ܣ�
		����ע��㣺

		1���� Buffer ���ڽ������ص������� I420 ��ʽ�� YUV ���ݡ�
		2��Buffer ��С = width * height * 3 / 2��
		3����Ƶ width �� height����ͨ�� IArLivePlayListener#onPlayEvent(int�� ArParams) �� PLAY_EVT_CHANGE_RESOLUTION �¼���ȡ����
	*/
	virtual bool addVideoRawData(char* yuvBuffer) = 0;
};

}
}

#endif	// __I_AR_LIVE_PLAY_KIT_H__
