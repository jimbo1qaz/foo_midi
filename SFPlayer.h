#ifndef __SFPlayer_h__
#define __SFPlayer_h__

#include "main.h"

#include <fluidsynth.h>

#ifndef _AUDIO_CHUNK_H_
typedef float audio_sample;
#endif

class SFPlayer
{
public:
	enum
	{
		loop_mode_enable = 1 << 0,
		loop_mode_force  = 1 << 1,
		loop_mode_xmi    = 1 << 2,
		loop_mode_marker = 1 << 3
	};

	// zero variables
	SFPlayer();

	// close, unload
	~SFPlayer();

	// configuration
	void setSoundFont( const char * in );

	// setup
	void setSampleRate(unsigned rate);

	bool Load(MIDI_file * mf, unsigned loop_mode, unsigned clean_flags);
	unsigned Play(audio_sample * out, unsigned count);
	void Seek(unsigned sample);

private:
	void setInt(const char *name, int val);
	void setNum(const char *name, double num);
	void setStr(const char *name, const char *str);

	void send_event(DWORD b);
	void render(audio_sample * out, unsigned count);

	void shutdown();
	void startup();

	fluid_settings_t * _settings;
	fluid_synth_t    * _synth;
	int                _soundFont;
	pfc::string8       sSoundFontName;

	unsigned           uSamplesRemaining;

	unsigned           uSampleRate;
	unsigned           uLoopMode;

	CSysexMap        * pSysexMap;
	MIDI_EVENT       * pStream;
	UINT               uStreamSize;

	UINT               uStreamPosition;
	DWORD              uTimeCurrent;
	DWORD              uTimeEnd;

	UINT               uStreamLoopStart;
	DWORD              uTimeLoopStart;
};

#endif