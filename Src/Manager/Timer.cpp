#include"../Application.h"
#include"Timer.h"

//シングルトン化
//---------------------------
//instanceの初期化
Timer* Timer::instance_ = nullptr;

Timer::Timer(void)
{
	timerFrameImg_ = 0;
	counter_ = COUNTER_ZERO;
	nowCount_ = 0;
	framePos_ = { 0,0 };
}

Timer::~Timer(void)
{
}

void Timer::Init(void)
{
	//画像読み込み
	timerFrameImg_ = LoadGraph((Application::PATH_IMAGE + "TimerFrame.png").c_str());

	//変数の初期化
	counter_ = COUNTER_ZERO;
	nowCount_ = GetNowCount();
	framePos_ = { Application::SCREEN_SIZE_X / 2, FRAME_SIZE_Y / 2 };
}

void Timer::Update(void)
{
	//時間計測
	if (GetNowCount() - nowCount_ >= SEC_2_MILLISEC)
	{
		nowCount_ = GetNowCount();
		counter_.Sec++;
	}
}

void Timer::Draw(void)
{
	//デバッグ
	DrawRotaGraph(framePos_.x, framePos_.y + 10, 1.0, 0.0, timerFrameImg_, true);

	DrawFormatString(framePos_.x, framePos_.y, IsTimeOver() ? 0x000000 : 0xff0000, "%d", TIME_LIMIT.Sec - counter_.Sec);
}

void Timer::Release(void)
{
}

void Timer::ResetTimer(void)
{
	nowCount_ = GetNowCount();
	counter_ = COUNTER_ZERO;
}

bool Timer::IsTimeOver(void)
{
	return counter_.Sec >= TIME_LIMIT.Sec;
}

void Timer::CreateInstance(void)
{
	//instance_がnullptrの場合は初期化されたのち生成処理を行う
	if (instance_ == nullptr)
	{
		instance_ = new Timer();
	}

	instance_->Init();
}

Timer& Timer::GetInstance(void)
{
	return *instance_;
}

void Timer::Destroy(void)
{
	delete instance_;
	instance_ = nullptr;
}
