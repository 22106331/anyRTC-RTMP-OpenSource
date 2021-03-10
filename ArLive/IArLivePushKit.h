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
#ifndef __I_AR_LIVE_PUSH_Kit_H__
#define __I_AR_LIVE_PUSH_Kit_H__
#include "ArLiveBase.h"

namespace ar {
namespace live {

class IArLivePushEvent
{
public:
	IArLivePushEvent(void) {};
	virtual ~IArLivePushEvent(void) {};

	virtual void onPushEvent(int nEvent, const ArParams&param, uint32_t nElapse) {
		(void)nEvent;
		(void)param;
		(void)nElapse;
	};
	virtual void onNetStatus(const ArParams& status) {
		(void)status;
	};
};



class IArLivePushKit
{
protected:
	IArLivePushKit(void) {};
	virtual ~IArLivePushKit(void) {};

public:
	/* ���������¼��ص�
	������
		pEvent	IArLivePushEvent*	�ص������¼����ն���
	*/
	virtual void setArLivePushEvent(IArLivePushEvent*pEvent) = 0;
	//**************************************************************************\\
	// ��������
	/* ��ʼ����
	������
		strPushUrl	char*	������ַ
	���أ�
		0�����óɹ�		<0: ʧ��
	*/
	virtual int startPush(const char* strPushUrl) = 0;
	/* ֹͣ����
	���أ�
		0�����óɹ�		<0: ʧ��
	*/
	virtual int stopPush() = 0;
	
	/* ��ͣ����ͷ����Ļ�ɼ��������Ƭ����״̬��
	���ܣ�
		��ʱֹͣ����ͷ����Ļ�ɼ�����ʹ�� ArLivePushConfig.pauseImg ��ָ����ͼƬ��Ϊ���ͼ�����������Ҳ������ν�ġ���Ƭ���� 
		����ܳ�����App���е���̨���еĳ������������� iOS ϵͳ�У��� App �е���̨�Ժ󣬲���ϵͳ����������� App ����ʹ������ͷ��
		��ʱ�Ϳ���ͨ������ pausePush() �����Ƭ״̬��
		���ھ�������������������ԣ��������һ��ʱ�䲻����Ƶ���ݣ���������Ͽ���ǰ���������ӡ�
	���أ�
		0�����óɹ�		<0: ʧ��
	*/
	virtual int pausePush() = 0;
	/* �ָ�����ͷ�ɼ���������Ƭ����״̬��
	���أ�
		0�����óɹ�		<0: ʧ��
	*/
	virtual int resumePush() = 0;
	/* ��ѯ�Ƿ�����������
	���أ�
		true������������false��δ������
	*/
	virtual bool isPushing() = 0;
};

}
}

#endif	// __I_AR_LIVE_PUSH_Kit_H__
