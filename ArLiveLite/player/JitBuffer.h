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
#ifndef __JIT_BUFFER_H__
#define __JIT_BUFFER_H__
#include <stdint.h>
#include <string>
#include <list>
#include "rtc_base/deprecated/recursive_critical_section.h"

class JitBuffer
{
public:
	JitBuffer(void);
	virtual ~JitBuffer(void);

	void SetPlaySetting(bool bAuto, int nCacheTime, int nMinCacheTime, int nMaxCacheTime, int nVideoBlockThreshold);
	void ResetTime();

	void GetData();
	void DoClear();

	void CacheAudData(const uint8_t* pdata, int len, uint32_t ts, int seqn);
	void CacheVidData(const uint8_t* pdata, int len, uint32_t ts, bool bKeyframe);

	void ClearPcmCache(uint32_t ts);

public:
	enum PlayStatus
	{
		PS_Init = 0,	// ��ʼ��״̬
		PS_Caching,		// ������
		PS_Playing,		// ������
	};

	virtual void OnBufferDecodeVideoData(const uint8_t* pData, int len, bool bKeyframe, uint32_t ts) = 0;
	virtual void OnBufferDecodeAudioData(const uint8_t* pData, int len, int seqn, uint32_t ts) = 0;
	virtual void OnBufferStatusChanged(PlayStatus playStatus) = 0;
	virtual bool OnBufferGetPuased() = 0;

private:
	struct PlaySetting
	{
		bool bAuto;					//�����Ƿ��Զ���������ʱ�䡣
		int nCacheTime;				//���ò���������ʱ�䡣
		int nMinCacheTime;			//������С�Ļ���ʱ�䡣
		int nMaxCacheTime;			//�������Ļ���ʱ�䡣
		int nVideoBlockThreshold;	//���ò�������Ƶ���ٱ�����ֵ��
	};

	PlayStatus	play_status_;			// ��ǰ״̬
	PlaySetting	play_setting_;

	bool		b_reset_time_;
	int32_t		n_cacheing_time_;		// ������ʱ�䣬����������ʱ�䣬����Ҫ��������ж�ȡ
	int32_t     n_cache_to_play_time_;	// ���岥��ʱ�䣬��ʼ�򿨶ٺ󣬱���ﵽ���ʱ��������²���
	int32_t		n_cache_to_play_max_;	// ���Ļ��岥��ʱ��
	uint32_t	last_sys_time_;			// �ϴε��õ�ϵͳʱ��
	uint32_t	n_sys_played_time_;		// �Ѿ����ŵ�ʱ��
	uint32_t	n_played_time_;			// �Ѿ����ŵ�ʱ��
	int64_t		decode_data_time_;		// ��������ݿ�ʼʱ��(DTS)
	int64_t		last_aud_dts_time_;		// ��¼��һ�ν������Ƶʱ���
	int64_t		last_vid_dts_time_;		// ��¼��һ�ν������Ƶʱ���

private:
	typedef struct PlyPacket
	{
		PlyPacket(bool isvideo) :_data(NULL), _data_len(0),
			_b_video(isvideo), _dts(0), _aud_seqn_(0), _b_vid_keyrame_(false), _duration(0){}

		virtual ~PlyPacket(void) {
			if (_data)
				delete[] _data;
		}
		void SetData(const uint8_t* pdata, int len, uint32_t ts) {
			_dts = ts;
			if (len > 0 && pdata != NULL) {
				if (_data)
					delete[] _data;
				if (_b_video)
					_data = new uint8_t[len + 8];
				else
					_data = new uint8_t[len];
				memcpy(_data, pdata, len);
				_data_len = len;
			}
		}
		uint8_t* _data;
		int _data_len;
		bool _b_video;
		uint32_t _dts;
		int _aud_seqn_;
		bool _b_vid_keyrame_;
		int _duration;
	}PlyPacket;

	rtc::RecursiveCriticalSection	cs_audio_recv_;
	std::list<PlyPacket*>	lst_audio_buffer_;
	rtc::RecursiveCriticalSection	cs_video_recv_;
	std::list<PlyPacket*>	lst_video_buffer_;
};

#endif	// __JIT_BUFFER_H__